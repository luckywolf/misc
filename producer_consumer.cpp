/*
Producer

lock(lock_bp)
while (free_bp.is_empty())
    cond_wait(cond_freebp_empty, lock_bp)
buffer ? free_bp.get_buffer()
unlock(lock_bp)

... produce data in buffer ...

lock(lock_bp)
data_bp.add_buffer(buffer)
cond_signal(cond_databp_empty)
unlock(lock_bp)

------------------------------------

Consumer

lock(lock_bp)
while (data_bp.is_empty())
    cond_wait(cond_databp_empty, lock_bp)
buffer ? data_bp.get_buffer()
unlock(lock_bp)

... consume data in buffer ...

lock(lock_bp)
free_bp.add_buffer(buffer)
cond_signal(cond_freebp_empty)
unlock(lock_bp)


*/


using namespace std;

#define MAX_COUNT 10
mutex mu;
condition_variable cond;
condition_variable cond_prod;
int count = 0;



void producer() {

   while (true) {
       unique_lock<mutex> locker(mu);
       cond_prod.wait(locker, []() {return count <  MAX_COUNT});
        // read buffer
       // generate a job
       ++count;
       cond.notify_all();
       locker.unlock(); // unlock is after notify_all
          
   }
}

void consumer() {
    while(true) {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, []() {return count != 0});
        // read buffer
        --count;
        cond_prod.notify_all();
        locker.unlock(); // unlock is after notify_all
       
     }
}

/* 
http://baptiste-wicht.com/posts/2012/04/c11-concurrency-tutorial-advanced-locking-and-condition-variables.html
*/

struct BoundedBuffer {
    int* buffer;
    int capacity;

    int front;
    int rear;
    int count;

    std::mutex lock;

    std::condition_variable not_full;
    std::condition_variable not_empty;

    BoundedBuffer(int capacity) : capacity(capacity), front(0), rear(0), count(0) {
        buffer = new int[capacity];
    }

    ~BoundedBuffer(){
        delete[] buffer;
    }

    void deposit(int data){
        std::unique_lock<std::mutex> l(lock);

        not_full.wait(l, [this](){return count != capacity; });

        buffer[rear] = data;
        rear = (rear + 1) % capacity;
        ++count;

        not_empty.notify_one();
    }

    int fetch(){
        std::unique_lock<std::mutex> l(lock);

        not_empty.wait(l, [this](){return count != 0; });

        int result = buffer[front];
        front = (front + 1) % capacity;
        --count;

        not_full.notify_one();

        return result;
    }
};

void consumer(int id, BoundedBuffer& buffer){
    for(int i = 0; i < 50; ++i){
        int value = buffer.fetch();
        std::cout << "Consumer " << id << " fetched " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void producer(int id, BoundedBuffer& buffer){
    for(int i = 0; i < 75; ++i){
        buffer.deposit(i);
        std::cout << "Produced " << id << " produced " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(){
    BoundedBuffer buffer(200);

    std::thread c1(consumer, 0, std::ref(buffer));
    std::thread c2(consumer, 1, std::ref(buffer));
    std::thread c3(consumer, 2, std::ref(buffer));
    std::thread p1(producer, 0, std::ref(buffer));
    std::thread p2(producer, 1, std::ref(buffer));

    c1.join();
    c2.join();
    c3.join();
    p1.join();
    p2.join();

    return 0;
}