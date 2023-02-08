// Advent of code 2022 - day
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct valve {
    string name;
    int flowrate;
    vector<string> tunnels;
    bool open;
};

vector<string> tokenize(string l, char tokenizer) {
    vector<string> tokens;
    stringstream check(l);
    string part;
    while (getline(check, part, tokenizer)) {
        tokens.push_back(part);
    }
    return tokens;
}

static vector<valve> valves;
static int mostPressure = 0;
static int iteretions = 0;

int valve_index(string val) {
    for (int i = 0; i < valves.size(); i++) {
        if (val == valves.at(i).name) {
            return i;
        }
    }
    return -1;
}

void most_pressure(int mins, int totalPressure, int pps, string vName) {
    mins++;
    totalPressure += pps;
    iteretions++;
    if (iteretions % 10000000 == 0) cout << iteretions;

    int currValveIndex = valve_index(vName);
    valve currValve = valves.at(currValveIndex);
    if (mins == 30) {
        if (mostPressure < totalPressure) {
            mostPressure = totalPressure;
            cout << mostPressure << endl;
        }
        return;
    }
    // Move
    for (int i = 0; i < currValve.tunnels.size(); i++) {
        string next = currValve.tunnels.at(i);
        most_pressure(mins, totalPressure, pps, next);
    }
    // Open
    if (!currValve.open && currValve.flowrate != 0) {
        currValve.open = true;
        pps += currValve.flowrate;
        most_pressure(mins, totalPressure, pps, vName);
    }

    most_pressure(mins, totalPressure, pps, vName);
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    while (getline(inputFile, line)) {
        vector<string> tokens = tokenize(line, ' ');
        valve v;
        v.name = tokens.at(0);
        v.flowrate = stoi(tokens.at(1));
        v.open = false;
        for (int i = 2; i < tokens.size(); i++) {
            v.tunnels.push_back(tokens.at(i));
        }
        valves.push_back(v);
    }

    most_pressure(0, 0, 0, "AA");

    cout << "Most pressure: " << mostPressure << endl;

    inputFile.close();

    return 0;
}
