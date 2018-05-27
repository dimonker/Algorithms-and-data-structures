#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("prefix.in");
    ofstream out("prefix.out");

    string s;
    fin >> s;
    vector<int> p(s.size(), 0);
    for (int i = 1; i < s.size(); i++){
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k])
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        p[i] = k;
    }

    for (int i = 0; i < p.size(); i++)
        out << p[i] << " ";

    fin.close();
    out.close();
    return 0;
}