#ifndef BOARD_H
#define BOARD_H

#pragma once

#include <iostream>
#include <vector>
#include "Condition.h"
#include "IllegalCoordinateException.h"
#include <fstream>
#include "Image.h"


using namespace std;



class Board {
  
    private:
    
      int size;
      Condition** board;
    

    public:

        Board(const int size);
        Board(const Board& board); 
        ~Board();
        
        Board& operator= (char c);
        Board& operator= (const Board& b);
        Condition& operator [](vector<int> vec);
  
      	friend istream &operator >> (istream  &input, Board &board);
        string draw(int picture);

        friend ostream& operator<< (ostream& os,const Board& board);
        
};
#endif
