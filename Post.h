//
// Created by Nima iji on 11/28/2018 AD.
//

#ifndef STACKOVERFLOW_IN_CPP_POST_H
#define STACKOVERFLOW_IN_CPP_POST_H

#include "DatabaseCore/xVector.h"
#include "Answer.h"
class Post {
private:
    string title,text;
    int like;
    xVector<Answer> answers;
    //Todo : time
public:
    Post(string title,string text):text(text){};
};


#endif //STACKOVERFLOW_IN_CPP_POST_H
