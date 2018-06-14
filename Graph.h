//
//  Graph.h
//  Graph_practice
//
//  Created by YF on 30/03/2018.
//  Copyright © 2018 YF. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include "Graphnode.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList1.h"
#include "Linkedlist2.h"

using std::string;
using std::vector;

template <class T>
class Graph
{
private:
    GraphNode<T> *head;
    int count_graphNode;
    COMPARE_FN (*cmp) (const T&, const T&);
    COMPARE_FN (*cmpD) (const T&, const T&);
    void (*print) (const T&);
    void (*update) (const T&,  T&);
    

public:
    Graph(){};
    Graph(COMPARE_FN (*cmp)(const T&, const T&), void (*print) (const T&)
          , COMPARE_FN (*cmpD) (const T&, const T&),  void (*update) (const T&, T&));
    
    int get_graphNode(){return this->count_graphNode;}
    bool insert_origin(const T&);
    bool insert_element(const T&, const T&);
    bool cheapestPath(const T&, const T&);
    bool shortestPath(const T&, const T&);
    bool cheapest_path_all_stops(const T&);
    bool check_visited(const T&);
    int check_exsited_vector(const T&, const vector<T>&);
    bool delete_origin(const T&);
    bool delete_element(const T&, const T&);
    GraphNode<T>* search_node(const T&);
    void print_origins();
    void print_stops(const T&);
    void update_previous(const T& obj, GraphNode<T> *ptr);
    void print_shortest_path(const T&);
    void search_for_element(const T&, T&);
    void clear_visited();
    void clear_previous();
    void setPrint(void (*print)(const T&)){this->print = print;}
    void setCmp(int (*cmp)(const T&, const T&)){this->cmp = cmp;}
    void setCmpD(int (*cmpD)(const T&, const T&)){this->cmpD = cmpD;}
    void setUpdate(void (*update) (const T&, T&)){this->update = update;}
    
    
    
};

template<class T>
Graph<T>:: Graph(COMPARE_FN (*cmp) (const T&, const T&), void (*print) (const T&)
                 ,COMPARE_FN (*cmpD) (const T&, const T&),  void (*update) (const T&, T&))
{
    this->cmp = cmp;
    this->print = print;
    this->update = update;
    this->cmpD = cmpD;
    count_graphNode = 0;
    this->head = new GraphNode<T>;
    this->head = nullptr;
}

template <class T>
bool Graph<T>::insert_origin(const T& data)
{
    GraphNode<T> *pNew;
    pNew = new GraphNode<T>(data, this->cmp, this->print);
    
    if(this->head == nullptr)
    {
        head = pNew;
        this->count_graphNode++;
        return true;
    }
    
    GraphNode<T> *pCurr = head;
    GraphNode<T> *pPre = nullptr;
    
    while(pCurr && cmp(pCurr->get_data(), data) == COMPARE_FN::LESS_THAN)
    {
        pPre = pCurr;
        pCurr = pCurr->get_next();
    }
    
    if (pCurr && cmp(pCurr->get_data(), data) == COMPARE_FN::EQUAL_TO)
        return false;
    
    if(pPre == nullptr)
    {
        this->head = pNew;
        pNew->set_next(pCurr);
    }
    else
    {
       pPre->set_next(pNew);
       pNew->set_next(pCurr);
        this->count_graphNode++;
    }
    
    return true;
}

template <class T>
bool Graph<T>::insert_element(const T& origin, const T& input)
{
    GraphNode<T> *pOrigin = search_node(origin);
    
    if (pOrigin)
    {
        pOrigin->insert(input);
        return true;
    }
    
    return false;
}

template <class T>
GraphNode<T>* Graph<T>::search_node(const T& obj)
{
    GraphNode<T> *pCur = this->head;
    
    while (pCur && cmp(pCur->get_data(), obj) == COMPARE_FN::LESS_THAN)
        pCur = pCur->get_next();
    
    if(pCur && cmp(pCur->get_data(), obj) == COMPARE_FN::EQUAL_TO)
        return pCur;
    
    return nullptr;

}

template <class T>
void Graph<T>::print_origins()
{
     GraphNode<T> *pCur = this->head;
     while (pCur)
     {
         this->print(pCur->get_data());
         pCur = pCur->get_next();
     }
}

template <class T>
void Graph<T>::print_stops(const T& obj)
{
    GraphNode<T> *pCur = this->head;
    
    while (pCur && cmp(pCur->get_data(), obj) == COMPARE_FN::LESS_THAN)
        pCur = pCur->get_next();
    
    if(pCur && cmp(pCur->get_data(), obj) == COMPARE_FN::EQUAL_TO)
         pCur->print_elements();
}


