<<<<<<< HEAD
#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include "logger.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;


enum MenuState {
    START,
    LOGGED_IN,
    END
};

int main() {
	Loggers* log = Logger::getInstance();
    User::init("SECRET_KEY");
    User * loggedInUser = nullptr;
    MenuState menuState = MenuState::START;
    string last_message;

    char choice;
    while(menuState != MenuState::END) {
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
                            loggedInUser = &User::login(username,password);
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
                cout << "d.delete account\nl. logout\ne. exit\n";
                cin >> choice;
                switch (choice) {
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
=======
#include <iostream>
#include <stdlib.h>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include "DatabaseCore/Database.h"
#include "Post.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;


enum MenuState {
    START,
    LOGGED_IN,
    POSTING,
    END
};

int main() {

    // Creating a database
    Database<User> users();
    Database<Post> posts();


    User::init("SECRET_KEY");
    User * loggedInUser = nullptr;
    MenuState menuState = MenuState::START;
    string last_message;

    char choice;
    while(menuState != MenuState::END) {
        system(CLEAR);
        if (!last_message.empty())
            cout << last_message << endl;
        last_message = "";
        switch (menuState) {
            case MenuState::START: {
                cout << "1. login\n2. signup\n3. write a question\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case '1': { // login
                        try {
                            string username, password;
                            cout << "Enter Username: ";
                            cin >> username;
                            cout << "Enter Password: ";
                            cin >> password;
                            loggedInUser = &User::login(username,password,0);
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
                            last_message = "User signed up!\n";
                        } catch (UsernameAlreadyExistsException &e) {
                            last_message = e.what();
                            break;

                        } catch (EmailAlreadyExistsException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case '3':{
                        string title,text;
                        cout<<"Enter a title:   "<<endl;
                        cin>>title;
                        cout<<"Enter a question:    "<<endl;
                        //getline(cin,text);
                        cin>>text;
                        menuState = MenuState::POSTING;
                        cout<<"title is:\t"<<title<<endl<<"text is:\t"<<text<<endl;
                        Post post(title,text);
                        //posts().insertIndex(post);
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
                cout << "d.delete account\nl. logout\ne. exit\n";
                cin >> choice;
                switch (choice) {
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
>>>>>>> ba5cb287c1c23b7e27ebce536e92b15e8daa7f6f
