//
//  main.cpp
//  Graph
//
//  Created by YF on 19/04/2018.
//  Copyright © 2018 YF. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Graph.h"
#include "City.h"
#include "Function.h"
using namespace std;


const int INFINITY = 10000;
const int SIZE = 5;

string origin[5] = {"Antioch", "Bakersfield", "Chicago", "Denver", "Elk City"};

string stops[5][4] = {{"Bakersfield","Chicago", "Denver", "Elk City"},
    {"Antioch", "Chicago","Denver", "Elk City"},
    {"Antioch","Bakersfield","Denver", "Elk City"},
    {"Antioch", "Bakersfield", "Chicago", "Elk City"},
    {"Antioch","Bakersfield", "Chicago", "Denver"}};

int dis[5][4] =         {{15, INFINITY, INFINITY, INFINITY},
    {20, INFINITY, 10, 35},
    {INFINITY, INFINITY, 5, 10},
    {31, 10, 5, INFINITY},
    {50, 35, 10, 5}};


/*
string origin[5] = {"A", "B", "C", "D", "E"};


string stops[5][4] = {{"B","C", "D", "E"},
                      {"A", "C","D", "E"},
                      {"A","B","D", "E"},
                      {"A", "B", "C", "E"},
                      {"A","B", "C", "D"}};


int dis[5][4] =         {{15, INFINITY, INFINITY, INFINITY},
                        {20, INFINITY, 10, 35},
                        {INFINITY, INFINITY, 5, 10},
                        {31, 10, 5, INFINITY},
                        {50, 35, 10, 5}};

*/

int main(int argc, const char * argv[]) {
     Graph<City> graph(compareCityName, printCity, compareD, update_total_distance);
/*
     City ori[5];
     City city[5][4];
    //Graph<City> graph(compareCityName, printCity, compareD, update_total_distance);
    

    for(int i=0; i<5; i++)
    {
          ori[i].name = origin[i];
          ori[i].distance = 0;
          ori[i].total_distance = 0;
          graph.insert_origin(ori[i]);
        for(int j=0 ; j<4; j++)
        {
             city[i][j].name = stops[i][j];
             city[i][j].distance = dis[i][j];
             graph.insert_element(ori[i], city[i][j]);
        }
    }
 
 */

    ifstream inFile;
    string filename2 = "/Users/yf/Desktop/city.csv";
    string line;
    inFile.open(filename2);
    
    while(getline(inFile, line))
    {
        
        long pos1 = line.find(',', 0);
        long pos2;
        string name1 = line.substr(0, pos1);
        City origin;
        origin.name = name1;
        origin.distance = 0;
        origin.total_distance = 0;
          graph.insert_origin(origin);
        
        for(int i = 0; i < SIZE - 1; i++)
        {
            pos2 = line.find(',', pos1 + 1);
            string name2 = line.substr(pos1  + 1, pos2 - pos1 - 1);
            pos1 = line.find(',', pos2 + 1);
            
            string d = line.substr(pos2 + 1, pos1 - pos2 - 1);
            
            int distance = stoi(d);
            
            if(distance != 10000)
            {
                City stop;
                stop.name = name2;
                stop.distance = distance;
                graph.insert_element(origin, stop);
                
            }
        }
    }
 
    //graph.print_origins();
            
//   graph.print_stops(ori[3]);
    

  //  graph.cheapestPath(ori[0], ori[1]);
 
 

 //   graph.cheapestPath(ori[0], ori[3]);
    
    
    
    
    
    
//    cout<<endl<<endl;
      City obj1, obj2;
      obj1.name = origin[4];
      obj2.name = origin[1];
    
    //  graph.print_origins();
    
   //  graph.print_stops(obj2);
    
    cout<<endl<<endl;
    
    
      graph.shortestPath(obj1, obj2);
    
    
    cout<<endl;
    
    
     graph.cheapestPath(obj1, obj2);
    
     cout<<endl<<endl;
    
    return 0;
}
