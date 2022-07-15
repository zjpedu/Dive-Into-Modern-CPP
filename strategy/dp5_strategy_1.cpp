/*
	下面的设计实际上存在问题：当我们想要扩展输出格式，比如增加 JSON 时，需要修改 append_list，
	违背了 OCP 原则。 因此我们想使用策略模式重新设计该应用。
*/
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

enum class OutputFormat
{
	Markdown,
	Html,
	XML
};

class TextProcessor
{
public:
	void clear()
	{
	oss.str("");
	oss.clear();
	}
	void append_list(const vector<string>& items)
	{

	//开始
	if(_format==OutputFormat::Html)
		oss << "<ul>" << endl;
	else if(_format==OutputFormat::XML)
	{
		//...
	}

	//子项目
	for (auto& item : items)
	{
		if(_format==OutputFormat::Html)
		{
			oss << "<li>" << item << "</li>" << endl;
		}
		else if(_format==OutputFormat::Markdown)
		{
			oss << " * " << item << endl;
		}
		else if(_format==OutputFormat::XML)
		{
		//...
		}
	}

	//结束
	if(_format==OutputFormat::Html)
		oss << "</ul>" << endl;
	else if(_format==OutputFormat::XML)
	{
		//...
	}
	}

	void set_output_format(const OutputFormat format)
	{
	_format=format;
	}
	string str() const { return oss.str(); }
private:
	ostringstream oss;
	OutputFormat _format;
};

int main()
{
	// markdown
	TextProcessor tp;
	tp.set_output_format(OutputFormat::Markdown);
	tp.append_list({"Software", "Design", "Pattern"});
	cout << tp.str() << endl;

	// html
	tp.clear();
	tp.set_output_format(OutputFormat::Html);
	tp.append_list( {"Software", "Design", "Pattern"});
	cout << tp.str() << endl;

	return 0;
}