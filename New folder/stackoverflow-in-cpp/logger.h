#pragma once
#include "User.h"

class Loggers {
protected:
	Loggers();
	static Loggers*  instance;
	static int count;
public:
	virtual void Log(User t);

};

class Logger:public Loggers
{
public:

	static Loggers*  getInstance();
		void Log(User t);

private:
	Logger();

};
