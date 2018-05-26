
class IllegalCharException{

private:
	char Char;
public:
    IllegalCharException(char Char){
    this->Char=Char;
   }
	
    const char theChar() const{
	return Char;
   }
};

