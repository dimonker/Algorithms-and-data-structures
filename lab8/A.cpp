#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("search1.in");
    ofstream out("search1.out");

    string p, t;
    fin >> p >> t;
    int sizeT = t.size();
    int sizeP = p.size();
    vector<int> ans;
    for (int i = 0; i < sizeT; i++){
        string k = t.substr(i, sizeP);
        if (p == t.substr(i, sizeP)){
            ans.push_back(i);
        }
    }
    out << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++){
        out << ans[i] + 1 << " ";
    }
    fin.close();
    out.close();
    return 0;
}