// threadtest.cc
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield,
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include <iostream>
#include <string>

using namespace std;

void Task1(int n);
void Task2(int n);
int getUserInput();
bool checkInputIsInt(char input[]);
char* int_toString(int n);
void helper_int_toString(int n, char *str, int i);
void shout(int S);

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Task1(int n)  //checkUserInput()
{
  bool hasLetters = false; // Holds number of letters entered by user. (a-z & A-Z)
  bool hasDigits = false;  // Holds number of numerical digits entered by users (0-9)
  bool hasDecimal = false; // flag if user input contains a decimal ( . )
  int numDecimal = 0;
  bool hasNull = false; // flag if user didn't enter anything.
  bool isInvalid = false; //
  bool hasNegative = false;

  char input[100];
  cout<<"Enter Something: ";
  cin.getline(input,100);

  for (int i=0;(unsigned)i<(unsigned)strlen(input) || i==0;i++)
  {
      int val = (int)input[i]; // val is the ASCII value of character at array index i

      if ((val >= 65 and val <=90) || (val >= 97 and val <= 122)) // ASCII values for Capital and Lowercase letters
      {
          hasLetters = true;
      }
      else if (val >= 48 and val <= 57) // ASCII values for numerical digits
      {
          hasDigits = true;
      }
      else if (val == 46) // ASCII value for decimal
      {
        numDecimal++;
        if (numDecimal == 1) { hasDecimal = true; }
        else if (numDecimal > 1) { hasDecimal = true ; }
      }
      else if (val == 0) // ASCII value for NULL (no input)
      {
          hasNull = true;
      }
      else if (val == 45 and i == 0) {
        hasNegative = true;
      }
      else
      {
          isInvalid = true;
      }
  }

  if (hasLetters && !hasDigits && !hasDecimal && !hasNull && !isInvalid && !hasNegative)
  {
    if (strlen(input) > 1) { cout<<"You entered a string.\n"; }
    else { cout<<"You entered a character.\n"; }
  }
  else if (!hasLetters && hasDigits && !hasDecimal && !hasNull && !isInvalid)
  {
    if (hasNegative) { cout<<"You entered a negative integer.\n"; }
    else { cout<<"You enterd an integer.\n"; }
  }
  else if (!hasLetters && hasDigits && hasDecimal && !hasNull && !isInvalid)
  {
    if (hasNegative) { cout<<"You entered a negative decimal number.\n"; }
    else { cout<<"You entered a decimal number.\n"; }
  }
  else if (!hasLetters && !hasDigits && !hasDecimal && hasNull && !isInvalid)
  {
    cout<<"You didn't enter anything!\n";
  }
  else
  {
    cout<<"Invalid String\n";
  }
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Task2(int n)  //ThreadTest()
{
  //DEBUG('t', "Debug");
  int T;
  int S;

  cout<<"Enter number of threads: ";
  T = getUserInput();
  cout<<"Enter number of Shouts: ";
  S = getUserInput();

  for (int i = 1; i <= T; i++)
  {
    char *name = int_toString(i);
    Thread *t = new Thread(name);
    t->Fork(shout, S);
  }
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// returns user input if it is valid (in this case, valid if integer. see checkInputIsInt <- return true if input is int)
int getUserInput()
{
  bool validInput = false;
  char *input = new char[100];
  while (!validInput) {
   // cout<<"Enter Something: ";
    cin.getline(input,100);
    validInput = checkInputIsInt(input);
  }
  return atoi(input);
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool checkInputIsInt(char input[])
{
  bool hasLetters = false; // Holds number of letters entered by user. (a-z & A-Z)
  bool hasDigits = false;  // Holds number of numerical digits entered by users (0-9)
  bool hasDecimal = false; // flag if user input contains a decimal ( . )
  int numDecimal = 0;
  bool hasNull = false; // flag if user didn't enter anything.
  bool isInvalid = false; //
  bool hasNegative = false;
//  bool hasMultipleDecimal = false;

  for (int i=0;(unsigned)i<(unsigned)strlen(input) || i==0;i++)
  {
      int val = (int)input[i]; // val is the ASCII value of character at array index i

      if ((val >= 65 and val <=90) || (val >= 97 and val <= 122)) { hasLetters = true; } // ASCII values for Capital and Lowercase letters
      else if (val >= 48 and val <= 57) { hasDigits = true; } // ASCII values for numerical digits
      else if (val == 0) { hasNull = true; } // ASCII value for NULL (no input)
      else if (val == 45 and i == 0) { hasNegative = true; }
      else if (val == 46) // ASCII value for decimal
      {
        numDecimal++;
        if (numDecimal == 1) { hasDecimal = true; }
  //      else if (numDecimal > 1) { hasMultipleDecimal = true ; }
      }
      else { isInvalid = true; }
  }
  if (hasLetters && !hasDigits && !hasDecimal && !hasNull && !isInvalid && !hasNegative)
  {
    if (strlen(input) > 1) { cout<<"You need to enter an integer value.\n"; }
    else { cout<<"You need to enter an integer value.\n"; }
  }
  else if (!hasLetters && hasDigits && !hasDecimal && !hasNull && !isInvalid)
  {
    if (hasNegative) { cout<<"You need to enter a positive integer.\n"; }
    else { return true;}
  }
  else if (!hasLetters && hasDigits && hasDecimal && !hasNull && !isInvalid)
  {
    if (hasNegative) { cout<<"You need to enter a positive integer.\n"; }
    else { cout<<"You need to enter an integer value.\n"; }
  }
  else if (!hasLetters && !hasDigits && !hasDecimal && hasNull && !isInvalid) { cout<<"You didn't enter anything!\n"; }
  else { cout<<"Invalid String\n"; }


  return false;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
char* int_toString(int n)
{
  char *str = new char[100];
  helper_int_toString(n, str, 0);
  return str;
}

// Recursive Function
void helper_int_toString(int n, char *str, int i)
{
  int num;
  if (n >= 1000)
  {
    num = n / 1000;
    n = n-(num*1000);
    str[i] = '0' + num;
    helper_int_toString(n,str,i+1);
  }
  else if (n >= 100)
  {
    num = n / 100;
    n = n-(num*100);
    str[i] = '0' + num;
    helper_int_toString(n,str,i+1);
  }
  else if (n >= 10)
  {
    num = n / 10;
    n = n-(num*10);
    str[i] = '0' + num;
    helper_int_toString(n,str,i+1);
  }
  else if (n >= 1)
  {
    num = n / 1;
    n = n-(num*1);
    str[i] = '0'+ num;
    helper_int_toString(n,str,i+1);
  }
  else if (n == 0)
  {
    str[i] = '0' + n;
  }
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void shout(int S)
{
    //srand(time(0)); // used for random number generation
    char shout_list[5][10] = { "Alpha", "Bravo", "Charlie", "Delta", "Echo" }; // shout list
    for (int i = 0; i<S;i++) {
      int yieldCount =  (Random()%5+3);
      //cout<<yieldCount<<"\n";
      int shout_index = (Random()%5); // to select random shout
      cout<<"Thread "<<currentThread->getName()<<" says: "<<shout_list[shout_index]<<"\n";
      for (int j = 3; j < yieldCount; j++)
      {
        currentThread->Yield();
      }
    }
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<





















//====================================================================================
//			ORIGINAL THREADTEST CODE
//====================================================================================
void
SimpleThread(int which)
{
    int num;
    for (num = 0; num < 5; num++)
    {
	     printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------
void
ThreadTest()
{
    //DEBUG('t', "Entering ThreadTest");

    //Thread *t = new Thread("forked thread");
    //t->Fork(SimpleThread, 1);
    SimpleThread(0);
}
