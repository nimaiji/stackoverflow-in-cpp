#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include "logger.h"

#define lower(str) transform(str.begin(), str.end(), str.begin(), ::tolower)
using namespace std;

enum UserType {
    ADMIN,
    MEMBER
};

class AbstractUser {

public:
    hash<string> pass_hash;
    virtual bool authenticate(string username, string password) = 0;
    virtual void deleteAccount() = 0;
    string username;
protected:
	friend class Logger;
    string password;
    string email;
    UserType type;
};
