#pragma once
#include <iostream>

/// <summary>
/// 解释器模式
/// A类，接口B类  C:B  D:B  CD去修改A的内容  然后A获得改变后的结果
/// </summary>
namespace interpreter {
	class Context {
	public:
		Context(int num)
			:m_num(num)
		{}
		void setNum(int num) {
			m_num = num;
		}
		int getNum() {
			return m_num;
		}
		void setRes(int res) {
			m_res = res;
		}
		int getRes() {
			return m_res;
		}
	private:
		int m_num;
		int m_res;
	};

	class Expression {
	public:
		virtual ~Expression() {}
		virtual void interpreter(Context* context) = 0;
	};

	class PlusExpression :public Expression {
	public:
		virtual void interpreter(Context* context) override {
			int num = context->getNum();
			num++;
			context->setRes(num);
			context->setNum(num);
		}
	};

	class MinusExpression :public Expression {
	public:
		virtual void interpreter(Context* context) override {
			int num = context->getNum();
			num--;
			context->setRes(num);
			context->setNum(num);
		}
	};

}

void test_interpreter() {
	using namespace interpreter;

	Expression* ex = nullptr;
	Context* ct = nullptr;

	ct = new Context(10);
	std::cout<< "ct->getNum():" << ct->getNum() << std::endl;

	ex = new PlusExpression();
	ex->interpreter(ct);
	std::cout<< "ct->getNum():" << ct->getNum() << std::endl;
	std::cout<<"ct->getRes():"<< ct->getRes() << std::endl;
	delete ex;
	ex = nullptr;

	ex = new MinusExpression();
	ex->interpreter(ct);
	std::cout<< "ct->getNum():" << ct->getNum() << std::endl;
	std::cout<<"ct->getRes():"<< ct->getRes() << std::endl;
	delete ex;
	ex = nullptr;
	delete ct;







}