#ifndef STACKOVERFLOW_IN_CPP_LOGGER_H
#define STACKOVERFLOW_IN_CPP_LOGGER_H
#pragma once

#include "User.h"

using namespace std;

class Loggers {
protected:
    Loggers();

    static Loggers *instance;
    static int count;
public:
    virtual void Log(User t);

};

class Logger : public Loggers {
public:

    static Loggers *getInstance();

    void Log(User t);

private:
    Logger();

};

#endif