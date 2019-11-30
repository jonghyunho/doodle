#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include <Windows.h>

using namespace std;

template <class T>
class TEvent {
 public:
  class Handler {
   public:
    Handler() { TEvent<T>::Register(this); }
    virtual ~Handler() { TEvent<T>::Unregister(this); }
    virtual int HandleEvent(const T& t) = 0;
  };
  typedef std::list<Handler*> HandlerList;

  class MessageQueue {
   public:
    MessageQueue() {}

    virtual ~MessageQueue() {}

    void Clear() {
      std::unique_lock<std::mutex> guard(mutex_);
      std::queue<std::shared_ptr<T>> empty_queue;
      std::swap(queue_, empty_queue);
    }

    void Enqueue(std::shared_ptr<T> t) {
      std::unique_lock<std::mutex> guard(mutex_);
      queue_.push(t);
    }

    std::shared_ptr<T> Dequeue() {
      std::unique_lock<std::mutex> guard(mutex_);
      std::shared_ptr<T> t = queue_.front();
      queue_.pop();
      return t;
    }

    bool IsEmpty() {
      std::unique_lock<std::mutex> guard(mutex_);
      return queue_.empty();
    }

   private:
    std::queue<std::shared_ptr<T>> queue_;
    std::mutex mutex_;
  };

  struct Container {
    HandlerList registry;
    MessageQueue message_queue;

    std::thread thread;
    std::mutex registry_mutex;
    std::mutex queue_mutex;
    std::condition_variable cv;

    int ref_count = 0;
    bool is_thread_running = false;
  };

 public:
  TEvent() {
    if (c_.ref_count == 0) {
      StartThread();
    }
    c_.ref_count++;
    cout << "TEvent(" << typeid(T).name() << ") : " << c_.ref_count << endl;
  }
  
  virtual ~TEvent() {
    c_.ref_count--;
    cout << "~TEvent(" << typeid(T).name() <<  ") : " << c_.ref_count << endl;
    
    if (c_.ref_count == 0) {
      {
        std::unique_lock<std::mutex> guard(c_.queue_mutex);
        c_.message_queue.Clear();
      }
      
      StopThread();
    }
  }

  void Enqueue(std::shared_ptr<T> t) {
    c_.message_queue.Enqueue(t);
    c_.cv.notify_all();
  }

 private:
  static void Register(Handler* handler) {
    cout << "Register" << endl;
    std::unique_lock<std::mutex> guard(c_.registry_mutex);
    c_.registry.push_back(handler);
  }

  static void Unregister(Handler* handler) {
    cout << "Unregister" << endl;
    typename std::list<Handler*>::iterator it;

    std::unique_lock<std::mutex> guard(c_.registry_mutex);
    for (it = c_.registry.begin(); it != c_.registry.end(); it++) {
      if (*it == handler) {
        c_.registry.remove(handler);
        break;
      }
    }
  }

  static void Notify(std::shared_ptr<T> t) {
    {
      std::unique_lock<std::mutex> guard(c_.queue_mutex);
      if (!c_.is_thread_running) {
        return;
      }
    }

    typename std::list<Handler*>::iterator it;
    for (it = c_.registry.begin(); it != c_.registry.end(); it++) {

      (*it)->HandleEvent(*t.get());
    }
  }

 private:
  void StartThread() {
    {
      std::unique_lock<std::mutex> guard(c_.queue_mutex);
      c_.is_thread_running = true;
    }    
    c_.thread = std::thread(&TEvent::Run, this);
  }

  void StopThread() {
    {
      std::unique_lock<std::mutex> guard(c_.queue_mutex);
      c_.is_thread_running = false;
    }
    c_.cv.notify_all();

    if (c_.thread.joinable()) {
      c_.thread.join();
    }
  }

  void Run() {
    while (c_.is_thread_running) {     
      while (!c_.message_queue.IsEmpty()) {
        std::shared_ptr<T> t = c_.message_queue.Dequeue();
        T::Notify(t);
      }

      {
        std::unique_lock<std::mutex> guard(c_.queue_mutex);
        c_.cv.wait(guard);
      }
    }

    cout << "exit thread" << endl;
  }

  //bool IsRunning() {
  //  std::unique_lock<std::mutex> guard(c_.queue_mutex);
  //  return c_.is_thread_running;
  //}

 private:
  static Container c_;
};

class CoinInsertedEvent : public TEvent<CoinInsertedEvent> {};
class CoinReleaseEvent : public TEvent<CoinReleaseEvent> {};
class ProductDispensedEvent : public TEvent<ProductDispensedEvent> {};

TEvent<CoinInsertedEvent>::Container TEvent<CoinInsertedEvent>::c_;
TEvent<CoinReleaseEvent>::Container TEvent<CoinReleaseEvent>::c_;
TEvent<ProductDispensedEvent>::Container TEvent<ProductDispensedEvent>::c_;

typedef std::shared_ptr<CoinInsertedEvent> CoinInsertedEventPtr;
typedef std::shared_ptr<CoinReleaseEvent> CoinReleaseEventPtr;
typedef std::shared_ptr<ProductDispensedEvent> ProductDispensedEventPtr;

class CoinChanger : public CoinReleaseEvent::Handler,
                    public ProductDispensedEvent::Handler {
 public:
  CoinChanger(string name) : name_(name) {
    cout << "CoinChanger constructor" << endl;
  }

  virtual ~CoinChanger() {
    cout << "CoinChanger destructor" << endl;
  }

 public:
  int HandleEvent(const ProductDispensedEvent& event) {
    cout << name_ << " : Product dispensed." << endl;
    return 0;
  }

  int HandleEvent(const CoinReleaseEvent& event) {
    cout << name_ << " : Coin released." << endl;
    return 0;
  }

 private:
  string name_;
};

class EventQueue {
 public:
  EventQueue() {}
  virtual ~EventQueue() {}

  void Register() {
    list_.push_back(this);
  }

  void CleanUp() {
    std::list<EventQueue *>::iterator it;
    for (; it != list_.end(); it++) {
      (*it)->
    }
    list_.push_back(this);
  }

  private:
    static std::list<EventQueue *> list_;
};

std::list<EventQueue *> EventQueue::list_;

class CoinReleaseEventQueue : public EventQueue {
 public:
  void Enqueue(CoinReleaseEventPtr event) {
    event->Enqueue(event);
    Register();
  }
};

int main() {
  CoinChanger coin_changer("coin changer 1");

  //{
    CoinReleaseEventPtr coinReleaseEvent(new CoinReleaseEvent());
    //ProductDispensedEventPtr productDispensedEvent(new ProductDispensedEvent());
    CoinReleaseEventQueue queue;
    queue.Enqueue(coinReleaseEvent);
    //MessageCore::QueueMessage(productDispensedEvent);
  //}

  cout << endl;

  //Sleep(1000);

  return 0;
}