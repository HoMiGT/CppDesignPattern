#pragma once
#include <iostream>
#include <mutex>


std::mutex g_mutex;

/// <summary>
/// 单例模式
/// 让你能够保证一个类只有一个实例，并提供一个访问该实例的全局节点
///  一个类只创建一个对象，其实类似于类的静态方法和静态成员
/// 单例的适用场景 通常是需要全局唯一访问点的情况，比如日志记录器，配置读取，线程池，数据库连接
/// 类的静态成员 通常是一些工具类，比如数据函数，数组操作，字符串处理，不需要访问任何实例变量的。
/// </summary>
namespace singleton {
	
	/// <summary>
	/// 懒汉式
	/// 非线程安全，需要使用锁来保证线程安全，使用时再创建内存
	/// </summary>
	class Idler{
	private:
		Idler(){
			std::cout << "Idler()" << std::endl;
		}

		static Idler* m_unsafe_instance;
		static Idler* m_safe_instance;

	public:
		~Idler() {
			std::cout << "~Idler()" << std::endl;
		}

		Idler(const Idler&) = delete;  // 明确删除copy构造函数
		Idler& operator=(const Idler&) = delete;  // 明确删除赋值构造函数

		static Idler* getUnsafeInstance() {
			if (!m_unsafe_instance) {
				m_unsafe_instance = new Idler();
			}
			return m_unsafe_instance;
		}

		static Idler* getSafeInstance() {
			g_mutex.lock();
			if (!m_safe_instance) {
				m_safe_instance = new Idler();
			}
			g_mutex.unlock();
			return m_safe_instance;
		}


		static void freeInstance() {
			if (m_unsafe_instance) {
				delete m_unsafe_instance;
				m_unsafe_instance = nullptr;
			}
			if (m_safe_instance) {
				delete m_safe_instance;
				m_safe_instance = nullptr;
			}
		}
	};

	Idler* Idler::m_unsafe_instance = nullptr;
	Idler* Idler::m_safe_instance = nullptr;

	/// <summary>
	/// 饿汉式 默认会创建一个对象，线程安全，缺点不使用也占用内存
	/// 访问量大的场景，使用饿汉式，访问量小的场景，使用懒汉式 ，这个是典型的以时间换空间
	/// </summary>
	class HungryHan {
	private:
		HungryHan() {
			std::cout << "HungryHan()" << std::endl;
		}

	public:
		~HungryHan() {
			std::cout << "~HungryHan()" << std::endl;
		}

		HungryHan(const HungryHan&) = delete;  // 明确删除copy构造函数
		HungryHan& operator=(const HungryHan&) = delete;  // 明确删除赋值构造函数

		static HungryHan* getInstance() {
			return m_instance;
		}

		static void freeInstance() {
			if (m_instance) {
				delete m_instance;
				m_instance = nullptr;
			}
		}

	private:
		static HungryHan* m_instance;


	};
	HungryHan* HungryHan::m_instance = new HungryHan();
}


void test_singleton() {
	using namespace singleton;

	Idler* p1 = Idler::getUnsafeInstance();
	Idler* p11 = Idler::getUnsafeInstance();

	Idler* p2 = Idler::getSafeInstance();
	Idler* p22 = Idler::getSafeInstance();

	HungryHan* p3 = HungryHan::getInstance();
	HungryHan* p33 = HungryHan::getInstance();

	std::cout << "p1:" << p1 << std::endl;
	std::cout << "p11:" << p11 << std::endl;

	std::cout << "p2:" << p1 << std::endl;
	std::cout << "p22:" << p11 << std::endl;

	std::cout << "p3:" << p1 << std::endl;
	std::cout << "p33:" << p11 << std::endl;

	Idler::freeInstance();
	HungryHan::freeInstance();

}