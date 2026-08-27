#ifndef LIBRARYUI_H
#define LIBRARYUI_H

#include "Library.h"

class LibraryUI{
private:
    Library library;

    void clear_cin();

    void Login();
    void Register();
    void UserMenu(const bool& Permissions);

    void BorrowBook();
    void ReturnBook();
    void AddBook();
    void RemoveBook();
    void RemoveUser();
public:
    LibraryUI() = default;
    void run();
};
#endif