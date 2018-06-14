//
//  main.cpp
//  csv_maker
//
//  Created by YF on 25/05/2018.
//  Copyright © 2018 YF. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int INFINITY = 10000;
const int SIZE = 5;
struct City
{
    string name;
    int distance;
    int total_distance;
};

string origin[5] = {"Antioch", "Bakersfield", "Chicago", "Denver", "Elk City"};


string stops[5][4] = {{"Bakersfield","Chicago", "Denver", "Elk City"},
    {"Antioch", "Chicago","Denver", "Elk City"},
    {"Antioch","Bakersfield","Denver", "Elk City"},
    {"Antioch", "Bakersfield", "Chicago", "Elk City"},
    {"Antioch","Bakersfield", "Chicago", "Denver"}};


int dis[5][4] =         {{15, 13, 20, 35},
    {20, 60, 10, 35},
    {15, 30, 5, 10},
    {31, 10, 5, 50},
    {50, 35, 10, 5}};


int main(int argc, const char * argv[]) {
   
    ofstream outFile;
    string filename = "city.csv";
    outFile.open(filename);
    
    if(outFile.is_open())
    
    for(int i = 0; i < SIZE; i++)
    {
        outFile<<origin[i]<<",";
        for (int j = 0; j < 4; j++)
        {
            outFile<<stops[i][j]<<",";
            
            if(dis[i][j] != INFINITY)
                outFile<<dis[i][j]<<",";
            else
                outFile<<INFINITY<<",";
        }
        outFile<<endl;
    }
    outFile.close();
    
    ifstream inFile;
    string filename2 = "/Users/yf/Desktop/city.csv";
    string line;
    inFile.open(filename2);
    
   // City *origin = new City[5];
    
    
    
    
    
    while(getline(inFile, line))
    {
        
        long pos1 = line.find(',', 0);
        long pos2;
        string name1 = line.substr(0, pos1);
        City origin;
        origin.name = name1;
        
        cout<<name1<<endl;
        
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
                cout<<stop.name<<" "<<stop.distance<<endl;
                
            }
        }
    }
    
    
    
    
    return 0;
}
