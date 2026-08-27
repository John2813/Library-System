#include "Book.h"

Book::Book(const std::string& title, const std::string& author, int year,int id)
    : title(title), author(author), id(id),year(year) {}

std::string Book::GetAuthor() const{
    return author;
}
std::string Book::GetTitle() const {
    return title;
}
int Book::GetYear() const{
    return year;
}
int Book::GetNum() const{
    return num;
}
int Book::GetId() const{
        return id;
    }