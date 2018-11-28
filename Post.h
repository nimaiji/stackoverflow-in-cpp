//
// Created by Nima iji on 11/28/2018 AD.
//

#ifndef STACKOVERFLOW_IN_CPP_POST_H
#define STACKOVERFLOW_IN_CPP_POST_H

#include "DatabaseCore/xVector.h"
#include "Answer.h"
class Post {
public:
    string title,text,author;
    int like;
    xVector<Answer> answers;
    //Todo : time
    Post(string title,string text,string author):text(text),title(title),author(author){};
};


#endif //STACKOVERFLOW_IN_CPP_POST_H
