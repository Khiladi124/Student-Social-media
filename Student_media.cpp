#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;

void message(void);
void receive(void);
void send(void);
void afterLogin(void);
void rate(void);

class UserInfo {
public:
    string password;
    string username;
    int followers;
    int following;

    // Default constructor
    UserInfo() {
        followers = 1;
        following = 1;
    }
} user;

class CloseFriend : public UserInfo {
public:
    void makeCloseFriend(string friendName) {
        ofstream file;
        file.open("D:\\College\\C++\\Sem-3\\" + user.username + "_closeFriends.txt", file.out | file.app);
        file << friendName << endl;
        file.close();
    }

    friend void showCloseFriends();
};

void showCloseFriends() {
    string friendName;
    ifstream read;
    read.open("D:\\College\\C++\\Sem-3\\" + user.username + "_closeFriends.txt");
    cout << "Close Friends list: \n";
    while (getline(read, friendName)) {
        cout << friendName << endl;
    }
    read.close();
}

bool checkFileIsEmpty(ifstream &file) {
    return file.peek() == EOF;
}

bool loggedIn() {
    string enteredUsername, enteredPassword;
    
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
    cout << "\t\t\t\t\t\t\t\t ------------\n\n\n\n";
    cout << "\t\t\t Enter Username : ";
    cin >> user.username;
    cout << "\n\n\t\t\t Enter Password : ";
    cin >> user.password;

    ifstream read;
    read.open("D:\\College\\C++\\Sem-3\\" + user.username + ".txt");
    getline(read, enteredUsername);
    getline(read, enteredPassword);

    if (enteredUsername == user.username && enteredPassword == user.password) {
        return true;
    } else {
        return false;
    }
}

void search() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
    cout << "\t\t\t\t\t\t\t\t ------------\n\n";
    cout << "\t\t\t Enter username : ";
    string searchedUsername, temp;
    cin >> searchedUsername;

    ifstream read;
    read.open("D:\\College\\C++\\Sem-3\\usernames.txt");
    while (getline(read, temp)) {
        if (temp == searchedUsername) {
            ifstream file;
            string followers[1], following[1];
            file.open("D:\\College\\C++\\Sem-3\\" + searchedUsername + ".txt");

            for (int i = 0; i < 3; i++) {
                getline(file, followers[0]);
            }
            for (int i = 0; i < 4; i++) {
                getline(file, following[0]);
            }

            cout << "\n\n\t\t\t\t\tUser found!!!" << endl;
            cout << "\n\t\t\tUsername : " << searchedUsername << endl;
            cout << "\n\t\t\tFollowers : " << followers[0] << endl;
            cout << "\n\t\t\tFollowing : " << following[0] << endl << endl << endl;

            read.close();
            file.close();

            return;
        }
    }
    cout << "\n\n\t\t\t\t\t No such user found!!" << endl << endl;
    return;
}

void follow() {
    fstream file1;
    fstream file2;
    ifstream read;
    read.open("D:\\College\\C++\\Sem-3\\usernames.txt");

    system("cls");
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
    cout << "\t\t\t\t\t\t\t\t ------------\n\n";
    cout << "\t\t\t Enter username : ";
    string followUsername, temp;
    cin >> followUsername;

    while (getline(read, temp)) {
        if (temp == followUsername) {
            ifstream file;
            string followers[1], following[1];
            file.open("D:\\College\\C++\\Sem-3\\" + followUsername + ".txt");

            for (int i = 0; i < 3; i++) {
                getline(file, followers[0]);
            }
            for (int i = 0; i < 4; i++) {
                getline(file, following[0]);
            }

            cout << "\n\t\t\t\t\t\tUser found!!!" << endl;
            cout << "\t\t\t\t\t\t\t\t ------------\n\n";
            cout << "\n\t\t\tUsername : " << followUsername << endl;
            cout << "\t\t\tFollowers : " << followers[0] << endl;
            cout << "\t\t\tFollowing : " << following[0] << endl;

            read.close();
            file.close();
            cout << "\t\t\t\t\t\t\t\t ------------\n\n";
            cout << "\n\n\t\t\tDo you want to follow?\n\t\t\t 1. Yes\n\t\t\t 2. No\n\t\t\t Your Choice : ";
            int choice;
            cin >> choice;

            if (choice == 2) {
                cout << "\n\t\t\tOkay!!\n\n";
                return;
            } else if (choice == 1) {
                file1.open("D:\\College\\C++\\Sem-3\\" + followUsername + ".txt");
                string line[1];

                for (int i = 0; i < 3; i++) {
                    getline(file1, line[0]);
                }

                string temp = line[0];
                int x = stoi(temp);
                x++;
                temp = to_string(x);

                file1.close();
                file1.open("D:\\College\\C++\\Sem-3\\" + followUsername + ".txt");

                for (int i = 0; i < 2; i++) {
                    getline(file1, line[0]);
                }
                file1 << temp;

                // Increasing the number of following of User.

                file2.open("D:\\College\\C++\\Sem-3\\" + user.username + ".txt");
                string getFollowing[1];

                for (int i = 0; i < 4; i++) {
                    getline(file2, getFollowing[0]);
                }

                string temp2 = getFollowing[0];
                int y = stoi(temp2);
                y++;
                temp2 = to_string(y);
                file2.close();
                file2.open("D:\\College\\C++\\Sem-3\\" + user.username + ".txt");

                for (int i = 0; i < 3; i++) {
                    getline(file2, getFollowing[0]);
                }
                file2 << temp2;
                cout << "\n\n\t\t\tSuccessfully Followed!!\n\n ";
            }
            cout << "press\n1. To add him to close friend\n2. to skip\nEnter your choice: ";
            int key;
            cin >> key;
            if (key == 1) {
                CloseFriend a;
                a.makeCloseFriend(followUsername);
                return;
            } else if (key == 2) {
                return;
            } else {
                cout << "You pressed a wrong key :(";
                return;
            }
        }
    }
    cout << "\n\n\t\t\t\t\tNo such user found" << endl << endl;
    return;
}

