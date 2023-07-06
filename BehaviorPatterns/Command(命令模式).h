#pragma once
#include <iostream>
#include <list>

/// <summary>
/// 命令模式
/// 它可以将请求转换为一个包含与请求相关的所有信息的独立对象。该转换让你能根据不同的请求将方法
/// 参数化、延迟请求执行或将其放入队列中，且能实现可撤销操作
/// 一个对象调用另一个对象的一般过程：创建目标对象的实例，设置调用参数，调用目标对象的方法。
/// 需要对其封装来减低耦合度
/// </summary>
namespace command {
	class Doctor {
	public:
		void diagnoseEye() {
			std::cout << "Doctor diagnose eye" << std::endl;
		}

		void diagnoseNose() {
			std::cout << "Doctor diagnose nose" << std::endl;
		}
	};

	class Command {
	public:
		virtual ~Command() {}
		virtual void diagnose() = 0;
	};

	class CommandEye :public Command {
	public:
		CommandEye(Doctor* doc) 
			:m_doc(doc)
		{}
		virtual void diagnose() override {
			m_doc->diagnoseEye();
		}
	private:
		Doctor* m_doc;
	};

	class CommandNose :public Command {
	public:
		CommandNose(Doctor* doc)
			:m_doc(doc)
		{}
		virtual void diagnose() override {
			m_doc->diagnoseNose();
		}
	private:
		Doctor* m_doc;
	};

	class Nurse {
	public:
		Nurse(Command* cmd)
			:m_cmd(cmd)
		{}
		void submitCmd() {
			m_cmd->diagnose();
		}
	private:
		Command* m_cmd;
	};

	class HeadNurse {
	public:
		HeadNurse() {
			m_list.clear();
		}
		void submitCmd() {
			for (auto it = m_list.begin(); it != m_list.end(); it++) {
				(*it)->diagnose();
			}
		}
		void setCmd(Command* cmd) {
			m_list.push_back(cmd);
		}

	private:
		std::list<Command*> m_list;
	};

}


void test_command() {
	using namespace command;
	Doctor* doc = new Doctor();
	Command* cmdEye = new CommandEye(doc);
	Command* cmdNose = new CommandNose(doc);
	cmdEye->diagnose();
	cmdNose->diagnose();

	std::cout << std::endl;

	Nurse* nurse = new Nurse(cmdEye);
	nurse->submitCmd();

	std::cout << std::endl;

	HeadNurse* headNurse = new HeadNurse();
	headNurse->setCmd(cmdEye);
	headNurse->setCmd(cmdNose);
	headNurse->submitCmd();

	delete headNurse;
	delete nurse;
	delete cmdNose;
	delete cmdEye;


}
