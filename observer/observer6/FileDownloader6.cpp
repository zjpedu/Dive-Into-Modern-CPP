#include <list>
#include <iostream>
using namespace std;


using ProgressListener = std::function<void(float)>;  // 缺点失去了前面的比较相等的问题


class Subject
{
private:
	list<ProgressListener>  m_iprogressList;//共享引用

public:
	void addIProgress(const ProgressListener& iprogress){
		m_iprogressList.push_back(iprogress);
	}

	// void removeIProgress(const ProgressListener& iprogress){
	// 	m_iprogressList.remove(iprogress);
	// }

protected:
	void onProgress(float value)  
	{
		for (auto& progress : m_iprogressList){
			progress(value);
		}
	}
};


class FileDownloader: public Subject
{
	string m_filePath;
	int m_fileNumber;

public:
	FileDownloader(const string& filePath, int fileNumber) :
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
};


struct ConsoleProgressObserver
{
	void operator()(float value)
	{
		cout<<". ";
	}

};


int main(){

	FileDownloader fd("https://www.baidu.com", 10);

	fd.addIProgress(ConsoleProgressObserver{});
	fd.addIProgress([](float value){ cout<< value<<endl;});
	fd.addIProgress([](float value){ cout<< value<<endl;});
	fd.download();

}