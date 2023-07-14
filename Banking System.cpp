//A banking system program 
// v1.0
//SEMESTER PROJECT
#include <iostream>
#include <fstream>//file handling
#include <Windows.h>//delay functionalities
#include <string>
#include <conio.h>//for _getch()


//reset password admin
void resetPass() {
    std::string oldPass;

    std::cout << "\n\t\t\t\tEnter old password: ";
    std::cin >> oldPass;//indicates the line you want to change

    std::ifstream aData;
    aData.open("admin.txt");

    std::string line;
    std::ofstream temp;//create a temporary file to store old data and add the new data you want to update
    temp.open("temp.txt", std::ios::app);
    //adds old data to the temporary file except the line you want to update 
    while (getline(aData, line)) {
        if (!aData.eof() && line != oldPass) {
            temp << line << std::endl;
        }
    }
    aData.close();
    temp.close();
    remove("admin.txt");//remove the old database
    rename("temp.txt", "admin.txt");//change the temporary file to be current the main database 

    std::string newPass;
    std::cout << "Enter new Password: ";
    int ch;
    ch = _getch();
    //hides the password
    while (ch != 13) {
        newPass.push_back(ch);
        std::cout << "*";
        ch = _getch();
    }


    temp.open("admin.txt", std::ios::app);
    //add the new password to the current main database
    temp << newPass;

    system("cls"); //clear console

    std::cout << "Password changed successfully " << std::endl;


}
//register new user
void  registerUser() {
    std::string userName;
    std::string  password;
    std::cout << "\n\t\t\t\t Enter User Name : ";
    std::cin >> userName;
    int ch;
    std::cout << "\n\t\t\t\t Password: ";
    ch = _getch();//gets the characters 

    /*13 is ASCII code for Enter .
    As long as user doesn't hit ENTER it keeps collecting characters
    and inserts to the password*/
    //this loop hides the password
    while (ch != 13) {
        password.push_back(ch);//inserts the characters to the password
        std::cout << "*";
        ch = _getch();
    }

    std::fstream uData;
    uData.open("usersDB.txt ", std::ios::app);

    if (uData.is_open()) {
        uData << userName << " " << password << " ";
    }

    uData.close();

    std::cout << "\n\n\t\t\t\t\t****REGISTRATION SUCCESSFUL****" << std::endl;


}
//deposit cash for the user
void deposit() {
    int amount;
    std::string userN;
    std::cout << "\t\t\twhich User do you want to deposit for : ";
    std::cin >> userN;

    int k = 0;

    std::string UserN2;

    std::ifstream uData;
    uData.open("usersDB.txt ");

    if (uData.is_open()) {
        while (uData >> UserN2) {
            if (UserN2 == userN) {
                k = 1;//checks if the user exits
            }
        }
        uData.close();
    }

    if (k == 1) {
        std::cout << "\n\t\t\tEnter the amount you want to deposit: ";
        std::cin >> amount;

        std::ofstream uData2;
        uData2.open("usersDB.txt ", std::ios::app);

        uData2 << amount << std::endl;
        uData2.close();

        std::cout << "\n\t\t\tsuccessfully deposited " << std::endl;
    }
    else if (k != 1) {
        std::cout << "\n\t\t\t User doesn't exist !" << std::endl;
    }



}
//admin menu
void  administratorLogin() {
m:
    std::string password, userName;

    std::cout << "\t\t\t\t Enter User Name: ";
    std::cin >> userName;
    int ch, k = 0;
    std::cout << "\n\n\t\t\t\t Enter password: ";
    ch = _getch();
    //this loop hides the password
    while (ch != 13) {
        password.push_back(ch);
        std::cout << "*";
        ch = _getch();
    }

    std::ifstream aData;
    aData.open("admin.txt");
    std::string aName, aPass;

    if (aData.is_open()) {
        while (aData >> aName >> aPass) {
            if (password == aPass && userName == aName) {
                k = 1;
            }
        }
        aData.close();
    }

    if (k == 1) {
        system("cls");
        std::cout << "\n\n\t\t\t\t\t *** LOGIN SUCCESSFUL ***";
        Sleep(700);
        system("cls");
    n:
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\t\t\t\t|-----------------------------------------------------|\n";
        std::cout << "\t\t\t\t|     Welcome to the Registration and Deposit page    |\n";
        std::cout << "\t\t\t\t|-----------------------------------------------------|\n";
        std::cout << "\t\t\t\t| 1) Deposit money for client                         |\n";
        std::cout << "\t\t\t\t| 2) Register new client                              |\n";
        std::cout << "\t\t\t\t| 3) Reset Password                                   |\n";
        std::cout << "\t\t\t\t|-----------------------------------------------------|\n";

        int choice;
        std::cout << "\n\t\t\t\tChoose an option to proceed: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            deposit();
            break;
        case 2:
            system("cls");
            registerUser();
            break;
        case 3:
            system("cls");
            resetPass();
            break;
        default:
            std::cout << "\n\t\t\t\tPlease choose a valid option from the choices given!\n";
            Sleep(600);
            system("cls");
            goto n;
        }

    }
    else {
        std::cout << "\n\n\t\t\t\t\t Access denied !" << std::endl;
        Sleep(800);
        system("cls");
        goto m;
    }
}



