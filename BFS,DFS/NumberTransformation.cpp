#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;

vector<set<int>> prim(1001);


struct val{
    int x;
    int step;
};

void f(int n){
    vector<int> resp;
    int div = 2;
    int num = n;

    while( n > 1 ){
        if(div > num) return;
        if(div == num) break;
        if(n % div == 0) {
            n /= div;
            prim[num].insert(div);
            
        }
        else div ++;      
    } 
}

void bfs(int s, int t){
    vector<bool> insertq(1001,false);
    queue<val> q;

    val cur, next;
    cur.step = 0; cur.x = s;

    q.push(cur);

    while(!q.empty()){
        cur = q.front();
        q.pop();

        if(cur.x == t) {
            cout << cur.step << endl;
            return;
        }
        
        if(prim[cur.x].size() == 0) f(cur.x);

        for(auto fator : prim[cur.x]){
            if(cur.x + fator == t){
                cout << cur.step + 1 << endl;
                return;
            }
            if(cur.x + fator > t){
                break;
            }
            if(!insertq[cur.x + fator]){
                next.x = cur.x + fator;
                next.step = cur.step + 1;
                q.push(next);
                insertq[next.x] = true;
            }
        }
    }
    

    cout << -1 << endl;

    return;
}


int main(){
    int n;
    cin >> n;

    int index = 0;
    
    while(index < n){
        cout << "Case " << index + 1 << ": "; 
        
        int s, t;
        cin >> s >> t;

        bfs(s,t);

        index ++;
    }

    return 0;
}