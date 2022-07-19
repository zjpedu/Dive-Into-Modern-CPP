#include <iostream>
#include <memory>
#include "Form.cpp"

class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};  // 观察者

class FileDownloader
{
	std::string m_filePath;
	int m_fileNumber;

	std::shared_ptr<IProgress>  m_iprogress;   // 观察者
	
public:
	FileDownloader(const std::string& filePath, int fileNumber) :
		m_filePath(filePath), 
		m_fileNumber(fileNumber){
	}

	void download(){
		//1.网络下载准备
		std::cout << "文件下载准备" << std::endl;
		//2.文件流处理
		std::cout << "文件正在处理" << std::endl;

		//3.设置进度
		for (int i = 0; i < m_fileNumber; i++){
			//...
			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
			m_iprogress->DoProgress(progressValue);
		}

	}

	void setProgress(std::shared_ptr<IProgress> progress)
	{
		m_iprogress=progress;
	}
};