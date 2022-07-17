class MainForm : public Form, public IProgress, 
	public  enable_shared_from_this<MainForm>
{
	shared_ptr<TextBox> txtFilePath;
	shared_ptr<TextBox> txtFileNumber;
	shared_ptr<ProgressBar> progressBar;

public:
	void Button1_Click(){

		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		shared_ptr<IProgress> ip=make_shared<ConsoleNotifier>();

		FileDownloader downloader(filePath, number);

		downloader.addIProgress(ip); 
		downloader.addIProgress(shared_from_this()); 

		downloader.download();

		downloader.removeIProgress(ip);

	}

	void DoProgress(float value) override{
		progressBar->setValue(value);
	}
};

class ConsoleNotifier : public IProgress {
public:
	void DoProgress(float value) override {
		cout << ".";
	}
};

