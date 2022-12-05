//
// Created by HBD on 2022/12/1.
//

#include "TM.h"

void TM::verbose_output() {
    cout << "Step   : " << step << endl;
    if (step == 16)
        cout << "find" <<endl;
    step++;
    cout << "State  : " << current_state << endl;
    for (int i = 0; i < tape_number; ++i) {
        string index = "Index" + to_string(i);
        if (i >= 0 && i <= 9)
            index.append(" ");
        index.append(": ");
        string tape = "Tape" + to_string(i);
        if (i >= 0 && i <= 9)
            tape.append("  ");
        else tape.append(" ");
        tape.append(": ");
        string head = "Head" + to_string(i);
        if (i >= 0 && i <= 9)
            head.append("  ");
        else head.append(" ");
        head.append(": ");
        unsigned int left = 0, right = tapes[i].length() - 1;
        for (; tapes[i][left] == '_' && left != positions[i] && left <= right; ++left);
        for (; right >= left && tapes[i][right] == '_' && right != positions[i]; --right);
        int j = (int)left;
        do {
            int offset = j - bases[i];
            index.append(to_string(abs(offset)));
            index.append(" ");
            tape.append(1, tapes[i][j]);
            tape.append(to_string(abs(offset)).length(), ' ');
            if (j == positions[i])
                head.append("^");
            else head.append(" ");
            head.append(to_string(abs(offset)).length(), ' ');
            j++;
        } while (j <= right);
        cout << index <<endl << tape << endl << head << endl;
    }
    cout << "---------------------------------------------" << endl;
}

TM::TM() {
    states = set<string>();
    input_alphabet = set<char>();
    tape_alphabet = set<char>();
    start_state = "0";
    blank = '_';
    end_states = set<string>();
    tape_number = 1;
    tapes = vector<string>(tape_number);
    positions = vector<int>({0});
    bases = vector<int>({0});
    current_state = "0";
    transitions = vector<pair<string, string>>();
    step = 0;
}

TM::TM(vector<string> &syntax) {
    // TODO: parse syntax
    step = 0;
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
        }
    }
}

void TM::read(string &input, bool verbose) {
    step = 0;
    current_state = start_state;
    tapes = vector<string>(tape_number, "___");
    tapes[0] = "_" + input + "_";
    positions = vector<int>(tape_number, 1);
    bases = vector<int>(tape_number, 1);
    string pointer;
    for (char c : input) {
        if (input_alphabet.find(c) == input_alphabet.end()) {
            pointer.append("^");
            if (verbose) {
                cerr << "Input: " << input << endl;
                cerr << "==================== ERR ====================" << endl;
                cerr << "error: " << '\'' << c << '\'' << " was not declared in the set of input symbols" << endl;
                cerr << "Input: " << input << endl;
                cerr << "       " << pointer << endl;
                cerr << "==================== END ====================" << endl;
                exit(-1);
            } else {
                cerr << "illegal input" << endl;
                exit(-1);
            }
        } else {
            pointer.append(" ");
        }
    }
    if (verbose) {
        cout << "Input: " << input << endl;
        cout << "==================== RUN ====================" << endl;
    }

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
            if (verbose)
                verbose_output();
        } else {
            if (verbose)
                verbose_output();
            string target = transitions[pos].second;
            for (int i = 0; i < tape_number; ++i) {
                char writen = target[i] == '*' ? tapes[i][positions[i]] : target[i];
                tapes[i][positions[i]] = writen;
                char towards = target[current_characters.length() + 1 + i];
                if (towards != 'l' && towards != 'r' && towards != '*') {
                    cerr << "Invalid direction" << endl;
                    exit(-1);
                }
                positions[i] += towards == '*' ? 0 : (towards == 'l' ? -1 : 1);
                if (positions[i] == -1) {
                    tapes[i] = "_" + tapes[i];
                    positions[i]++;
                    bases[i]++;
                }
                if (positions[i] == tapes[i].length())
                    tapes[i] = tapes[i] + "_";
                if (positions[i] == tapes[i].length() - 1 && tapes[i][positions[i]] != '_')
                    tapes[i] = tapes[i] + "_";
                current_state = target.substr(target.find_last_of(' ') + 1);
            }
            if (end_states.find(current_state) != end_states.end()) {
                stop = true;
                if (verbose)
                    verbose_output();
            }
        }
    }
    unsigned int left = 0, right = tapes[0].length() - 1;
    for (; left <= right && tapes[0][left] == '_'; ++left);
    for (; right >= left && tapes[0][right] == '_'; --right);
    if (verbose) {
        cout << "Result: "<< tapes[0].substr(left, right - left + 1) << endl;
        cout << "==================== END ====================";
    }
    else cout << tapes[0].substr(left, right - left + 1) << endl;

}