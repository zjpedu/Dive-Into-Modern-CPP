#include "FileDownloader2.cpp"

class ConsoleNotifier : public IProgress {
public:
	void DoProgress(float value) override{
		std::cout << ".";
	}
};


class MainForm : public Form, public IProgress, 
	public std::enable_shared_from_this<MainForm>
{
	std::shared_ptr<TextBox> txtFilePath;
	std::shared_ptr<TextBox> txtFileNumber;
	std::shared_ptr<ProgressBar> progressBar;

public:
	void Button1_Click(){

		std::string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		FileDownloader downloader(filePath, number);

		// std::shared_ptr<IProgress> ip=std::make_shared<ConsoleNotifier>();
		// downloader.setProgress( ip);
	
		// std::shared_ptr<IProgress> ip{this};  // 这个是错误的，有声明周期问题，会出现多次 delete
		// downloader.setProgress(ip);
		downloader.setProgress( shared_from_this()); // 当前 this 指针作为观察者
		
		downloader.download();
	}

	void DoProgress(float value) override {
		progressBar->setValue(value);
	}
};