template <class T>
bool Graph<T>::check_visited(const T& obj)
{
    GraphNode<T> *pCur = this->head;
    
    while (pCur && cmp(pCur->get_data(), obj) == COMPARE_FN::LESS_THAN)
        pCur = pCur->get_next();
    
    if(pCur && cmp(pCur->get_data(), obj) == COMPARE_FN::EQUAL_TO)
        return pCur->get_visited();
    
    return false;
}


template<class T>
int Graph<T>::check_exsited_vector(const T& obj, const vector<T> &my_vector)
{
    for (auto i = 0; i < my_vector.size(); i++)
    {
        if(this->cmp(obj, my_vector[i]) == COMPARE_FN::EQUAL_TO)
            return int(i);
    }
    
    return -1;
}


template <class T>
void Graph<T>::update_previous(const T& obj, GraphNode<T> *ptr)
{
     GraphNode<T> *pDes = search_node(obj);
     pDes->set_previous(ptr);
}


template <class T>
void Graph<T>::search_for_element(const T& first, T& second)
{
     GraphNode<T> *pCur = search_node(first);
     pCur->search_element(second);
}

template <class T>
void Graph<T>::print_shortest_path(const T& destination)
{
    Stack<T> stack;
     GraphNode<T> *pCur = search_node(destination);
    
     while(pCur)
     {
         stack.push(pCur->get_data());
         pCur = pCur->get_previous();
     }
     while(!stack.isEmpty())
     {
         T dataOut, dataOut2;
         stack.pop(dataOut);
         if(stack.getTop(dataOut2))
         {
             search_for_element(dataOut, dataOut2);
             print(dataOut);
             cout<<" –––  ";
             print(dataOut2);
            cout<<endl;
         }
     }
}

template <class T>
bool Graph<T>::cheapestPath(const T& origin, const T& destination)
{
    LinkedList1<T> *linkedlist = new LinkedList1<T>(this->cmp, this->cmpD);
    GraphNode<T> *pDes = search_node(destination);
    GraphNode<T> *pOrigin = search_node(origin);
    if(pOrigin)
        pOrigin->set_previous(nullptr);
    if(linkedlist->insert(origin))
    
    while(pDes->get_visited() == false && linkedlist->getCount() != 0)
    {
        T obj;
        linkedlist->remove_first(obj);
        
        if(check_visited(obj) == false)
        {
            GraphNode<T> *pHold = search_node(obj);
            pHold->set_visited_true();
            if (pDes->get_visited() == true)
                break;
            
            Stack<T> stack = pHold->get_stack();
            //vector<T> temp_vector;
            // temp_vector = pHold->get_all_elements();
            
            while(!stack.isEmpty())
            {
                T temp;
                stack.pop(temp);
                if (check_visited(temp) == true)
                continue;
                
                update(obj, temp);
                if(linkedlist->insert(temp) == true)
                {
                    update_previous(temp, pHold);
                }
                
            }
            /*
            for(auto i = 0; i < temp_vector.size(); i++)
            {
                if (check_visited(temp_vector[i]) == true)
                    continue;
                
                update(obj, temp_vector[i]);
                if(linkedlist->insert(temp_vector[i]) == true)
                {
                    update_previous(temp_vector[i], pHold);
                }

            }
             */
        }
    }
    
    if(pDes->get_visited() == true)
    {
        print_shortest_path(destination);
        this->clear_previous();
        return true;
        
    }
    this->clear_previous();
    
    return false;
}



template <class T>
bool Graph<T>::cheapest_path_all_stops(const T& origin)
{
    
    vector<T> container;
    int stops_visitest = 0;
    GraphNode<T> *pOrigin = search_node(origin);
   
    Queue<T> queue;
    if(pOrigin)
        pOrigin->set_previous(nullptr);
    
    container.push_back(origin);
    
    while(stops_visitest != count_graphNode && container.size() != 0)
    {
        T obj;
        obj = container.back();
        container.pop_back();
        
        if(check_visited(obj) == false)
        {
            queue.enqueue(obj);
            GraphNode<T> *pHold = search_node(obj);
            pHold->set_visited_true();
            stops_visitest ++;
            if (stops_visitest == count_graphNode)
                break;
            
            
            vector<T> temp_vector;
            temp_vector = pHold->get_all_elements();
            
            for(auto i = 0; i < temp_vector.size(); i++)
            {
                if (check_visited(temp_vector[i]) == true)
                    continue;
                
                update(obj, temp_vector[i]);
                bool check = false;
                auto j = 0;
                while(check == false && j < container.size())
                {
                    if(cmp(container[j], temp_vector[i]) == COMPARE_FN::EQUAL_TO)
                        check = true;
                    
                    if(check == false)
                        j++;
                }
                if(check)
                {
                    if(cmpD(container[j], temp_vector[i]) == COMPARE_FN::GREATER_THAN)
                    {
                        container[j] = temp_vector[i];
                    }
                }
                else
                {
                    container.push_back(temp_vector[i]);
                }
                
            }
            sort(container.begin(), container.end(), cmpD);
        }
    }
    
    
    if(stops_visitest == count_graphNode)
    {
        T dataOut;
        while(!queue.isEmpty())
        {
            queue.dequeue(dataOut);
            print(dataOut);
            std::cout<<endl;
        }
        return true;
        
    }
    
    return false;
}

