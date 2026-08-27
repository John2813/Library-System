#ifndef USERNODE_H
#define USERNODE_H

#include "User.h"

struct UserNode {
    User* user;
    UserNode* next;

    explicit UserNode(User* user) : user(user), next(nullptr) {}
};
#endif