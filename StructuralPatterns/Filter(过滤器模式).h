#pragma once
#include <iostream>
#include <string>
#include <list>

/// <summary>
/// 过滤器模式
/// </summary>
namespace filter {
	class Person {
	public:
		Person(const std::string& name,const std::string& gender,const std::string& number)
			:m_name(name),m_gender(gender),m_number(number)
		{}

		const std::string& get_name() const {
			return m_name;
		}
		const std::string& get_gender() const {
			return m_gender;
		}
		const std::string& get_number() const {
			return m_number;
		}
	
	private:
		std::string m_name;
		std::string m_gender;
		std::string m_number;
	};

	class Filter {
	public:
		virtual ~Filter(){}
		virtual std::list<Person> filter(std::list<Person>& persons) = 0;
		virtual Filter* clone() = 0;
	};

	class NameFilter :public Filter {
	public:
		NameFilter(const std::string& name) {
			this->m_name = name;
		}
		virtual std::list<Person> filter(std::list<Person>& persons) override {
			std::list<Person> result_persons;
			for (std::list<Person>::iterator it = persons.begin(); it != persons.end(); ++it) {
				if ((*it).get_name().find_first_of(m_name, 0) != -1) {
					result_persons.push_back(*it);
				}
			}
			return result_persons;
		}

		NameFilter* clone() override {
			return new NameFilter(*this);
		}
	private:
		std::string m_name;
	};

	class GenderFilter :public Filter {
	public:
		GenderFilter(const std::string& gender) {
			this->m_gender = gender;
		}

		virtual std::list<Person> filter(std::list<Person>& persons) override {
			std::list<Person> result_persons;
			for (std::list<Person>::iterator it = persons.begin(); it != persons.end(); ++it) {
				if ((*it).get_gender().find_first_of(m_gender,0)!=-1) {
					result_persons.push_back(*it);
				}
			}
			return result_persons;
		}

		GenderFilter* clone() override {
			return new GenderFilter(*this);
		}
	private:
		std::string m_gender;
	};

	class NumberFilter :public Filter {
	public:
		NumberFilter(const std::string& number) {
			this->m_number = number;
		}

		virtual std::list<Person> filter(std::list<Person>& persons) override {
			std::list<Person> result_persons;
			for (auto it = persons.begin(); it != persons.end(); ++it) {
				if ((*it).get_number().find_first_of(this->m_number,0) !=-1) {
					result_persons.push_back(*it);
				}
			}
			return result_persons;
		}

		NumberFilter* clone() override {
			return new NumberFilter(*this);
		}

	private:
		std::string m_number;
	};


	class ListFilter :public Filter {
	public:
		ListFilter(std::list<Filter*>& filters) {
			this->m_filters = filters;
		}
		~ListFilter() {
			for (auto filter = m_filters.begin(); filter != m_filters.end(); ++filter) {
				delete* filter;
				*filter = nullptr;
			}
		}

		virtual std::list<Person> filter(std::list<Person>& persons) override {
			std::list<Person> result_persons=persons;
			for (auto filter = m_filters.begin(); filter != m_filters.end(); ++filter) {
				result_persons = (*filter)->filter(result_persons);
			}
			return result_persons;
		}

		virtual ListFilter* clone() override {
			return nullptr;
		}
		
	private:
		std::list<Filter*> m_filters;
	};

	void printPersons(std::list<Person> persons) {
		for (auto person = persons.begin(); person != persons.end(); ++person) {
			std::cout << (*person).get_name() << " " << (*person).get_gender() << " " << (*person).get_number() << std::endl;
		}
	}

}

void test_filter() {
	using namespace filter;

	std::list<Person> persons;
	persons.push_back(Person("a", "男", "1"));
	persons.push_back(Person("ab", "女", "66"));
	persons.push_back(Person("abc", "男", "166"));
	persons.push_back(Person("b", "男", "61"));
	persons.push_back(Person("bc", "女", "16"));
	persons.push_back(Person("bcd", "男", "21"));
	persons.push_back(Person("c", "女", "88"));
	persons.push_back(Person("cd", "男", "101"));
	persons.push_back(Person("cde", "女", "102"));

	std::list<Filter*> filters;

	Filter* filter = new NameFilter("a");
	printPersons(filter->filter(persons));
	filters.push_back(filter->clone());
	delete filter;
	std::cout << std::endl;

	filter = new GenderFilter("男");
	printPersons(filter->filter(persons));
	filters.push_back(filter->clone());
	delete filter;
	std::cout << std::endl;

	filter = new NumberFilter("6");
	printPersons(filter->filter(persons));
	filters.push_back(filter->clone());
	delete filter;
	std::cout << std::endl;

	filter = new ListFilter(filters);
	printPersons(filter->filter(persons));
	delete filter;
	filter = nullptr;
}


