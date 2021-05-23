#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <ctype.h>

using namespace std;

int dfs(map<int,vector<int>> g, int no, vector<bool> visit, int &resp){
    visit[no] = true;
    int no_pai = 1;

    for (int i = 0; i < g[no].size(); i++){
        if (!visit[g[no][i]]){

            int no_filho = dfs(g, g[no][i], visit, resp);
 
            if (no_filho % 2 == 0)
                resp++;
 
            else
                no_pai += no_filho;
        }
    }
 
    return no_pai;
}


int main(){
    int nv, ne;
    cin >> nv >> ne;
    map<int,vector<int>> g;

    int v, u;

    for(int i = 0; i < ne; i ++){
        cin >> v >> u;
        g[v-1].push_back(u-1);
        g[u-1].push_back(v-1);
    }

    int resp = 0;
    vector<bool> visit(nv);

    for(auto a : visit) a = false;

    dfs(g,0,visit,resp);

    cout << resp << endl;
    
    return 0;
}
