#include "TM.h"

int main() {
    string file_name = "../case2.tm";
    string input;
    input.append(99, '1');
    bool verbose = false;
    vector<string> syntax;
    ifstream in_file(file_name, ios::in);
    if (!in_file) {
        cerr << "Error occurred while opening file " + file_name << endl;
        exit(-1);
    }
    string line;
    while (getline(in_file, line))
        syntax.push_back(line);
    in_file.close();
    TM tm = TM(syntax);
    tm.read(input, verbose);
    return 0;
}
