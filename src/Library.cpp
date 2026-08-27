#include "Library.h"
#include "Book.h"
#include "User.h"
#include "BookNode.h"
#include "UserNode.h"
#include <ncurses.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

Library:: Library(){
    this->init();
    UserChange = false;
    BookChange = false;
    Books = nullptr;//where i forgot
    CurrentUser = nullptr;
    LoadData("../data/Book_data.txt","../data/User_data.txt");
}
void Library:: init() {// Initialize the library with some books and users, loading the TUI
    Users = new UserNode(new User("Root", "root", 0));    
}
void Library:: LoadData(const std::string& book,const std::string& user) {//Load data from files, books and users
    std::ifstream bfs(book);
    if(!bfs) {
        std::cout<<"Failed to load Book\n";
        return;
    }

    std::string line;
    while(std::getline(bfs,line)){
        int id,year,copies;
        bool Usable = false;
        std::string author,title;

        std::stringstream ss(line);//split the whole line with space
        ss >> id >> title >> author >> year >> copies >> Usable;
        if(Usable)
            LoadBook(id,title,author,year,copies);
        else
            continue;
    }

    std::ifstream ufs(user);
    if(!ufs) {
        std::cout<<"Failed to load User\n";
        return;
    }

    while(std::getline(ufs,line)){
        int id;
        bool Usable = false;
        std::string username,password;

        std::stringstream ss(line);//split the whole line with space
        ss >> id >> username >> password >> Usable;
        if(Usable)
            LoadUser(id,username,password);
        else
            continue;
    }
}