//reset user pass
void resetUserPass() {
    std::string userName, password, pass, line;
    int amount;

    std::cout << "\n\t\t\t\tEnter Old Password: ";
    std::cin >> password;

    std::ifstream uData;
    uData.open("usersDB.txt ");

    std::ofstream temp;
    temp.open("temp.txt", std::ios::app);
    if (uData.is_open()) {
        while (uData >> userName >> pass >> amount) {
            if (!uData.eof() && pass != password) {
                temp << userName << " " << pass << " " << amount << std::endl;
            }
        }
    }
    uData.close();
    temp.close();


    std::string newPass;

    std::cout << "\n\t\t\t\tEnter new password: ";
    std::cin >> newPass;

    temp.open("temp.txt ", std::ios::app);
    uData.open("usersDB.txt");

    if (uData.is_open()) {
        while (uData >> userName >> pass >> amount) {
            if (!uData.eof() && pass == password) {
                temp << userName << " " << newPass << " " << amount << std::endl;
            }
        }
    }
    uData.close();
    temp.close();

    remove("usersDB.txt ");
    rename("temp.txt", "usersDB.txt ");

    std::cout << "\n\t\t\t\tPassword successfully changed ! " << std::endl;
}
//check balance for user
void checkBalance() {
    std::ifstream uData;
    uData.open("usersDB.txt ");

    std::string uName, password, pass;
    int amount;
    std::cout << "\n\t\t\t\tEnter password: ";


    int ch;
    ch = _getch();
    while (ch != 13) {
        pass.push_back(ch);
        std::cout << "*";
        ch = _getch();
    }




    if (uData.is_open()) {
        while (uData >> uName >> password >> amount) {
            if (password == pass)

                std::cout << "\n\n\t\t\t\t Balance is: " << amount << std::endl;
        }       std::cout << "\n\t\t\t\t          ----------";
        uData.close();
    }


}
//withdraw cash 
void withdrawCash() {
    std::string userName, password, pass;
    int amount, k = 0;

    std::cout << "\n\t\t\t\tEnter Password: ";

    int ch;
    ch = _getch();
    while (ch != 13) {
        password.push_back(ch);
        std::cout << "*";
        ch = _getch();
    }

    std::ifstream uData;
    uData.open("usersDB.txt ");

    std::ofstream temp;
    temp.open("temp.txt", std::ios::app);



    if (uData.is_open()) {
        while (uData >> userName >> pass >> amount) {
            if (!uData.eof() && pass != password) {
                temp << userName << " " << pass << " " << amount << std::endl;
            }
        }
    }
    uData.close();
    temp.close();

p:
    int newAmount;

    std::cout << "\n\t\t\t\tHow much do you want to withdraw: ";
    std::cin >> newAmount;

    temp.open("temp.txt ", std::ios::app);
    uData.open("usersDB.txt");

    if (uData.is_open()) {
        while (uData >> userName >> pass >> amount) {
            if (!uData.eof() && pass == password) {
                //checks if the amount is sufficient to work with
                if (amount >= newAmount) {
                    amount -= newAmount;
                    temp << userName << " " << pass << " " << amount << std::endl;
                    k = 1;
                }
                else if (amount < newAmount) {
                    std::cout << "\n\t\t\t\tYou cant withdraw Cash!" << std::endl;
                }
                else {
                    std::cout << "\n\t\t\t\tPlease enter a valid amount !" << std::endl;
                    Sleep(600);
                    system("cls");
                    goto p;
                }

            }
        }
    }
    uData.close();
    temp.close();

    remove("usersDB.txt ");
    rename("temp.txt", "usersDB.txt ");

    if (k == 1) {
        std::cout << "\n\t\t\t\t    Account successfully credited ! " << std::endl;
        std::cout << "\n\t\t\t\t|--------------------------------------|\n";
    }


}



