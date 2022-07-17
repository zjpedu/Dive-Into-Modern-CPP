class MainForm : public Form, public IProgress, 
	public enable_shared_from_this<MainForm>
{
	shared_ptr<TextBox> txtFilePath;
	shared_ptr<TextBox> txtFileNumber;
	shared_ptr<ProgressBar> progressBar;

public:
	void Button1_Click(){

		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		FileDownloader downloader(filePath, number);

		//shared_ptr<IProgress> ip=make_shared<ConsoleNotifier>();
		//downloader.setProgress( ip);
	
		//shared_ptr<IProgress> ip{this};
		//downloader.setProgress(ip);
		downloader.setProgress( shared_from_this()); // 当前 this 指针作为观察者
		
		downloader.download();
	}

	void DoProgress(float value) override {
		progressBar->setValue(value);
	}
};

class ConsoleNotifier : public IProgress {
public:
	void DoProgress(float value) override{
		cout << ".";
	}
};

