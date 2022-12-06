//
// Created by HBD on 2022/12/1.
//

#ifndef TURING_TM_H
#define TURING_TM_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class TM {
private:
    set<string> states;
    set<char> input_alphabet;
    set<char> tape_alphabet;
    string start_state;
    char blank;
    set<string> end_states;
    int tape_number;
    vector<string> tapes;
    vector<int> positions;
    vector<int> bases;
    string current_state;
    vector<pair<string, string>> transitions;
    int step;

    void verbose_output();

public:
    TM();

    explicit TM(vector<string> &syntax);

    void read(string &input, bool verbose);
};


#endif //TURING_TM_H
