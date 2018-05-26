#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

#include "Board.h"

Board::Board(int size){
    int i,j;
    this->size = size;
    board = new Condition*[size];
    
    for(i = 0; i < size; ++i){
    board[i] = new Condition[size];
    }
    i=0;  
    /**
     * filling all board with dots ( . ) */
    for(i = 0; i < size; i++) {
      for(j = 0; j <  size; j++) {
          board[i][j] = '.';
        }
    }
}

/** copy Constructor */
Board::Board(const Board& board) {
     this->size = board.size;
     this->board = new Condition*[this->size];
        
     for(int i = 0; i < board.size; i++)
        this->board[i] = new Condition[this->size];
           int i,j;     
      for( i = 0; i < board.size; i++) {
         for( j = 0; j < board.size; j++) {
            this->board[i][j] = board.board[i][j];
        }
    }
}

/** Distrctor */
Board::~Board(){
    for(int i = 0; i <size ; ++i)
       delete[] board[i];
       delete[] board;
}


Board& Board::operator= (char c) {
     if(c !='.' && c !='X' && c!= 'O')
     throw IllegalCharException(c);
       
     for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
           board[i][j] = c;
    return *this;
}

Board& Board::operator= (const Board& b) {
        this->~Board();
        size = b.size;
        board = new Condition*[size];
        
        for(int i = 0; i < size; i++)
        board[i] = new Condition[size];
        
        for(int i = 0; i < size; i++)
                for(int j = 0; j < size; j++)
                  board[i][j].set_Point(b.board[i][j].get_Point());
    return *this;
}


Condition& Board::operator[] (vector<int> vec) {
    // if ((vec.at(0) ||vec.at(1))<0 || (vec.at(0)||vec.at(1))>= size)
         if (vec.at(0) < 0 || vec.at(0) >= size || vec.at(1) < 0 || vec.at(1) >= size)
     throw IllegalCoordinateException(vec.at(0), vec.at(1));
     return board[vec.at(0)][vec.at(1)];
}   



ostream& operator << (ostream & os, const Board & board){
    for(int i = 0 ; i < board.size ; i++){
        for(int j = 0 ; j < board.size ; j++){
            os << board.board[i][j];
        }
        os << endl;
    }
    return os;
}












