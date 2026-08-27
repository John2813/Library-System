#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book{
private:
    std::string title;
    std::string author;
    int id;
    int year;
    int num; 

public:
    explicit Book(const std::string& title, const std::string& author, int year,int id);
    //remember that 'explicit' should be used in the defination of a class.
    std::string GetAuthor() const;
    std::string GetTitle() const;
    int GetYear() const;
    int GetNum() const;
    int GetId() const;
    void ChangeNum(int newNum) { num = newNum; }
    //all the members are 'std' types,no need to declare a destructor
 
};

#endif