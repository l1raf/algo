#include <iostream>
#include <string>

using namespace std;

int LevenshteinDistance(string &s, int len_s, string &t, int len_t, int max) {
    int cost;

    if (len_s == 0)
        return len_t;

    if (len_t == 0)
        return len_s;

    if (s[len_s - 1] == t[len_t - 1])
        cost = 0;
    else
        cost = 1;

    max += cost;

    if (max > 2)
        return 3;

    return min(LevenshteinDistance(s, len_s - 1, t, len_t, max) + 1,
               min(LevenshteinDistance(s, len_s, t, len_t - 1, max) + 1,
                   LevenshteinDistance(s, len_s - 1, t, len_t - 1, max) + cost));
}

int getNumberOfMatches(string *commands, int numberOfCommands, string input, int numberOfErrors) {
    int count = 0;

    for (int j = 0; j < numberOfCommands; j++) {
        int cost = LevenshteinDistance(input, input.length(), commands[j], commands[j].length(), 0);

        if (cost <= numberOfErrors && abs((int) (input.length() - commands[j].length())) <= numberOfErrors)
            count++;
    }

    return count;
}

int main(int argc, const char *[]) {
    int numberOfCommands, numberOfErrors, numberOfUserCommands;

    cin >> numberOfCommands;

    auto *commands = new string[numberOfCommands];

    for (int i = 0; i < numberOfCommands; i++)
        cin >> commands[i];

    cin >> numberOfErrors;
    cin >> numberOfUserCommands;

    for (int i = 0; i < numberOfUserCommands; i++) {
        string input;
        cin >> input;
        cout << getNumberOfMatches(commands, numberOfCommands, input, numberOfErrors) << "\n";
    }

    delete[] commands;
}