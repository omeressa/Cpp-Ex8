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

    istream& operator>> (istream &is,  Board &board){
        string file;
        is>>file;
        int size=file.length();
        Board temp(size);
        int i;
        for(i=0; i<size; i++) temp[{0,i}] = file[i];
        int num = 1;
        while(is>>file){
            i=0;
            for(i=0; i<size; i++) temp[{num, i}] = file[i];
            num++;
        }
        b=temp;
        return is;
    }


  string Board::draw(int num){
     Board board{size};
     board=*this;
	string fileName ="TicTacToe.ppm";
	int length = num, width = num;
	ofstream output(fileName, ios::app |ios::binary );
	output << "P6" << endl << length <<" " << width << endl << 255 << endl;

	RedGreenBlue image[length*length];
        
    for(int j=0; j<length;j++){  // row
       for(int i=0; i<length;i++){ // column
/*
*giving all three the number 255 gives us a white board pic
*/
           image[(length*j)+i].red =255;
           image[(length*j)+i].green = 255;
           image[(length*j)+i].blue =255; 
         }
       }

/*
* creat lines
*/
	for(int i=0;i<size;++i){//create col
		int len =i*(length/size);
		for(int j=10;j<length-10;++j){
/*
*giving only the blue one 255 and others 
* give them zero makes our TicTacToe board col a blue col
*/
			image[(length*j)+len].red =0;
			image[(length*j)+len].green =0;
			image[(length*j)+len].blue =255;
		}
	}
	for(int i=0;i<size;++i){//create rows
	    int wid=i*(length/size);
        for(int j=10;j<length-10;++j){
/*
*giving only the blue one 255 and others 
* give them zero makes our TicTacToe board rows a blue rows
*/
          	image[(wid*length)+j].red =0;
          	image[(wid*length)+j].green =0;
            image[(wid*length)+j].blue =255;
		}
	}
	for(int i=0;i<size;++i){//X and Y signs
		for(int j=0;j<size;++j){
            int len, to_len, wid, to_wid;
			len =j*(length/size);
		    to_len =(j+1)*(length/size);
			wid =i*(length/size);
			to_wid =(i+1)*(length/size);
            
            if(board[{i,j}] =='O'){//draw O
				   int len_dist =(to_len-len)/2;
                   int wid_dist =(to_wid-wid)/2;
                   int rad = len_dist;
				   for(int i=0;i<to_wid-wid-10;++i){
					  int j=sqrt((rad*rad)-(i-len_dist)*(i-len_dist))+wid_dist;
					  int a =5;
/*
*sign O will be black cuz all green red and blue = 0;
*/
                      image[length*((wid+j)-a)+len+i].green =0;
          			  image[length*((wid+j)-a)+len+i].blue =0;
                      image[length*((wid+j)-a)+len+i].red =0;
          			  image[length*(to_wid+a-j)+len+i].green =0;
          			  image[length*(to_wid+a-j)+len+i].blue =0;
                      image[length*(to_wid+a-j)+len+i].red =0;
				}
			}
/*
*giving all green red and blue zero ,makes our X sign color black
*/
		else if(board[{i,j}] =='X'){ // draw X
			   for(int t=0;t<to_wid-wid-10;++t) {
                   image[length*(t+wid)+len+t].green =0;
                   image[length*(t+wid)+len+t].red =0;
	               image[length*(t+wid)+len+t].blue =0;
		           image[length*(t+wid)+to_len-t].blue =0;
                   image[length*(t+wid)+to_len-t].green =0;
                   image[length*(t+wid)+to_len-t].red =0;
				}
			} 
		}
	}

/*
*image processing
*/
	output.write (reinterpret_cast <char*>(& image),3 * num*num);
	output.close ();
	return fileName;
}

    /*
    *    http://www.informit.com/articles/article.aspx?p=328647
    */







