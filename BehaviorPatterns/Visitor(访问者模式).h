#pragma once
#include <iostream>
#include <string>
#include <list>

/// <summary>
///  访问者模式
/// 把数据结构和对数据结构的操作解耦合，使得操作集合可相对自由地演化而不影响数据结构
/// </summary>
namespace visitor {
	class ParkElement;

	class Visitor {
	public:
		virtual ~Visitor(){}
		virtual void visit(ParkElement* parkElement) = 0;
	};

	class ParkElement {
	public:
		virtual ~ParkElement(){}
		virtual void accept(Visitor* visitor) = 0;
		virtual std::string getName() = 0;
	};

	class ParkA : public ParkElement {
	public:
		virtual ~ParkA(){}
		virtual void accept(Visitor* visitor) override {
			visitor->visit(this);
		}

		virtual std::string getName(){
			return "ParkA";
		}
	};

	class ParkB : public ParkElement {
	public:
		virtual ~ParkB() {}
		virtual void accept(Visitor* visitor) override {
			visitor->visit(this);
		}
		virtual std::string getName(){
			return "ParkB";
		}
	};

	class Park :public ParkElement {
	public:
		Park() {
			m_parks.clear();
		}

		void setParkElement(ParkElement* pe) {
			m_parks.push_back(pe);
		}
		std::string getName() {
			return "park";
		}
		virtual void accept(Visitor* visitor) override {
			for (auto it = m_parks.begin(); it != m_parks.end(); it++) {
				visitor->visit(*it);
			}
		}

	private:
		std::list<ParkElement*> m_parks;
	};


	class VisitorA :public Visitor {
	public:
		virtual ~VisitorA() {}
		virtual void visit(ParkElement* parkelement) override {
			std::cout << "VisitorA visit " << parkelement->getName() << std::endl;
		}
	};

	class VisitorB :public Visitor {
	public:
		virtual ~VisitorB() {}
		virtual void visit(ParkElement* parkelement) override {
			std::cout << "VisitorB visit " << parkelement->getName() << std::endl;
		}
	};

	class VisitorManager :public Visitor {
	public:
		virtual void visit(ParkElement* park)override {
			std::cout << "visitor Manager: " << park->getName() << std::endl;
		}
	};
}

void test_visitor() {
	using namespace visitor;
	Visitor* va = new VisitorA();
	Visitor* vb = new VisitorB();

	ParkElement *pa = new ParkA();
	ParkElement* pb = new ParkB();

	pa->accept(va);
	pb->accept(vb);

	delete pb;
	delete pa;
	delete vb;
	delete va;


	std::cout << std::endl << std::endl;

	pa = new ParkA();
	pb = new ParkB();

	Park* p = new Park();
	p->setParkElement(pa);
	p->setParkElement(pb);

	Visitor* vm = new VisitorManager();
	p->accept(vm);

	delete vm;
	delete p;
	delete pb;
	delete pa;

}