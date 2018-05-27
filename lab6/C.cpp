#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool check(vector<vector<int>> &arr){
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr.size(); j++){
            if (arr[i][j] > 1)
                return true;
            }
    return false;

}

int main() {
    ifstream fin("input.txt");
    ofstream out("output.txt");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> arr;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        arr[i].assign(n, 0);
    }

    for (int i = 1; i <= m; i++){
        int x, y;
        fin >> x >> y;
        arr[x - 1][y - 1]++;
        arr[y - 1][x - 1]++;
    }

    bool flag = check(arr);
    (flag) ? out << "YES" : out << "NO";

    fin.close();
    out.close();
    return 0;
}