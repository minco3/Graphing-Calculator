#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/queue/MyQueue.h"
#include "../../includes/token/function.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/token.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/str_to_infix/str_to_infix.h"
//------------------------------------------------------------------------------------------

using namespace std;

bool test_shunting_yard(bool debug = false)
{
  Queue<Token *> infix; // infix expression: 3 * 5
  infix.push(new Integer(3));
  infix.push(new Operator("*"));
  infix.push(new Integer(5));
  ShuntingYard sy(infix);
  Queue<Token*> postfix = sy.postfix(); // generate postfix
  cout << "3 * 5: " << postfix << endl;

  Queue<Token *> infix2;
  infix2.push(new Integer(3));
  infix2.push(new Operator("*"));
  infix2.push(new LeftParen());
  infix2.push(new Integer(5));
  infix2.push(new Operator("+"));
  infix2.push(new Integer(6));
  infix2.push(new Operator("-"));
  infix2.push(new Function("X"));
  infix2.push(new RightParen());
  infix2.push(new Operator("/"));
  infix2.push(new Integer(9));
  sy.infix(infix2);
  postfix = sy.postfix();
  cout << "3*(5+6-X)/9: " << postfix << endl;

  // iterator postfix queue
  ShuntingYard sy2;
  postfix = sy2.postfix(infix2);
  for (Queue<Token *>::Iterator it = postfix.begin(); it != postfix.end(); it++){
    cout <<setw(2)<< *it;
  }
  cout << endl;

  // release memory
  for (Queue<Token*>::Iterator it = infix.begin(); it != infix.end(); ++it)
    delete *it;

  for (Queue<Token*>::Iterator it = infix2.begin(); it != infix2.end(); ++it)
    delete *it;

  cout << "\n\n--------- Shunting Yard DONE ---------\n\n" << endl;
  return true;
}

bool test_rpn(bool debug = false)
{
  Queue<Token *> postfix; // postfix expression: 3 5 *
  postfix.push(new Integer(3));
  postfix.push(new Integer(5));
  postfix.push(new Operator("*"));
  RPN rpn(postfix);
  cout << "3 5 *: " << rpn() << endl << endl;

  Queue<Token *> postfix2; // postfix expression: 3 X *
  postfix2.push(new Integer(3));
  postfix2.push(new Function("X"));
  postfix2.push(new Operator("*"));
  rpn.set_input(postfix2);
  cout << "3 X *: (X=2): " << rpn(2) << endl << endl;

  Queue<Token *> postfix3; // postfix expression: 3 5 6 + X - * 9 /
  postfix3.push(new Integer(3));
  postfix3.push(new Integer(5));
  postfix3.push(new Integer(6));
  postfix3.push(new Operator("+"));
  postfix3.push(new Function("X"));
  postfix3.push(new Operator("-"));
  postfix3.push(new Operator("*"));
  postfix3.push(new Integer(9));
  postfix3.push(new Operator("/"));
  rpn.set_input(postfix3);
  cout << "3 5 6 + X - * 9 /: (X=2): " << rpn(2) << endl;

  // release memory
  for (Queue<Token*>::Iterator it = postfix.begin(); it != postfix.end(); ++it)
    delete *it;

  for (Queue<Token*>::Iterator it = postfix2.begin(); it != postfix2.end(); ++it)
    delete *it;

  cout << "\n\n--------- RPN DONE ---------\n\n" << endl;
  return true;
}

bool test_shunting_rpn(bool debug) {
  Queue<Token *> infix; // infix expression: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3
  infix.push(new Integer(3));
  infix.push(new Operator("+"));
  infix.push(new Function("X"));
  infix.push(new Operator("*"));
  infix.push(new Integer(2));
  infix.push(new Operator("/"));
  infix.push(new LeftParen());
  infix.push(new Integer(1));
  infix.push(new Operator("-"));
  infix.push(new Integer(5));
  infix.push(new RightParen);
  infix.push(new Operator("^"));
  infix.push(new Integer(2));
  infix.push(new Operator("^"));
  infix.push(new Integer(3));
  ShuntingYard sy(infix);
  Queue<Token*> postfix = sy.postfix(); // generate postfix

  cout << "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3: " << postfix << endl;
  
  RPN rpn(postfix);
  cout << "3 X 2 * 1 5 - 2 3 ^ ^ / +: (X=4): " << rpn(4) << endl;

  // release memory
  for (Queue<Token*>::Iterator it = infix.begin(); it != infix.end(); ++it)
    delete *it;
  for (Queue<Token*>::Iterator it = postfix.begin(); it != postfix.end(); ++it)
    delete *it;
    cout << "\n\n--------- SHUNTING RPN DONE ---------\n\n" << endl;
  return true;
}

bool test_shunting_yard_new_funcs(bool debug = false) {
    Queue<Token *> infix; // infix expression: 5 * ( Max(X, 4) + 6)
    
    infix.push(new Integer(5));
    infix.push(new Operator("*"));
    infix.push(new LeftParen);
    infix.push(new Function("Max"));
    infix.push(new LeftParen);
    infix.push(new Function("X"));
    infix.push(new Integer(4));
    infix.push(new RightParen);
    infix.push(new Operator("+"));
    infix.push(new Integer(6));
    infix.push(new RightParen);

    ShuntingYard sy(infix);
    Queue<Token*> postfix = sy.postfix(); // generate postfix
    cout << "5 * ( Max(X, 4) + 6): " << postfix << endl;

    // release memory
    for (Queue<Token*>::Iterator it = infix.begin(); it != infix.end(); ++it)
        delete *it;

    return true;

}

bool test_line(bool debug = false) {
  Queue<Token*> infix = strToInfix("X");
  ShuntingYard sy(infix);
  Queue<Token*> postfix = sy.postfix();
  RPN rpn(postfix);
  cout << rpn(1) << endl; // test 1
  for (int i=0; i<100; i++) {
    if (rpn(i)!=i) {
      cout << i << ", " << rpn(i) << endl;
      return false;
    }
  }
  return true;
}

//Lord help me! 
bool debug = false;

TEST(TEST_SHUNTING_YARD, TestShuntingYard)
{
  bool success = test_shunting_yard(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_RPN, TestRPN)
{
  bool success = test_rpn(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_SHUNTING_RPN, TestShuntingRPN)
{
  bool success = test_shunting_rpn(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_SHUNTING_YARD, newFunctionTest)
{
  bool success = test_shunting_yard_new_funcs(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_RPN, TestLine)
{
  bool success = test_line(debug);
  EXPECT_EQ(success, true);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running myTest.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

/*
[==========] Running 2 tests from 2 test cases.
[----------] Global test environment set-up.
[----------] 1 test from TEST_SHUNTING_YARD
[ RUN      ] TEST_SHUNTING_YARD.TestShuntingYard
3 * 5: [3]->[5]->[*]->|||

3*(5+6-X)/9: [3]->[5]->[6]->[+]->[X]->[-]->[*]->[9]->[/]->|||

 3 5 6 + X - * 9 /


--------- Shunting Yard DONE ---------


[       OK ] TEST_SHUNTING_YARD.TestShuntingYard (0 ms)
[----------] 1 test from TEST_SHUNTING_YARD (0 ms total)

[----------] 1 test from TEST_RPN
[ RUN      ] TEST_RPN.TestRPN
3 5 *: 15

3 X *: (X=2): 6

3 5 6 + X - * 9 /: (X=2): 3


--------- RPN DONE ---------


[       OK ] TEST_RPN.TestRPN (0 ms)
[----------] 1 test from TEST_RPN (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 2 tests.
*/