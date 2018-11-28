#include "Database.h"
#include <fstream>

Database::Database() {

};

void Database::insertIndex(T t) {
    v.push_back(t);
}

T &Database::dropIndex(int t) {
    return v[t];
}