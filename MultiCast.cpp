#include <algorithm>
#include <iostream>
#include <list>
#include <string>

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

  static void Register(Handler* handler) { registry_.push_back(handler); }

  static void Unregister(Handler* handler) {
    typename std::list<Handler*>::iterator it;

    for (it = registry_.begin(); it != registry_.end(); it++) {
      if (*it == handler) {
        registry_.remove(handler);
        return;
      }
    }
  }

  static void Notify(TEvent<T>* t) {
    typename std::list<Handler*>::iterator it;

    for (it = registry_.begin(); it != registry_.end(); it++) {
      (*it)->HandleEvent(*(T*)t);
    }
  }

  void Notify() { T::Notify(this); }

 private:
  static HandlerList registry_;
};

class CoinInsertedEvent : public TEvent<CoinInsertedEvent> {};
class CoinReleaseEvent : public TEvent<CoinReleaseEvent> {};
class ProductDispensedEvent : public TEvent<ProductDispensedEvent> {};

class CoinChanger : public CoinReleaseEvent::Handler,
                    public ProductDispensedEvent::Handler {
 public:
  CoinChanger(string name) : name_(name) {}

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

TEvent<CoinInsertedEvent>::HandlerList TEvent<CoinInsertedEvent>::registry_;
TEvent<CoinReleaseEvent>::HandlerList TEvent<CoinReleaseEvent>::registry_;
TEvent<ProductDispensedEvent>::HandlerList
    TEvent<ProductDispensedEvent>::registry_;

int main() {
  CoinChanger coinChanger("coin changer 1");
  CoinReleaseEvent coinReleaseEvent;
  ProductDispensedEvent productDispensedEvent;

  coinReleaseEvent.Notify();
  productDispensedEvent.Notify();

  cout << endl;

  CoinChanger coinChanger2("coin changer 2");

  CoinReleaseEvent coinReleaseEvent2;
  coinReleaseEvent2.Notify();

  return 0;
}