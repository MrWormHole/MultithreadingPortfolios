#include "pch.h"
#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using namespace std;
int pos = 0;
string lines[43];
ifstream reader;

void thread1(string s) {
	printf("%s\n", s.c_str());
}

void thread2(int i) {
	cout << i << endl;
}

void thread3() {
	pos++;
}

void readAndStore(ifstream& stream,string *str,int index) {
	string temp = "";
	getline(stream,temp);
	str[index] = temp;
	//cout << str[index] << endl;
}

void printWithDelay() {
	while (pos != 43) {
		thread t1(thread1, lines[pos]);
		t1.join();
		thread t3(thread3);
		t3.join();
		Sleep(1000);
	}
}

int main() {
	//serial threading(Part One) notice that parallel threading causes unpredictable results
	/*
	thread t2(thread2, 8);
	t2.join();
	thread t2_again(thread2, 10);
	t2_again.join();
	*/

	//reading from file and printing with threads(Part Two) didn't notice duplicate lines
	reader.open("caged_bird.txt");
	cout << "Reading now ...\n";
	for (int i = 0; i < size(lines); i++) {
		readAndStore(reader, lines,i);
	}
	cout << "Reading has finished. Printing now ...\n";
	printWithDelay();
	reader.close();

	return 0;
}