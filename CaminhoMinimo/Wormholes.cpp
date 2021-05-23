#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>

using namespace std;

struct edge{
    int u, w, t;
};

bool bellman(vector<edge> &g, int v, int e, vector<int> &d){
    
    for(int i = 0; i < v; i ++){
        for(int j = 0; j < e; j ++){
            if(d[g[j].u] > d[g[j].w] + g[j].t){
                d[g[j].u] = d[g[j].w] + g[j].t;
            }
        }
    }
    for(int j = 0; j < e; j ++){
        if(d[g[j].u] > d[g[j].w] + g[j].t) return true;
    }
    return false;
}

void solve(){
    int v, e;

    cin >> v >> e;

    vector<int> d(v,0);
    vector<edge> a(e);

    int u, w, t;
    for(int i = 0; i < e; i ++){
        cin >> a[i].u >> a[i].w >> a[i].t;
    }

    if(bellman(a,v,e,d)) cout << "possible" << endl;
    else cout << "not possible" << endl;
}

int main(){
    int n;

    cin >> n;
    
    for(int i = 0; i < n; i ++) solve();

    return 0;
}