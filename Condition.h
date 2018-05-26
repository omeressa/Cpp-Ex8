#pragma once
#include <iostream>
#include "IllegalCharException.h"

using namespace std;

class Condition {
  
      private:
    
        char p;

    public:
        
        Condition();
        Condition(char Char);
        void operator=(char c);
        friend bool operator == (Condition const &, char const &);
    
        void set_Point(char c);
        char get_Point();
        operator char();
  
        friend ostream& operator<< (ostream& , const Condition&);
};
