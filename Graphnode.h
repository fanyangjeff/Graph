//
//  Graphnode.h
//  Graph_practice
//
//  Created by YF on 30/03/2018.
//  Copyright © 2018 YF. All rights reserved.
//

#ifndef Graphnode_h
#define Graphnode_h
#include "LinkedList.h"
#include "Function.h"
#include <vector>

template <class T>
class GraphNode
{
private:
    T data;
    int count_listnode;
    bool visited;
    GraphNode<T> *next;
    GraphNode <T> *previous;
    LinkedList<T> *list;
    
    COMPARE_FN (*cmp) (const T&, const T&);
    void (*print) (const T&);
public:
    GraphNode(){};
    GraphNode(const T&, COMPARE_FN (*compare)(const T&, const T&), void (*print) (const T&));
    void insert(const T& input);
    
    //mutators
    bool get_visited(){return this->visited;}
    bool delete_element(const T& obj){return this->list->remove(obj);}
    T get_data(){return this->data;}
    GraphNode* get_next(){return this->next;}
    GraphNode* get_previous(){return this->previous;}
    vector<T> get_all_elements(){return this->list->get_list();}
    Stack<T> get_stack(){return this->list->get_elements();}
    
    //accessors
    void set_visited_true(){this->visited = true;}
    void set_visited_false(){this->visited = false;}
    void set_data(const T&){this->data = data;}
    void set_next(GraphNode *ptr){this->next = ptr;}
    void set_previous(GraphNode *ptr){this->previous = ptr;}
    
    void print_elements(){list->traverse();}
    void search_element(T& obj){list->search(obj);}
    
    
};

template <class T>
GraphNode<T>::GraphNode(const T& input, COMPARE_FN (*compare)(const T&, const T&),
                        void (*print) (const T&))
{
    this->data = input;
    this->next = nullptr;
    this->previous = nullptr;
    this->visited = false;
    count_listnode = 0;
    this->cmp = compare;
    this->print = print;
    list = new LinkedList<T>(this->cmp, this->print);
}

template <class T>
void GraphNode<T> ::insert(const T& input)
{
    this->list->insert(input);
}


#endif /* Graphnode_h */

