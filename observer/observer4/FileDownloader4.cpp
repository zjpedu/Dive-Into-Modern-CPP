#include <iostream>
#include <memory>
#include <list>
#include "Form.cpp"

struct IProgress{
	virtual void DoProgress(float value) {};
	virtual ~IProgress(){};

	/* 使用 std::weak_ptr 时必须要重载 == 操作符 */
	friend bool operator==(const std::weak_ptr<IProgress> left, const std::weak_ptr<IProgress> right){
		std::shared_ptr<IProgress> l = left.lock();
		std::shared_ptr<IProgress> r = right.lock();
		return l != nullptr && r != nullptr && (l->id == l->id);
	}
private:
	int id;
};



class Subject
{
private:
	// std::list<std::shared_ptr<IProgress>>  m_iprogressList;//共享引用

	std::list<std::weak_ptr<IProgress>> m_iprogressList;//弱引用

public:
	void addIProgress(const std::shared_ptr<IProgress>& iprogress){
		m_iprogressList.push_back(iprogress);
	}
	void removeIProgress(const std::shared_ptr<IProgress>& iprogress){
		m_iprogressList.remove(iprogress);
	}

protected:
	virtual void onProgress(float value)  
	{
		for (auto& progress : m_iprogressList){
			// progress->DoProgress(value);

			 //弱引用检查生命周期是否存在？
			std::shared_ptr<IProgress> s_progress=progress.lock();
			if ( s_progress!=nullptr ) {
                s_progress->DoProgress(value);
            }
		}

		//...记住弱引用删除
		for (auto& progress : m_iprogressList){
			 //弱引用检查生命周期是否存在？
			if(progress.expired()){
				removeIProgress(progress.lock());
			}
		}
	
	}
};


class FileDownloader: public Subject
{
	std::string m_filePath;
	int m_fileNumber;

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
			Subject::onProgress(progressValue);//通知观察者
		}

	}


	 void onProgress(float value) override{

		 Subject::onProgress(value);

		 //log..... 扩展操作
	 }
};