//user menu
void userMenu() {
o:
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t\t\t|-----------------------------------------------------------------------|\n";
    std::cout << "\t\t\t|                        **** WELCOME USER ***                          |\n";
    std::cout << "\t\t\t|-----------------------------------------------------------------------|\n";
    std::cout << "\t\t\t|                                                                       |\n";
    std::cout << "\t\t\t| 1) Withdraw Cash                                                      |\n";
    std::cout << "\t\t\t|                                                                       |\n";
    std::cout << "\t\t\t| 2) Check balance                                                      |\n";
    std::cout << "\t\t\t|                                                                       |\n";
    std::cout << "\t\t\t| 3) Reset Password                                                     |\n";
    std::cout << "\t\t\t|                                                                       |\n";
    std::cout << "\t\t\t|-----------------------------------------------------------------------|\n";

    int choice;
    std::cout << "\n\t\t\t\tChoose an option: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        withdrawCash();
        break;
    case 2:
        system("cls");
        checkBalance();
        break;
    case 3:
        system("cls");
        resetUserPass();
        break;
    default:
        std::cout << "\n\t\t\t\tPlease choose a valid option from the choices given!\n";
        Sleep(600);
        system("cls");
        goto o;
    }

}




//user-login
void  userLogin() {
m://allows the user to choose again if they  enter invalid option and tells the compiler to repeat the process after this point

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t\t\t|------------------------------------------------------------------------|\n";
    std::cout << "\t\t\t|                                                                        |\n";
    std::cout << "\t\t\t|                Welcome to the normal User Login page                   |\n";
    std::cout << "\t\t\t|                                                                        |\n";
    std::cout << "\t\t\t|------------------------------------------------------------------------|\n";


    std::string uName;
    std::string password;
    int ch;
    int k = 0;//checks if user successfully logged in

    std::cout << "\n\t\t\t\t Enter User Name: ";
    std::cin >> uName;
    std::cout << "\n\t\t\t\t Password: ";

    ch = _getch();
    while (ch != 13) {
        password.push_back(ch);
        std::cout << "*";
        ch = _getch();
    }

    std::fstream uData;
    uData.open("usersDB.txt ", std::ios::in);

    std::string uSerName, pass;
    int amount;

    if (uData.is_open()) {
        while (uData >> uSerName >> pass >> amount) {
            if (uSerName == uName && password == pass) {
                k = 1;
            }
        }

        uData.close();
    }

    if (k == 1) {
        system("cls");
        std::cout << "\n\n\t\t\t\t\t\t*** Welcome ***" << std::endl;
        std::cout << "t\t\t\t\t\t|----------------------------|\n";

        Sleep(500);//delay for 1 second
        system("CLS");

        userMenu();//go to user menu function
    }
    else if (k != 1) {
        std::cout << "\n\n\t\t\t\t\t\t   Failed to log in - Please try again  " << std::endl;
        Sleep(500);
        system("cls");
        goto m;//takes the user wherever m was defined and repeats the process below m
    }


}
//main menu
void menu() {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t\t\t|----------------------------------------------------------------|\n";
    std::cout << "\t\t\t|         *** WELCOME TO STRATHMORE E-CASH SERVICES ***          |\n";
    std::cout << "\t\t\t|----------------------------------------------------------------|\n";
    std::cout << "\t\t\t|                                                                |\n";
    std::cout << "\t\t\t| 1) User                                                        |\n";
    std::cout << "\t\t\t|                                                                |\n";
    std::cout << "\t\t\t| 2) Administrator                                               |\n";
    std::cout << "\t\t\t|                                                                |\n";
    std::cout << "\t\t\t| 3) Exit                                                        |\n";
    std::cout << "\t\t\t|                                                                |\n";
    std::cout << "\t\t\t|----------------------------------------------------------------|\n";

    int choice;
    std::cout << "\n\t\t\tChoose an option to proceed: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        userLogin();
        break;
    case 2:
        system("cls");
        administratorLogin();
        break;
    case 3:
        system("cls");
        exit(0);
        break;
    default:
        std::cout << "\t\t\tPlease choose a valid option from the choices given!\n";
    }
}

int main()
{
    menu();

    system("pause>0");
}


//CREATED BY MOHAMED ABDIKAFi