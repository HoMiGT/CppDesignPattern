#pragma once
#include <iostream>
#include <list>

/// <summary>
/// 组合模式
/// 你可以使用将对象组合成树状结构，并且能够像使用独立对象一样使用它们
/// 单个对象和多个对象具有一致的接口
/// 不同类型的类，可以通过继承接口类，都转换成接口类来进行函数调用，实现组合的效果
/// </summary>
namespace composite {

	class IFile {
	public:
		virtual ~IFile(){}
		virtual void display() = 0;
		virtual int add(IFile* iFile) = 0;
		virtual int remove(IFile* iFile) = 0;
		virtual std::list<IFile*>* getChild() = 0;
	};

	class File :public IFile {
	public:
		File(std::string name) {
			this->m_name = name;
		}
		virtual void display() override {
			std::cout << "File:" << this->m_name << std::endl;
		}
		virtual int add(IFile* iFile) override {
			return -1;
		}
		virtual int remove(IFile* iFile) override {
			return -1;
		}

		virtual std::list<IFile*>* getChild() override {
			return nullptr;
		}

	private:
		std::string m_name;
	};

	class Dir :public IFile {
	public:
		Dir(std::string name) {
			this->m_name = name;
			this->m_list = new std::list<IFile*>;
			this->m_list->clear();
		}

		virtual ~Dir(){
			if (m_list) {
				delete m_list;
				m_list = nullptr;
			}
		}

		virtual void display() override {
			std::cout << "Dir:" << this->m_name << std::endl;
		}

		virtual int add(IFile* iFile) {
			this->m_list->push_back(iFile);
			return 0;
		}

		virtual int remove(IFile* iFile) {
			this->m_list->remove(iFile);
			return 0;
		}

		virtual std::list<IFile*>* getChild() {
			return this->m_list;
		}

	private:
		std::string m_name;
		std::list<IFile*>* m_list;
	};

	void showTree(IFile* root,int level) {
		if (!root) {
			return;
		}

		for (int i = 0; i < level; ++i) {
			std::cout << "\t";
		}

		root->display();

		std::list<IFile*>* my_list = root->getChild();

		// 若子节点为文件，直接显示文件名
		if (!my_list) {
			return;
		}
		else {
			// 若子节点为文件夹，则递归调用
			for (std::list<IFile*>::iterator it = my_list->begin(); it != my_list->end(); ++it) {
				if (!(*it)->getChild()) {
					for (int i = 0; i < level + 1; ++i) {
						std::cout << "\t";
					}
					(*it)->display();
				}
				else {
					showTree(*it, level + 1);
				}
			}
		}
	}

}


void test_composite() {
	using namespace composite;

	Dir* root = new Dir("C");
	File* file1 = new File("file1");
	root->add(file1);

	Dir* dir1 = new Dir("dir1");
	File* file2 = new File("file2");
	dir1->add(file2);
	root->add(dir1);

	showTree(root, 0);

	delete file1;
	file1 = nullptr;
	delete file2;
	file2 = nullptr;
	delete dir1;
	delete root;


}