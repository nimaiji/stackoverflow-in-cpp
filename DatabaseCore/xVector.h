#ifndef CPP_STACKOVERFLOW_XVECTOR_H
#define CPP_STACKOVERFLOW_XVECTOR_H

#include <vector>
#include "Exportable.h"

template <class T>
class xVector:public std::vector<T>,public Exportable {

};


#endif //CPP_STACKOVERFLOW_XVECTOR_H
