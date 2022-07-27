#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class Singleton {
 private:
  static Singleton *pinstance_;
  static std::mutex mutex_;

 protected:
  /**
   * @brief The only constructor called by GetInstance
   */
  Singleton(const std::string value) : value_(value) {}
  ~Singleton() {}
  std::string value_;

 public:
  /**
   * Singletons should not be cloneable;
   */
  Singleton(const Singleton &other) = delete;
  /**
   * Singletons should not be assignable;
   */
  void operator=(const Singleton &) = delete;
  /**
   * This is the static method that controls the access to the singleton
   * instance. On the first run, it creates a singleton object and places it
   * into the static field. On subsequent runs, it returns the client existing
   * object stored in the static field.
   */
  static Singleton *GetInstance(const std::string &value);

  void SomeBusinessLogic() {  //...
  }

  std::string value() const { return value_; }
};

/**
 * @brief Static methods should be defined outside the class.
 *
 */
Singleton *Singleton::pinstance_{nullptr};
std::mutex Singleton::mutex_;

/**
 * @brief The only way to construct the object
 * The first time we call GetInstance we will lock the storage location and then
 * we make sure again that the variable is null and then we set the value. RU:
 *
 */
Singleton *Singleton::GetInstance(const std::string &value) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new Singleton(value);
  }
  return pinstance_;
}

void ThreadFoo() {
  // Following code emulates slow initialization.
  std::this_thread::sleep_for(std::chrono::microseconds(1000));
  Singleton *singleton = Singleton::GetInstance("FOO");
  std::cout << singleton->value() << "\n";
}

void ThreadBar() {
  // Following code emulates slow initialization.
  std::this_thread::sleep_for(std::chrono::microseconds(1000));
  Singleton *singleton = Singleton::GetInstance("BAR");
  std::cout << singleton->value() << std::endl;
}

int main() {
  std::cout << "If you see the same value, then singleton was resued"
            << std::endl;
  std::thread t1(ThreadFoo);
  std::thread t2(ThreadBar);

  t1.join();
  t2.join();

  return 0;
}