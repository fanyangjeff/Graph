#ifndef TEAM_PROJECT_LINKEDLIST
#define TEAM_PROJECT_LINKEDLIST

#include <vector>
#include "Stack.h"
#include "Function.h"
using std::vector;

template <class T>
class LinkedList {
private:
    COMPARE_FN (*cmp)(const T&, const T&);
    void (*print)(const T&);
    
    struct ListNode {
        T data;
        ListNode *next;
    };
    ListNode *head;
    
public:
    LinkedList(){};
    LinkedList(COMPARE_FN (*cmp)(const T&, const T&),void (*print)(const T&));
    ~LinkedList();
    bool insert(const T&);
    bool remove(const T &dataOut);
    bool search(T &dataOut);
    void traverse();
    vector<T> get_list();
    Stack<T> get_elements();
    void clear();
};

template <class T>
LinkedList<T>::LinkedList(COMPARE_FN (*cmp)(const T&, const T&), void (*print)(const T&))
{
    head = new ListNode;
    head = nullptr;
    this->cmp = cmp;
    this->print = print;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    ListNode *curr = head, *prev;
    
    while (curr)
    {
        prev = curr;
        curr = curr->next;
        delete prev;
    }
}

template <class T>
bool LinkedList<T>::insert(const T &newRecord)
{
    ListNode *pNew;
    pNew = new ListNode;
    pNew->data = newRecord;
    pNew->next = nullptr;
    
    if(this->head == nullptr)
    {
        head = pNew;
        return true;
    }
    
    ListNode *pCurr = head;
    ListNode *pPre = nullptr;
    
    while(pCurr && cmp(pCurr->data, newRecord) == COMPARE_FN::LESS_THAN)
    {
        pPre = pCurr;
        pCurr = pCurr->next;
    }
    
    if (pCurr && cmp(pCurr->data, newRecord) == COMPARE_FN::EQUAL_TO)
        return false;
    
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
    
    return true;
}



template <class T>
bool LinkedList<T>::remove(const T &dataOut)
{
    ListNode *curr, *prev;
    
    if(head == nullptr)
        return false;
    
    curr = head;
    if(cmp(curr->data, dataOut) == COMPARE_FN::EQUAL_TO)
    {
        head = curr->next;
        delete curr;
        
        return true;
    }
    
    prev = head;
    curr = head->next;
    
    while (curr && cmp(curr->data, dataOut) == COMPARE_FN::LESS_THAN)
    {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr && cmp(curr->data, dataOut) == COMPARE_FN::EQUAL_TO)
    {
        prev->next = curr->next;
        delete curr;
        
        return true;
    }
    
    return false;
}

template <class T>
bool LinkedList<T>::search(T &dataOut)
{
    ListNode *nodePtr = head;
    
    while (nodePtr)
    {
        if (cmp(nodePtr->data, dataOut) == COMPARE_FN::EQUAL_TO)
        {
            dataOut = nodePtr->data;
            return true;
        }
        nodePtr = nodePtr->next;
    }
    
    return false;
}

template <class T>
void LinkedList<T>::traverse()
{
    ListNode *pCur = this->head;
    while(pCur)
    {
        this->print(pCur->data);
        std::cout<<std::endl;
        pCur = pCur->next;
    }
}


template <class T>
void LinkedList<T>::clear()
{
    
    if(head == nullptr)
        return;
    
    ListNode *pre= head;
    ListNode *pwalk  = head->next;
    
    
    while(pwalk)
    {
        pre = pwalk;
        delete pre;
        pwalk = pwalk->next;
    }
    head = nullptr;
}

template <class T>
vector<T> LinkedList<T>::get_list()
{
    vector<T> my_vector;
    ListNode *pCur = this->head;
    while(pCur)
    {
        my_vector.push_back(pCur->data);
        pCur = pCur->next;
    }
    return my_vector;
}


template <class T>
Stack<T> LinkedList<T>::get_elements()
{
    Stack<T> stack;
    ListNode *pCur = this->head;
    while(pCur)
    {
        stack.push(pCur->data);
        pCur = pCur->next;
    }
    return stack;
}
#endif //TEAM_PROJECT_LINKEDLIST_H

