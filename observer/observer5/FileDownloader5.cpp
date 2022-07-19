#include <list>
#include <iostream>
using namespace std;

// 隐式约定
// struct ProgressObserver{
// 	void operator()(float value)
// 	{

// 	}
// };


template<typename ProgressObserver>
class Subject
{
private:
	list<ProgressObserver>  m_iprogressList;  // 所有的观察者就是遵从上述隐式约定的函数对象

public:
	void addIProgress(const ProgressObserver& iprogress){
		m_iprogressList.push_back(iprogress);
	}
	void removeIProgress(const ProgressObserver& iprogress){
		m_iprogressList.remove(iprogress);  // list 的 remove 函数需要调用 operator== 操作符，所以需要这个观察者对象重载 operator== 才行，否则报错
	}

protected:
	void onProgress(float value)  
	{
		for (auto& progress : m_iprogressList){
			progress(value);//隐式约定
		}
	}
};


template<typename ProgressObserver>
class FileDownloader: public Subject<ProgressObserver>
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
			Subject<ProgressObserver>::onProgress(progressValue);//通知观察者
		}

	}
};


struct ConsoleProgressObserver
{
	int _id;
	ConsoleProgressObserver(int id):_id(id){

	}

	friend bool operator==(const ConsoleProgressObserver& left, const ConsoleProgressObserver& right)
	{
		return left._id==right._id;
	}

	void operator()(float value)
	{
		cout<<". ";
	}

};

struct ProgressBarObserver
{
	void operator()(float value)
	{
		//....
	}
};


int main(){

	FileDownloader<ConsoleProgressObserver> fd("https://baidu.com", 15);
	//FileDownloader<ProgressBarObserver> fd2(...);

	ConsoleProgressObserver pob(101);
	fd.addIProgress(pob);
	fd.download();

	fd.removeIProgress(pob);
	fd.download();

}