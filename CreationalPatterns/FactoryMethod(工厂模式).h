#pragma once
#include <iostream>

/// <summary>
/// 简单工厂模式 不符合23种 设计模式 
/// </summary>
namespace simple_factory {
	class Fruit {
	public:
		virtual ~Fruit() {}
		virtual void sayName() = 0;
	};

	class Apple : public Fruit {
	public:
		virtual void sayName() {
			std::cout << "I am an apple." << std::endl;
		}
	};

	class Orange : public Fruit {
	public:
		virtual void sayName() {
			std::cout << "I am an orange." << std::endl;
		}
	};

	class Factory {
	public:
		Fruit* create(const char* p) {
			if (strcmp(p, "apple")) {
				return new Apple();
			}
			else if (strcmp(p, "orange")) {
				return new Orange();
			}
			else {
				return nullptr;
			}
		}
	};
}

void test_simple_factory() {
	using namespace simple_factory;
	Factory factory;
	Fruit* apple = factory.create("apple");
	Fruit* orange = factory.create("orange");
	apple->sayName();
	orange->sayName();
	delete apple;
	delete orange;
}

/// <summary>
/// 工厂方法模式
/// 在父类中提供创建对象的接口以允许子类决定实例化对象的类型
/// 适合一维变化的场景  同一系列分类，很多种水果都可以归类为水果
/// 实体类实现了接口类
/// </summary>
namespace factory {
	class Fruit {
	public:
		virtual ~Fruit() {}
		virtual void sayName() = 0;
	};

	class Apple : public Fruit {
	public:	
		virtual void sayName() {
			std::cout << "I am an apple." << std::endl;
		}
	};

	class Orange : public Fruit {
	public:
		virtual void sayName() {
			std::cout << "I am an orange." << std::endl;
		}
	};

	class Factory {
	public:
		virtual ~Factory() { }
		virtual Fruit* create() = 0;
	};

	class AppleFactory : public Factory {
	public:
		Fruit* create() {
			return new Apple();
		}
	};

	class OrangeFactory : public Factory {
	public:
		Fruit* create() {
			return new Orange();
		}
	};
}

void test_factory() {
	using namespace factory;
	Factory* fac = nullptr;
	Fruit* fruit = nullptr;

	fac = new AppleFactory();
	fruit = fac->create();
	fruit->sayName();

	delete fruit;
	delete fac;

	fac = new OrangeFactory();
	fruit = fac->create();
	fruit->sayName();

	delete fruit;
	delete fac;


}



