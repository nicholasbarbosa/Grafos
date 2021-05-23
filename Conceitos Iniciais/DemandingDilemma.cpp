#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int t, n, m;
    
    cin >> t; 
    while (t > 0){
        t --;
        cin >> n >> m;

        vector<vector<int>> matriz(n,vector<int>(m));  //martiz de incidencia
        
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < m; j ++)
                cin >> matriz[i][j];
    
    
        //se uma aresta incide em mais de 2 vertices ou incide em apenas um vértice, é falso
        //se tiver arestas mustiplas é falso

        int verifica;   //soma os vertices incidentes às arestas
        bool valido = true; 

        //auxiliares para verificar arestas multiplas
        vector<int> aux(n); //auxiliar que vai guardar os dados da aresta
        map<vector<int>,int> arestas;   //adiciona as arestas no map

        for(int j = 0; j < m; j ++){
            verifica = 0;
            if(!valido) break;  //se n for válido, break

            for(int i = 0; i < n; i ++){
                if(matriz[i][j] == 1){
                    verifica ++;
                    if(verifica > 2) break; //se tiver mais de 2 vertices incidentes na aresta, é falso
                } 
                aux[i] = matriz[i][j];  //vetor que representa a aresta
            }
            if(verifica!=2){
                valido = false;
                break;
            }
            
            arestas[aux] ++;
            for(auto a : arestas) if(arestas[a.first] > 1) {valido = false; break;}
        }



        if(valido) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}