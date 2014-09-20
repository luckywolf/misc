/*
version 1
https://www.zybuluo.com/smilence/note/540
*/

template <typename T>
class BlockingQueue{
    private:
        queue<T> _queue;
        mutex _mutex;
        condition_variable _cond;
    public:
        void push( const T& item){
            unique_lock<mutex> locker(_mutex);
            _queue.push(item);
            locker.unlock();
            _cond.notify_one(); 
        }
        T pop(){
            unique_lock<mutex> locker(_mutex);
            _cond.wait(locker, [=](){ return !_queue.empty() ;} );  //lambda function, capture by value
            T item = _queue.front();
            _queue.pop();
            return item; 
        }
};

/*
version 2
http://juanchopanzacpp.wordpress.com/2013/02/26/concurrent-queue-c11/
*/

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
 
template <typename T>
class Queue
{
 public:
 
  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
  }
 
  void pop(T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
  }
 
  void push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }
 
  void push(T&& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }
 
 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};