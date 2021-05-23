#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve(){
    int r, c;
    bool flag = false;
    cin >> r >> c;

    vector<string> campo(r);
    string linha;

    for(int i = 0; i < r; i ++){
        cin >> linha;
        campo[i] = linha;
    }

    for(int i = 0; i < r; i ++){
        for(int j = 0; j < c; j ++){
            if(campo[i][j] == 'S'){
                if(i + 1 < r && campo[i + 1][j] == '.') campo[i + 1][j] = 'D';
                if(i - 1 >= 0 && campo[i - 1][j] == '.') campo[i - 1][j] = 'D';
                if(j + 1 < c && campo[i][j + 1] == '.') campo[i][j + 1] = 'D';
                if(j - 1 >= 0 && campo[i][j - 1] == '.') campo[i][j - 1] = 'D';

                if(i + 1 < r && campo[i + 1][j] == 'W') flag = true;
                if(i - 1 >= 0 && campo[i - 1][j] == 'W') flag = true;
                if(j + 1 < c && campo[i][j + 1] == 'W') flag = true;
                if(j - 1 >= 0  && campo[i][j - 1] == 'W') flag = true;
            }
            if(flag){
                cout << "No\n";
                return;
            }
        }
    }

    cout << "Yes\n";
    for(auto a : campo) cout << a << "\n";
}

int main(){

    solve();

    return 0;
}