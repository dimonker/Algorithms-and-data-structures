#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int size = 0;

struct element{
    int d;
    int vertex;
    element(){}
    element(int x, int order):d(x), vertex(order){};

    element& operator = (const element& other){
        if (this == &other)
            return *this;
        d = other.d;
        vertex = other.vertex;
        return *this;
    }
};

void siftUp(vector<element> &arr, int i){
    element tmp = arr[i];
    int parent = i/2;
    while((parent > 0) && (arr[parent].d >= tmp.d)){
        if (arr[parent].d == tmp.d && arr[parent].vertex < tmp.vertex)
            break;
        arr[i] = arr[parent];
        i = parent;
        parent /= 2;
    }
    arr[i] = tmp;
}

void siftDown(vector<element> &arr, int i){
    element tmp = arr[i];
    while (2*i <= size){
        int j = i * 2;
        if((j+1 <= size) && (arr[j].d > arr[j+1].d))
            j++;
        if ((j+1 <= size) && arr[j].d == arr[j+1].d && arr[j].vertex > arr[j+1].vertex)
            j++;
        if(tmp.d < arr[j].d)
            break;
        if (tmp.d == arr[j].d && tmp.vertex < arr[j].vertex)
            break;
        else{
            arr[i] = arr[j];
            i = j;
        }
    }
    arr[i] = tmp;
}

void insert(vector<element>& priorityQueue, int d, int vertex){
    size++;
    priorityQueue[size] = element(d, vertex);
    siftUp(priorityQueue, size);
}

int find(vector<element>& priorityQueue, int vertex){
    for (int i = 1; i <= size; i++){
        if (priorityQueue[i].vertex == vertex)
            return i;
    }
}

void swap(element &a, element &b){
    element tmp = a;
    a = b;
    b = tmp;
}

int extractMin(vector<element>& priorityQueue){
    int min = priorityQueue[1].vertex;
    //cout << min << " " << priorityQueue[1].vertex << endl;
    int last = size;
    swap(priorityQueue[1], priorityQueue[last]);
    size--;
    siftDown(priorityQueue, 1);
    return min;
}

void decreaseKey(vector<element>& priorityQueue, int vertex, int d){
    int pos = find(priorityQueue, vertex);
    priorityQueue[pos].d = d;
    siftUp(priorityQueue, pos);
}


void dfs(int v, vector<int> &d, vector<int> &visited, vector<vector<int>> &arr,
         vector<element> &priorityQueue, vector<int> &p)
{
    visited[v] = 1;
    for (int i = 0; i < arr[v].size(); i++){
        int currentV = arr[v][i];
        if (d[currentV] > d[v] + 1){
            d[currentV] = d[v] + 1;
            decreaseKey(priorityQueue, currentV, d[currentV]);
            p[currentV] = v;
        }

    }
    int nextV = extractMin(priorityQueue);
    if (visited[nextV] == 0)
        dfs(nextV, d, visited, arr, priorityQueue, p);

}




int main() {
    fstream fin("input.txt");
    ofstream out("output.txt");

    int n, m;
    fin >> n >> m;

    vector<vector<int>> arr;
    vector<int> visited;
    vector<int> d;
    char state[n+1][m+1];

    vector<element> priorityQueue;
    priorityQueue.resize(1000000);
    for (int i = 1; i <= n * m; i++){
        insert(priorityQueue, INT32_MAX, i);
    }

    arr.resize(n * m + 1);
    visited.assign(n*m + 1, 0);
    d.assign(n*m + 1, INT32_MAX);


    int S, T;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            char x;
            fin >> x;
            state[i][j] = x;
            if (x != '#' && state[i][j - 1] != '#' && j - 1 != 0){
                int number = (i-1) * m + j;
                arr[number].push_back(number - 1);
                arr[number - 1].push_back(number);
            }
            if (x != '#' && state[i-1][j] != '#' && i - 1 != 0){
                int number = (i-1) * m + j;
                arr[number].push_back(number - m);
                arr[number - m].push_back(number);
            }
            if (x == 'S')
                S = (i-1) * m + j;
            if (x == 'T')
                T = (i-1) * m + j;

        }
    }

    d[S] = 0;//start
    vector<int> p;
    p.resize(n*m + 1);
    dfs(S, d, visited, arr, priorityQueue, p);

    if (d[T] == INT32_MAX)
        out << -1 << endl;
    else{
        out << d[T] << endl;
        vector<char> path;
        for (int v = T; v != S; v = p[v]){
            if (p[v] == v - 1)
                path.push_back('R');
            else if (p[v] == v - m)
                path.push_back('D');
            else if (p[v] == v + 1)
                path.push_back('L');
            else if (p[v] == v + m)
                path.push_back('U');
        }
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++)
            out << path[i];
    }

    fin.close();
    out.close();
    return 0;
}