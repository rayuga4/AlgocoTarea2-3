#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

int readFile(string filename, int column, int row = 0){
    int pos = row*(26*2)+column*2;
    ifstream file(filename);
    file.seekg(pos,ios::beg);
    char value[3];
    file.read(value,2);
    value[2] = '\0';
    return atoi(value);
}

int costo_sub(char a, char b){
    int x = a-'a';
    int y = b-'a';
    string filename = "cost_replace.txt";
    return readFile(filename,x,y);
}

int costo_ins(char a){
    int x = a-'a';
    string filename = "cost_insert.txt";
    return readFile(filename,x);
}

int costo_del(char a){
    int x = a-'a';
    string filename = "cost_delete.txt";
    return readFile(filename,x);
}

int costo_trans(char a, char b){
    int x = a-'a';
    int y = b-'a';
    string filename = "cost_transpose.txt";
    return readFile(filename,x,y);
}

int evaluar(string s1, string s2){
    if (s1==s2){
        return 0;
    }
    if (s1.length()==0){
        int cost = 0;
        for (int i = 0;i<int(s2.length());i++){
            cost = cost+costo_ins(s2[i]);
        }
        return cost;
    }
    if (s2.length()==0){
        int cost = 0;
        for (int i = 0;i<int(s1.length());i++){
            cost = cost+costo_del(s1[i]);
        }
        return cost;
    }
    if (s1.length()==1 and s2.length()==1){
        return costo_sub(s1[0],s2[0]);
    }
    for (int i = 0;i<int(min(s1.length(),s2.length()));i++){
        if (s1[i]==s2[i]){
            return evaluar(s1.substr(0,i),s2.substr(0,i))+evaluar(s1.substr(i+1),s2.substr(i+1));
        }
    }
    string aux = s1;
    aux[0] = s2[0];
    int sub = evaluar(aux,s2) + costo_sub(s1[0],s2[0]);
    int ins = evaluar(s2[0]+s1,s2) + costo_del(s2[0]);
    int del = evaluar(s1.substr(1),s2) + costo_del(s1[0]);
    int trans = (10^31)-1;
    if (s1.length()>=2 and s2.length()>=2){
        if (s1[0]==s2[1] or s1[1]==s2[0]){
            aux = s1;
            aux[0] = s1[1];
            aux[1] = s1[0];
            trans = evaluar(aux,s2) + costo_trans(s1[0],s1[1]);
        }
    }
    return min({sub,ins,del,trans});
}

int main(){
    string s1,s2;
    string filename = "set 9.txt";
    ifstream file(filename);
    getline(file,s1);
    s1.erase(s1.length()-1); // remueve el \n
    getline(file,s2);
    file.close();
    auto start = chrono::system_clock::now();
    int cost = evaluar(s1,s2);
    auto end = chrono::system_clock::now();
    auto timeTaken = end-start;
    cout<<cost<<endl;
    cout<<timeTaken.count()<<endl;
}
