#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <array>
#include <algorithm>
#include <deque>
#include <set>
#include <map>

using namespace std;

//nao sigam este exemplo! Normalmente usamos esses defines apenas em competicoes de programacao para ganhar tempo!
#define f(i,k) for(int i=0;i<k;i++)

struct Sat2 {
public:
    //Cria o grafo de 2-Sat (inicialmente vazio) com numVariaveis variaveis (contamos a partir de 1)
    Sat2(int numVariaveis) {
        vars = numVariaveis;
        implica = vector<vector<vector<int>>> (numVariaveis+1, vector<vector<int>>(2));
        valor = vector<int>(numVariaveis+1,-1); 
    }
    //Adiciona uma clausula ao 2-Sat contendo as variaveis c1 e c2
    //As variaveis devem contar a partir de 1 !!!!
    //Adiciona a clausula: 
    //Se ambos v1 v2 true: (c1 OR c2)
    //Se v1 for false: (!c1 OR c2)
    //Se v2 for false: (c1 OR !c2)
    //Se ambos  false: (!c1 OR !c2)
    void addClausula(int c1,bool v1,int c2, bool v2) {
        
        implica[c1][!v1].push_back( c2*(v2?1:-1)  ); //-1 indica ~
        implica[c2][!v2].push_back( c1*(v1?1:-1) ); // ~c2 -> c1 (ou ~c2 -> ~c1 (<==> -c1) )
        
    }


    //No seu trabalho voce devera utilizar apenas a funcao "addImplicacao"
    //termine essa implementacao abaixo!
    //dica : a solucao sera MUITO simples . Apenas reaproveite a funcao addClausula e chame-a abaixo...
    //Adiciona uma implicacao do tipo (c1 --> c2)
    //se valor for false: (!c1 --> c2)
    //se valor2 for false: (c1 --> !c2)
    //se ambos false: (!c1 --> !c2)
    void addImplicacao(int c1, bool valor, int c2, bool valor2) {
        addClausula(c1, !valor, c2, valor2);
    }

    //retorna true iff a formula for satisfativel...
    bool satisfativel() {       
        for (int i = 1; i <= vars; ++i) {
           if ( !verificaVariavel(i) ) { //Se nao funciona com i = false e nem com i=true ==> nao funciona mesmo!
             return false;
           }
        }
        //se nenhuma variavel gera "conflitos" --> entao formula eh satisfativel...
        return true;
    }
private:
    vector<vector<vector<int>>> implica;    //grafo de implicacao... implica[x][0] = vertice da variavel x valendo false. implica[x][1] = vertice de x valendo true
                                            //em cada variavel temos a sua lista de adjacencia.
                                            //Se 4 esta em implica[2][0] , isso significa que !2 --> 4
                                            //Se -4 esta em implica[2][0], isso significa que !2 --> !4 (ou seja, numeros negativos indicam NOT)
    vector<int> valor;
    int vars;
    
    //verifica se funciona atribuir o valor val para a variavel x
    //o valor podera ser 0 (false) ou 1 (true)
    //-1 indica que ainda nao atribui um valor booleano para a variavel..
    bool funciona(int x, int val) {
        if (valor[x]!=-1) { //já atribuí valor...
                return valor[x] == val; //Para funcionar, o valor desejado deve ser o mesmo valor que foi atribuido a x...
        }
        valor[x] = val; //Para funcionar, x deverá valer: val
        
        f(i,implica[x][val].size()) 
             if (!funciona( abs(implica[x][val][i]), (implica[x][val][i]<0 ? 0:1) ) ) { //Se x->y, y nao deve implicar na variavel x valer ~val...
                 valor[x] = -1;
                 return false;
             }    
                                  
        return true; 
    }
      
