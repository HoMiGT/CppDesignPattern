#pragma once
#include <iostream>

/// <summary>
/// 原型模式
/// 让你能够复制已有对象，而又无需使代码依赖它们所属的类
///  方便写函数接口，多个类型的对象都可以转成同一个类型
/// </summary>
namespace prototype {
	
	class  Potato{
	public:
		virtual ~Potato() {}
		virtual Potato* clone() = 0;
		virtual void print() = 0;
	};


	class CPotato :public Potato {
	public:
		CPotato() {
			m_name = "";
			m_age = 0;
			m_des = nullptr;
		}
		CPotato(const std::string name, int age,const char* des) {
			m_name = name;
			m_age = age;
			m_des = new char[strlen(des) + 1];
			strcpy(m_des, des);
		}
		~CPotato() {
			if (m_des != nullptr) {
				delete[] m_des;
				m_des = nullptr;
			}
		}

		virtual Potato* clone() {
			CPotato* tmp = new CPotato();
			tmp->m_name = this->m_name;
			tmp->m_age = this->m_age;
			tmp->m_des = new char[strlen(this->m_des) + 1];  // 深拷贝
			strcpy(tmp->m_des, this->m_des);
			return tmp;
		}

		virtual void print() {
			std::cout << m_name << std::endl;
			std::cout << m_age << std::endl;
			std::cout << m_des << std::endl;
		}


	private:
		std::string m_name;
		int m_age;
		char* m_des;
	
	};
}

void test_prototype() {
	using namespace prototype;
	Potato* p1 = new CPotato("p1", 1, "p1 des");
	Potato* p2 = p1->clone();
	p1->print();
	p2->print();
	delete p1;
	p1 = nullptr;
	delete p2;
	p2 = nullptr;
}

