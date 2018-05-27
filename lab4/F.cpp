#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct element{
    int x;
    int order;
    element(){}
    element(int x, int order):x(x), order(order){};
};

void siftUp(vector<element> &arr, int i){
    element tmp = arr[i];
    int parent = i/2;
    while((parent > 0) && (arr[parent].x > tmp.x)){
        arr[i] = arr[parent];
        i = parent;
        parent /= 2;
    }
    arr[i] = tmp;
}

int siftDown(vector<element> &arr, int i){
    element tmp = arr[i];
    while (2*i <= arr.size() - 1){
        int j = i * 2;
        if((j+1 <= arr.size() - 1) && (arr[j].x > arr[j+1].x)){
            j++;
        }
        if(tmp.x <= arr[j].x)
            break;
        else{
            arr[i] = arr[j];
            i = j;
        }
    }
    arr[i] = tmp;
    return i;
}

void insert(vector<element>& priorityQueue, int x, int order){
    priorityQueue.push_back(element(x, order));
    siftUp(priorityQueue, priorityQueue.size() - 1);
}

int minimum(vector<element>& priorityQueue){
    return priorityQueue[1].x;
}

int find(vector<element>& priorityQueue, int minOrder){
    for (int i = 1; i < priorityQueue.size(); i++){
        if (priorityQueue[i].order == minOrder)
            return i;
    }
}

void swap(element &a, element &b){
    element tmp = a;
    a = b;
    b = tmp;
}

void removeElem(vector<element>& priorityQueue, int &minOrder){
    int pos = find(priorityQueue, minOrder++);
    int last = priorityQueue.size() - 1;
    swap(priorityQueue[pos], priorityQueue[last]);
    priorityQueue.pop_back();
    pos = siftDown(priorityQueue, pos);
    siftUp(priorityQueue, pos);
}

int main() {
    ifstream fin;
    ofstream out;
    fin.open("queuemin.in");
    out.open("queuemin.out");
    //fin.open("input.txt");
    //out.open("output.txt");

    int n;
    fin >> n;
    vector<element> priorityQueue;
    priorityQueue.push_back(element(0,0));

    int order = 1;
    int minOrder = 1;
    for (int i = 0; i < n; i++){
        string str;
        fin >> str;
        if (str == "+"){
            int x;
            fin >> x;
            insert(priorityQueue, x, order++);
        }
        if (str == "?"){
            out << minimum(priorityQueue) << endl;
        }
        if (str == "-"){
            removeElem(priorityQueue, minOrder);
        }
    }



    fin.close();
    out.close();
    return 0;
}