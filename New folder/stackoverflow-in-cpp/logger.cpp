#include <iostream>
#include "logger.h"
#include <fstream>

Loggers::Loggers() {};

Loggers* Loggers::instance = NULL;
int Loggers::count = 0;

Logger::Logger() {};

Loggers* Logger::getInstance() {
	if (instance == NULL) {
		instance = new Logger();
		return instance;
	}

	else {
		return instance;
	}
}



void Logger::Log(User t) {
	count++;
	fstream f("Log.txt", ios::trunc | ios::in | ios::out);
	f.seekg(ios::end);
	f << t.username << "  " << t.email << endl;
	f.close();
}

