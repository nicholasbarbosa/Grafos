#include <iostream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;
//o tamanho da maior arovore.

int depth(int no, map<int,vector<int>> grafo){
	if(grafo[no].size() == 0){  //se for folha, retorna
        return 1;
	}

	int depth_son = 0;
	
    for(int i = 0; i < grafo[no].size(); i++){  //profundidade dos filhos
		depth_son = max(depth_son,depth(grafo[no][i],grafo));
	}

	return 1 + depth_son; //retorna a profundidade + 1, que sao os grupos
}

int main(){
    map<int,vector<int>> grupos;
    vector<int> raiz;
    int n, aux, cont = 0;

    cin >> n;

    while(n > 0){
        n --;
        
        cin >> aux;

        if(aux != -1) grupos[aux - 1].push_back(cont);  //a entrada é o pai do nó 
        else raiz.push_back(cont);   
        
        cont ++;
    }

    int depth_raiz = 0;
  
    for(int i = 0; i < raiz.size(); i ++) 
        depth_raiz = max(depth_raiz,depth(raiz[i],grupos));  //compara a prfundidade de cada arvore

    cout << depth_raiz << endl;

    return 0;
}

