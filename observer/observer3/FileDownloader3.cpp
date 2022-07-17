class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};


class FileDownloader
{
	string m_filePath;
	int m_fileNumber;

	list<shared_ptr<IProgress>>  m_iprogressList;   // 一组观察者
	
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
			onProgress(progressValue);
		}

	}

	void addIProgress(const shared_ptr<IProgress>& iprogress){
		m_iprogressList.push_back(iprogress);
	}

	void removeIProgress(const shared_ptr<IProgress>& iprogress){
		m_iprogressList.remove(iprogress);
	}
protected:
	void onProgress(float value)  
	{
		for (auto& progress : m_iprogressList){
			progress->DoProgress(value);
		}
	}
};