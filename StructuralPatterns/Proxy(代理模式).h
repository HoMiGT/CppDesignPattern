#pragma once
#include <iostream>

/// <summary>
/// 代理模式
/// 让你能够提供对象的替代品或其占位符。代理控制着对于原对象的访问，并允许在将请求提交给对象前后进行一些处理
/// 防止直接访问某一个类，提供一种类似授权的机制
/// 本质上就是一个接口类，多个类实现了接口类，然后依次将类的实例赋值给接口类类型的成员，这样就实现代理，有点类似于装饰模式，给函数增加功能
/// 如完成一次互联网请求大概要遵循的协议
/// </summary>
namespace proxy {

	class Protocol {
	public:
		virtual ~Protocol(){}
		virtual void request() = 0;
		virtual void response() = 0;
	};

	class IPProtocol:public Protocol {
	public:
		virtual void request() override {
			std::cout << "Add IPProtocol header info" << std::endl;
		}
		virtual void response() override {
			std::cout << "Parse IPProtocol header info" << std::endl;
		}
	};

	class TcpProtocol:public Protocol {
	public:
		TcpProtocol() {
			m_protocol = new IPProtocol();
		}
		virtual ~TcpProtocol() {
			if (m_protocol) {
				delete m_protocol;
				m_protocol = nullptr;
			}
		}

		virtual void request() override{
			std::cout << "Add TcpProtocol header info" << std::endl;
			m_protocol->request();
		}

		virtual void response() override{
			m_protocol->response();
			std::cout << "Parse TcpProtocol header info" << std::endl;
		}

	private:
		Protocol* m_protocol;
	};

	class HttpProtocol:public Protocol {
	public:
		HttpProtocol() {
			m_protocol = new TcpProtocol();
		}	
		virtual ~HttpProtocol() {
			if (m_protocol) {
				delete m_protocol;
				m_protocol = nullptr;
			}
		}

		virtual void request() override {
			std::cout << "Add HttpProtocol header info" << std::endl;
			m_protocol->request();
		}

		virtual void response() override {
			m_protocol->response();
			std::cout << "Parse HttpProtocol header info" << std::endl;
		}


	private:
		Protocol* m_protocol;
	};

}

void test_proxy() {
	using namespace proxy;
	HttpProtocol* protocol = new HttpProtocol();

	protocol->request();
	protocol->response();

	delete protocol;
}
