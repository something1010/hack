#include <iostream>
#include <ctime>  
#include <thread>
#include <fstream>
#include <vector>
#include <string>

using namespace std::this_thread;
using namespace std::chrono;
using namespace std;

int randFrom(int from, int to) {
	return (int(rand()) % (to - from + 1)) + from;
}

struct ip {
	int one;
	int two;
	int tree;
	int four;
	int port;
	ip(){
		one = randFrom(0, 255);
		two = randFrom(0, 255);
		tree = randFrom(0, 255);
		four = randFrom(0, 255);
		port = randFrom(0, 255);
	}
	string getIp(bool showPort) {
		string str = to_string(one) + "." + to_string(two) + "." + to_string(tree) + "." + to_string(four);
		if (showPort) {
			str += ":";
			str += to_string(port);
		}
		return str;
	}
};

struct path {
	vector<string> pat;
	path() {
		pat.clear();
		pat.push_back("C:");
	}
	int getSize() { return pat.size(); }
};

struct file {
	int size;
	string name;
	path pathto;
	file() {
		size = 0;
	}
};

struct folder {
	vector<file> files;
	vector<folder> folders;
	string name;
	folder() {
		name = "default";
		file filedef;
		filedef.name = "index.ini";
		files.push_back(filedef);
	}
};

string login;
string password;
ip global;

void sleepf(int number, char type) {
	if(type == 's') sleep_until(system_clock::now() + seconds(number));
	else if(type == 'm') sleep_until(system_clock::now() + milliseconds(number));
}

bool trycon(int isretry) {
	cout << "connecting to ";
	cout << global.getIp(true);
	sleepf(1, 's');

	cout << " .";

	sleepf(1, 's');

	cout << ".";

	sleepf(1, 's');

	cout << ".\n";

	sleepf(2, 's');
	if (randFrom(0, 100) > 10) {
		cout << "success! \n";
		return true;
	}
	else {
		if (isretry >= 10) {
			cout << "too many attempts failed! try later.";
			return false;
		}
		char retry;
		int error = randFrom(200, 20000);
		cout << "error occurred during execution: 0x" << error << ", retry? [Yes/No]";
		cin >> retry;
		if (retry == 'y' || retry == 'Y') {
			trycon(isretry + 1);
		}
		else {
			cout << "program stopped due to the error 0x" << error << endl;
			return false;
		}
	}
}

void cmd(bool admin) { ;

	bool toexit = false;
	string command;

	while (!toexit) {
		if(command != "") cout << "cm : ";
		cin >> command;
		if (command == "exit") {
			toexit = true;
		}
		if (command[0] == 'e' && command[1] == 'c') cout << command << endl;
	}
	command = "";
}

void action() {

	sleepf(2, 's');

	bool admin = false;
	int whattodo = 0;

	if ((login == "user" && password == "5") || (login == "" && password == "")) admin = true;

	if (admin) cout << "hello, admin. What can i do for you? : ";
	else cout << "what would you like to do: ";
	cout << "\n" <<
		"0. exit. \n"
		"1. show command prompt. \n";
	cin >> whattodo;
	switch (whattodo)
	{
	case 0:
		break;
	case 1:
		cmd(admin);
	default:
		break;
	};
	return;
}

int main() {

	srand(time(0));
	time_t result = time(0);

	ip local;
	global = local; // redefining global ip to set it to random

	cout << "please, input your login: ";
	cin >> login;
	sleepf(2, 's');

	cout << "please, input your password: ";
	cin >> password;
	sleepf(3, 's');

	//ofstream logs("log.txt");
	//logs << login << " " << password << " " << asctime(localtime(&result)) << "\n";
	//logs.close();

	if (!trycon(0)) {
		exit(1);
	}

	fstream f;
	ofstream fout;
	ifstream fin;
	fin.open("log.txt");
	fout.open("log.txt", ios::app);
	if (fin.is_open())
		fout << login << " | " << password << " | " << global.getIp(true) << " | " << asctime(localtime(&result));
	fin.close();
	fout.close();

	action();

	return 0;
}
