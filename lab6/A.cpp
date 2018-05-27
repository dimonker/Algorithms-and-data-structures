#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream out("output.txt");

    int n, m;
    fin >> n >> m;
    int arr[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
        arr[i][j] = 0;
    }

    for (int i = 0; i < m; i++){
        int x, y;
        fin >> x >> y;
        arr[x - 1][y - 1] = 1;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            out << arr[i][j] << " ";
        }
        out << endl;
    }


    fin.close();
    out.close();
    return 0;
}