#include <iostream>
#include <fstream>

using namespace std;

long long inverse = 0;

void Merge(int *arr, int first, int mid, int last){
    int i = first;
    int j = mid;
    int tmp[last - first];

    for (int k = first; k < last; k++){

        if (i == mid){
            tmp[k - first] = arr[j];
            j++;
        }else if (j == last){
            tmp[k - first] = arr[i];
            i++;
        }else if (arr[i] <= arr[j]){
            tmp[k - first] = arr[i];
            i++;
        }else if (arr[i] > arr[j]){
            tmp[k - first] = arr[j];
            j++;
            inverse += mid - i;
        }
    }

    for (int k = first; k < last; k++){
        arr[k] = tmp[k - first];
    }
}

void MergeSort(int *arr, int first, int last){
    if (first + 1 >= last)
        return;
    int mid = (first + last)/2;
    MergeSort(arr, first, mid);
    MergeSort(arr, mid, last);
    Merge(arr, first, mid, last);
}

int main() {
    ifstream fin;
    ofstream out;
    fin.open("inversions.in");
    out.open("inversions.out");
    //fin.open("input.txt");
    //out.open("output.txt");

    int n;
    fin >> n;

    int arr[n];

    for (int i = 0; i < n; i++){
        arr[i] = i;
        fin >> arr[i];
    }

    MergeSort(arr, 0, n);

    out << inverse;
    fin.close();
    out.close();
    return 0;
}