#ifndef __STUDENT_H_
#define __STUDENT_H_

#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

class DigitalWallet {

	unordered_map<string, queue<pair<int, int>>> toAddQ; 
	unordered_map<string, int> currentMoney; 
	queue<pair<int, string>> expireQ;

	void updateMoneyOnTime(size_t time, string person_id){
		queue<pair<int, int>> & q = toAddQ[person_id];
		int expiredMoney = 0;
		while (!q.empty() && q.front().second < time) { 
			expiredMoney += q.front().first, q.pop();
		}
		currentMoney[person_id] -= expiredMoney;
		total_expired += expiredMoney; // global status
	}

	public:
	int total_give = 0, total_spent = 0, total_expired = 0;

  void add_money(size_t time, string person_id, 
									int amount, size_t duration) {
		updateMoneyOnTime(time, person_id);
		toAddQ[person_id].emplace(amount, time + duration);
		currentMoney[person_id] += amount;
		total_give += amount;
		expireQ.emplace(time + duration, person_id);
	}


  bool use_money(size_t time, string person_id, int amount) {
		updateMoneyOnTime(time, person_id);
		if (currentMoney[person_id] < amount) return false;
		currentMoney[person_id] -= amount;
		total_spent += amount; // global status

		queue<pair<int, int>> & q = toAddQ[person_id];
		while (!q.empty() && amount >= q.front().first) {
			amount -= q.front().first; q.pop();
		}
		if (!q.empty()) q.front().first -= amount;
		return true;
	}

  int current_money(size_t time, string person_id) {
		updateMoneyOnTime(time, person_id);
		return currentMoney[person_id];
  }

  void status(size_t time, long long &total_give, 
													 long long &total_spent, 
													 long long &total_expired) {
		total_give = this->total_give;
		total_spent = this->total_spent;
		string personId;
		while (!expireQ.empty() && expireQ.front().first < time) {
			personId = expireQ.front().second; expireQ.pop();
			updateMoneyOnTime(time, personId);
		}
		total_expired = this->total_expired;
	}
	
};

#endif
