#pragma once
#include <iostream>
#include <string>

/// <summary>
/// 备忘录模式
/// 让你在不暴露对象实现细节的情况下保存和恢复对象之前的状态
/// </summary>
namespace memento {
	class Memento {
	public:
		Memento(const std::string& name, int age) 
			:m_name(name),m_age(age)
		{}
		std::string getName() {
			return m_name;
		}
		void setName(const std::string& name) {
			m_name = name;
		}

		int getAge() {
			return m_age;
		}

		void setAge(int age) {
			m_age = age;
		}
	private:
		std::string m_name;
		int m_age;
		
	};

	class Person {
	public:
		Person(const std::string& name, int age)
			:m_name(name), m_age(age)
		{}
		void showInfo() {
			std::cout<<"name:"<<m_name<<" ,age:" <<m_age<< std::endl;
		}
		std::string getName() {
			return m_name;
		}
		int getAge() {
			return m_age;
		}
		void setAge(int age) {
			m_age = age;
		}
		Memento* createMemento() {
			return new Memento(m_name, m_age);
		}

		void setMemento(Memento* memento) {
			m_name = memento->getName();
			m_age = memento->getAge();
		}

	private:
		std::string m_name;
		int m_age;
	};


	class Caretaker {
	public:
		Caretaker(Memento* mem) {
			this->m_memento = mem;
		}
		Memento* getMemento() {
			return m_memento;
		}
		void setMemento(Memento* mem) {
			this->m_memento = mem;
		}

	private:
		Memento* m_memento;
	};
}

void test_memento() {
	using namespace memento;

	Person* p = new Person("zhangsan", 20);
	p->showInfo();

	Memento* mem = p->createMemento();
	Caretaker* care = new Caretaker(mem);

	p->setAge(18);
	p->showInfo();

	p->setMemento(care->getMemento());
	p->showInfo();

	delete care;
	delete mem;
	delete p;

}
