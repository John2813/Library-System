#ifndef USER_H
#define USER_H

#include <string>
class Book;
class BookNode;

class User{
private:
    std::string UserName;
    std::string Password;
    BookNode* BorrowedBook;
    int BorrowedCount = 0;
    int MaxBorrowedCount = 5;
    int id;
public:
    explicit User(const std::string& username, const std::string& password,const int id);
    std::string GetUserName() const;
    std::string GetPassword() const;
    int GetBorrowedCount() const;
    BookNode* GetBorrowedBook() const;
    void BorrowBook(Book* book);
    void ReturnBook(Book*book);
    void ShowBorrowedBooks() const;
    int GetID() const;
    ~User();
};
#endif