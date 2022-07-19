#include <iostream>
#include <memory>
#include <list>
#include "Form.cpp"

class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};


class FileDownloader  // Subject 被观察者
{
	std::string m_filePath;
	int m_fileNumber;

	std::list<std::shared_ptr<IProgress>>  m_iprogressList;   // 一组观察者
	
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
			onProgress(progressValue);
		}

	}

	void addIProgress(const std::shared_ptr<IProgress>& iprogress){
		m_iprogressList.push_back(iprogress);
	}

	void removeIProgress(const std::shared_ptr<IProgress>& iprogress){
		m_iprogressList.remove(iprogress);
	}
protected:
	void onProgress(float value)  
	{
		for (auto& progress : m_iprogressList){
			progress->DoProgress(value);  // 通知所有的观察者
		}
	}
};