#pragma once

/// <summary>
/// 状态者模式
/// 根据实现接口类里根据提前设置的值来执行不同参数下的不同行为
/// </summary>
namespace state {
	class Worker;
	class State;
	class StateOne;
	class StateTwo;

	class Worker {
	public:
		Worker();
		~Worker();
		void dothing();
		int getHour() {
			return m_hour;
		}
		void setHour(int hour) {
			m_hour = hour;
		}

		State* getCurState() {
			return m_state;
		}

		void setState(State* state) {
			m_state = state;
		}

	private:
		int m_hour;
		State* m_state;
	};

	class State {
	public:
		virtual ~State() {}
		virtual void dothing(Worker* worker) = 0;
	};

	class StateOne :public State {
	public:
		virtual void dothing(Worker* worker) override;
	};

	class StateTwo :public State {
		virtual void dothing(Worker* worker) override;
	};

	void StateOne::dothing(Worker* worker) {
		int h = worker->getHour();
		if (h == 7 || h == 8) {
			std::cout << "eat" << std::endl;
		}
		else {
			delete worker->getCurState();
			worker->setState(new StateTwo());
			worker->getCurState()->dothing(worker);
		}
	}

	void StateTwo::dothing(Worker* worker) {
		int h = worker->getHour();
		if (h >= 9) {
			std::cout << "work" << std::endl;
		}
		else {
			delete worker->getCurState();
			worker->setState(new StateTwo());
			worker->getCurState()->dothing(worker);
		}
	}
	Worker::Worker() {
		m_state = new StateOne();
	}

	Worker::~Worker() {
		if (m_state != nullptr) {
			delete m_state;
			m_state = nullptr;
		}
	}

	void Worker::dothing() {
		m_state->dothing(this);
	}

}

void test_state() {
	using namespace state;
	Worker* worker = new Worker();
	worker->setHour(7);
	worker->dothing();

	worker->setHour(10);
	worker->dothing();

	delete worker;
}