#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, string> c;
map<string, string> a;
map<string, bool> used;

void RemoveQuotes(string& param) {
    param.erase(0, 1);
    param.erase(param.length() - 1, 1);
}

string toLower(const string& s) {
    string result = s;
    for (char& c : result) c = tolower(c);
    return result;
}

bool isWordBoundary(char c) {
    return isspace(c) || c == '.' || c == ',' || c == '!' || c == '?' || c == '"' || c == '\0';
}

bool isWordPart(char c) {
    return isalnum(c) || c == '_' || c == '\'';
}

void processText(string& s) {
    string result;
    size_t i = 0;

    while (i < s.length()) {
        bool found = false;

        for (const auto& [pattern, expansion] : c) {
            if (i + pattern.length() > s.length()) continue;

            string part = s.substr(i, pattern.length());

            bool validBoundary = true;
            if (i > 0 && isWordPart(s[i - 1])) validBoundary = false;
            if (i + pattern.length() < s.length() && isWordPart(s[i + pattern.length()])) validBoundary = false;

            if (!validBoundary) continue;

            if (part == pattern) {
                result += expansion;
                found = true;
            }
            else {
                string upperPattern = pattern;
                transform(upperPattern.begin(), upperPattern.end(), upperPattern.begin(), ::toupper);
                if (part == upperPattern) {
                    string upperExpansion = expansion;
                    transform(upperExpansion.begin(), upperExpansion.end(), upperExpansion.begin(), ::toupper);
                    result += upperExpansion;
                    found = true;
                }
                else if (part.length() > 0 && isupper(part[0]) &&
                    equal(pattern.begin() + 1, pattern.end(), part.begin() + 1,
                        [](char a, char b) { return tolower(a) == tolower(b); }) &&
                    tolower(part[0]) == tolower(pattern[0])) {
                    string capitalizedExpansion = expansion;
                    capitalizedExpansion[0] = toupper(capitalizedExpansion[0]);
                    result += capitalizedExpansion;
                    found = true;
                }
            }

            if (found) {
                i += pattern.length();
                break;
            }
        }

        if (!found) {
            for (const auto& [pattern, expansion] : a) {
                if (i + pattern.length() > s.length()) continue;

                string part = s.substr(i, pattern.length());
                if (part != pattern) continue;

                bool validBoundary = true;
                if (i > 0 && isWordPart(s[i - 1])) validBoundary = false;
                if (i + pattern.length() < s.length() && isWordPart(s[i + pattern.length()])) validBoundary = false;

                if (validBoundary && !used[pattern]) {
                    result += expansion;
                    i += pattern.length();
                    used[pattern] = true;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            result += s[i++];
        }
    }

    s = result;
}

void Sol() {
    int cn, an;
    cin >> cn >> an;
    cin.ignore();

    while (cn--) {
        string crule;
        getline(cin, crule);
        size_t splitPos = crule.find(" -> ");
        string ckey = crule.substr(0, splitPos);
        string cval = crule.substr(splitPos + 4);
        RemoveQuotes(ckey);
        RemoveQuotes(cval);
        c[ckey] = cval;
    }

    while (an--) {
        string arule;
        getline(cin, arule);
        size_t splitPos = arule.find(" -> ");
        string akey = arule.substr(0, splitPos);
        string aval = arule.substr(splitPos + 4);
        RemoveQuotes(akey);
        RemoveQuotes(aval);
        a[akey] = aval + " (" + akey + ")";
    }

    string line;
    vector<string> block;
    while (getline(cin, line)) {
        if (line == "#") {
            used.clear();
            for (int i = 0; i < block.size(); i++) {
                processText(block[i]);
            }

            for (size_t i = 0; i < block.size(); i++) {
                cout << block[i];
                if (i < block.size() - 1) cout << '\n';
            }
            cout << "\n#";
            if (!cin.eof()) cout << '\n';

            block.clear();
            if (cin.eof()) break;
        }
        else {
            block.push_back(line);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Sol();
    return 0;
}