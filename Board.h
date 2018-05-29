#ifndef BOARD_H
#define BOARD_H

#pragma once

#include <iostream>
#include <vector>
#include "Condition.h"
#include "IllegalCoordinateException.h"
#include <string>
#include <fstream>
#include <math.h>



using namespace std;



class Board {
  
    private:
    
      int size;
      Condition** board;
    

    public:

        Board(const int size);
        Board(const Board& board); 
        Board();
        //Board():board(nullptr),size(0){}


        ~Board();
        
        Board& operator= (char c);
        Board& operator= (const Board& b);
        Condition& operator [](vector<int> vec);
  
      	friend istream &operator >> (istream  &input, Board &board);
        string draw(int picture);

        friend ostream& operator<< (ostream& os,const Board& board);
  
        const uint Size()const {return (uint)size;}
        
};

struct RedGreenBlue {
  uint8_t red, green, blue;
  public:
    RedGreenBlue() {}
    RedGreenBlue(uint8_t red, uint8_t green, uint8_t blue){
      this->red = red;
      this->green = green;
      this->blue = blue;
    }
};
#endif
