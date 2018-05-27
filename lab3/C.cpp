#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main() {
    ifstream fin;
    ofstream out;
    fin.open("brackets.in");
    out.open("brackets.out");
    //fin.open("input.txt");
    //out.open("output.txt");
    string str;
    while (getline(fin, str)){
        string result = "YES";
        stack<char> brackets;
        for (int i = 0; i < str.size(); i++){
            if (str[i] == '[' || str[i] == '('){
                brackets.push(str[i]);
            }
            else{
                if (brackets.empty()){
                    result = "NO";
                    break;
                }
                bool brackets1 = brackets.top() == '[' && str[i] == ']';
                bool brackets2 = brackets.top() == '(' && str[i] == ')';
                if (brackets1 || brackets2){
                    brackets.pop();
                    continue;
                }else{
                    result = "NO";
                    break;
                }
            }
        }
        if (!brackets.empty())
            result = "NO";
        out << result << endl;
    }


    fin.close();
    out.close();
    return 0;
}