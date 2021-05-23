#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct no{  //struct q guarda a posição e o tempo
    int i, j;
    int tempo;
    char tipo;
};

bool anda(vector<string> &g, int x, int y, int r, int c, vector<vector<int>> &visit){
    if(x < 0 || y < 0 || x >= r || y >= c) {
		return false;
	}
	if(g[x][y] == '#' || g[x][y] == 'F' || g[x][y] == 'S') {
		return false;
	}
	return true;
}

bool andajoe(vector<string> &g, int x, int y, int r, int c, vector<vector<int>> &visit){
    if(x < 0 || y < 0 || x > r-1 || y > c-1) {
		return false;
	}
	if(g[x][y] == '#' || g[x][y] == 'J' || g[x][y] == 'F') {
		return false;
	}
	return true;
}

void bfs(vector<string> &g, queue<no> &elem, vector<vector<int>> &tf, int &flag, int &ans){
    no atual, prox; //um no que representa o primeiro elemento da fila no estado atual e os possiveis proximos passos
    int ax, ay;

    int nx[4] = {1,0,-1,0}; //representa o deslocamento
    int ny[4] = {0,1,0,-1};

    while(!elem.empty()){
        atual = elem.front();
        elem.pop();

        if(atual.tipo == 'F'){  //se o primeiro elemento da fila for fogo
            for(int i = 0; i < 4; i ++){
                ax = atual.i + nx[i]; ay = atual.j + ny[i];

                if(anda(g,ax,ay,g.size(),g[0].size(),tf)){  //se o fogo pode andar
                    g[ax][ay] = atual.tipo; //altera no mapa do labirinto
                    
                    prox.i = ax;
                    prox.j = ay;
                    prox.tipo = atual.tipo;
                    prox.tempo = atual.tempo + 1;
                    tf[ax][ay] = prox.tempo;    //guarda o estado do 'novo' fogo
                    
                    elem.push(prox);    //push no proximo elemento
                }
            }
        }

        if(atual.tipo == 'J' ){ //se o primeiro elemento ad fila for fogo
            if(g[atual.i][atual.j] == 'F' && atual.tempo>=tf[atual.i][atual.j]) continue;   //se a posição atual for um fogo, mas ele tiver tempo maior que o do joe
                                                                                            //quer dizer q o joe ainda pode andar e ele ainad n foi pego
            if(atual.i == 0||atual.j == 0||atual.i == g.size()-1 ||atual.j == g[0].size()-1){   //se o joe chega na saida, retorna
                flag=1;
                ans=atual.tempo;
                return;
            }

            for(int i = 0; i < 4; i ++){
                ax = atual.i + nx[i]; ay = atual.j + ny[i];
                
                if(andajoe(g,ax,ay,g.size(),g[0].size(),tf)){   //ve se o joe pode andar
                    g[ax][ay] = atual.tipo;


                    prox.i = ax;
                    prox.j = ay;
                    prox.tipo = atual.tipo;
                    prox.tempo = atual.tempo + 1;

                    elem.push(prox);    //adiciona a prox pos do joe na fila
                }
            }
        }  
    }

    return;
}

void solve(){
    int r, c;   //numero de linhas e colunas
    string aux; //auxiliar para ler a matriz

    cin >> r >> c;

    vector<string> map(r+2);    //matriz q representa o labirinto
    string extra;   //vou adicionar 2 linhas e duas colunas para representar a saida do lab

    for(int i = 0; i < c+2; i ++) extra += "S";

    vector<vector<int>> tf(r+2,vector<int>(c+2,-1));    //estado dos fogos

    map[0] = extra;
    for(int i = 1; i < r+1; i ++){    //le a entrada
        cin >> aux;
        map[i] = "S" + aux + "S";
    }
    map[r+1] = extra;   //agr o labirinto original esta certado por linhas de "S" que representam a saida


    pair<int,int> joe;  //pos do jo
    queue<no> elem; //fila que guarda as pos do fogo e do joe
    
    no atual;


    for(int i = 0; i < r+1; i ++)
        for(int j = 0; j < c+1; j ++){
            if(map[i][j] == 'F'){   //seta a posição do fogo no tempo 0
                atual.i = i;
                atual.j = j;
                atual.tempo = 0;
                atual.tipo = 'F';
                tf[i][j] = 0;

                elem.push(atual);
            }

            if(map[i][j] == 'J') {
                atual.i = i;
                atual.j = j;
                atual.tempo = 0;
                atual.tipo = 'J';

                elem.push(atual);
            }
        }

    int flag = 0, ans = 0;
    bfs(map,elem,tf,flag,ans);   //bfs

    if(flag) cout << ans << endl;
	else cout << "IMPOSSIBLE" << endl;
}

int main(){
    int n;
    cin >> n;

    for(int i = 0; i < n; i ++)
        solve();

    return 0;
}