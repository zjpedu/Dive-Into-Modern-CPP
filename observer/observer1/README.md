### 观察者模式

#### 观察者模式问题由来

我们看 `FileDownloader1.cpp` 和 `MainForm1.cpp` 的代码的构造函数注释中看出， processBar 这个
变量存在强耦合。这是一种不好的设计。

```c++
class FileDownloader
{
	string m_filePath;
	int m_fileNumber;
	shared_ptr<ProgressBar> m_progressBar;

public:
	FileDownloader(const string& filePath, 
	int fileNumber, 
	shared_ptr<ProgressBar> progressBar) :
		m_filePath(filePath), 
		m_fileNumber(fileNumber),
		m_progressBar(progressBar)   // 从 MainForm 中传递过来
	{

	}
	void download(){
		//1.网络下载准备

		//2.文件流处理

		//3.设置进度条
		for (int i = 0; i < m_fileNumber; i++){
			//...
			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
			m_progressBar->setValue(progressValue);
		}
		//4.文件存储
	}
};
```

```c++
class MainForm : public Form
{
	shared_ptr<TextBox> txtFilePath;
	shared_ptr<TextBox> txtFileNumber;
	shared_ptr<ProgressBar> progressBar;  // 在 Button1_Click() 函数中，将 processBar 传递给 FileDownloader 的构造函数
public:
	void Button1_Click(){
		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		FileDownloader downloader(filePath, 
			number, progressBar);
		downloader.download();
	}
};
```