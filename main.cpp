#include "TM.h"

int main(int argc, char* argv[]) {
    string option;
    string file_name;
    string input;
    bool verbose;

    if (argc == 1) {
        cerr << "invalid usage" << endl;
        exit(-1);
    } else if (argc == 2) {
        string arg1 = argv[1];
        if (arg1 == "--help" || arg1 == "-h") {
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
            return 0;
        } else if (arg1.length() >= 3 && arg1.substr(arg1.length() - 3) == ".tm") {
            file_name = arg1;
            verbose = false;
        }
        else {
            cerr << "invalid usage" << endl;
            exit(-1);
        }
    } else if (argc == 3) {
        string arg1 = argv[1];
        string arg2 = argv[2];
        if ((arg1 == "-v" || arg1 == "--verbose") && arg2.length() >= 3 && arg2.substr(arg2.length() - 3) == ".tm") {
            verbose = true;
            file_name = arg2;
        } else if (arg1 == "-h" || arg1 == "--help") {
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
            return 0;
        } else if (arg1.length() >= 3 && arg1.substr(arg1.length() - 3) == ".tm") {
            file_name = arg1;
            input = arg2;
            verbose = false;
        } else {
            cerr << "invalid usage" << endl;
            exit(-1);
        }
    } else if (argc == 4) {
        string arg1 = argv[1];
        string arg2 = argv[2];
        string arg3 = argv[3];
        if (arg1 == "-h" || arg1 == "--help") {
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
            return 0;
        } else if ((arg1 == "-v" || arg1 == "--verbose") && arg2.length() >= 3 && arg2.substr(arg2.length() - 3) == ".tm") {
            file_name = arg2;
            input = arg3;
            verbose = true;
        } else {
            cerr << "invalid usage" << endl;
            exit(-1);
        }
    } else {
        string arg1 = argv[1];
        if (arg1 == "-h" || arg1 == "--help") {
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
            return 0;
        } else {
            cerr << "invalid usage" << endl;
            exit(-1);
        }
    }

    vector<string> syntax;
    ifstream in_file(file_name, ios::in);
    if (!in_file) {
        cerr << "error occurred while opening file " + file_name << endl;
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
