#pragma once

/// <summary>
/// 策略模式
/// 策略模式定义了一系列算法，并将每个算法封装起来，使他们可以相互替换，且算法的变化不会影响到使用算法的客户
/// 策略模式让算法独立于使用它的客户而变化
/// </summary>
namespace strategy {
	class Strategy {
	public:
		virtual ~Strategy() {};
		virtual void crypt() = 0;
	};

	class AES :public Strategy {
	public:
		virtual void crypt() override {
			std::cout << "AES crypt" << std::endl;
		}
	};

	class DES :public Strategy {
	public:
		virtual void crypt() override {
			std::cout << "DES crypt" << std::endl;
		}
	};

	class Context {
	public:
		void setStrategy(Strategy* strategy) {
			this->m_strategy = strategy;
		}
		void operation() {
			this->m_strategy->crypt();
		}

	private:
		Strategy* m_strategy;
	};
}


void test_strategy() {
	using namespace strategy;
	Strategy* des = new DES();
	des->crypt();

	std::cout << std::endl;

	Context* context = new Context();
	context->setStrategy(des);
	context->operation();

	delete context;
	delete des;

}
