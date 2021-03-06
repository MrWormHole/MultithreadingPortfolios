#include "pch.h"
#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;
int pos = 0;
string lines[43];
ifstream reader;
mutex mtx;
bool isPaused = false;

void thread1(string i) {
	cout << i << endl;
}

void thread2() {
	mtx.lock();
	pos++;
	mtx.unlock();
}

void thread3(string s) {	mtx.lock();	if (s == "resume" && isPaused == true) {
		cout << "******** RESUMED ********" << endl;
		isPaused = false;
	}
	else if (s == "pause" && isPaused == false) {
		cout << "******** PAUSED ********" << endl;
		isPaused = true;
	}
	else if(s == "exit") {
		cout << "******** EXITED ********" << endl;
		exit(0);
	}
	mtx.unlock();
}

void readAndStore(ifstream& stream, string *str, int index) {
	string temp = "";
	getline(stream, temp);
	str[index] = temp;
}

void printWithDelay() {
	if (pos == 43) { 
		pos = 0;  
		cout << endl;
	}
	if (!isPaused) {
		thread t1(thread1, lines[pos]);
		t1.join();
		thread t2(thread2);
		t2.join();
		Sleep(1000);
	}
}

int main() {
	reader.open("caged_bird.txt");
	cout << "Reading now ...\n";
	for (int i = 0; i < size(lines); i++) {
		readAndStore(reader, lines, i);
	}
	
	cout << "Reading has finished. Printing now ...\n";
	while (true) {
		printWithDelay();
		
		if (GetAsyncKeyState('R')) {
			thread t3(thread3, "resume");
			t3.join();
		}
		if (GetAsyncKeyState('P')) {
			thread t3(thread3, "pause");
			t3.join();
		}
		if (GetAsyncKeyState('Q')) {
			thread t3(thread3, "exit");
			t3.join();
		}
	}
	
	reader.close();
	return 0;
}