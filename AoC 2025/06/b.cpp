#include "template.cpp"

int n;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    vector<string> input;
    string str;
    while (getline(cin, str)) {
        input.push_back(str);
    }
    int n = sz(input);
    string ops = input.back(); input.pop_back(); n--;
    ll ans = 0;
    // cerr << n << endl;
    for (int i = 0; i < sz(ops); i++)
        if (ops[i] == '+' || ops[i] == '*') {
            vector<ll> numbers = {};
            for (int x = i; 1; x++) {
                ll number = 0;
                for (int j = 0; j < n; j++) {
                    if (x >= sz(input[j]) || input[j][x] == ' ') continue;
                    number = number * 10 + input[j][x] - '0';
                }
                if (number == 0) break;
                numbers.push_back(number);
            }
            ll sum = 0;
            if (ops[i] == '+') {
                for (auto v : numbers) sum += v;
            } else {
                sum = 1;
                for (auto v : numbers) sum *= v;
            }
            cerr << sum << endl;
            for(auto v : numbers) cerr << v << " "; cerr << endl;
            ans += sum;
        }
    cout << ans << endl;
}