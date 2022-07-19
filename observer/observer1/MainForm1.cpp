#include <iostream>
#include <memory>
#include <string>
#include "FileDownloader1.cpp"


class MainForm: public Form
{
	std::shared_ptr<TextBox> txtFilePath;
	std::shared_ptr<TextBox> txtFileNumber;
	std::shared_ptr<ProgressBar> progressBar;
public:
	void Button1_Click(){
		std::string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		FileDownloader downloader(filePath, 
			number, progressBar);
		downloader.download();
	}
};

