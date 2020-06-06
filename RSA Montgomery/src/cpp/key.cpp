#include "../header/key.h"

key::key(){}

key::key(string content)
{
    this->content = content;
}

string key::GetContent()
{
    return this->content;
}

void key::SetContent(string content)
{
    this->content = content;
}