    //Verifica se tudo esta ok com a variavel i no grafo de implicacao...
    //Se i nao puder ser true nem false --> nao esta ok --> retorna false
    bool verificaVariavel(int i) { 
        f(k,vars+1) valor[k]=-1;
        if ( funciona(i,0) ) return true; //Funciona com a variavel i = ~i ?
        f(k,vars+1) valor[k]=-1;
        if ( funciona(i,1) ) return true; //Funciona com a variavel i = i ?
        return false; 
    }    
};

int quadrante(int l1, int c1, int l2, int c2){

    if(l2 - l1 < 0 && c2 - c1 > 0) return 1;    //pra frente e pra cima
    if(l2 - l1 < 0 && c2 - c1 < 0) return 2;    //pra tras e pra cima
    if(l2 - l1 > 0 && c2 - c1 < 0) return 3;    //pra tras e pra baixo
    if(l2 - l1 > 0 && c2 - c1 > 0) return 4;    //pra frente e pra baixo

    if(c2 - c1 > 0 && l1 - l2 == 0) return 5;   //so andar pra frente
    if(c2 - c1 < 0 && l2 - l1 == 0) return 6;   //so andar pra tras
    if(c2 - c1 == 0 && l2 - l1 < 0) return 7;   //andar pra cima
    if(c2 - c1 == 0 && l2 - l1 > 0) return 8;   //andar pra baixo
    
    return -1;
}

void solve(){
    int s, a, m;

    cin >> s >> a >> m;

    Sat2 solver(m*10);
    vector<vector<bool>> g(s+1,vector<bool>(a+1));

    while(m > 0) {
        m --;
        int x1,y1,x2,y2;
        int quad;

        cin >> x1 >> y1 >> x2 >> y2;
        //cout << x1+a << " " << y1 << " " << x2+a << " " << y2 << endl;
        quad = quadrante(x1,y1,x2,y2);
        //cout << quad << endl;

        if(quad == 5) solver.addImplicacao(x1+a,false,x1+a,true);   //anda pra frente
        
        if(quad == 6) solver.addImplicacao(x1+a,true,x1+a,false);   //anda pra tras

        if(quad == 7) solver.addImplicacao(y1,true,y1,false);       //andra pra cima

        if(quad == 8) solver.addImplicacao(y1,false,y1,true);   //anda pra baixo
    
        if(quad == 1){
            solver.addImplicacao(y1,true,x1+a,true);
            solver.addImplicacao(y1,true,y2,false);
            solver.addImplicacao(x2+a,false,x1+a,true);
            solver.addImplicacao(x2+a,false,y2,false);
        }
        else if(quad == 2){
            solver.addImplicacao(x2+a,true,x1+a,false);
            solver.addImplicacao(x2+a,true,y2,false);
            solver.addImplicacao(y1,true,x1+a,false);
            solver.addImplicacao(y1,true,y2,false);
    
            solver.addImplicacao(y2,true,y1,false);
            solver.addImplicacao(y2,true,x2+a,false);
            solver.addImplicacao(x1+a,true,y1,false);
            solver.addImplicacao(x1+a,true,x2+a,false);
        }
        else if(quad == 3){
            solver.addImplicacao(x2+a,true,x1+a,false);
            solver.addImplicacao(x2+a,true,y2,true);
            solver.addImplicacao(y1,false,x1+a,false);
            solver.addImplicacao(y1,false,y2,true);
        }
        else if(quad == 4){
           solver.addImplicacao(x2+a,false,x1+a,true);
           solver.addImplicacao(x2+a,false,y2,true);
           solver.addImplicacao(y1,false,x1+a,true);
           solver.addImplicacao(y1,false,y2,true);


            solver.addImplicacao(x1+a,false,x2+a,true);
            solver.addImplicacao(x1+a,false,y1,true);
            solver.addImplicacao(y2,false,x2+a,true);
            solver.addImplicacao(y2,false,y1,true);
       }
    }

    cout << (solver.satisfativel()?"Yes":"No") << endl;
    
}

int main() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i ++) solve();

    return 0;
}