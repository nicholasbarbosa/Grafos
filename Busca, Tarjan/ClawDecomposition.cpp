#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

bool ehbipartido(vector<vector<int>> &g,vector<int> &nos, int v, int grupo){
    if(nos[v] == -1) nos[v] = grupo;
    bool resp = true;
    int tam = g[v].size();
    if(tam != 3) return false;
    for(int i = 0; i < tam; i ++){
        if(nos[g[v][i]] == -1){
            if(grupo == 0) resp = ehbipartido(g,nos,g[v][i],1);
            else  resp = ehbipartido(g,nos,g[v][i],0);
        }
        else if(nos[g[v][i]] == nos[v]) resp = false;
    } 
    return resp;
}

void solve(){
    int aux;

    while(cin >> aux){
        if(aux == 0) break;
        else{
            int v, u;
            vector<vector<int>> g(aux);
            vector<int> nos(aux);
            bool bipartido = true;

            while(true){
                cin >> v >> u;
                if(v == 0 && u == 0) break;

                g[v-1].push_back(u-1);
                g[u-1].push_back(v-1);
                nos[u-1] = -1;
                nos[v-1] = -1;
                
            }

            for(int i = 0; i < aux; i ++) {
                if(!ehbipartido(g,nos,i,0)) {cout << "NO\n"; bipartido = false; break;}
            }
            if(bipartido) cout << "YES\n";
        }
    }
}

int main(){
    solve();
    return 0;
}