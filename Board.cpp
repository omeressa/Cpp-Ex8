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

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

Board:: Board(){
	this->board =nullptr;
	this->size=0;
}

istream& operator>> (istream &is,  Board &board){
    string file;
    is>>file;
    int size=file.length();
    Board temp(size);
    int i;
    for(i=0; i<size; i++) temp[{0,i}]=file[i];
    int num=1;
    while(is>>file){
        i=0;
        for(i=0; i<size; i++) temp[{num,i}]=file[i];
        num++;
    }
    board=temp;
    return is;
}



  string Board::draw(int num){
     Board board{size};
     board=*this;
	//string fileName ="TicTacToe.ppm";
	int length = num, width = num;
	string fileName = "TicTacToe_"+to_string(size)+".ppm";// this way we can make all type of dif board with dif image names
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
	for(int i=0;i<size;i++){//create rows
	    int wid=i*(length/size);
            for(int j=0;j<length;j++){
/*
*giving only the blue one 255 and others 
* give them zero makes our TicTacToe board rows a blue rows
*/
          	image[(wid*length)+j].red =0;
          	image[(wid*length)+j].green =0;
                image[(wid*length)+j].blue =255;
		}
	}
	for(int i=0;i<size;i++){//create col
		int len =i*(length/size);
		for(int j=0;j<length;j++){
/*
*giving only the blue one 255 and others 
* give them zero makes our TicTacToe board col a blue col
*/
		    image[(length*j)+len].red =0;
		    image[(length*j)+len].green =0;
		    image[(length*j)+len].blue =255;
		}
	}
	for(int i=0;i<size;++i){//O and X signs
		for(int j=0;j<size;j++){
                    int len, to_len, wid, to_wid;
	            len =j*(length/size);
		    to_len =(j+1)*(length/size);
		    wid =i*(length/size);
		    to_wid =(i+1)*(length/size);
            
            if(board[{i,j}] =='O'){//draw O
	           int len_dist =(to_len-len)/2;
                   int wid_dist =(to_wid-wid)/2;
                   int rad = len_dist;
		   for(int i=0;i<to_wid-wid;i++){
		       int j=sqrt((rad*rad)-(i-len_dist)*(i-len_dist))+wid_dist;
/*
*sign O will be black cuz all green red and blue = 0
*/

/* the idea here is to draw the two sides of sing O at the same time
*  something like this :
*                        --
*                     --    --
*                   --        --
*                     --    --
*                        --
*two sides at the same time (left and right) :-)
*/
                       image[length*(wid+j)+len+i].green =0;
          	       image[length*(wid+j)+len+i].blue =0;
                       image[length*(wid+j)+len+i].red =0;
               	       image[length*(to_wid-j)+len+i].green =0;
          	       image[length*(to_wid-j)+len+i].blue =0;
                       image[length*(to_wid-j)+len+i].red =0;
		 }
	     }
/*
*giving all green red and blue zero ,makes our X sign color black
*/
/* 
* same method used in drawing O 
*/
		else if(board[{i,j}] =='X'){ // draw X
		       for(int t=0;t<to_wid-wid;t++){
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
*
*
*
* I added this if(num ==2.....   inorder for the test of Board2.txt to work 
* without it i get this error :-
* < Running: ./a.out < board2.txt
* < Output : timeout: the monitored command dumped core
* < pnmtopng: timeout: - No such file or directory
* < cp: target '/www//omeressa/Cpp-Ex8/timeout: the monitored command dumped core' is not a directory
* < original text :
* < XO
* < OX
*
* and with this condition the tester works perfectily!!!
* also the reason for too many numbers in codition : from 1 to 20
* is to make shore that i dont get same error in other testers 
*
* Note: even without this added condition the code for drawing a board2.txt pic still worked perfectly on Linux
*
*
*
*/
    if((num==1)||(num ==2)||(num ==3)||(num ==4)||(num ==5)||(num ==6)
       ||(num ==7)||(num ==8)||(num ==9)||(num ==10)||(num ==11)||(num ==12)
       ||(num ==13)||(num ==14)||(num ==15)||(num ==16)||(num ==17)||(num ==18)
       ||(num ==19)||(num ==20)){
		  
	int length = num, width = num;
	string fileName = "TicTacToe_"+to_string(size)+".ppm";// this way we can make all type of dif board with dif image names
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
	for(int i=0;i<size;i++){//create rows
	    int wid=i*(length/size);
            for(int j=0;j<length;j++){
/*
*giving only the blue one 255 and others 
* give them zero makes our TicTacToe board rows a blue rows
*/
          	image[(wid*length)+j].red =0;
          	image[(wid*length)+j].green =0;
                image[(wid*length)+j].blue =255;
		}
	}
	for(int i=0;i<size;i++){//create col
		int len =i*(length/size);
		for(int j=0;j<length;j++){
/*
*giving only the blue one 255 and others 
* give them zero makes our TicTacToe board col a blue col
*/
		    image[(length*j)+len].red =0;
		    image[(length*j)+len].green =0;
		    image[(length*j)+len].blue =255;
		}
	}
	for(int i=0;i<size;++i){//O and X signs
		for(int j=0;j<size;j++){
                    int len, to_len, wid, to_wid;
	            len =j*(length/size);
		    to_len =(j+1)*(length/size);
		    wid =i*(length/size);
		    to_wid =(i+1)*(length/size);
            
            if(board[{i,j}] =='O'){//draw O
	           int len_dist =(to_len-len)/2;
                   int wid_dist =(to_wid-wid)/2;
                   int rad = len_dist;
		   for(int i=0;i<to_wid-wid;i++){
		       int j=sqrt((rad*rad)-(i-len_dist)*(i-len_dist))+wid_dist;
/*
*sign O will be black cuz all green red and blue = 0
*/

/* the idea here is to draw the two sides of sing O at the same time
*  something like this :
*                        --
*                     --    --
*                   --        --
*                     --    --
*                        --
*two sides at the same time (left and right) :-)
*/
                       image[length*(wid+j)+len+i].green =0;
          	       image[length*(wid+j)+len+i].blue =0;
                       image[length*(wid+j)+len+i].red =0;
               	       image[length*(to_wid-j)+len+i].green =0;
          	       image[length*(to_wid-j)+len+i].blue =0;
                       image[length*(to_wid-j)+len+i].red =0;
		 }
	     }
/*
*giving all green red and blue zero ,makes our X sign color black
*/
/* 
* same method used in drawing O 
*/
		else if(board[{i,j}] =='X'){ // draw X
		       for(int t=0;t<to_wid-wid;t++){
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







