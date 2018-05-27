#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin;
    ofstream out;
    fin.open("radixsort.in");
    out.open("radixsort.out");
//    fin.open("input.txt");
//    out.open("output.txt");

    int n, m, k;
    fin >> n >> m >> k;

    vector<string> str;
    str.resize(n);
    for (int i = 0; i < n; i++){
        fin >> str[i];
    }

    for (int i = 0; i < k; i++){
        vector<vector<string>> buf;
        buf.resize('z' - 'a' + 1);
        for (int j = 0; j < n; j++){
            buf[str[j][m - i - 1] - 'a'].push_back(str[j]);
        }
        str.clear();
        for (int j = 0; j < 'z' - 'a'; j++){
            if (!buf[j].empty()){
                for (int l = 0; l < buf[j].size(); l++){
                    str.push_back(buf[j][l]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++){
        out << str[i] << endl;
    }

    fin.close();
    out.close();
    return 0;
}