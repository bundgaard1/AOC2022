// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>

static long int modd = 1;
#include "monkey.cpp"
using namespace std;

void print_monkeys(vector<Monkey> m);
void print_worry(vector<Monkey> m);

int main(void) {
    vector<Monkey> monkeys;

    monkeys.push_back(Monkey({79, 98}, 23, 2, 3, '*', 19));
    monkeys.push_back(Monkey({54, 65, 75, 74}, 19, 2, 0, '+', 6));
    monkeys.push_back(Monkey({79, 60, 97}, 13, 1, 3, '*', 0));
    monkeys.push_back(Monkey({74}, 17, 0, 1, '+', 3));

    // Find booster
    for (int i = 0; i < monkeys.size(); i++) {
        modd *= monkeys.at(i).testValue;
    }
    cout << modd << endl;

    for (int round = 1; round <= 1000; round++) {
        for (int i = 0; i < monkeys.size(); i++) {
            while (!monkeys.at(i).items.empty()) {
                long int newValue = monkeys.at(i).inspect();
                long int reciveMonkey = monkeys.at(i).test(newValue);
                // cout << reciveMonkey << endl;
                monkeys.at(i).items.erase(monkeys.at(i).items.begin());
                monkeys.at(reciveMonkey).items.push_back(newValue);
            }
        }
        cout << "Round " << round << endl;
        // print_monkeys(monkeys);
    }
    print_monkeys(monkeys);
    cout << endl;
    print_worry(monkeys);
}

void print_monkeys(vector<Monkey> m) {
    for (int i = 0; i < m.size(); i++) {
        cout << "Monkey " << i << ": ";
        Monkey curr = m.at(i);
        for (int j = 0; j < curr.items.size(); j++) {
            cout << m.at(i).items.at(j) << ", ";
        }
        cout << endl;
    }
}
void print_worry(vector<Monkey> m) {
    for (int i = 0; i < m.size(); i++) {
        cout << "Monkey " << i << ": " << m.at(i).inspects << endl;
    }
    cout << endl;
}
