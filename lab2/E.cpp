#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

int statistic(vector<int> &arr, int n, int k) {
    int left = 1;
    int right = n;
    while (true){
        if (left + 1 >= right)
        {
            if ((right == left + 1) && (arr[right] < arr[left])) {
                swap (arr[left], arr[right]);
            }
            return arr[k];
        }
        int mid = (left + right) / 2;
        swap (arr[mid], arr[left + 1]);
        if (arr[left] > arr[right])
            swap (arr[left], arr[right]);
        if (arr[left + 1] > arr[right])
            swap (arr[left + 1], arr[right]);
        if (arr[left] > arr[left + 1])
            swap (arr[left], arr[left + 1]);
        int i = left + 1;
        int j = right;
        int x = arr[left + 1];
        while(true)
        {
            do {
                i++;
            }while (arr[i] < x);
            do {
                j--;
            } while (arr[j] > x) ;
            if (i > j)
                break;
            swap (arr[i], arr[j]);
        }
        arr[left + 1] = arr[j];
        arr[j] = x;
        if (j >= k)
            right = j-1;
        if (j <= k)
            left = i;
    }
}


int main() {
    ifstream fin;
    ofstream out;
    fin.open("kth.in");
    out.open("kth.out");
    //fin.open("input.txt");
    //out.open("output.txt");

    int n, k, a, b, c;
    fin >> n >> k >> a >> b >> c;

    vector<int> arr;
    arr.resize(n + 1);
    fin >> arr[1];
    fin >> arr[2];
    for (int i = 3; i <= n; i++){
        arr[i] = arr[i-2] * a + arr[i-1] * b + c;
    }

    out << statistic(arr, n, k) << endl;

    fin.close();
    out.close();
    return 0;
}