void viewProfile() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
    cout << "\t\t\t\t\t\t\t\t ------------\n\n";
    cout << "\t\t\t\t\t\t\t--------YOUR PROFILE PAGE--------\n\n";

    ifstream file;
    string followers[1], following[1];
    file.open("D:\\College\\C++\\Sem-3\\" + user.username + ".txt");

    for (int i = 0; i < 3; i++) {
        getline(file, followers[0]);
    }
    for (int i = 0; i < 4; i++) {
        getline(file, following[0]);
    }

    cout << "\n\t\t\tUsername : " << user.username << endl << endl;
    cout << "\t\t\tFollowers : " << followers[0] << endl << endl;
    cout << "\t\t\tFollowing : " << following[0] << endl << endl << endl;

    file.close();
    cout << "want to see close friends list?(Y/N): ";
    char key;
    cin >> key;
    if (key == 'Y' || key == 'y' || key == 'n' || key == 'N') {
        showCloseFriends();
    } else {
        cout << "enter wrong input :(";
    }
}

void passwordChange() {
    string newPass;
    string temp;
    fstream file;
    
    file.open("D:\\College\\C++\\Sem-3\\" + user.username + ".txt");
    for (int i = 0; i < 2; i++) {
        getline(file, temp);
    }
    file.close();
    system("cls");
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
    cout << "\t\t\t\t\t\t\t\t ------------\n\n";
    cout << "\n\t\t\tEnter current password : ";
    cin >> newPass;
    
    if (newPass == temp) {
        cout << "\n\t\t\tEnter new password : ";
        cin >> newPass;

        file.open("D:\\College\\C++\\Sem-3\\" + user.username + ".txt");
        getline(file, temp);

        file << newPass;
        cout << "\n\n\t\t\t\t\tPassword changed!!!\n\n";
        file.close();
    } else {
        cout << "\n\n\t\t\t\t\tInvalid Password!!!!\n\n";
    }

    system("PAUSE");
    return;
}

void rate() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
    cout << "\t\t\t\t\t\t\t\t ------------\n\n";
    cout << "\n\n\t\t\t\t\tPlease Enter your User Experience by Giving Rating out of 10\n";
    int rating;
    cin >> rating;

    if (rating >= 0 && rating <= 10) {
        cout << "\n\n\t\t\t\t\t\tThank you so much to give your feedback :)\n\n";
        system("PAUSE");
        return;
    } else {
        cout << "\n\n\t\t\t\t\t\tPlease enter value between 0-10 \n";
    }
}
void message()
{
    system("cls");
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
        cout << "\t\t\t\t\t\t\t\t ------------\n\n";
    cout<<"\n\t\t\tEnter :"<<endl<<"\n\n\t\t\t 1 : Send Message "<<endl<<"\n\n\t\t\t 2 : Received Messages  "<<endl<<"\n\n\t\t\t 3 : To Exit"<<endl;
    int choice;
    cin>>choice;
    if(choice==1){
     send();
     cout<<"\n\n\t\t\t Message Sent!!\n\n";
    }
    else if(choice==2){
    receive();
    }
     else if(choice==3){
    after_login();
    }
    else {
        cout<<"\n\n\t\t\tEnter Valid Choice"<<endl;
        system("PAUSE");
        after_login();
    }
}
void receive(){
    system("cls");
    cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
        cout << "\t\t\t\t\t\t\t\t ------------\n\n";
   
    

     ifstream file;
            string followers[1];
            file.open("D:\\College\\C++\\Sem-3\\"+ob.username+"msg.txt");

            for(int i=0; i<15; i++)
            {
                getline(file, followers[0]);
                cout<<followers[0]<<endl;
            }
            file.close();




}
void send(){
     system("cls");
     cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
        cout << "\t\t\t\t\t\t\t\t ------------\n\n";
    time_t now =time(0);
    char* dt = ctime(&now);
    cout<<"\n\t\t\tEnter Name to whom you want to send Message : "<<endl;
    string n,str;
    cin>>n;
    getchar();
    cout<<"\n\n\t\t\t Type Your Message here \n"<<endl;
    getline(cin, str); 
    ofstream file;
    file.open("D:\\College\\C++\\Sem-3\\"+n+"msg.txt", file.out | file.app);
        file<<endl<<str<<"\t\t"<<dt<<"\t\t"<<"From :: "+ob.username<<endl<<endl;
        file.close();

}

