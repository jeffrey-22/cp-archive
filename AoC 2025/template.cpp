#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); i++)

vector<string> readTokens(const string& lineDelims = "\n\r",
                          const string& tokenDelims = " -|;")
{
    string raw;
    // Read raw text until EOF
    while (true) {

        // Read *chunks* separated by any line delimiter
        char c;
        raw.clear();
        while (cin.get(c)) {
            if (lineDelims.find(c) != string::npos) break;
            raw.push_back(c);
        }

        // If EOF and no characters read → done
        if (!cin && raw.empty()) return {};

        // Check "!!!"
        if (raw.size() >= 3 && raw[0]=='!' && raw[1]=='!' && raw[2]=='!')
            return {};

        // Check if blank: contains only delimiters
        if (raw.find_first_not_of(tokenDelims) == string::npos)
            continue;       // skip blank logical line

        break;              // got a usable "line"
    }

    // Split raw into tokens by tokenDelims
    vector<string> tokens;
    size_t start = raw.find_first_not_of(tokenDelims);
    while (start != string::npos) {
        size_t end = raw.find_first_of(tokenDelims, start);
        tokens.push_back(raw.substr(start, end - start));
        start = raw.find_first_not_of(tokenDelims, end);
    }

    return tokens;
}