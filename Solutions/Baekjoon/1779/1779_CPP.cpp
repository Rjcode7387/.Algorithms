#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    int id = 0;
    int len = 0;
    array<unique_ptr<TrieNode>, 128> next{};
};

class TextProcessor {
public:
    TextProcessor(int contractionCount, int acronymCount)
        : contractionCount(contractionCount), acronymCount(acronymCount) {
        root = make_unique<TrieNode>();
        expansions.resize(contractionCount * 3 + acronymCount + 1);
        processRules();
        processText();
    }

private:
    const int contractionCount;
    const int acronymCount;
    unique_ptr<TrieNode> root;
    vector<string> expansions;
    int currentId = 0;
    int keyId = 0;

    static char toUpper(char c) {
        return (c >= 'a' && c <= 'z') ? c - 32 : c;
    }

    void processRules() {
        string line;
        getline(cin, line);

        for (int i = 1; i <= contractionCount; i++) {
            getline(cin, line);
            auto [key, value] = parseRule(line);

            insertIntoTrie(key, value, false, false);

            string upperKey = key;
            string upperValue = value;
            for (char& c : upperKey) c = toUpper(c);
            for (char& c : upperValue) c = toUpper(c);
            insertIntoTrie(upperKey, upperValue, false, false);

            string capitalizedKey = key;
            string capitalizedValue = value;
            if (!key.empty()) capitalizedKey[0] = toUpper(key[0]);
            if (!value.empty()) capitalizedValue[0] = toUpper(value[0]);
            insertIntoTrie(capitalizedKey, capitalizedValue, false, false);
        }

        keyId = currentId;

        for (int i = 1; i <= acronymCount; i++) {
            getline(cin, line);
            auto [key, value] = parseRule(line);
            insertIntoTrie(key, value + " (" + key + ")", true, false);
        }
    }

    pair<string, string> parseRule(const string& line) {
        size_t start = line.find('\"') + 1;
        size_t end = line.find('\"', start);
        string key = line.substr(start, end - start);

        start = line.find('\"', end + 1) + 1;
        end = line.find('\"', start);
        string value = line.substr(start, end - start);

        return { key, value };
    }

    void insertIntoTrie(const string& key, const string& value, bool isAcronym, bool isCapitalized) {
        TrieNode* current = root.get();
        for (char c : key) {
            unsigned char idx = static_cast<unsigned char>(c);
            if (!current->next[idx]) {
                current->next[idx] = make_unique<TrieNode>();
            }
            current = current->next[idx].get();
            current->len++;
        }

        if (current->id == 0) {
            current->id = ++currentId;
            expansions[current->id] = value;
        }
    }

    void processText() {
        vector<bool> firstAppearance(currentId + 1, false);
        vector<string> currentBlock;
        bool isFirstBlock = true;
        string line;

        while (getline(cin, line)) {
            if (line[0] == '#') {
                printBlock(currentBlock, isFirstBlock);
                cout << "#";
                currentBlock.clear();
                fill(firstAppearance.begin() + keyId + 1, firstAppearance.end(), false);
                isFirstBlock = false;
                continue;
            }

            string processedLine;
            for (size_t i = 0; i < line.length(); i++) {
                auto matchResult = findLongestMatch(line, i, firstAppearance);
                if (matchResult.first.empty()) {
                    processedLine += line[i];
                }
                else {
                    processedLine += matchResult.first;
                    i += matchResult.second - 1;
                }
            }
            currentBlock.push_back(processedLine);
        }

        if (!currentBlock.empty()) {
            printBlock(currentBlock, isFirstBlock);
        }
    }

    pair<string, size_t> findLongestMatch(const string& text, size_t start, vector<bool>& firstAppearance) {
        TrieNode* current = root.get();
        size_t matchLength = 0;
        int matchId = 0;

        for (size_t i = start; i < text.length(); i++) {
            unsigned char idx = static_cast<unsigned char>(text[i]);
            if (!current->next[idx]) break;

            current = current->next[idx].get();
            if (current->id > 0) {
                if (current->id <= keyId || !firstAppearance[current->id]) {
                    matchLength = i - start + 1;
                    matchId = current->id;
                }
            }
        }

        if (matchId > 0) {
            if (matchId > keyId) firstAppearance[matchId] = true;
            return { expansions[matchId], matchLength };
        }
        return { "", 0 };
    }

    void printBlock(const vector<string>& block, bool isFirst) {
        if (!isFirst && !block.empty()) cout << "\n";
        for (size_t i = 0; i < block.size(); i++) {
            cout << block[i];
            if (i < block.size() - 1) cout << "\n";
        }
        if (!block.empty()) cout << "\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, a;
    cin >> c >> a;

    TextProcessor processor(c, a);
    return 0;
}