#include <iostream>
#include <fstream>
#include "FLIST.h"

int main()
{
    std::ifstream file("data.txt");
    FLIST list(file);
    list.print("");
}

