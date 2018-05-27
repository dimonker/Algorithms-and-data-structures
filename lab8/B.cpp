#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("search2.in");
    ofstream out("search2.out");

    string p, s;
    fin >> p >> s;
    int sizeP = p.size(), sizeS = s.size();
    vector<int> ans;
    string subStr = p + "$" + s;
    vector<int> pref(subStr.size(), 0);
    for (int i = 1; i < subStr.size(); i++){
        int k = pref[i - 1];
        while (k > 0 && subStr[i] != subStr[k])
            k = pref[k - 1];
        if (subStr[i] == subStr[k])
            k++;
        pref[i] = k;
    }

    for (int i = 0; i < sizeS; i++)
        if (pref[sizeP + i + 1] == sizeP)
            ans.push_back(i - sizeP + 1);

    out << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
        out << ans[i] + 1 << " ";

    fin.close();
    out.close();
    return 0;
}