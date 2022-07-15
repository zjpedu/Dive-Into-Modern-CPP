#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

/* 虚基类不能创建对象，但是能够声明该类型的指针，利用多态性绑定具体类型 */
class ListStrategy
{
public:
	virtual ~ListStrategy() = default;

	/* 抽象出的业务逻辑，导出类必须要实现这种纯虚函数，并且都得是 public */
	virtual void add_list_item(ostringstream& oss, const string& item)=0;
	virtual void start(ostringstream& oss)=0;
	virtual void end(ostringstream& oss) =0;
};



class MarkdownListStrategy : public ListStrategy
{
public:
	void add_list_item(ostringstream& oss, const string& item) override
	{
		oss << " * " << item << endl;
	}

	void start(ostringstream& oss) override {}
	void end(ostringstream& oss) override {}
};

class HtmlListStrategy : public ListStrategy
{
public:
	void start(ostringstream& oss) override
	{
		oss << "<ul>" << endl;
	}

	void end(ostringstream& oss) override
	{
		oss << "</ul>" << endl;
	}

	void add_list_item(ostringstream& oss, const string& item) override
	{
		oss << "<li>" << item << "</li>" << endl;
	}
};

//扩展
struct XMLListStrategy :  ListStrategy
{
	void add_list_item(ostringstream& oss, const string& item) override {}
	void start(ostringstream& oss) override {}
	void end(ostringstream& oss) override {}
};

class TextProcessor
{
public:

	TextProcessor(const TextProcessor& rhs)=delete;
	TextProcessor(TextProcessor&& rhs)=default;
	/* std::unique_ptr 没有 copy ctor，因此需要 std::move */
	TextProcessor(unique_ptr<ListStrategy> ls):
	list_strategy(std::move(ls))
	{

	}
	void clear()
	{
		oss.str("");
		oss.clear();
	}

	//稳定--> 复用，动态绑定具体实现
	void append_list(const vector<string> items)
	{
		list_strategy->start(oss);
		for (auto& item : items)
			list_strategy->add_list_item(oss, item);
		list_strategy->end(oss);
	}
	string str() const { return oss.str(); }
private:
	ostringstream oss;
	//ListStrategy list_s;
	//ListStrategy* list_strategy;
	unique_ptr<ListStrategy> list_strategy;
};

int main()
{
	// markdown
	TextProcessor tp1(std::make_unique<MarkdownListStrategy>());
	tp1.append_list({"Software", "Design", "Pattern"});
	std::cout << tp1.str() << std::endl;

	TextProcessor tp2(std::make_unique<HtmlListStrategy>());
	tp2.append_list({"Software", "Design", "Pattern"});
	std::cout << tp2.str() << std::endl;
	return 0;
}