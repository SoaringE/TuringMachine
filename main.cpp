#include "TM.h"

int main() {
    string syntax;
    string file_name = "/palindrome_detector_2tapes.tm";
    ifstream in_file(file_name, ios::in);
    if (!in_file) {
        cerr << "Error occurred while opening file " + file_name << endl;
        exit(-1);
    }
    while (!in_file.eof()) {
        string temp;
        in_file >> temp;
        syntax += temp;
    }
    in_file.close();
    cout << syntax << endl;
    return 0;
}
