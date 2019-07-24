#include <iostream>
#include <iomanip> //setw() , setfill()
#include <vector>
#include <algorithm>    // std::sort

using namespace std;

/*1.1. Write a class Time with three ﬁelds hr, min, sec representing hour, minutes, seconds. Store time in 24 hour format.
A constructor is used to initialize time objects, which takes time in 24H format. Constructor may throw exceptions.*/
class Time
{
public:
	int hour, minute, second;
	//constructor with default value 0                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	Time(int h, int m, int s) :hour(h), minute(m), second(s) {
		if (h >= 24 || h < 0 || m >= 60 || m < 0 || s >= 60 || s < 0) {
			throw(std::domain_error("Time value out of range"));
		}
	}
	virtual ~Time() {}

	/*	void getTime() {
			cout << "Enter time:" << endl;
			cout << "Hours?   ";
			cin >> hour;
			cout << "Minutes? ";
			cin >> minute;
			cout << "Seconds? ";
			cin >> second;
		}*/

		//2.2. Write a type conversion operator which converts Time to the number of seconds passed since 00:00:00.
	int convertIntoSeconds() const {
		return hour * 3600 + minute * 60 + second;
	}

	void displayTime() {
		cout << "The time is = " << setw(2) << setfill('0') << hour << ":"
			<< setw(2) << setfill('0') << minute << ":"
			<< setw(2) << setfill('0') << second << endl;
		cout << "Time in total seconds: " << convertIntoSeconds();
	}
};

ostream& operator<<(ostream& os, const Time& time) {
	os << setw(2) << setfill('0') << time.hour << ":"
		<< setw(2) << setfill('0') << time.minute << ":"
		<< setw(2) << setfill('0') << time.second << endl;
	return os;
}
/*2.3. Write an enum Time::Format consisting of two members [TF24,TF12], representing 24 hrs time format and 12 hrs time format.
*/

#include <string>
/*2.3 Declare a class TimeFormat which returns a string for Time object in the speciﬁed format.You could use the function std::to string for converting numeric datatypes to string.*/
class Timeformat {
public:
	enum Format { TF24, TF12 };
private:
	Format format;
public:
	Timeformat(Format format) :format(format) {}
	void print(const Time& time) {
		switch (format) {
		case TF12:
			if (time.hour == 0 || time.hour == 12)
				std::cout << "12";
			else
				std::cout << setw(2) << setfill('0') << time.hour % 12;
			std::cout << ':' << setw(2) << setfill('0') << time.minute << ':' << setw(2) << setfill('0') << time.second;

			if (time.hour / 12 == 0)
				std::cout << " AM";
			else
				std::cout << " PM";
			break;
		case TF24:
			std::cout << setw(2) << setfill('0') << time.hour << ":"
				<< setw(2) << setfill('0') << time.minute << ":"
				<< setw(2) << setfill('0') << time.second << endl; ;
			break;
		}
	}


};

/*2.4 Declare a class TimeComparator which compares two Time objects a,b and returns true if a < b, false otherwise*/
class TimeComparator {
public:
	bool operator()(const Time& time, const Time& othertime) {
		if (time.convertIntoSeconds() < othertime.convertIntoSeconds())
			return true;
		else
			return false;
	}

};


int main() {
	Time T(13, 37, 00); //creating objects
/*	T.getTime();*/
	T.convertIntoSeconds();
	T.displayTime();

	//2.5 In main function, declare a vector of Time. Initialize the vector with 10 objects.
	std::vector<Time> v;
	for (int i = 0; i <= 10; ++i) {
		Time Ti(i, i, i);
		v.push_back(Ti);
	};

	v.erase(v.begin() + 5);
	Time t11(11, 11, 11);
	v.insert(v.begin(), t11);

	// print out content:
	std::cout << "\nmyvector contains:\n";
	for (std::vector<Time>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << ' ' << *it;
	};
	std::cout << "\nprint the begin out"
		<< ' ' << *(v.begin())
		<< '\n';
	//Use std::sort() with TimeComparator to sort the vector in descending order.
	std::sort(v.begin(), v.end(), TimeComparator());//To use TimeComparator class here, a functor is needed, so the public bool operator() is defined as comparison

	std::cout << "\nmyvector contains after sort:\n";
	for (std::vector<Time>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << ' ' << *it;
	};
	std::cout << '\n';

	Timeformat(Timeformat::TF12).print(*v.begin());

	std::vector<Time> v1{ Time(12,00,00), Time(10,00,00) };

	std::cout << "\nmyvector using initiazer_list vector:\n";

	for (auto it = v1.begin(); it != v1.end(); ++it) { //shortcut for std::vector<Time>::iterator
		std::cout << ' ' << *it;
	};

	return 0;
}

/*
The time is = 13:37:00
Time in total seconds: 49020
myvector contains:
 11:11:11
 00:00:00
 01:01:01
 02:02:02
 03:03:03
 04:04:04
 06:06:06
 07:07:07
 08:08:08
 09:09:09
 10:10:10

print the begin out 11:11:11


myvector contains after sort:
 00:00:00
 01:01:01
 02:02:02
 03:03:03
 04:04:04
 06:06:06
 07:07:07
 08:08:08
 09:09:09
 10:10:10
 11:11:11

12:00:00 AM
myvector using initiazer_list vector:
 12:00:00
 10:00:00
*/