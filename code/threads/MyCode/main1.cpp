#include <iostream>

using namespace std;

int main() 
{
    int number_of_letters = 0; // Holds number of letters entered by user. (a-z & A-Z)
    int number_of_digits = 0;  // Holds number of numerical digits entered by users (0-9)
    int hasDecimal = false; // to flag if user input contains a decimal ( . )
    int hasNull = false; // to flag if user didn't enter anything.

    // note: any character input not specified above will be considered invalid input.

    char input[100];
    cout<<"Enter Something: ";
    cin.getline(input,100);

    for (int i=0;input[i]!='\0';i++)
    {
        int val = (int)input[i]; // val is the ASCII value of character at array index i
        if ((val >= 65 and val <=90) || (val >= 97 and val <= 122))
        {
            cout<<"You entered a letter! \n";
            number_of_letters++;
        }
        else if (val >= 48 and val <= 57)
        {
            cout<<"You enterd a number! \n";
            number_of_digits++;
        }
        else if (val == 46)
        {
            cout<<"You entered a period! \n";
            hasDecimal = true;
        }
        else if (val == 0)
        {
            cout<<"You didn't enter anything!!!!!";
            hasNull = true;
        }
        else 
        {
            cout<<"Your input is invalid";
        }
    } 
    cout<<"\n";



    return 0;
}
