#include "ChainOfResponsibility(责任链模式).h"
#include "Command(命令模式).h"
#include "Interpreter(解释器模式).h"
#include "Iterator(迭代器模式).h"
#include "Mediator(中介者模式).h"
#include "Memento(备忘录模式).h"
#include "Observer(观察者模式).h"
#include "State(状态模式).h"
#include "Strategy(策略模式).h"
#include "TemplageMethod(模板方法模式).h"
#include "Visitor(访问者模式).h"

int main() {
	//test_chainOfResponsibility(); // 责任链模式
	//test_command(); // 命令模式
	//test_interpreter(); // 解释器模式
	//test_mediator(); // 中介者模式
	test_memento(); // 备忘录模式
	return 0;
}