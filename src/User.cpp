#include "User.h"
#include "Book.h"
#include "BookNode.h"

User::User(const std::string& username, const std::string& password,const int id){
    this->UserName = username;
    this->Password = password;
    BorrowedBook = nullptr;
    this->id = id;
}

std::string User::GetUserName() const{
    return UserName;
}

std::string User::GetPassword() const{//need to use in login func
    return Password;
}

int User::GetBorrowedCount() const{
    return BorrowedCount;
}

BookNode* User::GetBorrowedBook() const {
    if(BorrowedCount <= 0){
        printf("No borrowed books.\n");
        return nullptr;
    } else {
        return BorrowedBook;
    }
}

void User::BorrowBook(Book* book) {
    if(BorrowedCount >= MaxBorrowedCount) {
        printf("You have reached the maximum borrowed books limit.\n");
        return;
    }

    BookNode* tmp = BorrowedBook;
    if(tmp == nullptr){
        BorrowedBook = new BookNode(book);
        BorrowedCount++;
        tmp = nullptr;
        return;
    }//where i make mistake. i forget to check if the book is already borrowed by the user
    while(tmp->next != nullptr){
        if(tmp->book->GetId() == book->GetId()){
            printf("You have already borrowed this book.\n");
            tmp = nullptr;
            return;
        }
        tmp = tmp->next;
    }

    BookNode* newNode = new BookNode(book);
    tmp->next = newNode;
    BorrowedCount++;
    // tmp->book->ChangeNum(tmp->book->GetNum() - 1); // Don't change the number twice.
    tmp = nullptr;
    return;
}

void User::ReturnBook(Book*book){
    if (book == nullptr) {
        printf("Error: Invalid book pointer (nullptr).\n");
        return;
    }
    if(BorrowedCount <= 0 || BorrowedBook == nullptr) {
        printf("You have no borrowed books to return.\n");
        return;
    }

    BookNode* tmp = BorrowedBook;
    BookNode* prev = nullptr;

    while(tmp != nullptr) {
        if(tmp->book != nullptr && tmp->book->GetId() == book->GetId()) {
            if(prev == nullptr) {
                BorrowedBook = tmp->next;
            } //clear the head of the list
            else {
                prev->next = tmp->next;
            }
            delete tmp;
            printf("===\n");
            BorrowedCount--;
            // tmp->book->ChangeNum(tmp->book->GetNum() + 1); // Don't change the number twice.
            tmp = nullptr;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    
}

int User::GetID() const{
    return id;
}
// **Show without TUI**
void User::ShowBorrowedBooks() const{
    if(BorrowedCount <= 0) {
        return;
    }

    BookNode* tmp = BorrowedBook;
    while(tmp != nullptr) {
        printf("ID: %d,Title: %s, Author: %s, Year: %d\n",tmp->book->GetId() ,tmp->book->GetTitle().c_str(), tmp->book->GetAuthor().c_str(), tmp->book->GetYear());
        tmp = tmp->next;
    }
}

User::~User() {
    while (BorrowedBook != nullptr) {
        BookNode* tmp = BorrowedBook;
        BorrowedBook = BorrowedBook->next;
        delete tmp; // destroy BookNode ,remain Book
    }
}