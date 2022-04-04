/*************************************************************************
                          PLD Compiler : ErrorHandler
                          ---------------------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//------ Interface of class <ErrorHandler> (file ErrorHandler.h) -------/
#pragma once

//--------------------------------------------------- Called interfaces
#include <string>
using namespace std;

//------------------------------------------------------------------ Types
enum errorType {ERROR, WARNING};

//------------------------------------------------------------------------
// Goal of class <ErrorHandler>
// The goal of this class is to handle errors and warnings
//------------------------------------------------------------------------
class ErrorHandler {
    
    public:
        void signal(int severity, string message, int lineNumber);
        bool hasError();
        bool hasWarning();
        
    protected:
        static string errorValues[2];
        bool error = false;
        bool warning = false;
        void generateMessage(int severity, string message, int lineNumber);
        
};