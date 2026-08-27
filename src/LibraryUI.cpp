#include "LibraryUI.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ncurses.h>
#include "Book.h"
#include "User.h"
#include "BookNode.h"
#include "UserNode.h"
#include "Library.h"
//interact interface

void LibraryUI::clear_cin(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void LibraryUI::Login(){
    bool Permissions = false;
    std::string username, password;
    std::cout<<"Enter username: ";
    std::cin >> username;
    clear_cin();
    std::cout<<"Enter password: ";
    std::cin >> password;
    clear_cin();
    if( library.UserLogin(username, password)) {
        std::cout<<"Login successful. Welcome, " << username << "!\n";
        // library.LoadTUI();
        if(username == "Root") 
            Permissions = true;
        else 
            Permissions = false;
    }

    UserMenu(Permissions);
}

void LibraryUI::Register(){

}

void LibraryUI::UserMenu(const bool& Permissions){
    char op2;
    bool run2 = true;
    while(run2){
        std::cout<<"Library Management System Menu:\n";
        std::cout<<"0. Backward\n";
        std::cout<<"1. Borrow books\n";
        std::cout<<"2. Return books\n";
        std::cout<<"3. List borrowed books\n"; 
        
        if (Permissions) {
            std::cout<<"4. Show all users\n";
            std::cout<<"5. Remove User\n";
            std::cout<<"6. Add a book\n";
            std::cout<<"7. Remove a book\n";
        }

        std::cin >> op2;
        clear_cin();
        switch(op2){
            case '0':
                std::cout << "Logging out...\n";
                run2 = false;
                break;
            case '1':
                BorrowBook();
                break;
            case '2':
                ReturnBook();
                break;
            case '3':
                std::cout << "Books you have borrowed:\n";
                if(library.GetCurrentUser()->GetBorrowedCount() <= 0) {
                    std::cout << "You have not borrowed a book\n";
                }
                library.GetCurrentUser()->ShowBorrowedBooks();
                break;
            case '4':
                if(!Permissions) {
                    std::cout << "Invalid option. Please try again.\n";
                    break;
                }
                else {
                    library.ShowAllUsers();
                }
                break;
            case '5':
                if(!Permissions) {
                    std::cout << "Invalid option. Please try again.\n";
                    break;
                }
                else{
                    RemoveUser();
                }
                break;
            case '6':
                if(!Permissions) {
                    std::cout << "Invalid option. Please try again.\n";
                    break;
                }
                else{
                    AddBook();
                }
                break;
            case '7':
                if(!Permissions) {
                    std::cout << "Invalid option. Please try again.\n";
                    break;
                }
                else{
                    RemoveBook();
                }
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    }
}

void LibraryUI::BorrowBook(){
    int borrowId;
                         
    if(library.ShowAllBooks()){
        std::cout << "Enter the ID of the book to borrow: ";
        std::cin >> borrowId;
        clear_cin();
        if(borrowId == 0) {//exit the borrow operation
            std::cout << "Exiting operation...\n";
            return;
        }
        library.BorrowBook(borrowId);
    }
    else {}
    return;
}

void LibraryUI::ReturnBook(){
    int returnId;
                                
    std::cout << "Books you have borrowed:\n";
    library.GetCurrentUser()->ShowBorrowedBooks();
    if(library.GetCurrentUser()->GetBorrowedBook() != nullptr){
            std::cout << "Enter the ID of the book to return: ";
        std::cin >> returnId;
        clear_cin();
        if(returnId == 0) {//exit the return operation
            std::cout << "Exiting operation...\n";
            return;
        }
        library.ReturnBook(returnId);
    }
    return;
}

void LibraryUI::RemoveUser(){
    int id;
    std::cout << "Enter user ID to remove: ";
    std::cin >> id;
    clear_cin();
    if(id == 0){
        std::cout << "Exiting operation...\n";
        return;
    }
    library.UserRemove(id);
}

void LibraryUI::AddBook(){
    int id, year;
    std::string title, author;
    std::cout << "Enter book ID: ";
    std::cin >> id;
    clear_cin();
    if(id == 0){
        std::cout << "Exiting operation...\n";
        return;
    }
    std::cout << "Enter book title: ";
    std::cin >> title;
    clear_cin();
    if(title == "0"){
        std::cout << "Exiting operation...\n";
        return;
    }
    std::cout << "Enter book author: ";
    std::cin >> author;
    clear_cin();
    if(author == "0"){
        std::cout << "Exiting operation...\n";
        return;
    }
    std::cout << "Enter book year: ";
    std::cin >> year;
    clear_cin();
    if(year == 0){
        std::cout << "Exiting operation...\n";
        return;
    }
    library.AddBook(id, title, author, year);
}

void LibraryUI::RemoveBook(){
    int id;
    std::cout << "Enter book ID to remove: ";
    std::cin >> id;
    clear_cin();

    if(id == 0){
        std::cout << "Exiting operation...\n";
        return;
    }
    library.RemoveBook(id);
}




void LibraryUI::run(){
    char op1;
    bool run1 = true;
    while(run1){
        std::cout<< "Welcome to the Library Management System\n";
        std::cout<< "1. Login\n";
        std::cout<<"2. register new user\n";
        std::cout<<"3. Exit\n";
        std::cout<<"input options number to operate: ";
        std::cin >> op1;
        clear_cin();
        switch(op1){
            case '1':
                Login();
                break;
            case '2':
                Register();
                break;
            case '3':
                std::cout << "Exiting the system. Goodbye!\n";
                run1 = false;
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}