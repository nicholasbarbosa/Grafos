/**
 *   //////////////////
 *   // MAXIMUM FLOW //
 *   //////////////////
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/****************
 * Maximum flow * (Ford-Fulkerson on an adjacency matrix)
 ****************
 * Takes a weighted directed graph of edge capacities as an adjacency 
 * matrix 'cap' and returns the maximum flow from s to t.
 *
 * PARAMETERS:
 *      - cap (global): adjacency matrix where cap[u][v] is the capacity
 *          of the edge u->v. cap[u][v] is 0 for non-existent edges.
 *      - n: the number of vertices ([0, n-1] are considered as vertices).
 *      - s: source vertex.
 *      - t: sink.
 * RETURNS:
 *      - the flow
 *      - fnet contains the flow network. Careful: both fnet[u][v] and
 *          fnet[v][u] could be positive. Take the difference.
 *      - prevv contains the minimum cut. If prevv[v] == -1, then v is not
 *          reachable from s; otherwise, it is reachable.
 * DETAILS:
 * FIELD TESTING:
 *      - Valladolid 10330: Power Transmission
 *      - Valladolid 653:   Crimewave
 *      - Valladolid 753:   A Plug for UNIX
 *      - Valladolid 10511: Councilling
 *      - Valladolid 820:   Internet Bandwidth
 *      - Valladolid 10779: Collector's Problem
 * #include <string.h>
 * #include <queue>
 **/

#include <string.h>
#include <string>
#include <ostream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// adjacency matrix (fill this up)
int cap[38][38];

// flow network
int fnet[38][38];

// BFS
int q[38], qf, qb, prevv[38];

int min(int x, int y){
    if(x < y) return x;
    return y;
}

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );

    int flow = 0;

    while( true )
    {
        // find an augmenting path
        memset( prevv, -1, sizeof( prevv ) );
        qf = qb = 0;
        prevv[q[qb++] = s] = -2;
        while( qb > qf && prevv[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( prevv[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    prevv[q[qb++] = v] = u;

        // see if we're done
        if( prevv[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = prevv[v]; u >= 0; v = u, u = prevv[v] )
            bot = min(cap[u][v] - fnet[u][v] + fnet[v][u],bot);

        // update the flow network
        for( int v = t, u = prevv[v]; u >= 0; v = u, u = prevv[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
}

bool solve(){
    char l;
    string s;
    int f = 0;
    map <int,char> converte;

    while (getline(cin, s)){
        if(s == "") break;
        cap[0][s[0] - 'A' + 1] = s[1] - '0';    //fluxo da fonte ao app

        converte[s[0] - 'A' + 1] = s[0];
       
        f += s[1] - '0';

        for(int i = 3; i < s.size() - 1; i ++) //fluxo do app ao pc
            cap[s[0] - 'A' + 1][s[i] - '0' + 27] = 1;
        

        for(int i = 3; i < s.size() - 1; i ++)   //fluxo do pc ao destin
            cap[s[i] - '0' + 27][37] = 1;
    }
    
    string resp = "__________";
    
    int flow = fordFulkerson(38,0,37);

    for(int i = 0; i < 38; i ++){
        for(int j = 0; j < 38; j ++)
            if(fnet[i][j] > 0 && fnet[j][i] > 0) {
                fnet[i][j] = fnet[i][j] - fnet[j][i];   
                fnet[j][i] = fnet[i][j] - fnet[j][i];
            }
    }

    if(f != flow) cout << "!" << endl;
    else{
        for(int i = 1; i < 27; i ++){
            for(int j = 27; j < 37; j ++){
                if(fnet[i][j] == 1 ) resp[j-27] = converte[i];
            }
        }
       
        if(resp == "__________") return false;
        cout << resp << endl;
    }
    return true;
}

//----------------- EXAMPLE USAGE -----------------
int main() {
    memset( cap, 0, sizeof( cap ) );

    while (true) {
        memset( cap, 0, sizeof( cap ) );
        if(!solve()) break;
    }
    
    return 0;
}