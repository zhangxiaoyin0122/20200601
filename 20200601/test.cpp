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
	//��̬��Ա����
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
	//��̬��Ա���� ��������
	static int cnt;
};
//��̬��Ա���� �����ʼ��
int Date::cnt = 0;
Date fun(Date d) {//��������
	return d;//��������
}
void test2() {
	Date d;//����
	Date d2 = fun(d);//��������  fun: �����Ż���ֻ�����ο������죺���Σ� ����d2
	//��̬��Ա����/��̬��Ա�������ʷ�ʽ
	//1.�������
	cout << d.cnt << endl;
	cout << d2.cnt << endl;
	cout << &d.cnt << endl;
	cout << &d2.cnt << endl;
	//����+�������޶���
	cout << &Date::cnt << endl;
	cout << Date::cnt << endl;
	cout << Date::getCount << endl;
	//��ͨ��Աֻ��ͨ���������,������ͨ����������
	d.Display();
	//Date::Display; �����÷�
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
	cout << d; //��Ϊcout������������������thisָ����ռ��һ��������λ��
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
	friend class Date;//����������Ϊʱ�������Ԫ��,��������������ֱ�ӷ���ʱ�����˽�г�Ա
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