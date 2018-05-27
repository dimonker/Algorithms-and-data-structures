#include <iostream>
#include <fstream>

using namespace std;

struct Runner{
    string country;
    string name;
    int place;
};

void Merge(Runner *arr, int first, int mid, int last){
    int i = first;
    int j = mid;
    Runner tmp[last - first];

    for (int k = first; k < last; k++){
        if(j == last || (arr[i].country <= arr[j].country && arr[i].place < arr[j].place && i < mid)){
            tmp[k - first] = arr[i];
            i++;
        }
        else{
            tmp[k - first] = arr[j];
            j++;
        }
    }
    for (int k = first; k < last; k++){
        arr[k] = tmp[k - first];
    }
}

void MergeSort(Runner *arr, int first, int last){
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
    fin.open("race.in");
    out.open("race.out");
    //fin.open("input.txt");
    //out.open("output.txt");

    int n;
    fin >> n;
    Runner runner[n];

    string inName, inCountry;

    for (int i = 0; i < n; i++){
        fin >> inCountry >> inName;
        runner[i].country = inCountry;
        runner[i].name = inName;
        runner[i].place = i + 1;
    }

    MergeSort(runner, 0, n);

    string lastCountry = "";
    for (int i = 0; i < n; i++){
        if(lastCountry != runner[i].country){
            out << "=== " << runner[i].country << " ===" << endl;
            lastCountry = runner[i].country;
        }
        out  << runner[i].name << endl;
    }

    fin.close();
    out.close();
    return 0;
}