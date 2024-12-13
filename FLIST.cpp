#pragma once
#include "FLIST.h"

FLIST::FLIST(std::ifstream& file)
{
    head = new NODE();
    tail = head;
    while (!file.eof())
    {
        ptrBook book = new Book(file);
        add_to_tail(book);
        book->up_count();
    }
}

FLIST::~FLIST()
{
    while (!empty())
    {
        del_from_head();
    }
    delete head;
    head = tail = nullptr;
}

void FLIST::add_to_head(ptrBook elem)
{
    adding_by_pointer(head->next, elem);
    if (head == tail)
        tail = tail->next;
}

void FLIST::add_to_tail(ptrBook elem)
{
    adding_by_pointer(tail->next, elem);
    tail = tail->next;
}

void FLIST::add_after(ptrNODE ptr, ptrBook elem)
{
    if (ptr)
    {
        adding_by_pointer(ptr->next, elem);
        if (ptr == tail)
            tail = tail->next;
    }
}

void FLIST::del_from_head()
{
    if (head->next)
    {
        deleting_by_pointer(head->next);
        if (!head->next)
            tail = head;
    }
}

void FLIST::print(const char* message, std::ostream& stream)
{
    ptrNODE p = head->next;
    while (p)
    {
        (p->info)->print();
        p = p->next;
    }
}

void FLIST::sorting()
{
    auto switch_pointers = [](ptrNODE q, ptrNODE p)
        {
            ptrNODE tmp = p->next;
            p->next = tmp->next;
            tmp->next = q->next;
            q->next = tmp;
        };
    auto find_place = [this](ptrBook elem)->ptrNODE // ptrStruct
        {
            ptrNODE result = head;
            while (result->next && result->next->info < elem) // <-- 
                result = result->next;
            return result;
        };
    ptrNODE hprev = head->next, h = head->next->next;
    while (h)
    {
        if (hprev->info > h->info) // <-- 
        {
            switch_pointers(find_place(h->info), hprev);
            h = hprev->next;
        }
        else
        {
            hprev = h;
            h = h->next;
        }
        tail = hprev;
    }
}