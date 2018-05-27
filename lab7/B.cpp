#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int size = 0;

struct dis{
    int v;
    long long d;
    dis(int v, int d):v(v),d(d){}
};

struct element{
    long long d;
    int vertex;
    element(){}
    element(long long x, int order):d(x), vertex(order){};

    element& operator = (const element& other){
        if (this == &other)
            return *this;
        d = other.d;
        vertex = other.vertex;
        return *this;
    }
};

vector<int> vertexInQueue;

void siftUp(vector<element> &arr, int i){
    element tmp = arr[i];
    int parent = i/2;
    while((parent > 0) && (arr[parent].d > tmp.d)){
        arr[i] = arr[parent];
        vertexInQueue[arr[i].vertex] = i;
        i = parent;
        parent /= 2;
    }
    arr[i] = tmp;
    vertexInQueue[arr[i].vertex] = i;
}

void siftDown(vector<element> &arr, int i){
    element tmp = arr[i];
    while (2*i <= size){
        int j = i * 2;
        if((j+1 <= size) && (arr[j].d > arr[j+1].d))
            j++;
        if(tmp.d < arr[j].d)
            break;
        else{
            arr[i] = arr[j];
            vertexInQueue[arr[i].vertex] = i;
            i = j;
        }
    }
    arr[i] = tmp;
    vertexInQueue[arr[i].vertex] = i;
}

void insert(vector<element>& priorityQueue, long long d, int vertex){
    size++;
    priorityQueue[size] = element(d, vertex);
    siftUp(priorityQueue, size);
}

int find(vector<element>& priorityQueue, int vertex){
    return vertexInQueue[vertex];
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

void decreaseKey(vector<element>& priorityQueue, int vertex, long long d){
    int pos = find(priorityQueue, vertex);
    priorityQueue[pos].d = d;
    siftUp(priorityQueue, pos);
}

void dfs(int v,
         vector<long long> &d,
         vector<int> &visited,
         vector<vector<dis>> &arr,
         vector<element> &priorityQueue)
{
    visited[v] = 1;

    for (int i = 0; i < arr[v].size(); i++){
        int currentV = arr[v][i].v;
        long long currentD = arr[v][i].d;
        if (d[currentV] > d[v] + currentD){
            d[currentV] = d[v] + currentD;
            decreaseKey(priorityQueue, currentV, d[currentV]);
        }

    }

    int nextV = extractMin(priorityQueue);

    if (visited[nextV] == 0)
        dfs(nextV, d, visited, arr, priorityQueue);

}

int main() {
    fstream fin("pathsg.in");
    ofstream out("pathsg.out");

    int n, m;
    fin >> n >> m;



    vector<vector<dis>> arr;
    vector<int> visited;
    vector<long long> d;
    vector<element> priorityQueue;
    priorityQueue.resize(2001);
    vertexInQueue.resize(n+1);
    arr.resize(n+1);


    vector<vector<long long>> distance;
    distance.resize(n+1);
    for (int i = 1; i <= n; i++){
        distance[i].assign(n+1, INT64_MAX);
    }
    d.assign(n+1, INT64_MAX);

    for (int i = 1; i <= m; i++){
        int a, b, weight;
        fin >> a >> b >> weight;
        arr[a].push_back(dis(b, weight));
    }



    for (int i = 1; i <= n; i++){
        visited.assign(n+1, 0);
        for (int j = 1; j <= n; j++){
            insert(priorityQueue, INT64_MAX, j);
            vertexInQueue[j] = j;
        }
        distance[i][i] = 0;
        dfs(i, distance[i], visited, arr, priorityQueue);
        visited.clear();
    }


    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            out << distance[i][j] << " ";
        }
        out << endl;
    }


    fin.close();
    out.close();
    return 0;
}