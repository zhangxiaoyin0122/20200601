#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test() {
	void* p = new char[0x7fffffff];
	cout << "new:" << p << endl;
}

class Date {
public:
	Date(int year = 2020,int month = 5,int day = 31)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		++cnt;
	}
	Date(const Date& d)
		:_year(d._year)
		,_month(d._month)
		,_day(d._day)
	{
		++cnt;
	}
	//静态成员函数
	static int getCount() {
		return cnt;
	}
	void Display() {
		cout << _year << "-" << _month << "-" << _day << endl;
		getCount();
		cout << cnt << endl;
	}
private:
	int _year;
	int _month;
	int _day;
public:
	//静态成员变量 类内声明
	static int cnt;
};
//静态成员变量 类外初始化
int Date::cnt = 0;
Date fun(Date d) {//拷贝构造
	return d;//拷贝构造
}
void test2() {
	Date d;//构造
	Date d2 = fun(d);//拷贝构造  fun: 进过优化，只有两次拷贝构造：传参， 创建d2
	//静态成员变量/静态成员函数访问方式
	//1.对象访问
	cout << d.cnt << endl;
	cout << d2.cnt << endl;
	cout << &d.cnt << endl;
	cout << &d2.cnt << endl;
	//类名+作用域限定符
	cout << &Date::cnt << endl;
	cout << Date::cnt << endl;
	cout << Date::getCount << endl;
	//普通成员只能通过对象访问,而不能通过类名访问
	d.Display();
	//Date::Display; 错误用法
}

class Date {
public:
	friend ostream& operator<<(ostream& _cout, Date& d);
	friend istream& operator>>(istream& _cin, Date& d);
	Date(int year = 2020, int month = 5, int day = 31)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{}
	/*void operator<<(ostream& _cout) {
		_cout << _year << "-" << _month << "-" << _day << endl;
	}*/
private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& _cout, Date& d) {
	_cout << d._year << "-" << d._month << "-" << d._day << endl;
	return _cout;
}
istream& operator>>(istream& _cin, Date& d) {
	_cin >> d._year >> d._month >> d._day;
	return _cin;
}
void test3() {
	Date d;
	cout << d; //因为cout的输出流对象和隐含的this指针抢占第一个参数的位置
}
class Date {
public:
	Date(int year = 2020,int month = 4,int day = 3)
		:_year(year)
		,_month(month)
		,_day(day)
	{}
private:
	int _year;
	int _month;
	int _day;
};
class Time {
public:
	friend class Date;//声明日期类为时间类的友元类,可以在日期类中直接访问时间类的私有成员
	Time(int hour = 23,int minute = 4,int second = 59)
		:_hour(hour)
		,_minute(minute)
		,_second(second)
	{}
private:
	int _hour;
	int _minute;
	int _second;
};
class A {
	class B {
	public:
		void fun(const A& a) {
			cout << a._a << endl;
			cout << a._sa << endl;
			cout << A::_sa << endl;

		}
	private:
		int _b;
	};
private:
	int _a;
	static int _sa;
};
int main() {
	test3();
	return 0;
}