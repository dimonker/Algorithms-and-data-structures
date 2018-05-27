#include <iostream>
#include <fstream>
#include <vector>

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

void dfs(int v,
         vector<int> &d,
         vector<int> &visited,
         vector<vector<int>> &arr,
         vector<element> &priorityQueue)
{
    visited[v] = 1;

    for (int i = 0; i < arr[v].size(); i++){
        int currentV = arr[v][i];
        if (d[currentV] > d[v] + 1){
            d[currentV] = d[v] + 1;
            decreaseKey(priorityQueue, currentV, d[currentV]);
        }

    }

    int nextV = extractMin(priorityQueue);

    if (visited[nextV] == 0)
        dfs(nextV, d, visited, arr, priorityQueue);

}

int main() {
    fstream fin("pathbge1.in");
    ofstream out("pathbge1.out");

    int n, m;
    fin >> n >> m;

    vector<vector<int>> arr;
    vector<int> visited;
    vector<int> d;
    vector<element> priorityQueue;
    priorityQueue.resize(1000000);
    for (int i = 1; i <= n; i++){
        insert(priorityQueue, INT32_MAX, i);
    }


    arr.resize(n+1);
    visited.assign(n+1, 0);
    d.assign(n+1, INT32_MAX - 1);
    d[1] = 0;

    for (int i = 1; i <= m; i++){
        int a, b;
        fin >> a >> b;
        arr[a].push_back(b);
        arr[b].push_back(a);
    }

    dfs(1, d, visited, arr, priorityQueue);

    for (int i = 1; i <= n; i++)
        out << d[i] << " "  ;


    fin.close();
    out.close();
    return 0;
}