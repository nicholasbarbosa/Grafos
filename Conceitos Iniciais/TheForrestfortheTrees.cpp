#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <ctype.h>

using namespace std;

void le(int &arvores, int &isolados){
    isolados = 0; arvores = 0;
    string arestas, aux, vertice;
    
    int ne = 0;//numero de arestas
    map<char,int> graus;//graus de cada vertice
    
    while(cin >> aux){
        if(aux[0] == '*') break;
        arestas += aux;
        ne ++;

        graus[aux[1]] ++;   //incrementa o grau de cada vertice
        graus[aux[3]] ++;
    }

    cin >> vertice;

    set<char> nv(vertice.begin(),vertice.end());

    nv.erase(',');
  
    for(auto a : nv) if(graus[a] == 0) isolados ++; //se o grau for zero, é isolado

    //sabemos que E = V - K, onde K representa o número de arvores, sendo assim:
    arvores = (nv.size() - ne) - isolados;
    
}
int main(){
    int n;
    cin >> n;
    int arvores, isolados;
    for(int i = 0; i < n ; i ++){
        le(arvores,isolados);
        cout << "There are " << arvores <<" tree(s) and " << isolados << " acorn(s).\n";
    }
    return 0;
}