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
                cout << "d. delete account\nl. logout\nw. write a question\ns. show all my posts\nx. delete a post by number\ne. exit\n";
                cin >> choice;
                switch (choice) {
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
                        Post p(title,text);
                        loggedInUser->addPost(p);
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

//=======
//
//#include <iostream>
//#include <stdlib.h>
//#include <string>
//#include "AbstractUser.h"
//#include "Exceptions.h"
//#include "User.h"
//#include "DatabaseCore/Database.h"
//#include "Post.h"
//
//#ifdef _WIN32
//#define CLEAR "cls"
//#else //In any other OS
//#define CLEAR "clear"
//#endif
//
//using namespace std;
//
//
//enum MenuState {
//    START,
//    LOGGED_IN,
//    POSTING,
//    END
//};
//
//int main() {
//
//    // Creating a database
//    Database<User> users();
//    Database<Post> posts();
//
//
//    User::init("SECRET_KEY");
//    User *loggedInUser = nullptr;
//    MenuState menuState = MenuState::START;
//    string last_message;
//
//    char choice;
//    while (menuState != MenuState::END) {
//        system(CLEAR);
//        if (!last_message.empty())
//            cout << last_message << endl;
//        last_message = "";
//        switch (menuState) {
//            case MenuState::START: {
//                cout << "1. login\n2. signup\n3. write a question\ne. exit\n";
//                cin >> choice;
//                switch (choice) {
//                    case '1': { // login
//                        try {
//                            string username, password;
//                            cout << "Enter Username: ";
//                            cin >> username;
//                            cout << "Enter Password: ";
//                            cin >> password;
//                            loggedInUser = &User::login(username, password, 0);
//                            menuState = MenuState::LOGGED_IN;
//                        } catch (WrongUsernameOrPasswordException &e) {
//                            last_message = e.what();
//                        }
//                        break;
//                    }
//                    case '2': { // signup
//                        try {
//                            string username, password, email;
//                            cout << "Enter Email: ";
//                            cin >> email;
//                            cout << "Enter Username: ";
//                            cin >> username;
//                            cout << "Enter Password: ";
//                            cin >> password;
//                            loggedInUser = &User::signup(username, password, email);
//                            menuState = MenuState::LOGGED_IN;
//                            last_message = "User signed up!\n";
//                        } catch (UsernameAlreadyExistsException &e) {
//                            last_message = e.what();
//                            break;
//
//                        } catch (EmailAlreadyExistsException &e) {
//                            last_message = e.what();
//                        }
//                        break;
//                    }
//                    case '3': {
//                        string title, text;
//                        cout << "Enter a title:   " << endl;
//                        cin >> title;
//                        cout << "Enter a question:    " << endl;
//                        //getline(cin,text);
//                        cin >> text;
//                        menuState = MenuState::POSTING;
//                        cout << "title is:\t" << title << endl << "text is:\t" << text << endl;
//                        Post post(title, text);
//                        //posts().insertIndex(post);
//                        break;
//                    }
//                    case 'e': { // exit
//                        menuState = MenuState::END;
//                        break;
//                    }
//                    default: { // unknown input
//                        last_message = "Unknown Input\n";
//                        break;
//                    }
//                }
//                break;
//            }
//            case MenuState::LOGGED_IN: {
//                cout << "d.delete account\nl. logout\ne. exit\n";
//                cin >> choice;
//                switch (choice) {
//                    case 'd': {
//                        try {
//                            loggedInUser->deleteAccount();
//                            cout << "Account successfully deleted\n";
//                            loggedInUser = nullptr;
//                            menuState = MenuState::START;
//                        }
//                        catch (DeleteAdminException &e) {
//                            last_message = e.what();
//                        }
//                        break;
//                    }
//                    case 'l': { // logout
//                        loggedInUser = nullptr;
//                        menuState = MenuState::START;
//                        last_message = "GOOD BYE\n";
//                        break;
//                    }
//                    case 'e': { // exit
//                        menuState = MenuState::END;
//                        break;
//                    }
//                    default: { // unknown input
//                        last_message = "Unknown Input\n";
//                        break;
//                    }
//
//                }
//            }
//        }
//    }
//    system(CLEAR);
//    cout << "GOODBYE" << endl;
//    return 0;
//}
//
//>>>>>>> ba5cb287c1c23b7e27ebce536e92b15e8daa7f6f
