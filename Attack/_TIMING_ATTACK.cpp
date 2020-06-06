#include <iostream>
#include <string.h>
#include <algorithm>

#include "./header/_Constants.h"
#include "./header/_Attack.h"

using namespace std;

const BIG n_ = SetValue("A32C8EF5AEE5768A5E37A91057C542690E03464D4CD088FB6EB1996A731F598CB44EB2A4522CD50A5D0F785ACAC3076320B8D8C97843CCB88DC9743F28616209");

int main(int argc, char const *argv[])
{	
	_Timing_Attack(n_);

	Free({n_});

	return 0;
}