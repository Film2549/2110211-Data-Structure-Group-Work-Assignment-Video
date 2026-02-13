#ifndef __STUDENT_H_
#define __STUDENT_H_

#include <string>

// you can include anything

using namespace std;

class DigitalWallet {
  // you can declare variables or write new function

 public:
  void add_money(size_t time, string person_id, int amount, size_t duration) {
    // your code here
  }

  bool use_money(size_t time, string person_id, int amount) {
    // your code here
  }

  int current_money(size_t time, string person_id) {
    // your code here
  }

  void status(size_t time, long long &total_give, long long &total_spent,
              long long &total_expired) {
    // your code here
  }
};

#endif
