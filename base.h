#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include <random>
using namespace std; 


#pragma warning(disable: 4996)


struct client {
    int id;
    string name;
    string surname;
    string patronymic;
    int arr[3];
    vector<double> prod;
    long long int number;

    client(int _id, const string& _surname, const string& _name, const string& _patronymic, const int _arr[3], const long long int _number, const vector<double> _prod)
        : id(_id), surname(_surname), name(_name), patronymic(_patronymic), number(_number){
        for (int i = 0; i < 3; ++i) {
            arr[i] = _arr[i];
        }
        prod = _prod;
    }

    void print() {
        cout << surname << " " << name << " " << patronymic << " ";
        for (int i = 0; i < 3; i++) {
            cout << arr[i] << ".";
        }
        cout << " \n" << number << " " << id << "\n";
        for (auto it = prod.begin(); it != prod.end(); it++) {
            cout << *it << " ";
        };
        cout << endl << endl;
    }

};



class client_data {
private:
    vector<client> clients;
    int id_next;

public:
    //......................................................................................................................................
    //helpful functions
    void getlen() { cout << id_next-1; };
    

    double sumpr(const client cl) {
        double s = 0;
        for (auto it = cl.prod.begin(); it != cl.prod.end(); it++) {
            s = s + *it; 
        }return s;
    }

    double avgpr(const client cl) {
        double s = 0; int n = 0; double m;
        for (auto it = cl.prod.begin(); it != cl.prod.end(); it++) {
            m = *it;
            s = s + m; n++; 
        }s = s / n;
        return s;
    }

    long int dt(const client cl) {
        int s=0;
        s = (cl.arr[2]) * 10000 + (cl.arr[1] * 100) + cl.arr[0];
        return s;
    }

    void mfiletovector(const string& filename, vector<string>& words) {
        ifstream file(filename);
        string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    };

    void mfiletovector(const string& filename, vector<double>& words) {
        ifstream file(filename);
        double word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    };

   

    int let1(int n, const client cl) {
        if (n <= cl.surname.size()) { int s = cl.surname[n]; return s; }
        else return -1000;
    }
    int let2(int n, const client cl) {
        if (n <= cl.name.size()) { int s = cl.name[n]; return s; }
        else return -1000;
    }
    int let3(int n, const client cl) {
        if (n <= cl.patronymic.size()) { int s = cl.patronymic[n]; return s; }
        else return -1000;
    }
    //......................................................................................................................................
    client_data() : id_next(1) {};

