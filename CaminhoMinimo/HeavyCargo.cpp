#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

void floyd(vector<vector<int>> &g, int n){
    vector<vector<int>> D(n,vector<int>(n));
    int resp = g[0][0];

    for(int k = 0; k < n; k ++)
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++){
                if(g[i][k] != 0 && g[k][j] != 0) g[i][j] = max(g[i][j], min(g[i][k], g[k][j]));
            }
}

void solve(){
    int n, r;
    string a1, a2;
    int p;
    int s = 1;

    while(true) {
        cin >> n >> r;
    
        if(n == 0 && r == 0) return;
        else{
            map<string, int> city;
            vector<vector<int>> g(n,vector<int>(n,(0)));
            int index = 1;

            for(int i = 0; i < r; i ++){
                cin >> a1 >> a2 >> p;

                
                if(city[a1] == 0) {
                    city[a1] = index;
                    index ++;
                }
                if(city[a2] == 0) {
                    city[a2] = index;
                    index ++;
                }
                

                g[city[a1]-1][city[a2]-1] = p;
                g[city[a2]-1][city[a1]-1] = p;
            }
            string origem, dest;

            cin >> origem >> dest;
            floyd(g,n);

            cout << "Scenario #" << s << endl;
            cout << g[city[origem] - 1][city[dest] - 1] << " tons" << endl << endl;
            s++;

            
        }
    }
}

int main(){
    solve();

    return 0;
}