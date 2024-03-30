//State Coding Exercise
//A combination lock is a lock that opens after the right digits have been entered.A lock is preprogrammed with a combination(e.g., 12345) and the user is expected to enter this combination to unlock the lock.
//
//The lock has a status  field that indicates the state of the lock.The rules are :
//
//If the lock has just been locked(or at startup), the status is LOCKED.
//If a digit has been entered, that digit is shown on the screen.As the user enters more digits, they are added to Status.
//If the user has entered the correct sequence of digits, the lock status changes to OPEN.
//If the user enters an incorrect sequence of digits, the lock status changes to ERROR.
//Please implement the CombinationLock  class to enable this behavior.Be sure to test both correctand incorrect inputs.
//
//Here is an example unit test for the lock :
//
//CombinationLock cl({ 1,2,3 });
//ASSERT_EQ("LOCKED", cl.status);
//cl.enter_digit(1);
//ASSERT_EQ("1", cl.status);
//cl.enter_digit(2);
//ASSERT_EQ("12", cl.status);
//cl.enter_digit(3);
//ASSERT_EQ("OPEN", cl.status);

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CombinationLock
{
  vector<int> combination;
  string entered;
  int pos;

public:
  string status;

  CombinationLock(const vector<int>& combination) : combination(combination), entered(""), pos(0), status("LOCKED") {}

  void enter_digit(int digit)
  {
    if (status == "LOCKED") {
      status = "";
    }

    entered += to_string(digit);

    if (combination[pos] != digit) {
      status = "ERROR";
      entered = "";
      pos = 0;
      return;
    }

    status += to_string(digit);

    ++pos;
    if (pos == combination.size()) {
      status = "OPEN";
    }
  }
};


int main()
{
    std::cout << "Hello World!\n";
}