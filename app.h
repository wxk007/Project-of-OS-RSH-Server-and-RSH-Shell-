//
// Created by vagrant on 18.11.16.
//

#ifndef PROJECT_APP_H
#define PROJECT_APP_H
#include <iostream>


class app
{
public:
    app();
    ~app();
    std::string start();
    int execute(std::string command);
};


#endif //PROJECT_APP_H
