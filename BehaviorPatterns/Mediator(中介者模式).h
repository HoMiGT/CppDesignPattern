#pragma once
#include <iostream>
#include <string>

/// <summary>
///  中介者模式
/// 定义一个中介来封装系列对象之间的交互
/// 像一个回调类一样
/// 来互相依赖的类，通过中介者来解耦
/// </summary>
namespace mediator {
	class Mediator;
	class Person {
	public:
		Person(const std::string& name, int sex, int condition, Mediator* mediator) 
			:m_name(name),m_sex(sex),m_condition(condition),m_mediator(mediator)
		{}
		virtual ~Person(){}
		int getCondition() {
			return m_condition;
		}
		int getSex() {
			return m_sex;
		}
		std::string getName() {
			return m_name;
		}
		virtual void getParter(Person* p) = 0;

	protected:
		std::string m_name;
		int m_sex;
		int m_condition;
		Mediator* m_mediator;
	};

	class Mediator {
	public:
		void getParter() {
			if (m_man->getSex() == m_woman->getSex()) {
				std::cout <<"the same of sex" << std::endl;
				return;
			}
			if (m_man->getCondition() == m_woman->getCondition()) {
				std::cout << m_man->getName() << "==" << m_woman->getName() << std::endl;
			}
			else {
				std::cout << m_man->getName() << "!=" << m_woman->getName() << std::endl;
			}
		}

		void setMan(Person* man) {
			m_man = man;
		}
		void setWoman(Person* woman) {
			m_woman = woman;
		}

	private:
		Person* m_man;
		Person* m_woman;
	};

	class Woman :public Person {
	public:
		Woman(const std::string&  name,int sex,int condition,Mediator* mediator)
			:Person(name,sex,condition,mediator)
		{}
		int getCondition() {
			return m_condition;
		}
		virtual void getParter(Person*p) override{
			m_mediator->setWoman(this);
			m_mediator->setMan(p);
			m_mediator->getParter();
		}
	};

	class Man :public Person {
	public:
		Man(const std::string& name,int sex,int condition,Mediator* mediator)
			:Person(name,sex,condition,mediator)
		{}
		int getCondition() {
			return m_condition;
		}
		virtual void getParter(Person* p) override {
			m_mediator->setMan(this);
			m_mediator->setWoman(p);
			m_mediator->getParter();
		}
	};

}

void test_mediator() {
	using namespace mediator;
	Mediator* mediator = new Mediator();

	Person* woman1 = new Woman("woman1",0,5,mediator);
	Person* woman2 = new Woman("woman2", 0, 5, mediator);
	Person* man1 = new Man("man1", 1, 6,mediator);
	Person* man2 =new Man("man2", 1, 5,mediator);

	woman1->getParter(woman2);
	woman1->getParter(man1);
	woman2->getParter(man1);
	woman2->getParter(man2);

	delete woman1;
	delete woman2;
	delete man1;
	delete man2;
	delete mediator;
}