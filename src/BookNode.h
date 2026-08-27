#ifndef BOOKNODE_H
#define BOOKNODE_H

#include "Book.h"

struct BookNode {
    Book* book;
    BookNode* next;
    BookNode(Book* b) : book(b), next(nullptr) {}
};
#endif