#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
class Book;
class User;
class BookNode;
class UserNode;

class Library{
private:
    int Booknum = 0;
    int Usernum = 1;// SDeal with new users' IDs, starting from 1 since the root user has ID 0ool
    bool UserChange;//0->write 1->delete
    bool BookChange;//decrease file write times
    BookNode* Books;
    UserNode* Users;
    User* CurrentUser;
public:
    explicit Library();
    void init();// Initialize the library with some books and users, loading the TUI
    void LoadData(const std::string& book,const std::string& user);// Load data from files, books and users
    void SaveBookData(const std::string& filename,const Book* book);// Save data to files, books
    void SaveUserData(const std::string& filename,const User* user);//Save data to files, users
    void LoadTUI();//Text User Interface
    User* GetCurrentUser() const { return CurrentUser; }
    void UserRegister(const std::string& username, const std::string& password);
    void UserRemove(const int id);
    bool UserLogin(const std::string& username, const std::string& password);
    void AddBook(const int id,const std::string& title, const std::string& author, int year);//for root
    void RemoveBook(const int id);//for root
    bool ShowAllBooks() const;//all users can see all books
    void ShowAllUsers() const;//root user can see all users
    void LoadBook(const int id, const std::string& title, const std::string& author, int year,int copies);//use when load books
    void LoadUser(const int id,const std::string& username, const std::string& password);//use when load users
    void BorrowBook(const int id);
    void ReturnBook(const int id);
    ~Library();
};
#endif