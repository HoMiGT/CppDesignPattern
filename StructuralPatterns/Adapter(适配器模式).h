#pragma once
#include <iostream>

/// <summary>
///  适配器模式
/// 让接口不兼容的对象能够相互合作
/// 俩个接口类的适配  比如苹果的Lightning 和 安卓的Type-C 进行适配
/// 要将苹果的Lightning 转换成 安卓的Type-C
/// 解决 一对一的问题
/// </summary>
namespace adapter {

	class AppleLightning {
	public:
		virtual void transform() {
			std::cout<< "AppleLightning transform" << std::endl;
		};
	};

	class AndroidTypeC {
	public:
		virtual void transform() = 0;
	};

	class Adapter :public AndroidTypeC {
	public:
		Adapter(AppleLightning* al)
			:m_al(al)
		{}
		virtual void transform() override {
			m_al->transform();
			std::cout<< "AppleLightning transforms to AndroidTypeC " << std::endl;
		}

	private:
		AppleLightning* m_al;
	};

}

void test_adapter() {
	using namespace adapter;
	AppleLightning* al = new AppleLightning();
	Adapter* atc = new Adapter(al);
	atc->transform();
	delete al;
	delete atc;
}


