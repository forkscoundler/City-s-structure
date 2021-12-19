#include <QtCore/QCoreApplication>
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <float.h>
#include <conio.h>
#include <climits>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <string>
#include <math.h>
#include <ctype.h>
#include <windows.h>
//announcing the constants
#define NAME_MEMO 30
#define MR_MEMO 30
using namespace std;
//prototypes of all functions
void showAll();
void addCity();
void growAr();
void delCity();
void sortByName();
void sortByDivision();
void showForPopul();
void showForDistricts();
void pause();
void joinSortarr(int *, int *, int *, int, int, int &);
int getInt(string prompt, int min, int max);
//creating a structure
struct City {
    char name[NAME_MEMO];
    long int population;
    char mayor[MR_MEMO];
    int districts;
};
City *ar;
int capacity;
int size;
typedef void MenuFunc();
struct MenuUnit{
    string text;
    MenuFunc *func;
};
typedef bool Comparator(City, City);
void merge(int *, int,int,int,Comparator *test);
void sortMerge(int *ar, int size, Comparator *test);

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    //initialize a list of cities
    SetConsoleTitleA("Vertebny I.V. PI-211 Lab. 13 Variant: Airport");
    City initAr [] = {{"Kyiv",2951952, "Klitschko",10},
                      {"Kharkiv",1443866,  "Terekhov",9},
                      {"Odessa",1015826, "Trukhanov",4},
                      {"Lviv",717486, "Sadovyi",6},
                      {"Dnipro",980948, "Filatov",8}
    };
    size = 5;
    capacity = 6;
    ar = new City[capacity];
    memcpy(ar, initAr, sizeof(City)*size);
    //creating the menu
    MenuUnit menu[] = {
        {"Show all cities", showAll},
        {"Add city", addCity},
        {"Delete city", delCity},
        {"Sort cities by alphabet", sortByName},
        {"Sort cities by city division", sortByDivision},
        {"Show cities which have count of population no less than ",showForPopul},
        {"Show cities which have less districts than ", showForDistricts},
        {"Exit", NULL},
    };
    while(true){
        system("cls");
        int count = 0;
        //Consoling the menu
        for( ; ; count++){
            cout  << " " << count + 1 << ". "
                    << menu[count].text << endl;
            if(menu[count].text.compare("Exit") == 0)
                break;
        }
        // Entering the variant
        int variant = getInt(" Enter variant number, please ",1, count+1);
        if(variant == count +1){
            cout << "\n Working with program is ended.\n";
            break;
        }
        // Calling for the function
        menu[variant - 1].func();
    }
    return app.exec();
}
//function which one is controling the length of the row,
//as well as display the text of the prompt not to enter the data
char* getStr(string prompt, int maxMemory){
    cout << prompt;
    string s;
    getline(cin,s);
    if(s.length() >= maxMemory)
        s = s.substr(0,maxMemory-1);
    //allocate memory for char array
    char* cStr = new char[s.length() +1];
    return strcpy(cStr, s.c_str());
}
//The "Entry of a whole number" option also allows you to control the range of numbers
//and display the note text without entering the data
int getInt(string prompt, int min, int max){
    int num; string s;
    do{
        cout << prompt;
        getline(cin,s);
        num = atoi(s.c_str());
    } while(num < min || num > max);
    num = atoi(s.c_str());
    return num;
}
//function for showing all cities list
void showAll(){
    cout <<"View all cities:"<<endl;
    printf("%-*s %-*s %s        %s\n",NAME_MEMO,"Name",
           MR_MEMO,"City's mayor","Population","Districts");
    for(int i=0;i<size;i++){
        printf("%-*s %-*s %3d           %3d\n", NAME_MEMO, ar[i].name,
               MR_MEMO,ar[i].mayor, ar[i].population, ar[i].districts);
    }
    pause();
}
//function for pausing program
void pause(){
    cout << "Press any key to continue..." ;
    getch();
}
//main sorting function
void sort(Comparator *test){
    for(int i=0; i < size - 1; i++)
        for(int j = i + 1; j < size; j++)
            if ((!test(ar[i], ar[j]))){
        City x =  ar[i];
        ar[i] =  ar[j];
        ar[j] =  x;
    }
}
//function for deleting city by number
void delCity(){
    printf("%-*s %-*s %s        %s\n",NAME_MEMO,"Name",
           MR_MEMO,"City's mayor","Population","Districts");
    for(int i=0;i<size;i++){
        printf("%-*s %-*s %3d           %3d\n", NAME_MEMO, ar[i].name,
               MR_MEMO,ar[i].mayor, ar[i].population, ar[i].districts);
    }
    cout << endl << "Choose the number of the city what you want delete"<<endl;
    int del;
    cin >> del;
    for(int i = del;i<size;++i)
    {
        ar[i-1]=ar[i];
    }
    size--;
    printf("%-*s %-*s %s        %s\n",NAME_MEMO,"Name",
           MR_MEMO,"City's mayor","Population","Districts");
    for(int i=0;i<size;i++){
        printf("%-*s %-*s %3d           %3d\n", NAME_MEMO, ar[i].name,
               MR_MEMO,ar[i].mayor, ar[i].population, ar[i].districts);
    }
    pause();
}
//function for testing names of the cities
bool testByName(City c1, City c2){
    return strcmp(c1.name, c2.name) <= 0;
}
//function for sorting by names of the cities
void sortByName(){
    sort(testByName);
    showAll();
}
//function for testing by division(firstly by number of districts, secondly by population)
bool testByDivision(City c1, City c2){
    if(c1.districts != c2.districts)
        return c1.districts < c2.districts;
    if(c1.population != c2.population)
        return c1.population > c2.population;
    return strcmp(c1.name, c2.name) <= 0;
}
//function for sorting by division
void sortByDivision(){
    sort(testByDivision);
    showAll();
}
//function for doing new array which will be bigger
void growAr(){
    capacity = capacity + capacity / 2;
    City* newAr = new City[capacity];
    // Copy old array to new
    memcpy(newAr, ar, size * sizeof(City));
    City *oldAr = ar;
    ar = newAr;
    // Old Deleting
    delete[] oldAr;
}
//function adding city to the list by all parametres
void addCity(){
    if(size == capacity)  growAr();
    strcpy(ar[size].name,
           getStr("Enter the city name: ",NAME_MEMO));
    ar[size].population =
            getInt("Enter the city population: ",0,45000000);
    strcpy(ar[size].mayor,
           getStr( "Enter the surname of the city mayor: ",MR_MEMO));
    ar[size].districts =
            getInt("Enter the number of the city's disctricts: ",0,20);
    size++;
    showAll();
}
//function showing list of the cities by population
//we reading number and comparing with each population
void showForPopul(){
    int popul;
    cout << "Enter the count of population you want: ";
    cin>>popul;
    sort(testByName);
    cout <<"\nCities which have population no less than" << popul << ":\n";
    printf("%-*s %-*s %s        %s\n",NAME_MEMO,"Name",
           MR_MEMO,"City's mayor","Population","Districts");
    for(int i=0;i<size;i++){
        if(ar[i].population >= popul)
            printf("%-*s %-*s %3d           %3d\n", NAME_MEMO, ar[i].name,
                   MR_MEMO,ar[i].mayor, ar[i].population, ar[i].districts);
    }
    pause();
};
//function showing list of the cities by districts
//we reading number and comparing with each number of districts
void showForDistricts(){
    int dis;
    cout << "Enter the count of districts you want: ";
    cin>>dis;
    sort(testByName);
    cout <<"\nCities which have less districts than" << dis << ":\n";
    printf("%-*s %-*s %s        %s\n",NAME_MEMO,"Name",
           MR_MEMO,"City's mayor","Population","Districts");
    for(int i=0;i<size;i++){
        if(ar[i].districts <= dis)
            printf("%-*s %-*s %3d           %3d\n", NAME_MEMO, ar[i].name,
                   MR_MEMO,ar[i].mayor, ar[i].population, ar[i].districts);
    }
    pause();
};
