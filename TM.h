//
// Created by HBD on 2022/12/1.
//

#ifndef TURING_TM_H
#define TURING_TM_H

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class TM {
private:
    set<string> states;
    set<char> input_alphabet;
    set<char> tape_alphabet;
    string start_state;
    char blank{};
    set<string> end_states;
    int tape_number{};
    vector<vector<int>> tapes;
    vector<int> positions;
    map<vector<string>, vector<string>> transitions;
public:
    TM() {
        states = set<string>();
        input_alphabet = set<char>();
        tape_alphabet = set<char>();
        start_state = "0";
        blank = '_';
        end_states = set<string>();
        tape_number = 1;
        tapes = vector<vector<int>>(tape_number, vector<int>());
        positions = vector<int>({0});
        transitions = map<vector<string>, vector<string>>();
    }
    explicit TM(string& syntax) {
        // TODO: parse syntax
    }
};


#endif //TURING_TM_H