void Library::SaveBookData(const std::string& filename,const Book* book){// Save data to files, books
    if (BookChange) { // override
        std::ifstream ifs(filename);
        if (!ifs) {
            std::cout << "Open File Error\n";
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        std::string target = book->GetTitle();
        bool found = false;

        // newline
        std::stringstream new_ss;
        new_ss << book->GetId() << " " << book->GetTitle() << " " 
               << book->GetAuthor() << " " << book->GetYear() << " " 
               << book->GetNum() << " " << 0;

        while (getline(ifs, line)) {
            std::stringstream ss(line);
            int id;
            std::string title;
            ss >> id >> title; // look for

            if (title == target) {
                lines.push_back(new_ss.str()); // replace
                found = true;
            } else {
                lines.push_back(line); // keep the other
            }
        }
        ifs.close();

        if(!found){
            std::cout << "Not Found\n";
        }
        // override old version
        std::ofstream ofs(filename, std::ios::trunc);
        if (!ofs) {
            std::cout << "Write Error\n";
            return;
        }
        for (const auto& l : lines) {
            ofs << l << "\n";
        }
    }
    else {//write
        std::ofstream ofs(filename,std::ios::app);
        if(!ofs){
            std::cout << "Write Error\n";
            return;
        }

        std::stringstream ss;
        ss << book->GetId() << " " 
           << book->GetTitle() << " " 
           << book->GetAuthor() << " " 
           << book->GetYear() << " " 
           <<book->GetNum()<<" "<< 1;
        ofs << ss.str() << "\n";
    }
}

void Library:: SaveUserData(const std::string& filename,const User* user) {// Save data to files, users
    if(UserChange){//delete(override)
        std::ifstream ifs(filename);
        if(!ifs){
            std::cout << "Open File Error\n";
            return;
        }
        
        std::vector<std::string> lines;
        std::string line;
        std::string target = user->GetUserName();
        bool found = false;

        std::stringstream new_ss;
        new_ss << user->GetID() <<" "
               << user->GetUserName() <<" "
               << user->GetPassword() <<" "
               << 0;

        while(getline(ifs,line)){
            int id;
            std::string username,password;

            std::stringstream ss(line);
            ss >> id >> username;

            if(username == target){
                lines.push_back(new_ss.str());
            }
            else{
                lines.push_back(line);
            }
        }
        ifs.close();

        if(!found){
            std::cout << "Not Found\n";
        }
        std::ofstream ofs(filename,std::ios::trunc);
        if(!ofs){
            std::cout << "Write Error\n";
            return;
        }

        for(const auto &line:lines){
            ofs << line << "\n";
        }

    }
    else {//write
        std::ofstream ofs(filename,std::ios::app);
        if(!ofs){
            std::cout << "Write Error\n";
            return;
        }

        std::stringstream ss;
        ss << user->GetID() << " " 
           << user->GetUserName() 
           << " " << user->GetPassword() 
           << " " << 1;
        ofs << ss.str() << "\n";
    }
}
void Library:: LoadTUI() {}//Text User Interface

void Library:: UserRegister(const std::string& username, const std::string& password) {//all can do
    User* newUser = new User(username, password,Usernum);
    UserNode* newNode = new UserNode(newUser);
    UserChange = false;
    SaveUserData("../data/User_data.txt",newUser);
    if(Users == nullptr) {
        Users = newNode;
    } else {
        UserNode* tmp = Users;
        while(tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
    Usernum++;
}

void Library::UserRemove(const int id){
    if(CurrentUser->GetUserName() != "Root"){
        std::cout << "Only the root user can remove books.\n";
        return;
    }

    UserNode *tmp = Users;
    UserNode *prev = nullptr;
    
    while(tmp != nullptr){
        if(tmp->user->GetID() == id){
            if(prev == nullptr){
                Users = tmp->next;
            }
            else{
                prev->next = tmp->next;
            }
            UserChange = true;
            SaveUserData("../data/User_data" , tmp->user);
            delete tmp->user;
            delete tmp;
            std::cout << "User Remove Successfully\n";
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    std::cout<<"User Not Found\n";
}

bool Library:: UserLogin(const std::string& username, const std::string& password) {
    UserNode* usr = Users;
    while(usr != nullptr) {
        if(usr->user->GetUserName() == username) {
            if(usr->user->GetPassword() == password) {
                CurrentUser = usr->user;
                return true;
            } 
            else {
                std::cout << "Incorrect password.\n";
                return false;
            }
        }
        usr = usr->next;
    } 
    std::cout << "User not found.\n";
    return false;
}

void Library::AddBook(const int id, const std::string& title, const std::string& author, int year) {
    if (CurrentUser == nullptr || CurrentUser->GetUserName() != "Root") {
        std::cout << "Only the root user can add new books.\n";
        return;
    }

    // find books with the same id
    BookNode* tmp = Books;
    BookNode* prev = nullptr;

    while (tmp != nullptr) {
        if (tmp->book->GetId() == id) {
            tmp->book->ChangeNum(tmp->book->GetNum() + 1); // increase the number of the existed book
            std::cout << "Book count increased successfully.\n";
            return; 
        }
        prev = tmp;      
        tmp = tmp->next; 
    }

    //new a book
    Book* newBook = new Book(title, author, year, id);
    newBook->ChangeNum(1); 
    BookNode* newNode = new BookNode(newBook);
    BookChange = false;
    SaveBookData("../data/Book_data.txt",newBook);

    
    if (Books == nullptr) {
        Books = newNode; // in the head
    } else {
        prev->next = newNode; //insert in the end
    }

    Booknum++;
    std::cout << "New book added successfully.\n";
}

void Library:: RemoveBook(const int id) {//for root
    if(CurrentUser->GetUserName() != "Root"){
        std::cout << "Only the root user can remove books.\n";
        return;
    }
    else{
        BookNode* tmp = Books;
        BookNode* prev = nullptr;
        while(tmp != nullptr) {
            if(tmp->book->GetId() == id) {
                if(prev == nullptr) {
                        Books = tmp->next;
                } 
                else {
                    prev->next = tmp->next;
                }
                BookChange = true;
                SaveBookData("../data/Book_data.txt",tmp->book);

                delete tmp->book;
                delete tmp;

                std::cout << "Book removed successfully.\n";
                return;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
        std::cout << "Book not found.\n";
}


void Library::LoadBook(const int id, const std::string& title, const std::string& author, int year,int copies) {//use when load
    // find books with the same id
    BookNode* tmp = Books;
    BookNode* prev = nullptr;

    while (tmp != nullptr) {
        if (tmp->book->GetId() == id) {
            tmp->book->ChangeNum(tmp->book->GetNum() + copies); // unipue the books data
            return; 
        }
        prev = tmp;      
        tmp = tmp->next; 
    }

    //new a book
    Book* newBook = new Book(title, author, year, id);
    newBook->ChangeNum(copies); 
    BookNode* newNode = new BookNode(newBook);

    
    if (Books == nullptr) {
        Books = newNode; // in the head
    } else {
        prev->next = newNode; //insert in the end
    }

    Booknum++;
}

void Library::LoadUser(const int id,const std::string& username, const std::string& password){
    User* newUser = new User(username, password,id);
        UserNode* newNode = new UserNode(newUser);
        if(Users == nullptr) {
            Users = newNode;
        } else {
            UserNode* tmp = Users;
            while(tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = newNode;
        }
        Usernum++;
}

bool Library:: ShowAllBooks() const {//all users can see all books
    BookNode* tmp = Books;
    if(tmp == nullptr) {
        std::cout << "No books available.\n";
        return false;
    }
    while(tmp != nullptr) {
        std::cout << "ID: " << tmp->book->GetId() 
                  << ", Title: " << tmp->book->GetTitle() 
                  << ", Author: " << tmp->book->GetAuthor() 
                  << ", Year: " << tmp->book->GetYear() 
                  << ", Available Copies: " << tmp->book->GetNum() << "\n";
        tmp = tmp->next;
    }   
    return true; 
}
void Library:: ShowAllUsers() const {//root user can see all users
    if(CurrentUser->GetUserName() != "Root"){
        std::cout << "Only the root user can see all users.\n";
    }
    else{
        UserNode* tmp = Users;
        if(tmp == nullptr) {
            std::cout << "No users available.\n";
            return;
        }
        while(tmp != nullptr) {
            std::cout << "ID: " << tmp->user->GetID() 
                      << ", Username: " << tmp->user->GetUserName() << "\n";
            tmp = tmp->next;
        }
    }
}
void Library:: BorrowBook(const int id) {
    BookNode* tmp = Books;
    while(tmp != nullptr) {
        if(tmp->book->GetId() == id) {
            if(tmp->book->GetNum() <= 0) {
                std::cout << "No available copies of this book.\n";
                return;
            }
            CurrentUser->BorrowBook(tmp->book);
            tmp->book->ChangeNum(tmp->book->GetNum() - 1); // Decrease the number of available copies
            std::cout << "Book borrowed successfully.\n";
            return;
        }
        tmp = tmp->next;
    }
}
void Library:: ReturnBook(const int id) {
    BookNode* tmp = CurrentUser->GetBorrowedBook();
    while(tmp != nullptr) {
        if(tmp->book->GetId() == id) {
            tmp->book->ChangeNum(tmp->book->GetNum() + 1); // Increase the number of available copies
            CurrentUser->ReturnBook(tmp->book);//change num before delete the booknode.
            std::cout << "Book returned successfully.\n";
            return;
        }
        tmp = tmp->next;//forgot
    }
}

Library::~Library(){
    while(Users != nullptr){
        UserNode *tmp = Users;
        Users = Users->next;
        delete tmp->user; 
        delete tmp;
    }

    while(Books != nullptr){
        BookNode *tmp = Books;
        Books = Books->next;
        delete tmp->book;//release Book first,then release BookNode;
        delete tmp;
    }

    CurrentUser = nullptr;//just remain null
}