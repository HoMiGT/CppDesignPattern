#pragma once

/// <summary>
/// 装饰模式 
/// 允许你通过将对象放入包含行为的特殊封装对象中来为原对象绑定新的行为
/// 通过继承来扩展功能，但是不改变原有类的结构
/// 多个类去继承接口类，并且实例化的时候将该接口类传入，
/// 进而在实现的函数里增加其他的函数，进而扩展行为
/// </summary>
namespace decorator {
	class Person {
	public:
		virtual ~Person() {};
		virtual void walk() = 0;
	};

	class WalkPerson :public Person {
	public:
		virtual void walk() override {
			std::cout << "Person can walk" << std::endl;
		}
	};

	class FlyPerson :public Person {
	public:
		FlyPerson(Person* person) {
			this->m_person = person;
		}
		virtual void walk() override {
			m_person->walk();
			fly();
		}

		void fly() {
			std::cout << "Person can fly" << std::endl;
		}
	private:
		Person* m_person;
	};


	class SwimPerson :public Person {
	public:
		SwimPerson(Person* person) {
			this->m_person = person;
		}

		virtual void walk() override {
			m_person->walk();
			swim();
		}

		void swim() {
			std::cout << "Person can swim" << std::endl;
		}

	private:
		Person* m_person;
		
	};

}

void test_decorator() {
	using namespace decorator;

	Person* person = new WalkPerson();
	person->walk();
	std::cout << std::endl;

	Person* flyPerson = new FlyPerson(person);
	flyPerson->walk();
	std::cout << std::endl;

	Person* swimPerson = new SwimPerson(flyPerson);
	swimPerson->walk();
	std::cout << std::endl;

	delete swimPerson;
	delete flyPerson;
	delete person;

}