    void additself(client_data &cl) {
        for (auto it = clients.begin(); it != clients.end(); it++) {
            cl.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod); //cout << "(tick)";
        }
    }
    //......................................................................................................................................
    //editing metods

    void add_cl(const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        client cl(id_next, surname, name, patronymic, arr, number, prod); //cl.print();
        if (safe_add(cl) != 6) { clients.push_back(client(id_next++, surname, name, patronymic, arr, number, prod)); }
        //clients.push_back(client(id_next++, surname, name, patronymic, arr, number, prod));
    }

    
    void delete_cl(int id) {
        int c = 0;
        int m;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->id == id) {
                clients.erase(it);
                id_next--;
                break;
            }
        }
        //cout << "go1\n\n";
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->id > id) {
                m=it->id;
                it->id = m - 1;
            }
        }
    }

    void delete_cl(const string& surname,const string& name,const string& patronymic) {
        vector<int> c;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic) {
                c.push_back(it->id);
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            delete_cl(*it);
        }
    }

    void delete_cl(const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        vector<int> c; int n=0;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "/";
            if (it->name == name && it->surname == surname && it->patronymic == patronymic && it->arr[0] == arr[0] && it->number == number && it->prod == prod && it->arr[1] == arr[1] && it->arr[2] == arr[2]) {
                c.push_back(it->id); //cout <<"("<< it->id<<")";
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            delete_cl(*it - n); n++;
        }
    }
    

    void edit_cl(int id, const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        for (auto& client : clients) {
            if (client.id == id) {
                client.surname = surname;
                client.name = name;
                client.patronymic = patronymic;
                client.number = number;
                for (int i = 0; i < 3; i++) {
                    client.arr[i] = arr[i];
                }
                    client.prod = prod;
            }
        }
    }

    void edit_cl2(int id, const string& surname) {
        for (auto& client : clients) {
            if (client.id == id) {
                client.surname = surname;
            }
        }
    }

    void edit_cl1(int id, const string& name) {
        for (auto& client : clients) {
            if (client.id == id) {
                client.name = name;
            }
        }
    }
    void edit_cl3(int id,const string& patronymic) {
        for (auto& client : clients) {
            if (client.id == id) {
                client.patronymic = patronymic;
            }
        }
    }

    void edit_cl1(int id,const int arr[3]) {
        for (auto& client : clients) {
            if (client.id == id) {
                for (int i = 0; i < 3; i++) {
                    client.arr[i] = arr[i];
                }
            }
        }
    }

    void edit_cl1(int id,const long long int number) {
        for (auto& client : clients) {
            if (client.id == id){
                client.number = number;
            }
        }
    }

    void edit_cl1(int id, const vector<double> prod) {
        for (auto& client : clients) {
            if (client.id == id) {
                client.prod = prod;
            }
        }
    }

    void edit_cl(string surnames, string names, string patronymics, const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        vector<int> c;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == names && it->surname == surnames && it->patronymic == patronymics) {
                c.push_back(it->id);
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            edit_cl(*it, surname, name, patronymic, arr, number, prod);
        }
    }

    void edit_cl(string surnames, string names, string patronymics, const int arr1[3], const long long int number1, const vector<double> prod1, const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        vector<int> c;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic && it->arr == arr1 && it->number == number1 && it->prod == prod1) {
                c.push_back(it->id);
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            edit_cl(*it, surname, name, patronymic, arr, number, prod);
        }
    }
    
    //......................................................................................................................................
    //printing methods
    void print_base() {
        for (auto& client : clients) {
            cout << client.surname << " " << client.name << " " << client.patronymic << " ";
            for (int i = 0; i < 3; i++) {
                cout << client.arr[i] << ".";
            }
            cout << " \n" << client.number << " "<< client.id << "\n";
            for (auto it = client.prod.begin(); it != client.prod.end(); it++) {
                cout << *it << " ";
            };
            cout << setprecision(10) << "\n (sum: " << sumpr(client) << "  avg spent:" << avgpr(client) << ")";
            cout << endl << endl;
        }
    };

    /*void print_base_file(FILE* filename) {
        setlocale(LC_ALL, "Russian");
        for (auto& client : clients) {
            fprintf(filename, "%s %s %s ", client.surname, client.name, client.patronymic);
            for (int i = 0; i < 3; i++) {
                fprintf(filename, "%d.", client.arr[i]);
            }
            fprintf(filename, "     %d", client.id);
            fprintf(filename, "\n%lld\n", client.number);
            
            for (auto it = client.prod.begin(); it != client.prod.end(); it++) {
                fprintf(filename, "%lf", *it);
            };
            fprintf(filename, "\n (sum: %10lf  avg spent: %10lf) ", sumpr(client), avgpr(client));
            fprintf(filename,"\n\n");
            //setprecision(10)
        }
 
    }*/

    void print_base_file(FILE* filename) {
        ofstream file(filename);
        for (auto& client : clients) {
            file << client.surname << " " << client.name << " " << client.patronymic << " ";
            for (int i = 0; i < 3; i++) {
                file << client.arr[i] << ".";
            }
            file << " \n" << client.number << "    " << client.id << "\n";
            for (auto it = client.prod.begin(); it != client.prod.end(); it++) {
                file << *it << " ";
            };
            file << setprecision(10) << "\n (sum: " << sumpr(client) << "  avg spent:" << avgpr(client) << ")";
            file << endl << endl;
        }
        
    }

    //......................................................................................................................................
    //sorting junk
    int partitionnum(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (clients[i].number <= pivot.number)
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (clients[i].number <= pivot.number) {
                i++;
            }

            while (clients[j].number > pivot.number) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortnum(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitionnum(start, end);
        quickSortnum(start, p - 1);
        quickSortnum(p + 1, end);
    }

    int partitionsum(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (sumpr(clients[i]) <= sumpr(pivot))
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (sumpr(clients[i]) <= sumpr(pivot)) {
                i++;
            }

            while (sumpr(clients[j]) > sumpr(pivot)) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortsum(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitionsum(start, end);
        quickSortsum(start, p - 1);
        quickSortsum(p + 1, end);
    }

    int partitionavg(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (avgpr(clients[i]) <= avgpr(pivot))
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (avgpr(clients[i]) <= avgpr(pivot)) {
                i++;
            }

            while (avgpr(clients[j]) > avgpr(pivot)) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortavg(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitionavg(start, end);
        quickSortavg(start, p - 1);
        quickSortavg(p + 1, end);
    }

    int partitiondate(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (dt(clients[i]) <= dt(pivot))
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (dt(clients[i]) <= dt(pivot)) {
                i++;
            }

            while (dt(clients[j]) > dt(pivot)) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortdate(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitiondate(start, end);
        quickSortdate(start, p - 1);
        quickSortdate(p + 1, end);
    }

    //......................................................................................................................................
    //sorting metods

    /*void sortby_alph() {
       sort(clients.begin(), clients.end(),
           [](const client& x, const client& y) {
           if (x.surname != y.surname) {
               return x.surname < y.surname;
           }
           else {
               if (x.name != y.name) {
                   return x.name < y.name;
               }
               else {
                   return x.patronymic < y.patronymic;
               }
           }
           });
    };*/

    void sortby_date() {
        quickSortdate(0, id_next - 2);
    };
    
    void sortby_spendings() {
        quickSortsum(0, id_next - 2);
    };

    void sortby_avgspent() {
        quickSortavg(0, id_next - 2);
    };

    void sortby_number() {
        quickSortnum(0, id_next - 2);
    };
    
    //.....................................................................................................................................
    //selection methods

    client_data select_0(int n) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->id == n) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    //важно
    client_data select_1(string surname) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->surname == surname) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_2(string name) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_3(string patronymic) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->patronymic == patronymic) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_(string surname, string name, string patronymic) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_(string surname, string name, string patronymic, int* arr,long long int num, vector<double> prod) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic && it->arr==arr && it->number==num && it->prod==prod) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    //важно
    client_data select_(vector<double> prod) {
        client_data out; int br = 0; int i;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            br = 0; i = 0;
            for (auto it1 = it->prod.begin(); it1 != it->prod.end() && i<prod.size(); it1++) {
                if (*it1 > prod[i] + 0.1 || *it1 < prod[i] - 0.1) { br = 1; }
                i++;
            }
            if (prod.size() == it->prod.size() && br == 0) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }
   
    //важно
    client_data select_(int* arr1,int* arr2) {
        int d1 = (arr1[2] * 10000) + (arr1[1] * 100) + arr1[0];
        int d2 = (arr2[2] * 10000) + (arr2[1] * 100) + arr2[0];
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << d1 << ") ";
            if (dt(*it) >= d1 && dt(*it) <= d2) {
                out.add_cl(it->surname,it->name,it->patronymic,it->arr,it->number,it->prod);
            }
        }
        return out;
    }

    //важно
    client_data select_(int* d1) {
        return select_(d1, d1);
    }

    //важно
    client_data select_1(double d1, double d2) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << avgpr(*it) << ") ";
            if (avgpr(*it) > d1 && avgpr(*it) < d2) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    //важно
    client_data select_1(double d1) {
        return select_1(d1-1, d1+1);
    }

    //важно
    client_data select_(double d1, double d2) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << avgpr(*it) << ") ";
            if (sumpr(*it) > d1 && sumpr(*it) < d2) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    //важно
    client_data select_(double d1) {
        return select_(d1-1, d1+1);
    }

    //важно
    client_data select_(long long int d1,long long int d2) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << it->number << ") ";
            if (it->number >= d1 && it->number <= d2) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    //важно
    client_data select_(long long int d1) {
        return select_(d1, d1);
    }

    client_data select_(int* arr1, int* arr2, double d1, double d2, double d3, double d4, long long int d5, long long int d6) {
        client_data out = select_(arr1, arr2);
        out = out.select_1(d1, d2);
        out = out.select_(d3, d4);
        out = out.select_(d5, d6);
        return out;
    }

    client_data select_(string surname, string name, string patronymic,int* arr1, double d1, double d3, long long int d6) {
        client_data out = select_(arr1); //out.print_base(); //cout << "\n000\n";
        out = out.select_1(d1-1,d1+1); //out.print_base();// cout << "\n111\n";
        out = out.select_(d3-1,d3+1); ///out.print_base();// cout << "\n111\n";
        out = out.select_(d6); //out.print_base();// cout << "\n111\n";
        out = out.select_(surname, name, patronymic);
        return out;
    }

    client_data select_( int* arr1, double d1, double d3, long long int d6) {
        client_data out = select_(arr1); //out.print_base(); //cout << "\n000\n";
        out = out.select_1(d1 - 1, d1 + 1); //out.print_base(); //cout << "\n111\n";
        out = out.select_(d3 - 1, d3 + 1); //out.print_base(); //cout << "\n111\n";
        out = out.select_(d6); //out.print_base(); //cout << "\n111\n";
        return out;
    }


    //......................................................................................................................................
    //correctness

    client_data correct() {
        client_data out; vector<int> f;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (dt(*it) < 20000101 || dt(*it) >= 20240701) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
                f.push_back(it->id);
            }
            else {
                long long int m = it->number;
                if (m < 74950000000 || ((m > 74959999999 && m < 74990000000)) || ((m > 74999999999) && (m < 79160000000)) || ((m > 79179999999) && (m < 79250000000)) || ((m > 79269999999) && (m < 79680000000)) || ((m > 79689999999) && (m < 79770000000)) || ((m > 79779999999) && (m < 7985000000)) ||
                    ((m > 79859999999) && (m < 84950000000)) || ((m > 84959999999 && m < 84990000000)) || ((m > 84999999999) && (m < 89160000000)) || ((m > 89179999999) && (m < 89250000000)) || ((m > 89269999999) && (m < 89680000000)) || ((m > 89689999999) && (m < 89770000000)) || ((m > 89779999999) && (m < 8985000000)) || m>89859999999) {
                    out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
                    f.push_back(it->id);
                }
                else {
                    for (auto it1 = it->prod.begin(); it1 != it->prod.end(); it1++) {
                        if (*it1 < 20000 || *it1>500000) {
                            out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
                            f.push_back(it->id);
                            break;
                        }
                    }
                }
            }
        }
        int n=0; sort(f.begin(), f.end());
        for (auto it = f.begin(); it != f.end(); it++) {
            delete_cl(*it - n); n++;
        }
        return out;
    }

    int safe_add(client cl) {
        int m = 0;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            int i = 0;
            if (it->number == cl.number) { i++;}
            if (it->surname == cl.surname) { i++;}
            if (it->name == cl.name) { i++;}
            if (it->patronymic == cl.patronymic) { i++; }
            if (dt(*it) == dt(cl)) { i++;}
            if (it->prod == cl.prod) { i++;}
            if (i > m) { m = i; }
            client cl1 = *it;
            //if (i == 6) { cl1.print(); cout << "("; cl.print(); cout << ")"; }
        }
        return m;
    }
    //......................................................................................................................................
    //imput generator

    void fixchar(char& c) {
        int br = 0;
        if (c == -16) { c = -88; return; }
        if (c == -15) { c = -72; return; }
        if (c >= -128 && c <= -81) { c = c + 64; return; }
        if (c >= -32 && c <= -17) { c = c + 16; return; }
    }

    void imput(client_data &clien, FILE* output, FILE* input) {
        vector<string> com = { "edit","delete","print","sort","select","generate","correct","add","break","","clear"};
        vector<string> sortcase = { "date","dt","num","number","avg","average","sum","summ" };
        int br = 0, st = 0, cas = -1, st1 = 0, sortcas = -1;
        char c=0; //10 enter 32 space 40 ( 41 ) 47 / 44 , 38 & 46 . 124 | 61 =
        double b = 0;
        int count = 0;
        client_data cl = clien;

        while (st1 == 0 && count < 500) {
            count++;
            //char c11 = -52;
            //cout << "cicle";
            int i;
            client_data cl2, cl3, cl4;
            string name = "", surname = "", patron = ""; int n = 0, s = 0, p = 0, n1 = 0, p1 = 0, s1 = 0;;//
            string imp = ""; imp.clear();
            double sum = -1, avg = -1, sum1 = -1, avg1 = -1, pr = 0;
            int arr[3] = { -1, -1, -1 }; int day = -1, year = -1, month = -1, year1 = -1, day1 = -1, month1 = -1;
            int arr1[3] = { -1, -1, -1 };
            vector<double> prod;
            long long int num = -1, num1 = -1; //
            int zskob=0,fskob = 0, sskob = 0, thskob = 0, foskob = 0, fiskob = 0;
            int pl = -1;
            int brek = 0;
            string sortc = "";
            client cli(1,surname,name,patron,arr,num,prod);
            
            fscanf_s(input, "%c", &c,1);
            cas = -1; st1 = 0;
            for (i = 0; (i < 255) && ((c == 10) || (c == 32) || (c==-52)); i++) {
                fscanf_s(input,"%c", &c,1);
                if (i == 254) { st = 1; };
            }
           
            if (st == 0) {
                for (int k = 0; (k < 255) && (c > 96) && (c < 123); k++) {
                    imp.append(1, c); fscanf_s(input, "%c", &c, 1);
                }

                //for (i = 0; i < size(imp); i++) {cout << imp[i];}

                for (i = 0; i < 11; i++) {
                    if (imp == com[i]) { cas = i; }
                }
                //cout << cas << "\n";

                if (cas == 0) {
                    setlocale(LC_ALL, "Russian"); st = 0;
                    n = 0; s = 0; zskob = 0; st = 0;
                    if (c == 40) {
                        s = fscanf_s(input,"%d", &n);
                        fscanf_s(input, "%c", &c, 1);
                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }
                        if (s != 0 && c == 41) {
                            cli.id = n; zskob = 1;
                        }
                    }
                    n = 0; s = 0; p = 0; fskob = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        fscanf_s(input, "%c", &c, 1); pl = c;
                        for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                            fixchar(c);  surname.append(1, c); fscanf_s(input, "%c", &c, 1); s = 1;
                        }
                        if (c == 44) {
                            //cout << "(zap1)";
                            fscanf_s(input, "%c", &c, 1);
                            for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                fixchar(c);  name.append(1, c); fscanf_s(input, "%c", &c, 1); n = 1;
                            }
                            if (c == 44) {
                                //cout << "(zap2)";
                                fscanf_s(input, "%c", &c, 1);
                                for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                    fixchar(c);  patron.append(1, c); fscanf_s(input, "%c", &c, 1); p = 1;
                                }

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input, "%c", &c, 1);
                                    if (k == 29) { st = 1; }
                                }

                                //cout << " ";  for (int k = 0; k < size(surname); k++) { cout << surname[k]; } cout << " ";
                                if (s == 1) { cli.surname = surname; } s = 0; surname.clear();
                                if (n == 1) { cli.name = name; } n = 0; name.clear();
                                if (p == 1) { cli.patronymic = patron; } p = 0; patron.clear();

                                cl2 = cl3;

                                //cout << 0;

                                if (c == 41) {
                                    if (st == 0) { fskob = 1; }
                                }
                            }
                        }
                        else {
                            if (c == 41) { fskob = 1; }
                        }

                    }
                    n = 0; s = 0; p = 0; sskob = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        n = fscanf_s(input,"%lld", &num);
                        fscanf_s(input, "%c", &c, 1);

                        if (n != 0) { cli.number = num; }
                        n = 0;
                        num = -1;

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 41) {
                            if (st == 0) { sskob = 1; }
                        };

                    }
                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0; thskob = 0;
                    brek = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        n = fscanf_s(input,"%d", &day);
                        fscanf_s(input, "%c", &c, 1);

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 46) {

                            p = fscanf_s(input,"%d", &month);
                            fscanf_s(input, "%c", &c, 1);

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input, "%c", &c, 1);
                                if (k == 29) { st = 1; }
                            }

                            if (c == 46) {

                                s = fscanf_s(input,"%d", &year);
                                fscanf_s(input, "%c", &c, 1);

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input, "%c", &c, 1);
                                    if (k == 29) { st = 1; }
                                }


                                if (p == 1 && s == 1 && n == 1) {
                                    //cout << "(" << year << " " << year1 << ")";
                                    arr[2] = year; arr[0] = day; arr[1] = month;
                                    cli.arr[0] = arr[0]; cli.arr[1] = arr[1]; cli.arr[2] = arr[2];
                                }

                                n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0;

                                if (c == 41) {
                                    if (st == 0) { thskob = 1; }
                                };
                            }
                        }
                        else {
                            if (c == 41 && n == 0) { thskob = 1; }
                        }

                        ///////
                    }
                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0; foskob = 0;
                    brek = 0; pr = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {

                        n = fscanf_s(input,"%lf", &pr);
                        if (n != 0) { prod.push_back(pr); }

                        while (brek != -1) {
                            fscanf_s(input, "%c", &c, 1);

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input, "%c", &c, 1);
                                if (k == 29) { st = 1; }
                            }

                            if (c == 124) {

                                n = fscanf_s(input,"%lf", &pr);
                                if (n != 0) {
                                    prod.push_back(pr);
                                }
                            }
                            else { brek = -1; }
                        }
                        if (c == 41) {
                            if (st == 0) { cli.prod = prod; foskob = 1; }
                        }
                    }
                    if (fskob == 1 && sskob == 1 && thskob == 1 && foskob == 1 && zskob==1) {
                        s = 0; n = cli.prod.size();
                        if (cli.name != "") { s++; cl.edit_cl1(cli.id, cli.name); }
                        if (cli.surname != "") { s++;  cl.edit_cl2(cli.id, cli.surname);}
                        if (cli.patronymic != "") { s++;  cl.edit_cl3(cli.id, cli.patronymic);}
                        if (cli.arr[0] != -1 && cli.arr[1] != -1 && cli.arr[2] != -1) { s++; cl.edit_cl1(cli.id, cli.arr); }
                        if (cli.number != -1) { s++;  cl.edit_cl1(cli.id, cli.number); }
                        if (n > 0) { s++;  cl.edit_cl1(cli.id, cli.prod); }
                        
                    }

                }

                if (cas == 1) {
                    setlocale(LC_ALL, "Russian");
                    n = 0; s = 0; zskob = 1; st = 0;
                    if (c == 40) {
                        s = fscanf_s(input, "%d", &n);
                        fscanf_s(input, "%c", &c, 1);
                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }
                        if (s != 0 && c == 41) {
                            cl2 = cl.select_0(n);
                            fprintf(output,"\n\n");
                            cl2.print_base_file(output);
                            fprintf(output,"\n");
                            cl.delete_cl(n); n = 0; 
                            zskob = 0; //cout << "";
                        }
                    }
                    n = 0; s = 0; p = 0;fskob = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        fscanf_s(input, "%c", &c, 1); pl = c;
                        for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                            fixchar(c);  surname.append(1, c); fscanf_s(input, "%c", &c, 1); s = 1;
                        }
                        if (c == 44) {
                            //cout << "(zap1)";
                            fscanf_s(input,"%c", &c,1);
                            for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                fixchar(c);  name.append(1, c); fscanf_s(input, "%c", &c, 1); n = 1;
                            }
                            if (c == 44) {
                                //cout << "(zap2)";
                                fscanf_s(input,"%c", &c,1);
                                for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                    fixchar(c);  patron.append(1, c); fscanf_s(input, "%c", &c, 1); p = 1;
                                }

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input, "%c", &c, 1);
                                    if (k == 29) { st = 1; }
                                }

                                //cout << " ";  for (int k = 0; k < size(surname); k++) { cout << surname[k]; } cout << " ";
                                if (s == 1) { cli.surname = surname; } s = 0; surname.clear();
                                if (n == 1) { cli.name = name; } n = 0; name.clear();
                                if (p == 1) { cli.patronymic = patron; } p = 0; patron.clear();

                                cl2 = cl3;

                                //cout << 0;
                                
                                if (c == 41) {
                                    if (st == 0) { fskob = 1; }
                                }
                            }
                        }
                        else {
                            if (c == 41) { fskob = 1; }
                        }

                    }
                    n = 0; s = 0; p = 0; sskob = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        n = fscanf_s(input, "%lld", &num);
                        fscanf_s(input, "%c", &c,1);

                        if (n != 0) { cli.number = num; }
                        n = 0;
                        num = -1;

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c,1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 41) {
                            if (st == 0) { sskob = 1; }
                        };

                    }
                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0; thskob = 0;
                    brek = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        n = fscanf_s(input,"%d", &day);
                        fscanf_s(input,"%c", &c,1);

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input,"%c", &c,1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 46) {

                            p = fscanf_s(input,"%d", &month);
                            fscanf_s(input,"%c", &c,1);

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input,"%c", &c,1);
                                if (k == 29) { st = 1; }
                            }

                            if (c == 46) {

                                s = fscanf_s(input,"%d", &year);
                                fscanf_s(input,"%c", &c,1);

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input,"%c", &c,1);
                                    if (k == 29) { st = 1; }
                                }


                                if (p == 1 && s == 1 && n == 1) {
                                    //cout << "(" << year << " " << year1 << ")";
                                    arr[2] = year; arr[0] = day; arr[1] = month;
                                    cli.arr[0] = arr[0]; cli.arr[1] = arr[1]; cli.arr[2] = arr[2];
                                }
                                    
                                n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0;

                                if (c == 41) {
                                    if (st == 0) { thskob = 1; }
                                };
                            }
                        }
                        else {
                            if (c == 41 && n == 0) { thskob = 1; }
                        }

                        ///////
                    }
                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0; foskob = 0;
                    brek = 0; pr = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {

                        n = fscanf_s(input,"%lf", &pr);
                        if (n != 0) { prod.push_back(pr); }

                        while (brek != -1) {
                            fscanf_s(input, "%c", &c, 1);

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input, "%c", &c, 1);
                                if (k == 29) { st = 1; }
                            }

                            if (c == 124) {
                                
                                n = fscanf_s(input,"%lf", &pr);
                                if (n != 0) {
                                    prod.push_back(pr);
                                }
                            }
                            else { brek = -1; }
                        }
                        if (c == 41) {
                            if (st == 0) { cli.prod = prod; foskob = 1; } 
                        }
                    }
                    if (fskob == 1 && sskob == 1 && thskob == 1 && zskob == 1 && foskob==1) {
                        cl2 = cl; s = 0; n = cli.prod.size();
                        if (cli.name != "") { cl2 = cl2.select_2(cli.name); s++; }
                        if (cli.surname != "") { cl2 = cl2.select_1(cli.surname); s++; }
                        if (cli.patronymic != "") { cl2 = cl2.select_3(cli.patronymic); s++; }
                        if (cli.arr[0] != -1 && cli.arr[1] != -1 && cli.arr[2] != -1) { cl2 = cl2.select_(cli.arr); s++; }
                        if (cli.number != -1) { cl2 = cl2.select_(cli.number); s++; }
                        if ( n > 0) { cl2 = cl2.select_(cli.prod); s++;}
                        if (s != 0) {
                            fprintf(output, "\n\n");
                            cl2.print_base_file(output);
                            fprintf(output, "\n");
                            for (auto it = cl2.clients.begin(); it != cl2.clients.end(); it++) {
                                cl.delete_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
                                //cout << it->surname << " " << it->name << " " << it->patronymic << it->arr << " " << it->number << " ";
                            }
                        }
                    }
                    
                }

                if (cas == 2) {
                    if (c == 40) {
                        fscanf_s(input,"%c", &c,1);
                        if (c == 41) {
                            fprintf(output, "\n\n");
                            cl.print_base_file(output);
                            fprintf(output, "\n");
                        }
                    }
                }

                if (cas == 3) {
                    sortcas = 0;
                    if (c == 40) {
                        fscanf_s(input, "%c", &c, 1);
                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }
                        for (int k = 0; (k < 255) && (c > 96) && (c < 123); k++) {
                            sortc.append(1, c); fscanf_s(input, "%c", &c, 1);
                        }
                        if (c == 41) {
                            //for (i = 0; i < size(sortc); i++) { cout << sortc[i]; }

                            for (int k = 0; k < 7; k++) {
                                if (sortc == sortcase[k]) { sortcas = k; }
                            } sortc.clear();
                            if (sortcas == 0 || sortcas == 1) {
                                cl.sortby_date();
                            }
                            if (sortcas == 2 || sortcas == 3) {
                                cl.sortby_number();
                            }
                            if (sortcas == 4 || sortcas == 5) {
                                cl.sortby_avgspent();
                            }
                            if (sortcas == 6 || sortcas == 7) {
                                cl.sortby_spendings();
                            }
                            if (sortcas == -1) {
                                fprintf(output, "\nnot a sorting space\n");
                            }

                            fprintf(output, "\n\n");
                            cl.print_base_file(output);
                            fprintf(output, "\n");
                        }
                    }
                }

                if (cas == 4) {
                    setlocale(LC_ALL, "Russian");
                    cl3 = cl; cl2 = cl; fskob = 0; st = 0;
                    if (c == 40) {
                        //cout << "(skob1)";
                        fscanf_s(input,"%c", &c,1); pl = c;
                        for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                            fixchar(c);  surname.append(1, c); fscanf_s(input,"%c", &c,1); s = 1;
                        }
                        if (c == 44) {
                            //cout << "(zap1)";
                            fscanf_s(input,"%c", &c,1);
                            for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                fixchar(c);  name.append(1, c); fscanf_s(input,"%c", &c,1); n = 1;
                            }
                            if (c == 44) {
                                //cout << "(zap2)";
                                fscanf_s(input,"%c", &c,1);
                                for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                    fixchar(c);  patron.append(1, c); fscanf_s(input,"%c", &c,1); p = 1;
                                }

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input,"%c", &c,1);
                                    if (k == 29) { st = 1; }
                                }

                                //cout << " ";  for (int k = 0; k < size(surname); k++) { cout << surname[k]; } cout << " ";
                                if (s == 1) { cl3 = cl3.select_1(surname); } s = 0; surname.clear();
                                if (n == 1) { cl3 = cl3.select_2(name); } n = 0; name.clear();
                                if (p == 1) { cl3 = cl3.select_3(patron); } p = 0; patron.clear();

                                cl2 = cl3;

                                //cout << 0;
                                while (brek != -2) {
                                    brek = 0;

                                    //cout << c;

                                    if (c == 47) {
                                        //...................................................................................................
                                        cl3 = cl;

                                        fscanf_s(input,"%c", &c,1);

                                        if (c == 32) {
                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                fscanf_s(input,"%c", &c,1);
                                                if (k == 29) { st = 1; }
                                            }
                                        }

                                        //pl = c; cout <<"("<< pl<<")";
                                        for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                            fixchar(c);  surname.append(1, c); fscanf_s(input,"%c", &c,1); s = 1; //cout << "(2)";
                                        }
                                        if (c == 44) {
                                            //cout << "zap3";
                                            fscanf_s(input,"%c", &c,1);
                                            for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                                fixchar(c);   name.append(1, c); fscanf_s(input,"%c", &c,1); n = 1; //cout << "(3)";
                                            }
                                            if (c == 44) {
                                                //cout << "zap4";
                                                fscanf_s(input,"%c", &c,1);
                                                for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                                    fixchar(c);   patron.append(1, c); fscanf_s(input,"%c", &c,1); p = 1; //cout << "(4)";
                                                }

                                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                                    fscanf_s(input,"%c", &c,1);
                                                    if (k == 29) { st = 1; }
                                                }

                                                //cout << " "; for (int k = 0; k < size(name); k++) { cout << name[k]; } cout << " ";
                                                if (s == 1) { cl3 = cl3.select_1(surname); } s = 0;  surname = "";
                                                if (n == 1) { cl3 = cl3.select_2(name); } n = 0; name = "";
                                                if (p == 1) { cl3 = cl3.select_3(patron); } p = 0; patron = "";

                                                cl3.additself(cl2); //cout << 4;

                                            }
                                            //.................................................................................................
                                        }
                                    }
                                    else {
                                        brek = brek - 1;
                                        if (c == 38) {
                                            //cout << 2;
                                            //....................................................................................................
                                            fscanf_s(input,"%c", &c,1);

                                            if (c == 32) {
                                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                                    fscanf_s(input,"%c", &c,1);
                                                    if (k == 29) { st = 1; }
                                                }
                                            }

                                            for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                                fixchar(c);  surname.append(1, c); fscanf_s(input,"%c", &c,1); s = 1;
                                            }
                                            if (c == 44) {
                                                fscanf_s(input,"%c", &c,1);
                                                for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                                    fixchar(c);  name.append(1, c); fscanf_s(input,"%c", &c,1); n = 1;
                                                }
                                                if (c == 44) {
                                                    fscanf_s(input,"%c", &c,1);
                                                    for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                                        fixchar(c);  patron.append(1, c); fscanf_s(input,"%c", &c,1); p = 1;
                                                    }

                                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                                        fscanf_s(input,"%c", &c,1);
                                                        if (k == 29) { st = 1; }
                                                    }

                                                    if (s == 1) { cl3 = cl3.select_1(surname); } s = 0; surname = "";
                                                    if (n == 1) { cl3 = cl3.select_2(name); } n = 0; name = "";
                                                    if (p == 1) { cl3 = cl3.select_3(patron); } p = 0;  patron = "";

                                                    cl2 = cl3;
                                                }
                                                //.................................................................................................
                                            }

                                        }
                                        else { brek = brek - 1; }
                                    }
                                }

                                if (c == 41) {
                                    //cout << "\n\n";
                                    //cl2.print_base();
                                    //cout << "\n";
                                    if (st == 0) { fskob = 1; }
                                }
                            }
                        }
                        else {
                            if (c == 41) { fskob = 1; }
                        }

                    }
                    brek = 0; sskob = 0; cl3 = cl2; cl4 = cl2;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        n = fscanf_s(input,"%lld", &num);
                        fscanf_s(input,"%c", &c,1);

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input,"%c", &c,1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 44 && n == 1) {
                            // cout << "(zap1)";
                            p = fscanf_s(input,"%lld", &num1);
                            fscanf_s(input,"%c", &c,1);

                            if (p == 0) { cl3 = cl3.select_(num); }
                            if (p == 1) { cl3 = cl3.select_(num, num1); } n = 0;  p = 0;
                            num = -1; num1 = -1;

                            cl2 = cl3;

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input,"%c", &c,1);
                                if (k == 29) { st = 1; }
                            }

                            //cout << 0;
                            while (brek != -2) {
                                brek = 0;

                                if (c == 47) {
                                    //...................................................................................................
                                    cl3 = cl4;

                                    n = fscanf_s(input,"%lld", &num);
                                    fscanf_s(input,"%c", &c,1);

                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                        fscanf_s(input,"%c", &c,1);
                                        if (k == 29) { st = 1; }
                                    }

                                    if (c == 44 && n == 1) {
                                        //cout << "zap2";
                                        p = fscanf_s(input,"%lld", &num1);
                                        fscanf_s(input,"%c", &c,1);

                                        //cout << " "; for (int k = 0; k < size(name); k++) { cout << name[k]; } cout << " ";
                                        if (p == 0) { cl3 = cl3.select_(num); }
                                        if (p == 1) { cl3 = cl3.select_(num, num1); } n = 0;  p = 0;
                                        num = -1; num1 = -1;

                                        cl3.additself(cl2);//cout << 4;

                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                            fscanf_s(input,"%c", &c,1);
                                            if (k == 29) { st = 1; }
                                        }

                                        //.................................................................................................
                                    }
                                }
                                else {
                                    brek = brek - 1;
                                    if (c == 38) {
                                        //...................................................................................................
                                        cl3 = cl2;

                                        n = fscanf_s(input,"%lld", &num);
                                        fscanf_s(input,"%c", &c,1);

                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                            fscanf_s(input,"%c", &c,1);
                                            if (k == 29) { st = 1; }
                                        }

                                        if (c == 44 && n == 1) {
                                            cout << "zap2";
                                            p = fscanf_s(input,"%lld", &num1);
                                            fscanf_s(input,"%c", &c,1);

                                            //cout << " "; for (int k = 0; k < size(name); k++) { cout << name[k]; } cout << " ";
                                            if (p == 0) { cl3 = cl3.select_(num); }
                                            if (p == 1) { cl3 = cl3.select_(num, num1); } n = 0;  p = 0;
                                            num = -1; num1 = -1;

                                            cl2 = cl3; //cout << 4;

                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                fscanf_s(input,"%c", &c,1);
                                                if (k == 29) { st = 1; }
                                            }

                                            //.................................................................................................
                                        }
                                    }
                                    else { brek = brek - 1; }
                                }
                            }

                            if (c == 41) {
                                /*cout << "\n\n";
                                cl2.print_base();
                                cout << "\n";*/
                                if (st == 0) { sskob = 1; }
                            };
                        }
                        else {
                            if (c == 41 && n == 0) { sskob = 1; }
                        }
                    }
                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0; thskob = 0;
                    cl3 = cl2; cl4 = cl2; brek = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        n = fscanf_s(input,"%d", &day);
                        fscanf_s(input,"%c", &c,1);

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input,"%c", &c,1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 46) {

                            p = fscanf_s(input,"%d", &month);
                            fscanf_s(input,"%c", &c,1);

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input,"%c", &c,1);
                                if (k == 29) { st = 1; }
                            }

                            if (c == 46) {

                                s = fscanf_s(input,"%d", &year);
                                fscanf_s(input,"%c", &c,1);

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input,"%c", &c,1);
                                    if (k == 29) { st = 1; }
                                }

                                if (c == 44) {

                                    n1 = fscanf_s(input,"%d", &day1);
                                    fscanf_s(input,"%c", &c,1);

                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                        fscanf_s(input,"%c", &c,1);
                                        if (k == 29) { st = 1; }
                                    }

                                    if (c == 46) {
                                        p1 = fscanf_s(input,"%d", &month1);
                                        fscanf_s(input,"%c", &c,1);

                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                            fscanf_s(input,"%c", &c,1);
                                            if (k == 29) { st = 1; }
                                        }

                                        if (c == 46) {
                                            s1 = fscanf_s(input,"%d", &year1);
                                            fscanf_s(input,"%c", &c,1);

                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                fscanf_s(input,"%c", &c,1);
                                                if (k == 29) { st = 1; }
                                            }
                                            //cout << 3;
                                        }
                                    }

                                    if (s1 == 1 && s == 1 && n == 1 && n1 == 1 && p == 1 && p1 == 1) {
                                        //cout << "(" << year << " " << year1 << ")";
                                        arr[2] = year; arr[0] = day; arr[1] = month;
                                        arr1[2] = year1; arr1[0] = day1; arr1[1] = month1;
                                        cl3 = cl3.select_(arr, arr1);
                                    }
                                    else {
                                        if (s == 1 && n == 1 && p == 1 && s1 == 0 && p1 == 0 && n1 == 0) {
                                            //cout << "(" << year << ")";
                                            arr[2] = year; arr[0] = day; arr[1] = month;
                                            cl3 = cl3.select_(arr);
                                        }
                                        else {
                                            if (s1 == 1 && n1 == 1 && p1 == 1 && s == 0 && p == 0 && n == 0) {
                                                arr1[2] = year1; arr1[0] = day1; arr1[1] = month1;
                                                cl3 = cl3.select_(arr1);
                                            }
                                            else { st = 1; }
                                        }
                                    }
                                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0;
                                    cl2 = cl3;

                                    while (brek != -2) {
                                        brek = 0;
                                        if (c == 47) {
                                            cl3 = cl4;
                                            n = fscanf_s(input,"%d", &day);
                                            fscanf_s(input,"%c", &c,1);

                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                fscanf_s(input,"%c", &c,1);
                                                if (k == 29) { st = 1; }
                                            }

                                            if (c == 46) {
                                                p = fscanf_s(input,"%d", &month);
                                                fscanf_s(input,"%c", &c,1);

                                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                                    fscanf_s(input,"%c", &c,1);
                                                    if (k == 29) { st = 1; }
                                                }

                                                if (c == 46) {
                                                    s = fscanf_s(input,"%d", &year);
                                                    fscanf_s(input,"%c", &c,1);

                                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                                        fscanf_s(input,"%c", &c,1);
                                                        if (k == 29) { st = 1; }
                                                    }

                                                    if (c == 44) {
                                                        n1 = fscanf_s(input,"%d", &day1);
                                                        fscanf_s(input,"%c", &c,1);

                                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                                            fscanf_s(input,"%c", &c,1);
                                                            if (k == 29) { st = 1; }
                                                        }

                                                        if (c == 46) {
                                                            p1 = fscanf_s(input,"%d", &month1);
                                                            fscanf_s(input,"%c", &c,1);

                                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                                fscanf_s(input,"%c", &c,1);
                                                                if (k == 29) { st = 1; }
                                                            }

                                                            if (c == 46) {
                                                                s1 = fscanf_s(input,"%d", &year1);
                                                                fscanf_s(input,"%c", &c,1);

                                                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                                                    fscanf_s(input,"%c", &c,1);
                                                                    if (k == 29) { st = 1; }
                                                                }
                                                            }
                                                        }

                                                        if (s1 == 1 && s == 1 && n == 1 && n1 == 1 && p == 1 && p1 == 1) {
                                                            //cout << 1;
                                                            arr[2] = year; arr[0] = day; arr[1] = month;
                                                            arr1[2] = year1; arr1[0] = day1; arr1[1] = month1;
                                                            cl3 = cl3.select_(arr, arr1);
                                                        }
                                                        else {
                                                            if (s == 1 && n == 1 && p == 1 && s1 == 0 && p1 == 0 && n1 == 0) {
                                                                arr[2] = year; arr[0] = day; arr[1] = month;
                                                                cl3 = cl3.select_(arr);
                                                            }
                                                            else {
                                                                if (s1 == 1 && n1 == 1 && p1 == 1 && s == 0 && p == 0 && n == 0) {
                                                                    arr1[2] = year1; arr1[0] = day1; arr1[1] = month1;
                                                                    cl3 = cl3.select_(arr1);
                                                                }
                                                                else { st = 1; }
                                                            }
                                                        }
                                                        n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0;
                                                        cl3.additself(cl2);

                                                    }
                                                }

                                            }

                                        }
                                        else {
                                            cl3 = cl2;
                                            brek = brek - 1;
                                            if (c == 38) {
                                                n = fscanf_s(input,"%d", &day);
                                                fscanf_s(input,"%c", &c,1);

                                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                                    fscanf_s(input,"%c", &c,1);
                                                    if (k == 29) { st = 1; }
                                                }

                                                if (c == 46) {
                                                    p = fscanf_s(input,"%d", &month);
                                                    fscanf_s(input,"%c", &c,1);

                                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                                        fscanf_s(input,"%c", &c,1);
                                                        if (k == 29) { st = 1; }
                                                    }

                                                    if (c == 46) {
                                                        s = fscanf_s(input,"%d", &year);
                                                        fscanf_s(input,"%c", &c,1);

                                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                                            fscanf_s(input,"%c", &c,1);
                                                            if (k == 29) { st = 1; }
                                                        }

                                                        if (c == 44) {
                                                            n1 = fscanf_s(input,"%d", &day1);
                                                            fscanf_s(input,"%c", &c,1);

                                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                                fscanf_s(input,"%c", &c,1);
                                                                if (k == 29) { st = 1; }
                                                            }

                                                            if (c == 46) {
                                                                p1 = fscanf_s(input,"%d", &month1);
                                                                fscanf_s(input,"%c", &c,1);

                                                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                                                    fscanf_s(input,"%c", &c,1);
                                                                    if (k == 29) { st = 1; }
                                                                }

                                                                if (c == 46) {
                                                                    s1 = fscanf_s(input,"%d", &year1);
                                                                    fscanf_s(input,"%c", &c,1);

                                                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                                                        fscanf_s(input,"%c", &c,1);
                                                                        if (k == 29) { st = 1; }
                                                                    }

                                                                }
                                                            }
                                                            //cout << n << p << s << n1 << p1 << s1;
                                                            if (s1 == 1 && s == 1 && n == 1 && n1 == 1 && p == 1 && p1 == 1) {
                                                                //cout << "(" << year << " " << year1 << ")";
                                                                arr[2] = year; arr[0] = day; arr[1] = month;
                                                                arr1[2] = year1; arr1[0] = day1; arr1[1] = month1;
                                                                cl3 = cl3.select_(arr, arr1);
                                                            }
                                                            else {
                                                                if (s == 1 && n == 1 && p == 1 && s1 == 0 && p1 == 0 && n1 == 0) {
                                                                    arr[2] = year; arr[0] = day; arr[1] = month;
                                                                    cl3 = cl3.select_(arr);
                                                                }
                                                                else {
                                                                    if (s1 == 1 && n1 == 1 && p1 == 1 && s == 0 && p == 0 && n == 0) {
                                                                        arr1[2] = year1; arr1[0] = day1; arr1[1] = month1;
                                                                        cl3 = cl3.select_(arr1);
                                                                    }
                                                                    else { st = 1; }
                                                                }
                                                            }
                                                            n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0;
                                                            cl2 = cl3;
                                                        }
                                                    }

                                                }

                                            }
                                            else {
                                                brek = brek - 1; //cout << brek;
                                            }
                                        }
                                        //////
                                    }

                                    if (c == 41) {
                                        /*cout << "\n\n";
                                        cl2.print_base();
                                        cout << "\n";*/
                                        if (st == 0) { thskob = 1; }
                                    };
                                }
                            }
                        }
                        else {
                            if (c == 41 && n == 0) { thskob = 1; }
                        }

                        ///////
                    }
                    brek = 0; foskob = 0; cl3 = cl2; cl4 = cl2;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        n = fscanf_s(input,"%lf", &avg);
                        fscanf_s(input, "%c", &c, 1);
                        //int p2 = c; cout << p2;
                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 124 && n != 0) {
                            //cout << "(zap1)";
                            p = fscanf_s(input,"%lf", &avg1);
                            //cout << avg1;
                            s = fscanf_s(input, "%c", &c, 1);
                            //cout << "(" << s << ")";

                            if (p == 0) { cl3 = cl3.select_1(avg); }
                            if (p != 0) { cl3 = cl3.select_1(avg, avg1); } n = 0;  p = 0;

                            cl2 = cl3;

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input, "%c", &c, 1);
                                if (k == 29) { st = 1; }
                            }

                            //cl3.getlen();
                            while (brek != -2) {
                                brek = 0;

                                if (c == 47) {
                                    //cout << "zap2";
                                    //...................................................................................................
                                    cl3 = cl4;

                                    n = fscanf_s(input,"%lf", &avg);
                                    fscanf_s(input, "%c", &c, 1);


                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                        fscanf_s(input, "%c", &c, 1);
                                        if (k == 29) { st = 1; }
                                    }
                                    //cout << c << avg;
                                    if (c == 124 && n != 0) {
                                        //cout << "zap2";
                                        p = fscanf_s(input,"%lf", &avg1);
                                        fscanf_s(input, "%c", &c, 1);
                                        //cout << avg1;

                                        //cout << " "; for (int k = 0; k < size(name); k++) { cout << name[k]; } cout << " ";
                                        if (p == 0) { cl3 = cl3.select_1(avg); cout << "p=0"; }
                                        if (p != 0) { cl3 = cl3.select_1(avg, avg1); cout << "p!=0"; } n = 0;  p = 0;

                                        cl3.additself(cl2);//cout << 4;

                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                            fscanf_s(input, "%c", &c, 1);
                                            if (k == 29) { st = 1; }
                                        }

                                        //.................................................................................................
                                    }
                                }
                                else {
                                    brek = brek - 1;
                                    if (c == 38) {
                                        //...................................................................................................
                                        cl3 = cl2;

                                        n = fscanf_s(input,"%lf", &avg);
                                        fscanf_s(input, "%c", &c, 1);

                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                            fscanf_s(input, "%c", &c, 1);
                                            if (k == 29) { st = 1; }
                                        }

                                        if (c == 124 && n != 0) {
                                            //cout << "zap2";
                                            p = fscanf_s(input,"%lf", &avg1);
                                            fscanf_s(input, "%c", &c, 1);

                                            //cout << " "; for (int k = 0; k < size(name); k++) { cout << name[k]; } cout << " ";
                                            if (p == 0) { cl3 = cl3.select_1(avg); }
                                            if (p != 0) { cl3 = cl3.select_1(avg, avg1); } n = 0;  p = 0;

                                            cl2 = cl3; //cout << 4;

                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                fscanf_s(input, "%c", &c, 1);
                                                if (k == 29) { st = 1; }
                                            }

                                            //.................................................................................................
                                        }
                                    }
                                    else { brek = brek - 1; }
                                }
                            }
                            //cout << c;
                            if (c == 41) {
                                /*cout << "\n\n";
                                cl2.print_base();
                                cout << "\n";*/
                                if (st == 0) { foskob = 1; }
                            };
                        }
                        else {
                            if (c == 41 && n == 0) { foskob = 1; }
                        }
                    }
                    brek = 0; fiskob = 0; cl3 = cl2; cl4 = cl2;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        n = fscanf_s(input,"%lf", &sum);
                        fscanf_s(input, "%c", &c, 1);

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }
                        int p2 = c; //cout << p2;

                        if (c == 124 && n != 0) {
                            //cout << "(zap1)";
                            p = fscanf_s(input,"%lf", &sum1);
                            //cout << sum1;
                            fscanf_s(input, "%c", &c, 1);


                            if (p == 0) { cl3 = cl3.select_(sum); }
                            if (p != 0) {
                                cl3 = cl3.select_(sum, sum1);
                            } n = 0;  p = 0;

                            cl2 = cl3;

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input, "%c", &c, 1);
                                if (k == 29) { st = 1; }
                            }

                            //cout << 0;
                            while (brek != -2) {
                                brek = 0;

                                if (c == 47) {
                                    //...................................................................................................
                                    cl3 = cl4;

                                    n = fscanf_s(input,"%lf", &sum);
                                    fscanf_s(input, "%c", &c, 1);

                                    for (int k = 0; (k < 30) && (c == 32); k++) {
                                        fscanf_s(input, "%c", &c, 1);
                                        if (k == 29) { st = 1; }
                                    }

                                    if (c == 124 && n != 0) {
                                        //cout << "zap2";
                                        p = fscanf_s(input,"%lf", &sum1);
                                        fscanf_s(input, "%c", &c, 1);

                                        //cout << " "; for (int k = 0; k < size(name); k++) { cout << name[k]; } cout << " ";
                                        if (p == 0) { cl3 = cl3.select_(sum); }
                                        if (p != 0) { cl3 = cl3.select_(sum, sum1); } n = 0;  p = 0;

                                        cl3.additself(cl2);//cout << 4;

                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                            fscanf_s(input, "%c", &c, 1);
                                            if (k == 29) { st = 1; }
                                        }

                                        //.................................................................................................
                                    }
                                }
                                else {
                                    brek = brek - 1;
                                    if (c == 38) {
                                        //...................................................................................................
                                        cl3 = cl2;

                                        n = fscanf_s(input,"%lf", &sum);
                                        fscanf_s(input, "%c", &c, 1);

                                        for (int k = 0; (k < 30) && (c == 32); k++) {
                                            fscanf_s(input, "%c", &c, 1);
                                            if (k == 29) { st = 1; }
                                        }

                                        if (c == 124 && n == 1) {
                                            //cout << "zap2";
                                            p = fscanf_s(input,"%lf", &sum1);
                                            fscanf_s(input, "%c", &c, 1);

                                            //cout << " "; for (int k = 0; k < size(name); k++) { cout << name[k]; } cout << " ";
                                            if (p == 0) { cl3 = cl3.select_(sum); }
                                            if (p != 0) { cl3 = cl3.select_(sum, sum1); } n = 0;  p = 0;

                                            cl2 = cl3; //cout << 4;

                                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                                fscanf_s(input, "%c", &c, 1);
                                                if (k == 29) { st = 1; }
                                            }

                                            //.................................................................................................
                                        }
                                    }
                                    else { brek = brek - 1; }
                                }
                            }

                            if (c == 41) {
                                if (st == 0) { fiskob = 1; }
                            };
                        }
                        else {
                            if (c == 41 && n == 0) { fiskob = 1; }
                        }
                    }
                    fscanf_s(input, "%c", &c, 1);
                    //int p11 = c;  cout << p11;
                    if (c == 61) {
                        if (fskob == 1 && sskob == 1 && thskob == 1 && foskob == 1 && fiskob == 1) {
                            cl = cl2;
                            fprintf(output, "\n\n");
                            cl.print_base_file(output);
                            fprintf(output, "\n");
                        }
                    }
                    else {
                        if (fskob == 1 && sskob == 1 && thskob == 1 && foskob == 1 && fiskob == 1) {
                            fprintf(output, "\n\n");
                            cl2.print_base_file(output);
                            fprintf(output, "\n");
                        }
                    }
                }

                if (cas == 5) {
                    n = 0; s = 0;
                    if (c == 40) {
                        s = fscanf_s(input,"%d", &n);
                        fscanf_s(input,"%c", &c,1);
                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input,"%c", &c,1);
                            if (k == 29) { st = 1; }
                        }
                        if (c == 41 && s == 1) {
                            cl.generate_base(n);
                           
                        }
                    }
                    fscanf_s(input, "%c", &c, 1);
                    //int p11 = c;  cout << p11;
                    if (c != 45) {
                        fprintf(output, "\n\n");
                        cl.print_base_file(output);
                        //cl.print_base();
                        fprintf(output, "\n");
                    }
                }

                if (cas == 6) {
                    if (c == 40) {
                        fscanf_s(input,"%c", &c,1);
                        if (c == 41) {
                            cl.correct();
                            fprintf(output, "\n\n");
                            cl.print_base_file(output);
                            fprintf(output, "\n");
                        }
                    }
                }

                if (cas == 7) {
                    //cout << "(0)";
                    setlocale(LC_ALL, "Russian"); st = 0;
                    n = 0; s = 0; p = 0; fskob = 0;
                    if (c == 40) {
                        //cout << "(skob1)";
                        fscanf_s(input, "%c", &c, 1); pl = c;
                        for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                            fixchar(c);  surname.append(1, c); fscanf_s(input, "%c", &c, 1); s = 1;
                        }
                        if (c == 44) {
                            //cout << "(zap1)";
                            fscanf_s(input, "%c", &c, 1);
                            for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                fixchar(c);  name.append(1, c); fscanf_s(input, "%c", &c, 1); n = 1;
                            }
                            if (c == 44) {
                                //cout << "(zap2)";
                                fscanf_s(input, "%c", &c, 1);
                                for (int k = 0; (k < 255) && (((c > -33) && (c < -15)) || ((c > -129) && (c < -80))); k++) {
                                    fixchar(c);  patron.append(1, c); fscanf_s(input, "%c", &c, 1); p = 1;
                                }

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input, "%c", &c, 1);
                                    if (k == 29) { st = 1; }
                                }

                                //cout << " ";  for (int k = 0; k < size(surname); k++) { cout << surname[k]; } cout << " ";
                                if (s == 1) { cli.surname = surname;  } s = 0; surname.clear();
                                if (n == 1) { cli.name = name; } n = 0; name.clear();
                                if (p == 1) { cli.patronymic = patron; } p = 0; patron.clear();

                                cl2 = cl3;

                                //cout << 0;

                                if (c == 41) {
                                    if (st == 0) { fskob = 1; }
                                }
                            }
                        }
                        else {
                            if (c == 41) { fskob = 1; }
                        }

                    }
                    n = 0; s = 0; p = 0; sskob = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        //cout << "(skob1)";
                        n = fscanf_s(input,"%lld", &num);
                        fscanf_s(input, "%c", &c, 1);

                        if (n != 0) { cli.number = num; }
                        n = 0;
                        num = -1;

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 41) {
                            if (st == 0) { sskob = 1; }
                        };

                    }
                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0; thskob = 0;
                    brek = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {
                        n = fscanf_s(input,"%d", &day);
                        fscanf_s(input, "%c", &c, 1);

                        for (int k = 0; (k < 30) && (c == 32); k++) {
                            fscanf_s(input, "%c", &c, 1);
                            if (k == 29) { st = 1; }
                        }

                        if (c == 46) {

                            p = fscanf_s(input,"%d", &month);
                            fscanf_s(input, "%c", &c, 1);

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input, "%c", &c, 1);
                                if (k == 29) { st = 1; }
                            }

                            if (c == 46) {

                                s = fscanf_s(input,"%d", &year);
                                fscanf_s(input, "%c", &c, 1);

                                for (int k = 0; (k < 30) && (c == 32); k++) {
                                    fscanf_s(input, "%c", &c, 1);
                                    if (k == 29) { st = 1; }
                                }


                                if (p == 1 && s == 1 && n == 1) {
                                    //cout << "(" << year << " " << year1 << ")";
                                    arr[2] = year; arr[0] = day; arr[1] = month;
                                    cli.arr[0] = arr[0]; cli.arr[1] = arr[1]; cli.arr[2] = arr[2];
                                }

                                n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0;

                                if (c == 41) {
                                    if (st == 0) { thskob = 1; }
                                };
                            }
                        }
                        else {
                            if (c == 41 && n == 0) { thskob = 1; }
                        }

                        ///////
                    }
                    n = 0; s = 0; p = 0; n1 = 0; s1 = 0; p1 = 0; foskob = 0;
                    brek = 0; pr = 0;
                    fscanf_s(input, "%c", &c, 1);
                    if (c == 40) {

                        n = fscanf_s(input,"%lf", &pr);
                        if (n != 0) { prod.push_back(pr); }

                        while (brek != -1) {
                            fscanf_s(input, "%c", &c, 1);

                            for (int k = 0; (k < 30) && (c == 32); k++) {
                                fscanf_s(input, "%c", &c, 1);
                                if (k == 29) { st = 1; }
                            }

                            if (c == 124) {

                                n = fscanf_s(input,"%lf", &pr);
                                if (n != 0) {
                                    prod.push_back(pr);
                                }
                            }
                            else { brek = -1; }
                        }
                        if (c == 41) {
                            if (st == 0) { cli.prod = prod; foskob = 1; }
                        }
                    }
                    if (fskob == 1 && sskob == 1 && thskob == 1 && foskob == 1) {
                        s = 0; n = cli.prod.size();
                        if (cli.name != "") {s++; }
                        if (cli.surname != "") { s++; }
                        if (cli.patronymic != "") {s++; }
                        if (cli.arr[0] != -1 && cli.arr[1] != -1 && cli.arr[2] != -1) {s++; }
                        if (cli.number != -1) { s++; }
                        if (n > 0) {s++; }
                        if (s == 6) {
                            cl2.add_cl(cli.surname, cli.name, cli.patronymic, cli.arr, cli.number, cli.prod);
                            cl.add_cl(cli.surname, cli.name, cli.patronymic, cli.arr, cli.number, cli.prod);
                            fprintf(output,"\n\n");
                            cl2.print_base_file(output);
                            fprintf(output,"\n\n");
                        }
                    }

                }

                if (cas == 8) {
                    if (c == 40) {
                        fscanf_s(input, "%c", &c, 1);
                        if (c == 41) {
                            st1 = 1; fprintf(output, "\nend of imput\n");
                        }
                    }
                }

                if (cas == -1) {
                    fprintf(output,"not a command!\n");
                    //for (i = 0; i < size(imp); i++) { cout << imp[i]; }
                }
                if (cas == 9) {
                    st1 = 1; b = 1;
                }
                if (cas == 10) {
                    client_data clnew;
                    cl = clnew;
                    if (c == 40) {
                        fscanf_s(input, "%c", &c, 1);
                        if (c == 41) {
                            fprintf(output, "\ncleared\n");
                        }
                    }
                }

                if (b > 0.5) {
                    fprintf(output, "(next cicle)\n");
                }b = 0;


                //cout << st;

            }
        }

        clien = cl;
    }


    //......................................................................................................................................
    //data generator

    void generate_base(int n) {
        setlocale(LC_ALL, "Russian");
        random_device rd;   // non-deterministic generator
        mt19937 gen(rd());  // to seed mersenne twister.
        long long int value = 0;

        vector<string> name_male;
        vector<string> surname_male;
        vector<string> sec_name_male;
        vector<string> name_fem;
        vector<string> surname_fem;
        vector<string> sec_name_fem;

        //vector<double> prod1;

        mfiletovector("namem.txt", name_male);
        mfiletovector("surnamem.txt", surname_male);
        mfiletovector("2namem.txt", sec_name_male);
        mfiletovector("namef.txt", name_fem);
        mfiletovector("surnamef.txt", surname_fem);
        mfiletovector("2namef.txt", sec_name_fem);
        //mfiletovector("costs.txt",prod1);

        for (int i = 0; i < n; i++) {
            //cout << i << " ";
            int month = gen() % 12 +1;
            int day = gen();
            int year = gen() % 24 + 2000;
            int arr[3]; //cout << "(" << month << ") ";

            int numprod = gen() % 20 + 1;
            double cost,cost1 ;

            vector<double> prod = { };
            for (int c = 0; c < numprod; c++) {
                cost = gen() % 48000; cost = cost * 10;
                cost1 = gen() % 1000; cost1 = cost1 / 100;
                cost = cost + cost1 +20000;
                prod.push_back(cost);
            }

            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                arr[0] = abs(day) % 31 + 1; arr[1] = month; arr[2] = year;
            }
            if (month == 4 || month == 6 || month == 9 || month == 11) {
                arr[0] = abs(day) % 30 + 1; arr[1] = month; arr[2] = year;
            }
            if (month == 2 && year % 4 == 0) {
                arr[0] = abs(day) % 29 + 1; arr[1] = month; arr[2] = year;
            };
            if (month == 2 && year % 4 != 0) {
                arr[0] = abs(day) % 28 + 1; arr[1] = month; arr[2] = year;
            };

            const long long int c = gen() % 10 + (gen() % 10) * 10 + (gen() % 10) * 100 + (gen() % 10) * 100 + (gen() % 10) * 1000 + (gen() % 10) * 10000 + (gen() % 10) * 100000 + (gen() % 10) * 1000000;
            const int m = gen() % 9; //cout << " (" << m << ") \n"; 
            const int m1 = gen() % 2 + 7;
            value = 0;
            if (m == 0) { value = 4950000000 + c + m1 * 10000000000;}
            if (m == 1) { value = 4990000000 + c + m1 * 10000000000;}
            if (m == 2) { value = 9160000000 + c + m1 * 10000000000;}
            if (m == 3) { value = 9170000000 + c + m1 * 10000000000;}
            if (m == 4) { value = 9250000000 + c + m1 * 10000000000;}
            if (m == 5) { value = 9260000000 + c + m1 * 10000000000;}
            if (m == 6) { value = 9850000000 + c + m1 * 10000000000;}
            if (m == 7) { value = 9770000000 + c + m1 * 10000000000;}
            if (m == 8) { value = 9680000000 + c + m1 * 10000000000;}
            //cout << " (" << value << ") \n";

            if (gen() % 2 == 0) {

                add_cl(surname_male[gen() % surname_male.size()], name_male[gen() % name_male.size()],
                    sec_name_male[gen() % sec_name_male.size()], arr, value,prod);
            }
            else {
                add_cl(surname_fem[gen() % surname_fem.size()], name_fem[gen() % name_fem.size()],
                    sec_name_fem[gen() % sec_name_fem.size()], arr, value,prod);
            }
        };
        //......................................................................................................................................
        //......................................................................................................................................
    };

}; 