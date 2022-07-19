#include <iostream>
#include <memory>
#include "FileDownloader4.cpp"


class ConsoleNotifier : public IProgress {
public:
	void DoProgress(float value) override {
		std::cout << ".";
	}
};


class MainForm : public Form, public IProgress, 
	public  std::enable_shared_from_this<MainForm>
{
	std::shared_ptr<TextBox> txtFilePath;
	std::shared_ptr<TextBox> txtFileNumber;
	std::shared_ptr<ProgressBar> progressBar;

public:
	void Button1_Click(){

		std::string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		std::shared_ptr<IProgress> ip=std::make_shared<ConsoleNotifier>();

		FileDownloader downloader(filePath, number);

		downloader.addIProgress(ip); 
		downloader.addIProgress(shared_from_this()); 

		downloader.download();

		downloader.removeIProgress(ip);
		downloader.removeIProgress(shared_from_this());

	}

	void DoProgress(float value) override{
		progressBar->setValue(value);
	}
};
