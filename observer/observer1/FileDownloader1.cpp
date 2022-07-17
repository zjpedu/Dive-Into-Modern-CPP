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
		m_progressBar(progressBar)
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