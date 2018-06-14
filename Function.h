//
//  Function.h
//  Graph
//
//  Created by YF on 03/05/2018.
//  Copyright © 2018 YF. All rights reserved.
//

#ifndef Function_h
#define Function_h
#include "City.h"
#include <string>
using std::string;

enum class COMPARE_FN
{
    LESS_THAN = -1,
    EQUAL_TO = 0,
    GREATER_THAN = 1
};


static COMPARE_FN compareCityName(const City& c1, const City&c2)
{
    if (c1.name < c2.name)
        return COMPARE_FN::LESS_THAN;
    
    else if(c1.name == c2.name)
        return COMPARE_FN::EQUAL_TO;
    
    else
        return COMPARE_FN::GREATER_THAN;
    
}


static void printCity(const City& c)
{
    if(c.distance <= 9999)
    {
        if (c.distance != 0)
        {
            std::cout<<c.name<<" "<<c.distance<<" ";
        
            if (c.total_distance != 0)
                std::cout<< c.total_distance ;
        }
    
        else
            std::cout<<c.name<<" ";
    }
        
}


static COMPARE_FN compareD(const City& c1, const City& c2)
{
    if(c1.total_distance > c2.total_distance)
        return COMPARE_FN::GREATER_THAN;
    else if(c1.total_distance < c2.total_distance)
        return COMPARE_FN::LESS_THAN;
    else
        return COMPARE_FN::EQUAL_TO;
}



static void update_total_distance(const City& c1, City& c2)
{
    c2.total_distance += c1.total_distance + c2.distance;
}



#endif /* Function_h */
