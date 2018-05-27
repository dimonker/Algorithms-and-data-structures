#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void dfs(int v, int component, vector<int> &visited, vector<vector<int> >& arr) {
    visited[v] = component;

    for (int i = 0; i < arr[v].size(); i++) {
        int nextV = arr[v][i];
        if (visited[nextV] == -1) {
            dfs(nextV, component, visited, arr);
        }
    }
}

int main() {
    ifstream fin("components.in");
    ofstream out("components.out");

    int components = 0;
    int a, b;
    int n, m;

    fin >> n >> m;

    vector<vector<int> > arr(n);
    vector<int> visited(n);

    for (int i = 0; i < n; i++)
      visited[i] = -1;

    for (int i = 0; i < m; i++) {
        fin >> a >> b;
        arr[a - 1].push_back(b - 1);
        arr[b - 1].push_back(a - 1);
    }

    for (int i = 0; i < n; i++)
        if (visited[i] == -1) {
            components++;
            dfs(i, components, visited, arr);
        }

    out << components << endl;
    for (int i = 0; i < n; i++)
        out << visited[i] << " ";
    return 0;
}