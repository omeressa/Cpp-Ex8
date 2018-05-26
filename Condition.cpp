#include <exception>
#include <iostream>
#include "Condition.h"

using namespace std;


Condition::Condition(){
    this->p='.';
}
Condition::Condition(char other){
    if(other != 'X' && other != 'O' && other != '.')
      throw IllegalCharException(other);
    this->p = other ;
}
void Condition::operator= (char other) {
    if (other != '.' && other != 'X' && other != 'O')
    throw IllegalCharException(other);
    this->p = other;}
Condition::operator char(){
    return this->p;
}

bool operator == (Condition const & x, char const & y){
    return x.p == y;
}

/** Stream **/
ostream& operator<< (ostream& os, const Condition& p) {
    os << p.p;
    return os;
}

/**helping functions **/
char Condition::get_Point(){
    return this->p;   
}
void Condition::set_Point(char other){
    if (other != '.' && other != 'X' && other != 'O')
    throw IllegalCharException(other);
    this->p = other;
}
