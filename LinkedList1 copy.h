//
//  LinkedList.h
//  LinkedList_homebase
//
//  Created by YF on 02/06/2018.
//  Copyright © 2018 YF. All rights reserved.
//

#ifndef LinkedList1_h
#define LinkedList1_h
#include "LinkedList_homebase.h"
#include "Function.h"

template<class T>
class LinkedList1
{
private:
    struct ListNode {
        T data;
        ListNode *next;
    };
    ListNode* head;
    int count;
    COMPARE_FN (*cmpD) (const T&, const T&);
    COMPARE_FN (*cmp) (const T&, const T&);
    
public:
    LinkedList1(COMPARE_FN (*cmp)(const T&, const T&), COMPARE_FN (*cmpD)(const T&, const T&)){this->cmp = cmp; this->cmpD = cmpD;}
    LinkedList1(){this->count = 0; this->head = 0;}
    bool search(const T&, T&);
    bool insert(const T&);
    bool remove_first(T&);
    void setcmpD(COMPARE_FN (*cmpD)(const T&, const T&)){this->cmpD = cmpD;}
    void setcmp(COMPARE_FN (*cmp)(const T&, const T&)){this->cmp = cmp;}
    int getCount(){return this->count;}
    bool isEmpty(){return this->count;}
};


template <class T>
bool LinkedList1<T>::insert(const T &newRecord)
{
    ListNode *pCurr = head;
    ListNode *pPre = nullptr;
    
    while(pCurr && cmp(pCurr->data, newRecord) != COMPARE_FN::EQUAL_TO)
    {
        pPre = pCurr;
        pCurr = pCurr->next;
    }
    
    if (pCurr && cmp(pCurr->data, newRecord) == COMPARE_FN::EQUAL_TO)
    {
        if(cmpD(pCurr->data, newRecord) == COMPARE_FN::GREATER_THAN)
        {
            this->count--;
            if(pPre == nullptr)
            {
                ListNode *temp = head;
                head = head->next;
                delete temp;
            }
            else
            {
                pPre->next = pCurr->next;
                delete pCurr;
            }
        }
        else
            return false;
        
    }
    
    ListNode *pNew;
    pNew = new ListNode;
    pNew->data = newRecord;
    pNew->next = nullptr;
        
    if(this->head == nullptr)
    {
        head = pNew;
        this->count++;
        return true;
    }
        
    pCurr = head;
    pPre = nullptr;
        
    while(pCurr && cmpD(pCurr->data, newRecord) == COMPARE_FN::LESS_THAN)
    {
        pPre = pCurr;
        pCurr = pCurr->next;
    }
        
    if(pPre == nullptr)
    {
        this->head = pNew;
        pNew->next = pCurr;
    }
    else
    {
        pPre->next = pNew;
        pNew->next = pCurr;
    }
    
    this->count++;
    return true;
}

template<class T>
bool LinkedList1<T>::search(const T& obj, T& outObj)
{
    ListNode *pwalk = head;
    while(pwalk)
    {
        if(cmp(obj, pwalk->data) == COMPARE_FN::EQUAL_TO)
        {
            outObj = pwalk->data;
            return true;
        }
    }
    return false;
    
}

template<class T>
bool LinkedList1<T>::remove_first(T& obj)
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



#endif /* LinkedList1_h */
