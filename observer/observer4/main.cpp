#include "MainForm4.cpp"

int main(){
	std::shared_ptr<MainForm> mainForm = std::make_shared<MainForm>();  // 对的
	// MainForm* mainForm = new MainForm();  // 抛出异常, why?
	mainForm->Button1_Click();
	return 0;
}