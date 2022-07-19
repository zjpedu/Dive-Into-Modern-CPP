#include <iostream>

struct ProgressBar{
	double progressBar;
	void setValue(double _progressBar){
		progressBar = _progressBar;
	}
};

struct TextBox{
	std::string getText(){
		std::cout << "TextBox getText() function call" << std::endl;
		return "";
	}
};

struct Form: public TextBox, public ProgressBar{

};