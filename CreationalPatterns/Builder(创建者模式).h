#pragma once
#include <iostream>
#include <string>

/// <summary>
/// 创建者模式
/// 使你可以分步骤创建复杂对象，该模式允许你使用相同的创建代码生成不同类型和形式的对象
/// 不同的建造商构建的东西不通，但是建造一个房子的步骤是固定的，
///  接口类依赖了实体类，新的实体类实现接口类，再由新的实体类参数传入接口类类型的实体类
/// </summary>
namespace builder {
	class House {
	public:
		void setFloor(std::string floor) {
			m_floor = floor;
		}
		void setWall(std::string wall) {
			m_wall = wall;
		}
		void setDoor(std::string door) {
			m_door = door;
		}
		void show() {
			std::cout << "m_floor: " << m_floor << std::endl;
			std::cout << "m_wall: " << m_wall << std::endl;
			std::cout << "m_door:" << m_door << std::endl;
		}
	private:
		std::string m_floor;
		std::string m_wall;
		std::string m_door;
	};

	class Builder {
	public:
		virtual ~Builder(){}
		virtual void makeFloor() = 0;
		virtual void makeWall() = 0;
		virtual void makeDoor() = 0;
		virtual House* getHouse() = 0;
	};

	class FlatBuilder :public Builder {
	public:
		FlatBuilder() {
			m_house = new House();
		}

		virtual ~FlatBuilder() {
			if (m_house != nullptr) {
				delete m_house;
				m_house = nullptr;
			}
		}

		void makeFloor() {
			m_house->setFloor("flat floor");
		}

		void makeWall() {
			m_house->setWall("flat wall");
		}

		void makeDoor() {
			m_house->setDoor("flat door");
		}

		House* getHouse() {
			return m_house;
		}
		
	private:
		House* m_house;
	};

	class VillaBuilder :public Builder {
	public:
		VillaBuilder() {
			m_house = new House();
		}
		virtual ~VillaBuilder() {
			if (m_house != nullptr) {
				delete m_house;
				m_house = nullptr;
			}
		}

		void makeFloor() {
			m_house->setFloor("villa floor");
		}

		void makeWall() {
			m_house->setWall("villa wall");
		}

		void makeDoor() {
			m_house->setDoor("villa door");
		}

		House* getHouse() {
			return m_house;
		}

	private:
		House* m_house;
	};


	class Director {
	public:
		void setBuild(Builder* builder) {
			m_builder = builder;
		}

		House* construct() {
			m_builder->makeFloor();
			m_builder->makeWall();
			m_builder->makeDoor();
			return m_builder->getHouse();
		}
	private:
		Builder* m_builder;
	};
}

void test_builder() {
	using namespace builder;
	
	Director* director = new Director();
	Builder* builder = nullptr;
	House* house = nullptr;

	builder = new VillaBuilder;
	director->setBuild(builder);
	director->construct();
	house = builder->getHouse();
	house->show();

	delete builder;
	builder = nullptr;

	builder = new FlatBuilder;
	director->setBuild(builder);
	director->construct();
	house = builder->getHouse();
	house->show();


	delete builder;
	delete director;

}


