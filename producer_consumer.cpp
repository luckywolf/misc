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
       locker.unlock();
          
   }
}

void consumer() {
    while(true) {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, []() {return count != 0});
        // read buffer
        --count;
        cond_prod.notify_all();
        locker.unlock();
       
     }
}