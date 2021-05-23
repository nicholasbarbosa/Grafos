#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct node{
    int i;
    double x, y;
};

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

double p(double x){
    return x*x;
}

double dist(double x1, double y1, double x2, double y2){
    return sqrt(p(x2-x1) + p(y2-y1));
}

void Kruskal(vector<edge> &arestas, vector<bool> &utilizadas,int nv,int ns){
    sort(arestas.begin(), arestas.end());

    double resp = 0;

    Make_Sets(nv);

   for(int i = 0; i < arestas.size(); i ++){
       if(Find_Set(arestas[i].u) != Find_Set(arestas[i].v)){
           utilizadas[i] = true;
           Union(arestas[i].u,arestas[i].v);
           resp += arestas[i].peso;
       }
    }

    cout << fixed << setprecision(2) << resp << "\n";
}

void solve(){
    int n;
    double x, y;
    int indice = 0;
   
    cin >> n;
    
    vector<node> vertices;
    vector<edge> arestas;
    node aux;
    
    for(int i = 0; i < n; i ++){
        cin >> x >> y;
        aux.x = x; aux.y = y; aux.i = indice;
        indice ++;
        vertices.push_back(aux);
    }
    raiz.resize(n);
    prox.resize(n);
    size.resize(n);
    edge e;

    for(auto v : vertices){
        for(auto u : vertices){
            if(u.i != v.i){
                e.u = u.i; e.v = v.i;
                e.peso = dist(v.x, v.y, u.x, u.y);
                arestas.push_back(e);
            }
        }
    }
    vector<bool> Autilizadas(arestas.size(),false);

    Kruskal(arestas, Autilizadas, n, (n*n-1)/2);
}

int main(){
    int n;

    cin >> n;

    for(int i = 0; i < n; i ++) {
        if(i > 0) cout << "\n";
        solve();
    }
}