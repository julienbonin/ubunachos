#include "copyright.h"
#include "system.h"
#include <array>
#include <iostream>

using namespace std;
using namespace array;

void
inputThread()
{
    char input[];
    cout<<"Enter a string: ";
    cin>>input;
    for (int n=0;n<input.size(); i++)
    {
	cout<<input[n]<<"\n";
    }

    currentThread->Yield();  
}

void checkInput() {
    
    Thread *t = new Thread("Input");

    t->Fork(inputThread);
    


}
