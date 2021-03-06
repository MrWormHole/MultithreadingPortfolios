#include "pch.h"
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable condVar;
int controlVal = 0;

void myFunc1(condition_variable* cv,int* control) {
	std::unique_lock<std::mutex> lck(mtx);
	while (true) {
		if (*control = 1) {
			break;
		}
		cv->wait(lck);
	}

	std::chrono::duration<double, std::milli> time_span(0);
	std::chrono::duration<double, std::milli> delay(2);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	while (true) {
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

		cout << "This is thread 1\n";
		cout << "Control value is " << *control << "\n";
		
		if (time_span.count() > delay.count()) {
			break;
		}
	}

	*control = 2;
}

void myFunc2(condition_variable* cv, int* control) {
	std::unique_lock<std::mutex> lck(mtx);
	while (true) {
		if (*control = 2) {
			break;
		}
		cv->wait(lck);
	}

	std::chrono::duration<double, std::milli> time_span(0);
	std::chrono::duration<double, std::milli> delay(2);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	while (true) {
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

		cout << "This is thread 2\n";
		cout << "Control value is " << *control << "\n";;

		if (time_span.count() > delay.count()) {
			break;
		}
	}

	*control = 3;
}

void myFunc3(condition_variable* cv, int* control) {
	std::unique_lock<std::mutex> lck(mtx);
	while (true) {
		if (*control = 3) {
			break;
		}
		cv->wait(lck);
	}

	std::chrono::duration<double, std::milli> time_span(0);
	std::chrono::duration<double, std::milli> delay(2);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	while (true) {
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

		cout << "This is thread 3\n";
		cout << "Control value is " << *control << "\n";;

		if (time_span.count() > delay.count()) {
			break;
		}
	}

	*control = 4;
}

void myFunc4(condition_variable* cv, int* control) {
	std::unique_lock<std::mutex> lck(mtx);
	while (true) {
		if (*control = 4) {
			break;
		}
		cv->wait(lck);
	}

	std::chrono::duration<double, std::milli> time_span(0);
	std::chrono::duration<double, std::milli> delay(2);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	while (true) {
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

		cout << "This is thread 4\n";
		cout << "Control value is " << *control << "\n";;

		if (time_span.count() > delay.count()) {
			break;
		}
	}

	*control = 0; //It ends here
}

int main()
{
	thread thread_1(myFunc1, &condVar, &controlVal);
	thread thread_2(myFunc2, &condVar, &controlVal);
	thread thread_3(myFunc3, &condVar, &controlVal);
	thread thread_4(myFunc4, &condVar, &controlVal);

	unique_lock<mutex> lck(mtx);
	controlVal = 1; //Following queue will be = 1,2,3,4
	condVar.notify_all();
	
	thread_4.join();
	thread_3.join();
	thread_2.join();
	thread_1.join();

	return 0;
}

