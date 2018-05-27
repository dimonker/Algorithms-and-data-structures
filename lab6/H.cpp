#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> color;
vector<int> parent;
int cycleStart = -1, cycleEnd;

bool dfs(int v, vector<vector<int>> &g){
    color[v] = 1;
    for (int i = 0; i < g[v].size(); i++){
        int next = g[v][i];
        if (color[next] == 0){
            parent[next] = v;
            if (dfs(next, g))
                return true;
        } else if (color[next] == 1){
            cycleEnd = v;
            cycleStart = next;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

int main() {
    ifstream fin("cycle.in");
    ofstream out("cycle.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> g;
    g.resize(n+1);
    color.assign(n+1, 0);
    parent.assign(n+1, 0);

    for(int i = 1; i <= m; i++){
        int a, b;
        fin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
        if(dfs(i, g))
            break;

    if (cycleStart == -1){
        out << "NO" << endl;
    } else{
        out << "YES" << endl;
        vector<int> cycle;
        cycle.push_back(cycleStart);
        for(int v = cycleEnd; v != cycleStart; v = parent[v]){
            cycle.push_back(v);
        }
        //cycle.push_back(cycleStart);
        reverse(cycle.begin(), cycle.end());
        out << cycle[0];
        for (int i = 1; i < cycle.size(); i++){
            out << " " << cycle[i];
        }
    }

    fin.close();
    out.close();
    return 0;
}