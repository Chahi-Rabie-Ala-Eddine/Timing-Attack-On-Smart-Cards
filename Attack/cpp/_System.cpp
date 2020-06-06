#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "../header/_System.h"
#include "../header/_BIGNUM.h"
#include "../header/_Constants.h"
#include "../header/_Statistics.h"
#include "../header/_Colors.h"

/*Compute smart card signature*/
string GetSmartCardSignature(string message) 
{
    string data, executable = "/home/aladin/Bureau/TER/SIDE\\ CHANNEL\\ ATTACK/Smart\\ Card/bin/SMARTCARD.bin " + message;
   	executable.append(" 2>&1");

    FILE * stream = popen(executable.c_str(), "r");
    char buffer[256];

    if(!stream)
    	throw runtime_error("Cannont read buffer !\n");

    else
    	while (!feof(stream))
	        if (fgets(buffer, 256, stream) != NULL) 
	        	data.append(buffer);
	
	pclose(stream);

    return data;
}
