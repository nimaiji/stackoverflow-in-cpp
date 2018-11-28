#ifndef CPP_STACKOVERFLOW_DATABASE_H
#define CPP_STACKOVERFLOW_DATABASE_H

#include <vector>
//#include "data.h"
#include "xVector.h"
#include <string>
template<class T>
class Database{
protected:
    string name,path;
    //File dFile;
    xVector<T> v;
public:
    Database();
    void insertIndex(T t);
    void insertIndex(int t);
    T& dropIndex(T t);
    T& dropIndex(int t);
    void updateIndex(T t,int index);
    void join(Database database);
    void join(string path);
};


#endif //CPP_STACKOVERFLOW_DATABASE_H
