#include <iostream>
#include <iomanip>
#include <cctype>
#include "stack.h"

int main()
{
    std::string next;
    char storage;
    std::string charArray;
    std::string newNext;
    Stack<char> p;

    std::cout << "Enter a string" << std::endl;
    std::getline(std::cin, next);

    for (char n : next)
    {
        if (isalpha(n))
        {
            newNext += n;
        }
    }

    std::string userInput = next;
    for (char n : newNext)
    {
        p.push(n);
    }

    while (!p.isStackEmpty())
    {
        p.pop(storage);
        charArray += storage;
    }

    for (int i = 0; i < newNext.size(); i++)
    {
        if (toupper(charArray[i]) != toupper(newNext[i]))
        {
            cout << userInput << "is NOT a Palindrome";
            return 0;
        }
    }
    cout << userInput << " IS a Palindrome";
}
