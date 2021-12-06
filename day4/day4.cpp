#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    int part1 = 0;
    int part2 = 0;

    string phrase;
    while (getline(cin, phrase)) {
        set<string> words1;
        set<string> words2;
        istringstream iss(phrase);
        string word;

        bool valid1 = true;
        bool valid2 = true;
        while (getline(iss, word, ' ')) {
            if (words1.find(word) == words1.end()) {
                words1.insert(word);
            }
            else {
                valid1 = false;
            }

            // Sort the letters in the word to normalise anagrams
            sort(word.begin(), word.end());
            if (words2.find(word) == words2.end()) {
                words2.insert(word);
            }
            else {
                valid2 = false;
            }
        }

        if (valid1) {
            ++part1;
        }

        if (valid2) {
            ++part2;
        }
    }


    // RESULTS...

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}