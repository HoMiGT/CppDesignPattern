#pragma once
#include <iostream>

/// <summary>
/// 外观模式
/// 能够为程序库，框架或其他复杂类提供一个简单的接口
/// 对外保持一致
/// 本质就是多个函数放在对外调用的一个函数内执行
/// </summary>
namespace facade {
	class Camera {
	public:
		void takePhoto() {
			std::cout << "Phone take some photos" << std::endl;
		}
	};

	class Call {
	public:
		void call() {
			std::cout << "Phone call some one" << std::endl;
		}
	};
	
	class Message {
	public:
		void sendMessage() {
			std::cout << "Phone send message" << std::endl;
		}
	};

	class Screen {
	public:
		void show() {
			std::cout << "Phone's screen show information" << std::endl;
		}
	};

	class Phone {
	public:
		Phone() {
			m_camera = new Camera;
			m_call = new Call;
			m_message = new Message;
			m_screen = new Screen;
		}
		~Phone() {
			if (m_camera) {
				delete m_camera;
				m_camera = nullptr;
			}
			if(m_call){
				delete m_call;
				m_call = nullptr;
			}
			if(m_message){
				delete m_message;
				m_message = nullptr;
			}
			if (m_screen){
				delete m_screen;
				m_screen = nullptr;
			}
		}

		void usePhone() {
			m_camera->takePhoto();
			m_call->call();
			m_message->sendMessage();
			m_screen->show();
		}

	private:
		Camera* m_camera;
		Call* m_call;
		Message* m_message;
		Screen* m_screen;
	};
}

void test_facade() {
	using namespace facade;

	std::cout << "使用外观模式之前" << std::endl;
	Camera* camera = new Camera;
	Call* call = new Call;
	Message* message = new Message;
	Screen* screen = new Screen;

	camera->takePhoto();
	call->call();
	message->sendMessage();
	screen->show();

	delete camera;
	delete call;
	delete message;
	delete screen;

	std::cout << "使用外观模式之后" << std::endl;
	Phone* phone = new Phone;
	phone->usePhone();
	delete phone;
}
