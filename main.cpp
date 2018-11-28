#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <DatabaseCore/xVector.h>
//#include "Logger.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;

class Loggers {
protected:
    Loggers() { };
    static Loggers *instance;
    static int count;
public:
    virtual void Log(User t){};

};

Loggers *Loggers::instance = NULL;

int Loggers::count = 0;


class Logger : public Loggers {
public:

    static Loggers *getInstance() {
        if (instance == NULL) {
            instance = new Logger();
            return instance;
        }else {
            return instance;
        }
    };

    void Log(User a) {
        count++;
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);



			fstream f("Log.txt", ios::app | ios::in | ios::out);
			f << "-----------------------------------------------------------------------" << endl;
			f << "Log" << count << ":    " << a.getEmail() << "  "
				<< a.username << "    Local: " << asctime(timeinfo) << endl;
			f.close();

    };

private:
    Logger(){};

};


enum MenuState {
    START,
    LOGGED_IN,
    END
};

int main() {
    xVector<Post> posts;
    Loggers *log = Logger::getInstance();
    //Loggers *loggers = Logger::getInstance();
    User::init("SECRET_KEY");
    User *loggedInUser = nullptr;
    MenuState menuState = MenuState::START;
    string last_message;

    char choice;
    while (menuState != MenuState::END) {
        system(CLEAR);
        if (!last_message.empty())
            cout << last_message << endl;
        last_message = "";
        switch (menuState) {
            case MenuState::START: {
                cout << "1. login\n2. signup\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case '1': { // login
                        try {
                            string username, password;
                            cout << "Enter Username: ";
                            cin >> username;
                            cout << "Enter Password: ";
                            cin >> password;
                            loggedInUser = &User::login(username, password, 0);
                            log->Log(*loggedInUser);
                            menuState = MenuState::LOGGED_IN;
                        } catch (WrongUsernameOrPasswordException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case '2': { // signup
                        try {
                            string username, password, email;
                            cout << "Enter Email: ";
                            cin >> email;
                            cout << "Enter Username: ";
                            cin >> username;
                            cout << "Enter Password: ";
                            cin >> password;
                            loggedInUser = &User::signup(username, password, email);
                            menuState = MenuState::LOGGED_IN;
							log->Log(*loggedInUser);
                            last_message = "User signed up!\n";
                        } catch (UsernameAlreadyExistsException &e) {
                            last_message = e.what();
                            break;

                        } catch (EmailAlreadyExistsException &e) {
                            last_message = e.what();
                        }
                        break;
                    }

                    case 'e': { // exit
                        menuState = MenuState::END;
                        break;
                    }
                    default: { // unknown input
                        last_message = "Unknown Input\n";
                        break;
                    }
                }
                break;
            }
            case MenuState::LOGGED_IN: {
                cout << "a. show all questions\nd. delete account\nl. logout\nw. write a question\ns. show all my posts\nx. delete a post by number\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case 'a':{
                        for(auto p:posts){
                            int cn = 0;
                            for(auto &p:posts){
                                cn++;
                                cout<<cn<<". Title:\t"<<p.title<<endl<<"Text:\t"<<p.text<<endl<<"Author:\t"<<p.author<<endl<<endl;
                            }
                        }
                        char cc;
                        cout<<"n. answer question\nb. back"<<endl;
                        cin>>cc;
                        switch(cc){
                            case 'n':{
                                int num = 0;
                                string aws;
                                cout<<"give me number of question:"<<endl;
                                cin>>num;
                                Post p = posts.at(num-1);

                                cout<<p.title<<endl;
                                cout<<"Title:\t"<<p.title<<endl<<"Text:\t"<<p.text<<"Author:\t"<<p.author<<endl<<endl;
                                cout<<"All Answers:"<<endl;
                                for (auto aa:p.answers) {
                                    cout<<aa.text<<endl;
                                }
                                cout<<"please wrtie your answer:\t";
                                cin>>aws;
                                Answer a(aws);
                                p.answers.push_back(a);
                                break;
                            }
                            case 'b':{
                                break;
                            }

                        }
                        break;
                    }
                    case 'x':{
                        int inx;
                        cout<<"Please insert post number:"<<endl;
                        cin>>inx;
                        loggedInUser->dltPost(inx);
                        break;
                    }
                    case 's':{
                        cout<<"Your posts are:"<<endl;
                        loggedInUser->printAllPosts();
                        break;
                    }
                    case 'w':{
                        string title,text;
                        cout<<"Enter title:\t"<<endl;
                        cin>>title;
                        cout<<"Enter text:\t"<<endl;
                        cin>>text;
                        Post p(title,text,loggedInUser->username);
                        loggedInUser->addPost(p);
                        posts.push_back(p);
                        break;
                    }
                    case 'd': {
                        try {
                            loggedInUser->deleteAccount();
                            cout << "Account successfully deleted\n";
                            loggedInUser = nullptr;
                            menuState = MenuState::START;
                        }
                        catch (DeleteAdminException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case 'l': { // logout
                        loggedInUser = nullptr;
                        menuState = MenuState::START;
                        last_message = "GOOD BYE\n";
                        break;
                    }
                    case 'e': { // exit
                        menuState = MenuState::END;
                        break;
                    }
                    default: { // unknown input
                        last_message = "Unknown Input\n";
                        break;
                    }

                }
            }

        }
    }
    system(CLEAR);
    cout << "GOODBYE" << endl;
    return 0;
}
