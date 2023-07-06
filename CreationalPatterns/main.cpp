#include "FactoryMethod(工厂模式).h"
#include "AbstractFactory(抽象工厂模式).h"
#include "Builder(创建者模式).h"
#include "Prototype(原型模式).h"
#include "Singleton(单例模式).h"

int main() {
	//test_simple_factory();  // 不属于23设置模式  简单工厂模式
	//test_factory();  // 属于23种设计模式  工厂模式
	//test_abstract_factory(); // 属于23种设计模式  抽象工厂模式
	//test_builder(); // 属于23种设计模式  创建者模式
	//test_prototype(); // 属于23种设计模式  原型模式
	test_singleton(); // 属于23种设计模式  单例模式
	return 0;
}