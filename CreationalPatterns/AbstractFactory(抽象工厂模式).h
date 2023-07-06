#pragma once
#include <iostream>

/// <summary>
/// 抽象工厂模式
/// 让你能创建一些系列相关的对象，而无需指定器具体类
/// 适合二维变化的场景   水果系列  每个水果的地域系列   系列下又有子系列
/// 对工厂方法进行工厂方法的二次接口改写 使得工厂方法可以生产工厂方法
/// 实体类实现接口类，又创建接口类依赖了原先的接口类
/// </summary>
namespace abstract_factory {
	class Fruit {
	public:
		virtual ~Fruit() {};
		virtual void sayName() = 0;
	};

	class LocalApple :public Fruit {
	public:
		virtual void sayName() {
			std::cout<<"I'm LocalApple"<<std::endl;
		}
	};

	class LocalOrange :public Fruit {
	public:
		virtual void sayName() {
			std::cout<<"I'm LocalOrange"<<std::endl;
		}
	};

	class ImportApple :public Fruit {
	public:
		virtual void sayName() {
			std::cout<<"I'm ImportApple"<<std::endl;
		}
	};

	class ImportOrange :public Fruit {
	public:
		virtual void sayName() {
			std::cout<<"I'm ImportOrange"<<std::endl;
		}
	};

	class Factory {
	public:
		virtual ~Factory() {}
		/// <summary>
		///  不符合开闭原则
		/// </summary>
		/// <returns></returns>
		virtual Fruit* createApple() = 0;
		virtual Fruit* createOrange() = 0;
	};

	class LocalFactory :public Factory {
	public:
		Fruit* createApple() {
			return new LocalApple();
		}

		Fruit* createOrange() {
			return new LocalOrange();
		}
	};

	class ImportFactory :public Factory {
	public:
		Fruit* createApple() {
			return new ImportApple();
		}
		Fruit* createOrange() {
			return new ImportOrange();
		}
	};

}

void test_abstract_factory() {
	using namespace abstract_factory;
	Factory* factory = new LocalFactory();
	Fruit* apple = factory->createApple();
	Fruit* orange = factory->createOrange();
	apple->sayName();
	orange->sayName();
	delete apple;
	delete orange;
	delete factory;
	factory = new ImportFactory();
	apple = factory->createApple();
	orange = factory->createOrange();
	apple->sayName();
	orange->sayName();
	delete apple;
	delete orange;
	delete factory;
}