void after_login()
{

    while (1)
    {
        system("cls");
        
        cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
        cout << "\t\t\t\t\t\t\t\t ------------\n\n";
        cout << " \t\t\t 1. Search\n\n";
        cout << " \t\t\t 2. Follow\n\n";
        cout << " \t\t\t 3. Messages\n\n";
        cout << " \t\t\t 4. View Profile\n\n";
        cout << " \t\t\t 5. Change Password\n\n";
        cout << " \t\t\t 6. Rate app\n\n";
        cout << " \t\t\t 7. Exit\n\n";

        int choice;
        cin >> choice;
        system("cls");

        switch (choice)
        {
        case 1:
            search();
            system("PAUSE");
            break;
        case 2:
            follow();
            system("PAUSE");
            break;
        case 3:
            message();
            system("PAUSE");
            break;
        case 4:
            view_profile();
            system("PAUSE");
            break;
        case 5:
            password_change();
            break;
        case 6:
            Rate();
            system("PAUSE");
            break;
        case 7:
            system("PAUSE");
            system("cls");
            exit(1);
        default:
            cout<<"\n\t\t\tInvalid input :( \n\n\t\t\tPlease enter values between (0-7)\n";
            system("PAUSE");
            after_login();
            break;
        }
    }
}

int main()
{
    system("cls");

    int choice;
    system("cls");
    cout << "\t\t\t\t\t\t\t\t WELCOME TO STUDENT-GRAM\n";
    cout << "\t\t\t\t\t\t\t\t  -------------------- \n\n\n\n ";
    cout << "\t\t\t\t 1.Register\n\n\n\n";
    cout << "\t\t\t\t 2.Login\n\n\n\n";
    cout << "\t\t\t\t Your choice : ";
    cin >> choice;
    if (choice == 1)
    {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t STUDENT-GRAM\n ";
        cout << "\t\t\t\t\t\t\t\t ------------\n\n\n\n";

        cout << "\t\t\t\t Select a username : ";
        cin >> ob.username;
        cout << "\n\n\t\t\t\t Select a password : ";
        cin >> ob.password;

        // ob.following = ob.followers = 1;

        ofstream file;
        file.open("D:\\College\\C++\\Sem-3\\" + ob.username + ".txt");
        file << ob.username << endl
             << ob.password << endl
             << ob.followers << endl
             << ob.following;
        file.close();

        file.open("D:\\College\\C++\\Sem-3\\usernames.txt", file.out | file.app);
        file << endl
             << ob.username;
        file.close();
        cout<<"\n\n\t\t\t\t\t\t\tAccount Created!!"<<endl<<endl;
        system("PAUSE");
        main();
    }

    else if (choice == 2)
    {
        system("cls");
        bool status = LoggedIn();
        if (!status)
        {
            cout << "\n\n\t\t\t\t\t\t\t Invalid Login!!\n\n";
            system("PAUSE");
            main();
        }
        else
        {
            cout << "\n\n\t\t\t\t\t\t\t Successfully Logged In!!\n\n";
            system("PAUSE");
            after_login();
        }
    }

    else
    {
        system("cls");
         cout << "\t\t\t\t\t\t\t\t WELCOME TO STUDENT-GRAM\n";
    cout << "\t\t\t\t\t\t\t\t  -------------------- \n\n\n\n ";
        cout << "\n\n\t\t\t\t\t Enter valid input : 1 or 2\n\n";
        system("PAUSE");
        main();
    }
}
void Intro(){

}
