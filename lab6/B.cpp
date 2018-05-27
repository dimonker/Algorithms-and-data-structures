#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool check(vector<vector<int>> arr){
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr.size(); j++){
            if (i == j){
                if (arr[i][j] == 1)
                    return false;
            }else{
                if (arr[i][j] != arr[j][i])
                    return false;
            }
        }
    return true;
}

int main() {
    ifstream fin("input.txt");
    ofstream out("output.txt");

    int n;
    fin >> n;
    vector<vector<int>> arr;
    arr.resize(n);
    for (int i = 0; i < n; i++)
        arr[i].resize(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            fin >> arr[i][j];
        }

    bool flag = check(arr);
    (flag) ? out << "YES" : out << "NO";

    fin.close();
    out.close();
    return 0;
}