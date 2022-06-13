#include<cstdio>
#include <iostream>
#include <cassert>
#include <type_traits>

#define call(...) ({ *(++top) = (Frame) { .pc = 0, __VA_ARGS__ }; })
#define ret()     ({ top--; })
#define goto(loc) ({ f->pc = (loc) - 1; })

struct Frame{
	int pc, n;
	char from, to, via;
};


// //凡是你当前程序想要保存的内存状态,我们实际上都能够写到这个 Frame,因为这就是当前的 stack frame
// struct Copy_Frame{
//     Frame* undo_stk;
//     Frame* redo_stk;
// };

void checkpoint(Frame* stk){
	// 把当时的 stk 信息写入到 nvm 上
	// std::cout << "function name: " << __PRETTY_FUNCTION__ << ", Line: " << __LINE__ << std::endl;
	std::cout << stk->pc << " " << stk->n  << " " << stk->from << " " << stk->to << " " << stk->via << std::endl;
}

// 非递归
void hanoi(int n, char from, char to, char via) {
	Frame stk[64], *top = stk - 1;
	call(n, from, to, via);
	for (Frame *f; (f = top) >= stk; f->pc++) {
		// checkpoint(stk);  // 设计不同的 checkpoint 方法
		switch (f->pc) {
			case 0: if (f->n == 1) { printf("%c -> %c\n", f->from, f->to); goto(4); } break;
			case 1: call(f->n - 1, f->from, f->via, f->to);   break;
			case 2: call(       1, f->from, f->to,  f->via);  break;
			case 3: call(f->n - 1, f->via,  f->to,  f->from); break;
			case 4: ret();                                    break;
			default: assert(0);
		}
	}
}

// 递归版本
void hanoid(int n, char from, char to, char via) {
	if (n == 1) {
		printf("%c -> %c\n", from, to);
	}
	else {
		hanoid(n - 1, from, via, to);
		hanoid(1,     from, to,  via);
		hanoid(n - 1, via,  to,  from);
	}
	return;
}

int main(){
	hanoi(3, 'A', 'C', 'B');
	std::cout << "------" << std::endl;
	hanoid(3, 'A', 'C', 'B');
	return 0;
}