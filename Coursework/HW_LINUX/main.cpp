#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <chrono>
#include <condition_variable>
#include <fstream>

using namespace std;

mutex mtx;
condition_variable condVar;
ofstream logger;

int controlVal = 0;
int problemVal = 0;
int solutionVal = 0;
int totalAttemptCounts = 0;
bool problemSolved = true;
bool signalReceived = false; 

// For logging every text into log.txt file
void writeLog(string text) {
	if (logger.is_open()) {
		logger << text;
	}
}

// For showing help menu and getting input from user prompt
void printHelp(int *sol) {

	string helpString = "What should i do with this problem?\n1. Choose a new direction\n2. Lift the wheel\n3. Do the brake\n";
	cout << helpString;
	writeLog(helpString);
	cin >> *sol;
	string s = to_string(*sol);
	writeLog(s);
}

// For showing the problem of a specific wheel
void printProblem(int *ctrlValue, int *probValue) {

	string problemString;
	string c = to_string(*ctrlValue);
	usleep(2000000);
	switch (*probValue) {
	case 1:
		problemString = "Wheel " + c + " encountered a rock and bumped into that rock.\n";
		cout << problemString;
		break;
	case 2:
		problemString = "Wheel " + c + " lost track of how far it has travelled due to loose sand\n";
		cout << problemString;
		break;
	case 3:
		problemString = "Wheel " + c + " dropped due to a hole or a cliff\n";
		cout << problemString;
		break;
	default:
		break;
	}
	writeLog(problemString);
	usleep(2000000);
}

// For assigning control value and problem value randomly for start
void generateProblem(condition_variable *cv, int *ctrlValue, int *probValue) {

	unique_lock<mutex> lck(mtx);

	// Pick a problem between 1 and 3, pick a control between 1 and 6 for wheels
	while (true) {
		if (*probValue>0 && *probValue<4 && *ctrlValue>0 && *ctrlValue<7) {
			cv->wait(lck);
		}
		else {
			*probValue = rand() % 3 + 1; 
			*ctrlValue = rand() % 6 + 1; 

			if (!signalReceived) {
				cv->notify_all();
			}
		}
	}
}

// For wheel class subsumption architecture which triggers a problem of the wheel and waits for the solution
void wheelSignal(condition_variable *cv, int *ctrlValue, int *probValue, int rank) {

	unique_lock<mutex> lck(mtx);

	while (true) {
		string wheelString;
		string c = to_string(*ctrlValue);

		// If control and rank are not same, notify the other wheel until it is the correct rank number
		if (*ctrlValue != rank) {
			cv->notify_one();
			cv->wait(lck, [&] {return controlVal == rank; });
		}
		else {
			wheelString = "!!! WHEEL " + c + " SENT A SIGNAL !!!\n";
			cout << wheelString;
			writeLog(wheelString);
			printProblem(ctrlValue, probValue);
			signalReceived = true;

			// Pick a random solution to the problem
			solutionVal = rand() % 3 + 1;
			problemSolved = false;

			// Notifying all the other threads so solution can be applied
			cv->notify_all();

			// Until problem is solved, we wait
			cv->wait(lck, [] {return problemSolved == true; });

			// Solution is obtained move onto other wheels
			cv->notify_all();
		}
	}
}

// For robot class subsumption architecture which triggers a solution for the wheel and waits for the correct solution
void robotSignal(condition_variable *cv, int *ctrlValue, int *probValue, int *solValue, int *attemptCounter,int correctSolution) {
	unique_lock<mutex> lck(mtx);

	while (true) {
		string attemptString;
		string solutionString;

		switch (correctSolution) {
		case 1:
			solutionString = "The robot tries to choose a new direction\n";
			break;
		case 2:
			solutionString = "The robot tries to lift a wheel\n";
			break;
		case 3:
			solutionString = "The robot tries to do a brake\n";
			break;
		default:
			break;
		}

		// If the robot doesn't have correct solution, notify other solutions and wait for the lock
		if (*solValue != correctSolution) {
			cv->notify_all();
			cv->wait(lck);
		}
		else {
			usleep(2000000);
			if (*attemptCounter >= 3) {
				// If attempts fail three times and more, ask for input from user prompt
				attemptString = "Attempts by robot has failed, waiting for manual instructions by a human\n";
				cout << attemptString;
				writeLog(attemptString);
				printHelp(solValue);
				*attemptCounter = 0;
			}
			else {
				cout << solutionString;
				writeLog(solutionString);
				usleep(2000000);
				// If the problem has found correct solution then problem is solved
				if (*probValue == correctSolution) {
					attemptString = "Attempt has succeeded\n";
					cout << attemptString;
					writeLog(attemptString);

					signalReceived = false;
					problemSolved = true;
					*solValue = 0;
					*probValue = 0;
					*ctrlValue = 0;
					*attemptCounter = 0;

					// Notify the other wheel that the problem has been solved
					cv->notify_one();
				}
				else {
					// If the problem didn't find the correct solution then it fails and tries again
					attemptString = "Attempt has failed\n";
					cout << attemptString;
					writeLog(attemptString);
					totalAttemptCounts++;
					// Try a random solution for next one
					*solValue = rand() % 3 + 1;
					// Notify other solutions so it can do the other solution that probably waits before
					cv->notify_all();
				}
			}
			usleep(2000000);
		}
	}
}

// For showing the robot movement after each problem is solved
void robotStart(condition_variable *cv) {

	unique_lock<mutex> lck(mtx);

	while (true) {
		string s = "---- Robot is moving ----\n";

		// Moving while the problem is already solved. If the problem is not solved, wait for the problem to be solved
		if (!problemSolved) {
			cv->wait(lck);
		}
		else {
			cout << s;
			writeLog(s);
			cv->notify_all();
			problemSolved = false;
			usleep(2000000);
		}
	}
}

int main() {
	srand(time(NULL));
	logger.open("log.txt");
	thread wheelThreads[7];
	thread robotThreads[4];

	// A thread that initializes a problem
	thread initializeProblem(generateProblem, &condVar, &controlVal ,&problemVal);
	// A thread that shows robot is moving
	thread startRobot(robotStart, &condVar);

	// Wheel threads
	for (int i = 1; i < 7; i++) {
		wheelThreads[i] = thread(wheelSignal, &condVar, &controlVal, &problemVal, i);
	}
	// Robot threads
	for (int i = 1; i < 4; i++) {
		robotThreads[i] = thread(robotSignal, &condVar, &controlVal, &problemVal, &solutionVal, &totalAttemptCounts, i);
	}

	// Join all threads
	initializeProblem.join();
	startRobot.join();
	for (int i = 1; i < 7; i++) {
		wheelThreads[i].join();
	}
	for (int i = 1; i < 4; i++) {
		robotThreads[i].join();
	}

	logger.close();
	return 0;
}
