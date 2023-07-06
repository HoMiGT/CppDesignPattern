#include "Adapter(适配器模式).h"
#include "Bridge(桥接模式).h"
#include "Composite(组合模式).h"
#include "Decorator(装饰模式).h"
#include "Facade(外观模式).h"
#include "Flyweight(享元模式).h"
#include "Proxy(代理模式).h"
#include "Filter(过滤器模式).h"

int main() {
	//test_adapter(); // 属于23种设计模式  适配器模式
	//test_bridge(); // 属于23种设计模式  桥接模式
	//test_composite(); // 属于23种设计模式  组合模式
	//test_decorator(); // 属于23种设计模式  装饰模式
	//test_facade(); // 属于23种设计模式  外观模式
	//test_flyweight(); // 属于23种设计模式  享元模式
	//test_proxy(); // 属于23种设计模式  代理模式
	test_filter();
	return 0;
}