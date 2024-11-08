#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <cmath>
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
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for (int i = 1;i<=n;i++){
        dp[i][0] = dp[i-1][0] + costo_del(s1[i-1]);
    }
    for (int i = 1;i<=m;i++){
        dp[0][i] = dp[0][i-1] + costo_ins(s2[i-1]);
    }
    for (int i = 1;i<=n;i++){
        for (int j = 1;j<=m;j++){
            int costo1 = dp[i-1][j] + costo_del(s1[i-1]);
            int costo2 = dp[i][j-1] + costo_ins(s2[j-1]);
            int costo3 = dp[i-1][j-1] + costo_sub(s1[i-1],s2[j-1]);
            int costo4 = pow(2,31)-1;
            if (i>1 && j>1 && s1[i-1]==s2[j-2] && s1[i-2]==s2[j-1]){
                costo4 = dp[i-2][j-2] + costo_trans(s1[i-1],s1[i-2]);
            }
            dp[i][j] = min({costo1,costo2,costo3,costo4});
        }
    }
    return dp[n][m];
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