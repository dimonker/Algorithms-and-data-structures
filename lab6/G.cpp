#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> color;
vector<int> answer;
bool flag = false;

void dfs (int v, vector<vector<int>> &g) {
    color[v] = 1;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (color[to] == 0)
            dfs (to, g);
        if (color[to] == 1){
            flag = true;
            return;
        }
    }
    color[v] = 2;
    answer.push_back (v);
}

void topological_sort(vector<vector<int>> &g) {
    for (int i = 1; i < g.size(); i++)
        color[i] = false;
    answer.clear();
    for (int i = 1; i < g.size(); i++)
        if (color[i] == 0)
            dfs (i, g);
    reverse(answer.begin(), answer.end());
}

int main() {
    ifstream fin("topsort.in");
    ofstream out("topsort.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> arr;
    arr.resize(n+1);
    color.resize(n+1);

    for(int i = 1; i <= m; i++){
        int a, b;
        fin >> a >> b;
        arr[a].push_back(b);
    }

    topological_sort(arr);

    if (flag){
        out << "-1" << endl;
    } else{
        for (int i = 0; i < n; i++){
            out << answer[i] << " ";
        }
    }


    fin.close();
    out.close();
    return 0;
}