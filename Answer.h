//
// Created by Nima iji on 11/28/2018 AD.
//

#ifndef STACKOVERFLOW_IN_CPP_ANSWER_H
#define STACKOVERFLOW_IN_CPP_ANSWER_H

#include "DatabaseCore/xVector.h"

class Answer {
    xVector<Answer> answers;
    int like;
    string text;
};


#endif //STACKOVERFLOW_IN_CPP_ANSWER_H
