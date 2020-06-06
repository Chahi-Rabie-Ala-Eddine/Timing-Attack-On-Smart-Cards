#ifndef KEY_H
#define KEY_H

#include <iostream>
#include <string.h>

using namespace std;

class key
{
    private:
    string content;

    public:
    key();
    key(string content);
    string GetContent();
    void SetContent(string content);

};

#endif // KEY_H
