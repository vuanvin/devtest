#include <iostream>
#include <mutex>
#include <set>
#include <string>
#include <thread>

class Account {
 public:
  Account(std::string name, double money) : name_(name), money_(money) {}

 public:
  void changeMoney(double amount) { money_ += amount; }

  std::string getName() { return name_; }
  double getMoney() { return money_; }
  std::mutex* getLock() { return &money_lock_; }

 private:
  std::string name_;
  double money_;
  std::mutex money_lock_;
};

class Bank {
 public:
  void addAccount(Account* account) { accounts_.insert(account); }

  bool transferMoney(Account* accountA, Account* accountB, double amount) {
    std::lock(*accountA->getLock(), *accountB->getLock());
    std::lock_guard<std::mutex> guardA(*accountA->getLock(), std::adopt_lock);
    std::lock_guard<std::mutex> guardB(*accountB->getLock(), std::adopt_lock);

    if (amount > accountA->getMoney()) {
      return false;
    }
    accountA->changeMoney(-amount);
    accountB->changeMoney(amount);

    return true;
  }

  double totalMoney() const {
    double sum = 0;
    for (auto a : accounts_) {
      sum += a->getMoney();
    }

    return sum;
  }

 private:
  std::set<Account*> accounts_;
};

std::mutex countLock;
void randomTransfer(Bank* bank, Account* accountA, Account* accountB) {
  while (true) {
    double randomMoney = ((double)rand() / RAND_MAX) * 100;
    if (bank->transferMoney(accountA, accountB, randomMoney)) {
      std::lock_guard<std::mutex> guardCountLock(countLock);
      std::cout << "Transfer " << randomMoney << " from " << accountA->getName()
                << " to " << accountB->getName()
                << ", Bank totalMoney: " << bank->totalMoney() << std::endl;
    } else {
      std::lock_guard<std::mutex> guardCountLock(countLock);
      std::cout << "Transfer failed, " << accountA->getName() << " has only $"
                << accountA->getMoney() << ", but " << randomMoney
                << " required" << std::endl;
    }
  }
}

int main() {
  Account a("Paul", 100);
  Account b("Moira", 100);

  Bank aBank;
  aBank.addAccount(&a);
  aBank.addAccount(&b);

  std::thread t1(randomTransfer, &aBank, &a, &b);
  std::thread t2(randomTransfer, &aBank, &b, &a);

  t1.join();
  t2.join();

  return 0;
}