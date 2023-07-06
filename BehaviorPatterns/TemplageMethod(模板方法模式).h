#pragma once

/// <summary>
///  模板方法模式
///  将一组方法封装起来，隐藏实现细节，提供一个接口
/// </summary>
namespace templagemethod {
	class CarFactory {
	public:
		virtual ~CarFactory() {};
		virtual void produteTransmission() = 0;
		virtual void produteEngine() = 0;
		virtual void produteBody() = 0;
		virtual void produteTire() = 0;

		void produte() {
			produteTransmission();
			produteEngine();
			produteBody();
			produteTire();
		}
	};

	class CarFactoryAudi : public CarFactory {
	public:
		virtual void produteTransmission() override {
			std::cout << "Audi Transmission is produted" << std::endl;
		}
		virtual void produteEngine() override {
			std::cout << "Audi Engine is produted" << std::endl;
		}
		virtual void produteBody() override {
			std::cout << "Audi Body is produted" << std::endl;
		}
		virtual void produteTire() override {
			std::cout << "Audi Tire is produted" << std::endl;
		}
	};

	class CarFactoryBenz : public CarFactory {
	public:
		virtual void produteTransmission() override {
			std::cout << "Benz Transmission is produted" << std::endl;
		}
		virtual void produteEngine() override {
			std::cout << "Benz Engine is produted" << std::endl;
		}
		virtual void produteBody() override {
			std::cout << "Benz Body is produted" << std::endl;
		}
		virtual void produteTire() override {
			std::cout << "Benz Tire is produted" << std::endl;
		}
	};
	class CarFactoryBMW : public CarFactory {
	public:
		virtual void produteTransmission() override {
			std::cout << "BMW Transmission is produted" << std::endl;
		}
		virtual void produteEngine() override {
			std::cout << "BMW Engine is produted" << std::endl;
		}
		virtual void produteBody() override {
			std::cout << "BMW Body is produted" << std::endl;
		}
		virtual void produteTire() override {
			std::cout << "BMW Tire is produted" << std::endl;
		}
	};

}

void test_templagemethod() {
	using namespace templagemethod;
	CarFactory* carFactory = new CarFactoryAudi();
	carFactory->produte();
	delete carFactory;

	std::cout << std::endl;

	carFactory = new CarFactoryBenz();
	carFactory->produte();
	delete carFactory;

	std::cout << std::endl;

	carFactory = new CarFactoryBMW();
	carFactory->produte();
	delete carFactory;
}