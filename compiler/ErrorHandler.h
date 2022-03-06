#pragma once

#include <string>
using namespace std;

enum errorType {ERROR, WARNING};

class ErrorHandler {
    
    public:
        void signal(int severity, string message, int lineNumber);
        bool hasError();
        bool hasWarning();
        
    protected:
        static string errorValues[2];
        bool error;
        bool warning;
        void generateMessage(int severity, string message, int lineNumber);
        
};