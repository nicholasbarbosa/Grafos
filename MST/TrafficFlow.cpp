#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct edge{
    int u = -1, v = -1;
    double peso = 0;
};

bool operator < (const edge &a,const edge &b) {
    return a.peso < b.peso;
}

bool operator > (const edge &a,const edge &b) {
    return a.peso > b.peso;
}

//Arrays a serem usados para na estrutura Union-Find
vector <int> raiz; //array de tamanho n, onde n é o número de vértices
vector <int> prox; //para fazer o encadeamento da lista
vector <int> size; //armazena o tamanho de cada lista

//=========================================================================
template <typename T>
void troca(T &a, T &b){
    T x = a;
    a = b;
    b = x;
}


void Make_Sets(int n){ //cria os n conjuntos
    for(int i = 0; i<n; i++){
        raiz[i] = i;
        prox[i] = i;
        size[i] = 1;
     }
}

int Find_Set(int i){
    return raiz[i];
}

void Union(int u, int v){
//A união é feita se u e v estão em conjuntos diferentes, ou seja se Find_Set(u) != Find_Set(v)

    int ru = raiz[u];
    int rv = raiz[v];
    if(size[ru] < size[rv] ){
        //lista de raiz rv recebe lista de raiz ru:
        size[rv] = size[rv] + size[ru];
        
        //altera a raiz dos elementos da lista de raiz ru:
        raiz[ru] = rv;
        for(int j = prox[ru]; j != ru; j=prox[j])
            raiz[j] = rv;
        
        troca(prox[ru], prox[rv]);
    }
    else{
        //lista de raiz ru recebe lista de raiz rv:
        size[ru] = size[ru] + size[rv];
        
        //altera a raiz dos elementos da lista de raiz rv:
        raiz[rv] = ru;
        for(int j = prox[rv]; j != rv; j = prox[j])
            raiz[j] = ru;
        troca(prox[ru], prox[rv]);
    }
}

void Kruskal(vector<edge> &arestas, vector<bool> &utilizadas,int nv,int ns){
    sort(arestas.rbegin(),arestas.rend());

    Make_Sets(nv);

    int resp = arestas[0].peso;

    for(int i = 0; i < arestas.size(); i ++){
        if(Find_Set(arestas[i].u) != Find_Set(arestas[i].v)){
            utilizadas[i] = true;
            Union(arestas[i].u,arestas[i].v);
            if(resp > arestas[i].peso) resp = arestas[i].peso;
        }
    }
    cout << resp << endl;
}

void solve(){
    int v, e;

    cin >> v >> e;

    raiz.resize(v);
    prox.resize(v);
    size.resize(v);

    vector<vector<int>> adj(v,vector<int>(v)); //Materiz de adj
    vector<edge> arestas; //Lista de arestas

    int w, u, p;

    for(int i = 0; i < e; i++){
        cin >> u >> w >> p;
        edge e;
        e.u = u;
        e.v = w;
        e.peso = p;
        arestas.push_back(e);
        adj[u][w] = p;
    }

    vector<bool> visit(arestas.size(),false);

    Kruskal(arestas, visit, v, e);
}

int main(){
    int n;

    cin >> n;

    for(int i = 0; i < n; i ++) {
        cout << "Case #" << i + 1 << ": ";
        solve();
    }

    return 0;
}