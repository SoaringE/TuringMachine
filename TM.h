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
    char blank;
    set<string> end_states;
    int tape_number;
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
    explicit TM(vector<string> &syntax) {
        // TODO: parse syntax
        for (string line : syntax) {
            if (line.empty() or line[line.find_first_not_of(' ')] == ';')
                continue;
            else {
                line = line.substr(0, line.find(';'));
                line = line.substr(line.find_first_not_of(' '));
                if (line.find("#Q") == 0) {
                    unsigned int pos = line.find('{') + 1;
                    while (pos < line.length()) {
                        string state;
                        for(; line[pos] != ',' && line[pos] != '}'; ++pos) {
                            state.push_back(line[pos]);
                        }
                        // TODO: Check if state is valid
                        states.insert(state);
                        ++pos;
                    }
                } else if (line.find("#S") == 0) {
                    unsigned int pos = line.find('{') + 1;
                    while (pos < line.length()) {
                        string symbol;
                        for(; line[pos] != ',' && line[pos] != '}'; ++pos) {
                            symbol.push_back(line[pos]);
                        }
                        // TODO: Check if state is valid
                        if (symbol.length() == 1)
                            input_alphabet.insert(symbol[0]);
                        ++pos;
                    }
                } else if (line.find("#G") == 0) {
                    unsigned int pos = line.find('{') + 1;
                    while (pos < line.length()) {
                        string symbol;
                        for(; line[pos] != ',' && line[pos] != '}'; ++pos) {
                            symbol.push_back(line[pos]);
                        }
                        // TODO: Check if state is valid
                        if (symbol.length() == 1)
                            tape_alphabet.insert(symbol[0]);
                        ++pos;
                    }
                } else if (line.find("#q0") == 0) {
                    unsigned int pos = line.find('=') + 1;
                    while (pos < line.length()) {
                        if (line[pos] != ' ')
                            start_state.push_back(line[pos]);
                        ++pos;
                    }
                } else if (line.find("#B") == 0) {
                    unsigned int pos = line.find('=') + 1;
                    string temp;
                    while (pos < line.length()) {
                        if (line[pos] != ' ')
                            temp.push_back(line[pos]);
                        ++pos;
                    }
                    if (temp.length() == 1)
                        blank = temp[0];
                } else if (line.find("#F") == 0) {
                    unsigned int pos = line.find('{') + 1;
                    while (pos < line.length()) {
                        string state;
                        for(; line[pos] != ',' && line[pos] != '}'; ++pos) {
                            state.push_back(line[pos]);
                        }
                        end_states.insert(state);
                        ++pos;
                    }
                } else if (line.find("#N") == 0) {
                    unsigned int pos = line.find('=') + 1;
                    string temp;
                    while (pos < line.length()) {
                        if (line[pos] != ' ')
                            temp.push_back(line[pos]);
                        ++pos;
                    }
                    tape_number = stoi(temp);
                } else {

                }
                cout << line << endl;
            }
        }
    }
};


#endif //TURING_TM_H
