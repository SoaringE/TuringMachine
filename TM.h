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
    vector<string> tapes;
    vector<int> positions;
    vector<int> left_bounds;
    string current_state;
    vector<pair<string, string>> transitions;
public:
    TM() {
        states = set<string>();
        input_alphabet = set<char>();
        tape_alphabet = set<char>();
        start_state = "0";
        blank = '_';
        end_states = set<string>();
        tape_number = 1;
        tapes = vector<string>(tape_number);
        positions = vector<int>({0});
        left_bounds = vector<int>({0});
        current_state = "0";
        transitions = vector<pair<string, string>>();
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
                    current_state = start_state;
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
                    string line_copy = line;
                    unsigned int pos = line_copy.find(' ');
                    string old_state = line_copy.substr(0, pos);
                    old_state.push_back(' ');
                    line_copy = line_copy.substr(pos + 1);
                    pos = line_copy.find(' ');
                    string old_characters = line_copy.substr(0, pos);
                    transitions.emplace_back(old_state + old_characters, line_copy.substr(pos + 1));
                }
                // cout << line << endl;
            }
        }
    }

    void read(string &input) {
        tapes = vector<string>(tape_number, "___");
        tapes[0] = "_" + input + "_";
        positions = vector<int>(tape_number, 1);
        left_bounds = vector<int>(tape_number, 1);
        bool stop = false;
        while (!stop) {
            string current = current_state + " ";
            string current_characters;
            for (int i = 0; i < tape_number; ++i) {
                current_characters.push_back(tapes[i][positions[i]]);
            }
            current += current_characters;
            unsigned int pos = 0;
            for (; pos < transitions.size(); ++pos) {
                string rule = transitions[pos].first;
                for (int i = 0; i < current.size(); ++i) {
                    if (rule[i] == '*')
                        rule[i] = current[i];
                }
                if (rule == current)
                    break;
            }
            if (pos == transitions.size()) {
                stop = true;
            } else {
                string target = transitions[pos].second;
                for (int i = 0; i < tape_number; ++i) {
                    tapes[i][positions[i]] = target[i] == '*' ? tapes[i][positions[i]] : target[i];
                    char towards = target[current_characters.length() + 1 + i];
                    if (towards != 'l' && towards != 'r' && towards != '*') {
                        cerr << "Invalid direction" << endl;
                        exit(-1);
                    }
                    positions[i] += towards == '*' ? 0 : (towards == 'l' ? -1 : 1);
                    if (positions[i] == -1) {
                        tapes[i] = "_" + tapes[i];
                        positions[i]++;
                        left_bounds[i]++;
                    }
                    if (positions[i] == tapes[i].length())
                        tapes[i] = tapes[i] + "_";
                    current_state = target.substr(target.find_last_of(' ') + 1);
                    // cout << tapes[i] << endl;
                }
                // cout << current_state << endl;
                // cout << endl;
                if (end_states.find(current_state) != end_states.end())
                    stop = true;
            }
        }
        for (int i = 0; i < tape_number; ++i) {
            cout << tapes[i] << endl;
            // cout << left_bounds[i] << endl;
        }

    }
};


#endif //TURING_TM_H
