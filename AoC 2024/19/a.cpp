std::vector<std::string> pattern;
std::vector<std::string> test;

void readInput() {
    bool isPart2 = false;
    std::string line;
    while (getline(std::cin, line)) {
        if (line.size() == 0) {isPart2 = true; continue;}
        if (!isPart2) {
            line.push_back(',');
            stringstream sin(line);
            std::string pat;
            while (sin >> pat) {pat.pop_back(); pattern.push_back(pat);}
        } else {
            test.push_back(line);
        }
    }
}

void solvePartOne() {
    

    long long answer = 0;
    for (auto testStr : test) {
        int n = testStr.size();
        std::vector<int> f(n, 0);
        for (int i = 0; i < n; i++) {
            for (auto patStr : pattern) {
                if (i + 1 < patStr.size()) continue;
                int matchOK = 1;
                for (int j = 0; j < patStr.size(); j++) {
                    if (testStr[i - j] != patStr[(int)(patStr.size()) - j - 1]) {
                        matchOK = 0;
                        break;
                    }
                }
                if (matchOK) {
                    int prevID = i - patStr.size();
                    int prevRes = 0;
                    if (prevID == -1) prevRes = 1; else if (prevID >= 0) prevRes = f[prevID];
                    f[i] |= prevRes;
                }
            }
        }
        if (f[n - 1]) {
            answer++;
        }
    }
    std::cout << "Answer = " << answer << std::endl;
}

void solvePartTwo() {
    

    long long answer = 0;
    for (auto testStr : test) {
        int n = testStr.size();
        std::vector<long long> f(n, 0);
        for (int i = 0; i < n; i++) {
            for (auto patStr : pattern) {
                if (i + 1 < patStr.size()) continue;
                int matchOK = 1;
                for (int j = 0; j < patStr.size(); j++) {
                    if (testStr[i - j] != patStr[(int)(patStr.size()) - j - 1]) {
                        matchOK = 0;
                        break;
                    }
                }
                if (matchOK) {
                    int prevID = i - patStr.size();
                    long long prevRes = 0;
                    if (prevID == -1) prevRes = 1; else if (prevID >= 0) prevRes = f[prevID];
                    f[i] += prevRes;
                }
            }
        }
        answer += f[n - 1];
    }
    std::cout << "Answer = " << answer << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}