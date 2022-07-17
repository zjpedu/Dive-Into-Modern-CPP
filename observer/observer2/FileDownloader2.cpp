class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};

class FileDownloader
{
	string m_filePath;
	int m_fileNumber;

	shared_ptr<IProgress>  m_iprogress;   // 观察者
	
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
			m_iprogress->DoProgress(value);
		}

	}

	void setProgress(shared_ptr<IProgress>  progress)
	{
		m_iprogress=progress;
	}
};