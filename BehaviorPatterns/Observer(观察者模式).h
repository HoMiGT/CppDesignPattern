#pragma once
#include <iostream>
#include <string>

/// <summary>
/// 观察者模式
/// 定义对象之间一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并自动更新
/// </summary>
namespace observer {
	class Publisher;

	class Subscriber {
	public:
		virtual void noNotify(Publisher* publisher) = 0;
		virtual void update(const std::string& state) = 0;
	};

	class Publisher {
	public:
		virtual void addObserver(Subscriber* subscriber) = 0;
		virtual void notify() = 0;

		virtual std::string getState() = 0;
		virtual void setState(const std::string& state) = 0;
	};

	class EmployeeSubscriber :public Subscriber {
	public:
		void noNotify(Publisher* publisher) override {
			std::string state = publisher->getState();
			update(state);
		}

		void update(const std::string& state) {
			std::cout << "employee:" << state << std::endl;
		}
	};

	class SecretaryPublisher :public Publisher {
	public:
		void addObserver(Subscriber* player) {
			m_list.push_back(player);
		}

		void notify() {
			for (auto it = m_list.begin(); it != m_list.end(); ++it) {
				(*it)->noNotify(this);
			}
		}

		std::string getState() {
			return m_state;
		}

		void setState(const std::string& state) {
			m_state = state;
			notify();
		}

	private:
		std::string m_state;
		std::list<Subscriber*> m_list;
	};

}

void test_observer() {
	using namespace observer;

	SecretaryPublisher* publisher = new SecretaryPublisher();
	EmployeeSubscriber* subscriber1 = new EmployeeSubscriber();
	EmployeeSubscriber* subscriber2 = new EmployeeSubscriber();

	publisher->addObserver(subscriber1);
	publisher->addObserver(subscriber2);

	publisher->setState("boss is coming");
	publisher->setState("boss is leaving");

	delete subscriber2;
	delete subscriber1;
	delete publisher;

}