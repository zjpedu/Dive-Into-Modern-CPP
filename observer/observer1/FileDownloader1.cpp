#include <iostream>
#include <memory>
#include "Form.cpp"
/*
	进度条 ProgressBar 尽然和 FileDownloader 耦合在一起
*/
class FileDownloader
{
	std::string m_filePath;
	int m_fileNumber;
	std::shared_ptr<ProgressBar> m_progressBar;

public:
	FileDownloader(const std::string& filePath, 
	int fileNumber, 
	std::shared_ptr<ProgressBar> progressBar) :
		m_filePath(filePath), 
		m_fileNumber(fileNumber),
		m_progressBar(progressBar)
	{

	}
	void download(){
		//1.网络下载准备
		std::cout << "文件下载准备" << std::endl;
		//2.文件流处理
		std::cout << "文件正在处理" << std::endl;
		//3.设置进度条
		for (int i = 0; i < m_fileNumber; i++){
			//...
			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
			m_progressBar->setValue(progressValue);
		}
		//4.文件存储
		std::cout << "文件保存" << std::endl;
	}
};