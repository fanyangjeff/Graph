//
//  Linkedlist2.h
//  LinkedList_homebase
//
//  Created by YF on 07/06/2018.
//  Copyright © 2018 YF. All rights reserved.
//

#ifndef Linkedlist2_h
#define Linkedlist2_h
#include "Function.h"

template<class T>
class LinkedList2
{
private:
    struct ListNode {
        T data;
        ListNode *next;
    };
    ListNode* head;
    COMPARE_FN (*cmp)(const T&, const T&);
    int count;
public:
    LinkedList2(COMPARE_FN (*cmp)(const T&, const T&));
    LinkedList2(){this->head == nullptr; this->count = 0;}
    bool insert(const T&);
    bool remove_first(T&);
    bool isEmpty() {return this->count == 0;}
    void setcmp( COMPARE_FN (*cmp)(const T&, const T&)){this->cmp = cmp;}
    
};


template <class T>
LinkedList2<T>::LinkedList2(COMPARE_FN (*cmp)(const T&, const T&))
{
    this->cmp = cmp;
    this->head = nullptr;
    this->count = 0;
}

template<class T>
bool LinkedList2<T>::insert(const T& obj)
{
    
    ListNode *pCurr = head;
    while(pCurr)
    {
        if(cmp(pCurr->data, obj) == COMPARE_FN::EQUAL_TO)
        {
            return false;    //indicates this piece of data has exsited
        }
        pCurr = pCurr->next;
    }
    
    
    pCurr = head;
    ListNode *newNode = new ListNode;
    newNode->data = obj;
    newNode->next = nullptr;
    this->count ++;
    if(this->head == nullptr)
    {
        head = newNode;
    }
    else
    {
        while(pCurr->next)
        {
            pCurr = pCurr->next;
        }
        
        pCurr->next = newNode;
    }
    return true;
}


template<class T>
bool LinkedList2<T>::remove_first(T& obj)
{
    if(this->head == nullptr)
        return false;
    else
    {
        ListNode *temp = head;
        head = head->next;
        obj = temp->data;
        delete temp;
        this->count--;
    }
    return true;
}


#endif /* Linkedlist2_h */
