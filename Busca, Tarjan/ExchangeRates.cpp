#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct cambio{
    int item2;
    int v1, v2;
};

int mdc(int m, int n){
    int r;
    if(n > m) swap(m,n);
    if(n == 0 && m == 0) return 1;
    while (n != 0){
        r = m%n;
        m = n;
        n = r;
    }

    return m;    
}

void dfs(vector<vector<cambio>> &g, int item1, int item2, pair<int,int> &aux, vector<bool> visit, bool &chegou){
    if(item1 == item2) {
        chegou = true;
        return;
    }
    
    if(visit[item1]) return;

    if(g[item1].size() == 0) {
        return;
    }

    visit[item1] = true;

    for(int i = 0; i < g[item1].size(); i ++){
        if(chegou) return;
        if(!visit[g[item1][i].item2]){    //se o proximo n tem filhos e nao é oq a gente quer, nao faz nada

            aux.first *= g[item1][i].v1;
            aux.second *= g[item1][i].v2;

            dfs(g,g[item1][i].item2,item2,aux,visit,chegou);
            
            if(!chegou){
                aux.first /= g[item1][i].v1;
                aux.second /= g[item1][i].v2;
            }
        }
    }
}

void solve(){
    vector<vector<cambio>> g(60);
    map<string,int> indice;
    int i = 0;
    queue<pair<string,string>> tc;
    
    char aux;
    string item1, item2;

    double v1, v2;
    vector<bool> visit(60);
    
    while (true){
        cin >> aux;
        if(aux == '.') break;
        if(aux == '!'){
            cambio item;

            cin >> v1 >> item1 >> aux >> v2 >> item2;

            if(indice.find(item1) == indice.end()) {indice[item1] = i; i ++;}

            if(indice.find(item2) == indice.end()) {indice[item2] = i; i ++;}

            item.item2 = indice[item2];
            item.v1 = v1; item.v2 = v2;

            g[indice[item1]].push_back(item);

            item.item2 = indice[item1];
            item.v1 = v2; item.v2 = v1;

            g[indice[item2]].push_back(item);

            visit[indice[item1]] = false;
            visit[indice[item2]] = false;
        }
        if(aux == '?'){
            bool flag = false;
            cin >> item1 >> aux >> item2;
            
            pair<int,int> resp = make_pair(1,1);    
            
            dfs(g,indice[item1],indice[item2],resp,visit, flag);
  
            int m = mdc(resp.first,resp.second);
        
            if(flag) cout << resp.first/m << " " << item1 <<" = "<< resp.second/m << " " << item2 << endl;
            else cout << "? " << item1 << " = ? " << item2 << endl;
        }
    }
}

int main(){
    solve();
    return 0;
}