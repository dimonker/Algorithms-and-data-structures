#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const __int128 INF = numeric_limits<__int128>::max();

int main() {
    ifstream fin("path.in");
    ofstream out("path.out");
    unsigned int n, m, s, u, v;
    int64_t weight;
    fin >> n >> m >> s;
    vector<vector<pair<unsigned int, int64_t>>> g(n);
    vector<__int128> distance(n, INF);
    vector<bool> visited(n, false);
    vector<bool> minDistance(n, true);

    for (unsigned int i = 0; i < m; ++i) {
        fin >> u >> v >> weight;
        g[u - 1].emplace_back(v - 1, weight);
    }


    distance[s - 1] = 0;
    visited[s - 1] = true;
    queue<unsigned int> q;

    for (int n = 0; n < g.size(); n++) {
        for (int i = 0; i < g.size(); i++) {
            for (size_t j = 0; j < g[i].size(); j++) {
                unsigned int to = g[i][j].first;
                int64_t weight = g[i][j].second;

                if (distance[i] != INF && distance[to] > distance[i] + weight) {
                    if (n == g.size() - 1)
                        q.push(to);
                    distance[to] = distance[i] + weight;
                    visited[to] = true;
                }
            }
        }
    }


    vector<bool> usedInNegativeCycle(g.size(), false);
    while (!q.empty()) {
        unsigned int u = q.front();
        q.pop();
        usedInNegativeCycle[u] = true;
        minDistance[u] = false;

        for (int i = 0; i < g[u].size(); i++) {
            unsigned int v = g[u][i].first;
            if (!usedInNegativeCycle[v])
                q.push(v);
        }
    }

    for (int i = 0; i < g.size(); i++) {
        if (!visited[i])
            out << "*" << endl;
        else if (!minDistance[i])
            out << "-" << endl;
        else
            out << static_cast<int64_t>(distance[i]) << endl;
    }

    fin.close();
    out.close();
    return 0;
}