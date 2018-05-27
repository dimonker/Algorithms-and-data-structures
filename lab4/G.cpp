#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int size = 0;

struct element{
    int x;
    int order;
    element(){}
    element(int x, int order):x(x), order(order){};

    element& operator = (const element& other){
        if (this == &other)
            return *this;
        x = other.x;
        order = other.order;
        return *this;
    }
};

void siftUp(vector<element> &arr, int i){
    element tmp = arr[i];
    int parent = i/2;
    while((parent > 0) && (arr[parent].x >= tmp.x)){
        if (arr[parent].x == tmp.x && arr[parent].order < tmp.order)
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
        if((j+1 <= size) && (arr[j].x > arr[j+1].x))
            j++;
        if ((j+1 <= size) && arr[j].x == arr[j+1].x && arr[j].order > arr[j+1].order)
            j++;
        if(tmp.x < arr[j].x)
            break;
        if (tmp.x == arr[j].x && tmp.order < arr[j].order)
            break;
        else{
            arr[i] = arr[j];
            i = j;
        }
    }
    arr[i] = tmp;
}

void insert(vector<element>& priorityQueue, int x, int order){
    size++;
    priorityQueue[size] = element(x, order);
    siftUp(priorityQueue, size);
}

int find(vector<element>& priorityQueue, int minOrder){
    for (int i = 1; i <= size; i++){
        if (priorityQueue[i].order == minOrder)
            return i;
    }
}

void swap(element &a, element &b){
    element tmp = a;
    a = b;
    b = tmp;
}

int extractMin(vector<element>& priorityQueue){
    int min = priorityQueue[1].x;
    //cout << min << " " << priorityQueue[1].order << endl;
    int last = size;
    swap(priorityQueue[1], priorityQueue[last]);
    size--;
    siftDown(priorityQueue, 1);
    return min;
}

void decreaseKey(vector<element>& priorityQueue, int key, int value){
    int pos = find(priorityQueue, key);
    priorityQueue[pos].x = value;
    siftUp(priorityQueue, pos);
}

int main() {
    ifstream fin;
    ofstream out;
    //fin.open("priorityqueue.in");
    //out.open("priorityqueue.out");
    fin.open("input.txt");
    out.open("output.txt");

    vector<element> priorityQueue;
    priorityQueue.resize(1000000);

    int order = 0;
    while (!fin.eof()){
        order++;
        string str;
        fin >> str;
        if (str == "push"){
            int x;
            fin >> x;
            insert(priorityQueue, x, order);
        }
        else if (str == "extract-min"){
            if (size == 0)
                out << "*" << endl;
            else
                out << extractMin(priorityQueue) << endl;
        }
        else if (str == "decrease-key"){
            int key, value;
            fin >> key >> value;
            decreaseKey(priorityQueue, key, value);
        }
    }
    fin.close();
    out.close();
    return 0;
}