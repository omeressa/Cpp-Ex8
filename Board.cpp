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

////////////////////////////////////////////////////////////

istream& operator>> (istream& is, Board& b){
    string filename,line;
    is >> filename;
    ifstream infile;
    infile.open(filename);
    
    /* file not fount exiption */

    if(infile.fail()){
      cout << "file not found !!!" << endl;
      exit(1);
    }
    
    uint i=0;
    infile >> line;
    Board temp((int)line.Size());
    while (i<temp.Size()) {
      if(i!=0)
        infile >> line;
      for (uint j = 0; j < temp.Size(); j++) {
        temp[{i,j}] = line[j];
      }
      i++;
    }
    b = temp;
    infile.close();
    return is;
}

/*
istream &operator>>(istream &in,  Board &b)
{
    Board temp;
    in >> temp;
    b = temp ;
    return in;
}*/


string Board::draw(int n){

      const int length = n, width = n;
      string fileName = "TicTacToe.ppm";
      ifstream File(fileName);
        bool fileExist = false;

        if(File){
            cout << "does exist!!!" << endl;
            fileExist = true;
        }

        int index = 1;

        while(fileExist){
            fileName = "TicTacToe";
            fileName += to_string(index);
            fileName += ".ppm";

            ifstream File(fileName);
            if(File) {index++;}
            else {fileExist=false;}
        }

    ofstream imageFile(fileName);//create new file
      cout << "omar_board: " << fileName << endl;

      imageFile << "P6" << endl << length <<" " << width << endl << 255 << endl;
      RedGreenBlue image[length*length];
      for (int j = 0; j < length; ++j){  
        for (int i = 0; i < length; ++i){
           image[(length*j)+i].red = (i % 256);
           image[(length*j)+i].green = (j % 256);
           image[(length*j)+i].blue = ( ((i*i)+(j*j)) % 256);
         }
      }
    /*
    *    http://www.informit.com/articles/article.aspx?p=328647
    */
      image[0].red = 255;
      image[0].blue = 0;
      image[0].green = 0;
    
      imageFile.write(reinterpret_cast<char*>(&image), 3*length*length); // processing image
      imageFile.close();
      return "TicTacToe.ppm";
    }









