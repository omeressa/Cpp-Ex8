
class IllegalCoordinateException{

private:
	int a;
	int b;

public:IllegalCoordinateException(int a,int b){
		this->a = a;
		this->b = b;
	}

	const std::string theCoordinate() const{
		return "("+std::to_string(a) + "," + std::to_string(b)+")";
	}

};

