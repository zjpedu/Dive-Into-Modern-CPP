#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <list>
using namespace std;

//Policy-based Design
class MarkdownListStrategy
{
public:
	void start(ostringstream& oss) {}
	void end(ostringstream& oss) {}
	void add_list_item(ostringstream& oss, const string& item)
	{
		oss << " * " << item << endl;
	}
};

class HtmlListStrategy
{
public:
	void start(ostringstream& oss)
	{
		oss << "<ul>" << endl;
	}

	void end(ostringstream& oss)
	{
		oss << "</ul>" << endl;
	}

	void add_list_item(ostringstream& oss, const string& item)
	{
		oss << "<li>" << item << "</li>" << endl;
	}
};


/* 将具体的类型做成了模板参数，很巧妙 */
template <typename ListPolicy>
class TextProcessor
{
public:
	void clear()
	{
		oss.str("");
		oss.clear();
	}
	void append_list(const vector<string> items)
	{
		list_strategy.start(oss);
		for (auto& item : items)
			list_strategy.add_list_item(oss, item);
		list_strategy.end(oss);
	}
	string str() const { return oss.str(); }
private:
	ostringstream oss;
	ListPolicy list_strategy;
};



int main()
{
	// markdown
	TextProcessor<MarkdownListStrategy> tp1;
	tp1.append_list({"Policy", "Design", "Pattern"});
	cout << tp1.str() << endl;
	cout<<sizeof(tp1)<<endl;

	// html
	TextProcessor<HtmlListStrategy> tp2;
	tp2.append_list({"Policy", "Design", "Pattern"});
	cout << tp2.str() << endl;
	cout<<sizeof(tp2)<<endl;
	return 0;
}