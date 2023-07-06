#pragma once
#include <iostream>
#include <map>
#include <utility>

/// <summary>
/// 享元模式
/// 摒弃了在每个对象中保存所有数据得方式，通过共享多个对象所共有的相同状态，让你能在有限的内存容量中载入更多对象
/// 共享元素，以共享的方式来避免大量拥有相同内容对象的开销
/// 本质上是将对象的属性分为内部状态和外部状态，内部状态是不变的，外部状态是变化的
/// 一个类只做信息存储，一个类实现对自己的静态单例，并对信息存储的类，进行对外共享。
/// 再一个类来调用操作类，既可以使用数据，实现了内部状态不变，外部状态可变。
/// 仅在程序必须支持大量对象且没有足够的内存容量时使用享元模式。
/// </summary>
namespace flyweight {
	/// <summary>
	/// 享元 内部状态
	/// </summary>
	class TreeModel {
	public:
		TreeModel(std::string mid) {
			this->m_modeID = mid;
		}
	private:
		std::string m_modeID;
	};

	/// <summary>
	/// 享元工厂: 单例，缓存已创建的享元
	/// </summary>
	class TreeModelFactory {
	private:
		TreeModelFactory() {
			m_map.clear();
		}
	public:
		~TreeModelFactory() {
			while (!m_map.empty()) {
				std::map<std::string, TreeModel*>::iterator it = m_map.begin();
				TreeModel* p = it->second;
				m_map.erase(it);
				delete p;
			}
		}

		static TreeModelFactory* getInstance() {  // 非线程安全
			if (m_instance == nullptr) {
				m_instance = new TreeModelFactory();
			}
			return m_instance;
		}

		TreeModel* getTreeModel(std::string id) {
			std::map<std::string, TreeModel*>::iterator it = m_map.find(id);
			if (it == m_map.end()) {
				TreeModel* tmp = new TreeModel(id);
				m_map.insert(std::pair<std::string, TreeModel*>(id, tmp));
				return tmp;
			}
			return it->second;
		}

	private:
		static TreeModelFactory* m_instance;
		std::map<std::string, TreeModel*> m_map;
	};
	TreeModelFactory* TreeModelFactory::m_instance = nullptr;


	// 变量：外部状态
	struct Position {
		int x;
		int y;
	};

	class Tree {
	public:
		Tree(std::string mid, int x, int y) {
			TreeModelFactory* factory = TreeModelFactory::getInstance();
			m_model = factory->getTreeModel(mid);
			m_pos.x = x;
			m_pos.y = y;
		}

	private:
		TreeModel* m_model;
		Position m_pos;
	};
}

void test_flyweight() {
	using namespace flyweight;

	std::string mid1 = "mod_001.fbx";
	Tree* t1_1 = new Tree(mid1, 10, 10);
	Tree* t1_2 = new Tree(mid1, 110, 110);

	std::string mid2 = "mod_002.fbx";
	Tree* t2_1 = new Tree(mid2, 20, 20);
	Tree* t2_2 = new Tree(mid2, 210, 210);

}