template <class T>
void Graph<T>::clear_visited()
{
    GraphNode<T> * pCur = this->head;
    while(pCur)
    {
        pCur->set_visited_false();
        pCur = pCur->get_next();
    }
    
}



template <class T>
bool Graph<T>::delete_origin(const T& origin)
{
    GraphNode<T> *pDes = search_node(origin);
    
    if(pDes == nullptr)
        return false;
    vector<T> container = pDes->get_all_elements();
    
    for(auto i=0; i<container.size(); i++)
    {
        GraphNode<T> *pHold = search_node(container[i]);
        if(pHold == nullptr)
            continue;
        pHold->delete_element(origin);
    }
    
    GraphNode<T> *pCurr = this->head;
    
    if(cmp(this->head->get_data(), origin) == COMPARE_FN::EQUAL_TO)
    {
        this->head = pCurr->get_next();
        delete pCurr;
        return true;
    }
    
    pCurr = this->head->get_next();
    GraphNode<T> *pPre = this->head;
    
    while(pCurr && cmp(pCurr->get_data(), origin) == COMPARE_FN::LESS_THAN)
    {
        pPre = head;
        pCurr = pCurr->get_next();
    }
    if(pCurr && cmp(pCurr->get_data(), origin) == COMPARE_FN::EQUAL_TO)
    {
        pPre->set_next(pCurr->get_next());
        delete pCurr;
        return true;
    }
    
    return false;
}


template <class T>
bool Graph<T>::delete_element(const T& origin, const T& element)
{
    GraphNode<T> *pDes = search_node(origin);
    
    if(pDes == nullptr)
        return false;
    
    return pDes->delete_element(element);
    
}

template<class T>
void Graph<T>::clear_previous()
{
    GraphNode<T>* pWalk = this->head;
    while(pWalk)
    {
        pWalk->set_visited_false();
        pWalk = pWalk->get_next();
    }
}

template<class T>
bool Graph<T>::shortestPath(const T& origin, const T& destination)
{
    //vector<T> container;
    LinkedList2<T> *linkedlist = new LinkedList2<T>(this->cmp);
    GraphNode<T> *pOri = this->search_node(origin);
    GraphNode<T> *pDes = this->search_node(destination);
    if(pOri && pDes)
    {
        linkedlist->insert(origin);
        //container.push_back(origin);
        pOri->set_previous(nullptr);
    }
    else
        return false;
    
    
    while(!linkedlist->isEmpty() && pDes->get_visited() == false)
    {
        T data;
        //data = *container.begin();
        //container.erase(container.begin());
        linkedlist->remove_first(data);

        GraphNode<T>* pHold = this->search_node(data);
    
        if (pDes->get_visited() == true)
            break;
        
        pHold->set_visited_true();
        
        if(pDes->get_visited() == true)
            continue;
        
        //vector<T> temp_container = pHold->get_all_elements();
        Stack<T> stack = pHold->get_stack();
        
        T obj;
        while(!stack.isEmpty())
        {
            stack.pop(obj);
            if(check_visited(obj))
                continue;
            if(linkedlist->insert(obj))
                update_previous(obj, pHold);
            
        }
        
        
        /*
        for(typename std::vector<T>::iterator it = temp_container.begin(); it != temp_container.end(); it++)
        {
           if(check_visited(*it) || check_exsited_vector(*it, container) != -1)
               continue;
            
            update_previous(*it, pHold);
            container.push_back(*it);
        }
         */
        
    }
    if(pDes->get_visited())
        print_shortest_path(destination);
    
    this->clear_previous();

    return pDes->get_visited();
}

#endif /* Graph_h */

