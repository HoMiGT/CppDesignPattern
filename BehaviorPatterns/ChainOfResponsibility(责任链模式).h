#pragma once
#include <iostream>

/// <summary>
/// 责任链模式
/// 允许你将请求沿着处理者链进行发送。收到请求后，每个处理者均可对请求进行处理，或将其传递给链上的下个处理者
/// 类似于装饰器，只不过人为强制除了执行自己的行为，还要指定了顺序，执行调用执行下一个对象的行为
/// </summary>
namespace chainOfResponsibility {
	class CarHandle {
	public:
		CarHandle() {
			m_handle = nullptr;
		}
		
		virtual ~CarHandle() {}
		virtual void handleRequest() = 0;
		virtual CarHandle* setNextHandle(CarHandle* handle) {
			m_handle = handle;
			return m_handle;
		}
	protected:
		CarHandle* m_handle;
	};

	class CarTransmissionHandle :public CarHandle {
	public:
		virtual void handleRequest() override {
			std::cout << "CarTransmissionHandle" << std::endl;
			if (m_handle != nullptr) {
				m_handle->handleRequest();
			}
		}
	};

	class CarBodyHandle :public CarHandle {
	public:
		virtual void handleRequest() override {
			std::cout << "CarBodyHandle" << std::endl;
			if (m_handle != nullptr) {
				m_handle->handleRequest();
			}
		}
	};

	class CarTireHandle :public CarHandle {
	public:
		virtual void handleRequest() override {
			std::cout << "CarTireHandle" << std::endl;
			if (m_handle != nullptr) {
				m_handle->handleRequest();
			}
		}
	};

	class CarEngineHandle :public CarHandle {
	public:
		virtual void handleRequest() override {
			std::cout << "CarEngineHandle" << std::endl;
			if (m_handle != nullptr) {
				m_handle->handleRequest();
			}
		}
	};

}

void test_chainOfResponsibility() {
	using namespace chainOfResponsibility;

	CarHandle* transmission = new CarTransmissionHandle();
	CarHandle* body = new CarBodyHandle();
	CarHandle* tire = new CarTireHandle();
	CarHandle* engine = new CarEngineHandle();

	// 写死调用顺序
	transmission->handleRequest();
	body->handleRequest();
	tire->handleRequest();
	engine->handleRequest();

	std::cout << "***************************"  << std::endl;

	// 可以设置顺序
	transmission->setNextHandle(tire)->setNextHandle(body)->setNextHandle(engine);
	transmission->handleRequest();

	delete engine;
	delete tire;
	delete body;
	delete transmission;

}


