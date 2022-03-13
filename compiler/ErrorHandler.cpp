/*************************************************************************
                          PLD Compiler : ErrorHandler
                          ---------------------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//---- Implementation of class <ErrorHandler> (file ErrorHandler.cpp) ------/

#include "ErrorHandler.h"
#include <iostream>

using namespace std;

string ErrorHandler::errorValues[2] = {"ERROR", "WARNING"};

void ErrorHandler::signal(int severity, string message, int lineNumber) {
	switch(severity) {
		case WARNING: warning = true; break;
		case ERROR: error = true; break;
	}
	generateMessage(severity, message, lineNumber);
}

void ErrorHandler::generateMessage(int severity, string message, int lineNumber) {
    cerr << errorValues[severity] << " : " << message << " at line " << lineNumber << "." << endl;
}

bool ErrorHandler::hasError() {
	return error;
}

bool ErrorHandler::hasWarning() {
	return warning;
}