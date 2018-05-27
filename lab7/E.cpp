#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


int main(){
    ifstream fin("negcycle.in");
    ofstream out("negcycle.out");

    unsigned int n;
    fin >> n;
    vector<vector<pair<int, int>>> g(n);
    int x;
    const int INF = 1000000000;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            fin >> x;
            if (x == INF)
                continue;
            g[i].emplace_back(j, x);
    }

    vector<int> parent(n, -1);
    vector<int64_t> distance(n, INT32_MAX);

    distance[0] = 0;
    int neg = -1;
    for (int ni = 0; ni < n; ni++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < g[i].size(); j++){
                int to = g[i][j].first;
                int weight = g[i][j].second;
                if (distance[to] > distance[i] + weight) {
                    if (ni == n - 1)
                        neg = to;
                    distance[to] = distance[i] + weight;
                    parent[to] = i;
                }
            }

    if (neg == -1)
        out << "NO" << endl;
    else{
        for (int i = 0; i < n; i++)
            neg = parent[neg];
        int current = neg;
        vector<int> negCycle;
        while (current != parent[neg] || negCycle.size() <= 1){
            negCycle.push_back(current);
            current = parent[current];
        }
        out << "YES" << endl;
        out << negCycle.size() << endl;
        for (int i = negCycle.size() - 1; i >= 0; i--)
            out << negCycle[i] + 1 << " ";
        out << endl;
    }

    fin.close();
    out.close();
    return 0;
}