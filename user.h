//
// Created by 74772 on 2019/4/13.
//

#ifndef JUNJIEBA_USER_H
#define JUNJIEBA_USER_H

#include <iostream>
#include <vector>
#include "file_module.h"
#include <float.h>
#include <iostream>
#include <limits.h>

using namespace std;

class User{
private:
    city depa,dest;
    int stt, meth;//strategy for travel method,lmt for time limit
    int lmt = INT_MAX;
    int least_time = 0;
    float least_price = 0.0;
    vector<junjie1> junjie11{10};
    vector<junjie2> junjie22{10};
    vector<int> precursor{10};
    
public:
    
    int get_time_from_input(){
        int hour,minute;
    Retime:
        cin>>hour;
        getchar();
        cin>>minute;
        if(hour>=24&&minute>=60){
            cout<<"illegal input, please input a correct time.";
            goto Retime;
        }
        return hour*60+minute;
    }
    
    User(){
        cout<<"please input your request!\n";
        cout<<"depature:";
        depa=(city)scan_city();
        cout<<"destination:";
        dest=(city)scan_city();
        cout<<"starting time:";
        stt=get_time_from_input();
        cout<<"now here are three travel method avalible, they are:\n1.travel in shortest time.\n2.travel in lowest cost.\n3.travel in lowest cost within limited time\n";
        cout<<"plaese chose your travel method:";
    Again:
        cin>>meth;
        switch(meth){
            case 1:
                Dijkstra((int)depa,stt,(int)dest,citynumber);
            case 2:
                break;
            case 3:
                cout<<"when do you want to be there:";
                cin>>lmt;
                break;
            default:
                cout<<"you chose an illegal number, please choose angain:";
                goto Again;
        }
        
        
    }
    
    //
    void Dijkstra(int city, int begin,int to_city,int strategy,int cities = citynumber)
    {// choose the right func according to the strategy
       
    }
    
    void Dijkstra2(int city, int begin, int to_city, int cities = citynumber)
    {
        vector<bool> is_min(cities, false);
        
        // initialize
        vector<junjie2> current(cities);    // temporary alternate array
        // it need a func that return A's min-weight to another cities
        is_min[city] = true;
        cheapest(junjie22, is_min, city);
        cheapest(current, is_min, city);
        for (int i = 0; i < cities; ++i) {
            precursor[i] = city;
        }
        
        // main flop
        float min;
        int cur_min;
        for (int i = 1; i < cities; ++i) {
            min = FLT_MAX;  // pass()
            
            for (int j = 0; j < cities; ++j) {
                if(!is_min[j] && junjie22[j].price_min < min){
                    cur_min = j;
                    min = junjie22[j].price_min;
                }
            }
            is_min[cur_min] = true;
            
            if (is_min[to_city]){   // break when the answer comes out
                break;
            }
            
            cheapest(current, is_min, city);
            
            for (int k = 0; k < cities; ++k) {
                if(!is_min[k] && (junjie22[cur_min].price_min + current[k].price_min < junjie22[k].price_min))
                {
                    junjie22[k].price_min = junjie22[cur_min].price_min + current[k].price_min;
                    precursor[k] = cur_min;
                    junjie22[k].path0 = current[cur_min].path0;
                }
            }
        }
        least_price = junjie22[to_city].price_min;
    }
    
    void dj_show_tickets2(int city, int cur_city)
    {   // city: departure, cur_city: present city
        if (cur_city != city){
            dj_show_tickets2(city, precursor[cur_city]);
            junjie22[cur_city].path0.print_path();
        }
    }
    
    void show_result2()
    {
        cout << "the least price is " << least_price << endl;
        
    }
    
};


#endif //JUNJIEBA_USER_H
