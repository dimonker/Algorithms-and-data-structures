#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class QuackQueue
{
    const int MODULE = 65536;
    queue<uint16_t> queue;

public:
    uint32_t get() {
        uint32_t result = queue.front();
        queue.pop();
        return result;
    }

    void put(int64_t value) {
        queue.push((uint16_t) (value % MODULE));
    }
};

void readData(ifstream& input, vector<string>& data) {

    while (!input.eof())
    {
        string line;
        input >> line;
        if (line != "")
            data.push_back(line);
        else break;
    }
}

void findLabels(vector<string>& data, map<string, int>& labels){
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][0] == ':')
        {
            labels[data[i].substr(1)] = i;
        }
    }
}

void runProgram(vector<string>& data, ofstream& outputStream){
    QuackQueue quackQueue;
    map<string, int> labels;
    vector<int> registers(26);
    findLabels(data, labels);

    int x, y;
    for (int line = 0; line < data.size(); line++)
    {
        string command = data[line];
        switch (command[0])
        {
            case '+':
                x = quackQueue.get();
                y = quackQueue.get();
                quackQueue.put(x + y);
                break;
            case '-':
                x = quackQueue.get();
                y = quackQueue.get();
                quackQueue.put(x - y);
                break;
            case '*':
                x = quackQueue.get();
                y = quackQueue.get();
                quackQueue.put(x * y);
                break;
            case '/':
                x = quackQueue.get();
                y = quackQueue.get();
                quackQueue.put(y != 0 ? x / y : 0);
                break;
            case '%':
                x = quackQueue.get();
                y = quackQueue.get();
                quackQueue.put(y != 0 ? x % y : 0);
                break;
            case '>':
                registers[command[1] - 'a'] = quackQueue.get();
                break;
            case '<':
                quackQueue.put(registers[command[1] - 'a']);
                break;
            case 'P':
                if (command.length() == 1)
                    outputStream << quackQueue.get() << endl;
                else
                    outputStream << registers[command[1] - 'a'] << endl;
                break;
            case 'C':
                if (command.length() == 1)
                    outputStream << (unsigned char) quackQueue.get();
                else
                    outputStream << (unsigned char) registers[command[1] - 'a'];
                break;
            case ':':
                break;
            case 'J':
                line = labels[command.substr(1)];
                break;
            case 'Z':
                if (registers[command[1] - 'a'] == 0)
                {
                    line = labels[command.substr(2)];
                }
                break;
            case 'E':
                if (registers[command[1] - 'a'] == registers[command[2] - 'a'])
                {
                    line = labels[command.substr(3)];
                }
                break;
            case 'G':
                if (registers[command[1] - 'a'] > registers[command[2] - 'a'])
                {
                    line = labels[command.substr(3)];
                }
                break;
            case 'Q':
                line = data.size();
                break;
            default:
                quackQueue.put(atoll(command.c_str()));
                break;
        }
    }
}

int main()
{
    //ifstream fin("quack.in");
    //ofstream out("quack.out");
    ifstream fin("input.txt");
    ofstream out("output.txt");

    vector<string> data;
    readData(fin, data);
    runProgram(data, out);

    fin.close();
    out.close();
    return 0;
}