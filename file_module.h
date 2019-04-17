//
//  Header.h
//  file process
//
//  Created by 王俊杰 on 2019/4/15.
//  Copyright © 2019 王俊杰. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <assert.h>
#include <vector>


using namespace std;

bool read_file();
enum city {beijing , shanghai, guangzhou, shenzhen, shantou, tianjing, hangzhou, nanning, chongqing, xiamen};
//if you want to add a city, add it here.The city name mustn't longer than 10 char unless length of cityname in the front of file_module.cpp
enum transportation {airplane,train,bus};
//enum city {beijing , shanghai, guangzhou, shenzhen, shantou, tianjing, hangzhou, nanning, chongqing, xiamen};
const int citynumber=10;
const int cityname=10;
const int pathname=10;

void print_city(city c);
void print_transportation(transportation a);

class path{
private:
    char name[pathname];
    city depa=beijing,dest=shanghai;
    int stt=0,edt=0,time_passed=0;
    float price=0;
    transportation tran;
    
public:
    int get_time(fstream &file){//read a time from the form of xx:xx to minutes started from 00:00 dorectly from file
        int hour,minute;
        file>>hour;
        file.seekg(1,ios::cur);
        file>>minute;
        return (hour*60+minute);
    }
    
    city get_depa(){//return depature
        return depa;
    }
    
    city get_dest(){//return destination
        return dest;
    }
    
    int get_stt(){
        return stt;
    }
    
    transportation get_tran(){
        return tran;
    }
    
    path(const path &copied){// copy constructure
        depa=copied.depa;
        dest=copied.dest;
        stt=copied.stt;
        edt=copied.edt;
        time_passed=copied.time_passed;
        tran=copied.tran;
        price=copied.price;
        for(int i=0;i<pathname;i++){
            name[i]=copied.name[i];
        }
    }
    
    path(fstream &file){
        int i;
        file>>i;
        tran=(transportation)i;
        file>>name;
        file>>i;
        depa=(city)i;
        file>>i;
        dest=(city)i;
        stt=get_time(file);
//        edt=get_time(file);
        file>>time_passed;
        edt=stt+time_passed;
        file>>price;
    }
    
    char *get_name(){
        return name;
    }
    
    path(){}
    float get_price(){
        return price;
    }
    
    void print_time(int time){
        int hour=time/60;
        int minute=time%60;
        if(hour<10){
            cout<<"0";
        }
        cout<<hour;
        cout<<":";
        if(minute<10){
            cout<<"0";
        }
        cout<<minute;
    }
    
    void print_path(){
        int day=1;
        cout<<"===================This is the begin of this path imformation===================\n";
        cout<<"==          transportation: ";
        print_transportation(tran);
        cout<<"\n==          ";
        cout<<"path name: "<<name<<"\n==          ";
        cout<<"departure: ";
        print_city(depa);
        cout<<"    destination: ";
        print_city(dest);
        cout<<"\n==          ";
        cout<<"start time:  ";
        print_time(stt);
        cout<<"    ";
        while(edt>=1440){
            day++;
            edt=edt-1400;
        }
        cout<<"end time:  ";
        print_time(edt);
        cout<<" of day "<<day<<"\n==          ";
        cout<<"time used: "<<time_passed<<"min\n==          ";
        cout<<"price: ¥"<<price<<"\n";
        cout<<"====================This is the end of this path imformation====================\n\n";
    }
};

typedef struct Junjie1{
    int time_min;
    path path0;
}junjie1;

typedef struct Junjie2{
    float price_min;
    path path0;
}junjie2;
int scan_city();
void search();
void cheapest(vector<junjie2>& junjie, vector<bool> is_min, int city, int cities = 10);



#endif /* Header_h */
