#include <iostream>
#include <fstream>
#include "FLIST.h"

int compare(ptrBook bookA, ptrBook bookB);
std::string max_count_by_spec(FLIST& list);
FLIST task(FLIST& list, const char* find_str);

int main()
{
    std::ifstream file("data.txt");
    FLIST list(file);
    list.print("");
    std::cout << "\n\nSORTED:\n\n\n";
    list.sorting(compare);
    list.print("");

    std::cout << "\n\nRESULT:\n\n\n";
    std::string str = max_count_by_spec(list);
    const char* str_c = str.c_str();
    std::cout << str_c << '\n';
    FLIST res(task(list, str_c));
    FLIST tmp(std::move(res));
    tmp.print("");
}



int compare(ptrBook bookA, ptrBook bookB)
{
    return strcmp(bookA->get_spec(), bookB->get_spec());
}

std::string max_count_by_spec(FLIST& list)
{
    int count{ 1 }, max_count{};
    std::string res{};
    ptrNODE ptr = list.get_head()->next;
    while (ptr->next)
    {
        if (compare(ptr->info, ptr->next->info) == 0)
            count++;
        else
        {
            if (max_count == count)
                res += ptr->info->get_spec();
            if (max_count < count)
            {
                max_count = count;
                res = ptr->info->get_spec();
            }
            count = 1;
        }
        ptr = ptr->next;
    }
    if (max_count == count)
        res += ptr->info->get_spec();
    if (max_count < count)
    {
        max_count = count;
        res = ptr->info->get_spec();
    }
    return res;
}

FLIST task(FLIST& list, const char* find_str)
{
    FLIST res;
    ptrNODE ptr = list.get_head()->next;
    while (ptr)
    {
        if (strstr(find_str, ptr->info->get_spec()))
        {
            ptrBook book = new Book(*ptr->info);
            res.add_to_tail(book);
        }
        ptr = ptr->next;
    }
    return res;
}
