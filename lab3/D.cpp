#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

struct numbers{
    int n1;
    int n2;
};

numbers lastTwoNumbers(stack<int> &calc){
    numbers n;
    n.n1 = calc.top();
    calc.pop();
    n.n2 = calc.top();
    calc.pop();
    return n;
}

int main() {
    ifstream fin;
    ofstream out;
    //fin.open("postfix.in");
    //out.open("postfix.out");
    fin.open("input.txt");
    out.open("output.txt");
    stack<int> calc;
    while (!fin.eof()){
       string str;
       fin >> str;
       if (str[0] >= '0' && str[0] <= '9'){
           calc.push(stoi(str));
       }else{
           numbers n;
           if (str == "*"){
               n = lastTwoNumbers(calc);
               calc.push(n.n2 * n.n1);
           }
           if (str == "+"){
               n = lastTwoNumbers(calc);
               calc.push(n.n2 + n.n1);
           }
           if (str == "-"){
               n = lastTwoNumbers(calc);
               calc.push(n.n2 - n.n1);
           }
       }
    }
    out << calc.top();

    fin.close();
    out.close();
    return 0;
}