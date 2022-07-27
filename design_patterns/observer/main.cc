#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

typedef std::string EventType;
class EventListener;

class EventManager {
 private:
  std::unordered_map<EventType, std::unordered_set<EventListener> > listeners;

 public:
  void subscribe(EventType eventType, const EventListener& listener) {}
  void unsubscribe(EventType EventType, const EventListener& listener) {}
  void notify(EventType eventType, std::string data) {
    for (auto listener : listeners.at(eventType)) {
      listener.update(data);
    }
  }
};

class EventListener {
 public:
  virtual void update(std::string filename) = 0;
};

class Editor {
 public:
  void openFile(std::string path) { this->file.open("path"); }

 public:
  EventManager evets;

 private:
  std::fstream file;
};

class LoggingListener : public EventListener {
 private:
  std::fstream log_;
  std::string message_;

 public:
  LoggingListener(std::string log_filename, std::string message)
      : message_(message) {
    this->log_.open(log_filename);
  }
  void update(std::string filename) {
    // update
    std::cout << filename << std::endl;
  }
};

class EmailAlertsListener : public EventListener {
 private:
  std::string email_;
  std::string message_;

 public:
  EmailAlertsListener(std::string email, std::string message)
      : message_(message), email_(email) {}

  void update(std::string filename) {
    // ...
    std::cout << filename << std::endl;
  }
};

class Application {
 public:
  void config() {
    Editor editor;
    LoggingListener logger("/tmp/observer_logger",
                           "some one open the log file");
    EmailAlertsListener emailAlert("/tmp/emailAlert", "hello");

    editor.evets.subscribe("open", logger);
  }
};

int main() {
  Application app;
  app.config();

  return 0;
}
