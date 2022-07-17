#include <list>
#include <iostream>
using namespace std;

// struct ProgressObserver{
// 	void operator()(float value)
// 	{

// 	}
// };


template<typename ProgressObserver>
class Subject
{
private:
	list<ProgressObserver>  m_iprogressList;

public:
	void addIProgress(const ProgressObserver& iprogress){
		m_iprogressList.push_back(iprogress);
	}
	void removeIProgress(const ProgressObserver& iprogress){
		m_iprogressList.remove(iprogress);
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
		//1.下载动作

		//2.设置进度
		for (int i = 0; i < m_fileNumber; i++){
			//...
			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
			onProgress(progressValue);//通知观察者
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

	FileDownloader<ConsoleProgressObserver> fd("https://boolan.com/bigfile", 15);
	//FileDownloader<ProgressBarObserver> fd2(...);

	ConsoleProgressObserver pob(101);
	fd.addIProgress(pob);
	fd.download();

	fd.removeIProgress(pob);
	fd.download();

}