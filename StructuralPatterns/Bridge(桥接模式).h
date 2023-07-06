#pragma once

/// <summary>
/// 桥接模式
/// 可将一个大类或一系列紧密相关的类拆分为抽象和实现俩个独立的层次结构，从而能在开发时分别使用
/// 解决 多对多 的问题，实现类之间组合，增加灵活性
/// 本质上还是一对一，其实将类型转换成了接口父类，通过定义接口父类与接口父类的关系来实现多对多
/// </summary>
namespace bridge {
	/// <summary>
	/// 变速箱
	/// </summary>
	class Transmission {
	public:
		virtual ~Transmission() {};
		virtual void install() = 0;
	};

	/// <summary>
	/// AT变速箱
	/// </summary>
	class AT :public Transmission {
	public:
		virtual void install() override {
			std::cout<< "Transmission AT is installed" << std::endl;
		}
	};

	/// <summary>
	/// 湿式双离合变速箱
	/// </summary>
	class WDCT :public Transmission {
	public:
		virtual void install() override {
			std::cout<< "Transmission WDCT is installed" << std::endl;
		}
	};

	class Car {
	public:
		Car(Transmission* transmission) {
			this->m_transmission = transmission;
		}
		virtual ~Car() {};
		virtual void installTransmission() = 0;

	protected:
		Transmission* m_transmission;
	};

	class Audi :public Car {
	public:
		Audi(Transmission* transmission)
			:Car(transmission)
		{}

		virtual void installTransmission() override {
			std::cout << "Audi:";
			this->m_transmission->install();
		}
	};
	
	class BMW :public Car {
	public:
		BMW(Transmission* transmission)
			:Car(transmission)
		{}

		virtual void installTransmission() override {
			std::cout << "BMW:";
			this->m_transmission->install();
		}
	};

	class Benz :public Car {
	public:
		Benz(Transmission* transmission)
			:Car(transmission)
		{}
		virtual void installTransmission() override {
			std::cout << "Benz:";
			this->m_transmission->install();
		}
	};

}

void test_bridge() {
	using namespace bridge;

	Transmission* tr = nullptr;
	Car* car = nullptr;

	tr = new WDCT();
	car = new Audi(tr);
	car->installTransmission();

	delete tr;
	tr = nullptr;
	delete car;
	car = nullptr;


	tr = new AT();
	car = new BMW(tr);
	car->installTransmission();

	delete car;
	car = nullptr;

	car = new Benz(tr);
	car->installTransmission();

	delete tr;
	tr = nullptr;
	delete car;
	car = nullptr;


}