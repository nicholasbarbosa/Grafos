#include <iostream>  
#include <queue>  
#include <cstdio>  
#include <cstring>  
#include <string>  
#include <string.h>  
#include <algorithm>  
#include <cassert>  
#include <cmath>  
#include <set>  
#include <map>

using namespace std; 
/*
2 3 1 -> 3 2 1
4 5 6
7 8 9
7 3 9
2 5 1
4 8 6
1 2 3
4 5 6
7 9 8
0
*/ 
map<string,string> resp;

string H(string g, int l){
    swap(g[0 + l*3],g[2 + l*3]);
    swap(g[0 + l*3],g[1 + l*3]);

    return g;
}

string V(string g, int c){
    swap(g[c],g[6 + c]);
    swap(g[c + 3],g[6 + c]);

    return g;
}

void bfs(){
    queue<string> q;
    q.push("123456789");

    while(!q.empty()){

        string aux = q.front();
        q.pop();

        string next = "";

        next = V(aux,0);
        if(resp[next] == "" && next!="123456789"){
            q.push(next);
 
            resp[next] = resp[aux]; 
            resp[next] = "V1" + resp[next];
        }

        next = V(aux,1);
        if(resp[next] == "" && next!="123456789"){
            q.push(next);

            resp[next] = resp[aux]; 
            resp[next] = "V2" + resp[next];
        }

        next = V(aux,2);
        if(resp[next] == "" && next!="123456789"){
            q.push(next);

            resp[next] = resp[aux]; 
            resp[next] = "V3"+ resp[next];
        }
//////////////////////////////////////////////////////////////// horizontal
        next = H(aux,0);
        if(resp[next] == "" && next!="123456789"){
            q.push(next);

            resp[next] = resp[aux]; 
            resp[next] = "H1"+ resp[next];
        }
        
        next = H(aux,1);
        if(resp[next] == "" && next!="123456789"){
            q.push(next);

            resp[next] = resp[aux]; 
            resp[next] = "H2"+ resp[next];
        }

        next = H(aux,2);
        if(resp[next] == "" && next!="123456789"){
            q.push(next);

            resp[next] = resp[aux]; 
            resp[next] = "H3"+ resp[next];
        }
    }
}

bool solve(){
    char t1, t2 , t3;
    string g = "";
    map<string,int> t;
    int b;

    for(int i = 0; i < 3; i ++) {
        cin >> t1;

        if(t1 == '0') return false;

        cin >> t2 >> t3;

        g.push_back(t1);
        g.push_back(t2);
        g.push_back(t3);
    }

    string next;
    
    if(next == "123456789") cout << "aa" << endl;

    bfs();
    
    if(resp[g] != "") {
        cout << resp[g].size()/2 << " " << resp[g] << "\n";
    }
    else if(g == "123456789") cout << 0 << " \n";
    else cout << "Not solvable" << "\n";

    return true;
}

int main(){
    bool flag = true;
    while (flag){
        flag = solve();
    }
}