std::string input;

void readInput() {
    input = "";
    std::string str;
    while (cin >> str)
        input = input + str;
}

bool isChrNum(char c) {return c >= '0' && c <= '9';}

void solvePartOne() {
    int len = input.size();
    std::vector<int> numDig(len, 0), isNumEnd(len, 0), isNumBeg(len, 0), numVal(len, 0);
    for (int i = 0; i < len; i++) {
        int isNxtNum = 0;
        if (i == len - 1) isNxtNum = 0;
        else {
            if (isChrNum(input[i + 1])) isNxtNum = 1; else isNxtNum = 0;
        }
        if (!isNxtNum && isChrNum(input[i])) {
            isNumEnd[i] = 1;
            int leftMostIdx = 0;
            for (int j = i; j >= 0; j--) if (!isChrNum(input[j])) {leftMostIdx = j + 1; break;}
            int val = 0;
            for (int j = leftMostIdx; j <= i; j++) val = val * 10 + input[j] - '0';
            isNumBeg[leftMostIdx] = 1;
            numDig[i] = numDig[leftMostIdx] = i - leftMostIdx + 1;
            numVal[i] = numVal[leftMostIdx] = val;
        }
    }
    long long sum = 0;
    for (int i = 1; i < len - 1; i++) {
        if (input[i] == ',' && isNumEnd[i - 1] && isNumBeg[i + 1] && numDig[i - 1] >= 1 && numDig[i - 1] <= 3 && numDig[i + 1] >= 1 && numDig[i + 3] <= 3) {
            int ok = 1;
            int x = i - numDig[i - 1] - 1;
            ok &= x - 3 >= 0 && input[x] == '(' && input[x - 1] == 'l' && input[x - 2] == 'u' && input[x - 3] == 'm';
            x = i + numDig[i + 1] + 1;
            ok &= x < len && input[x] == ')';
            if (ok) {
                sum += 1ll * numVal[i - 1] * numVal[i + 1];
            }
        }
    }
    std::cout << "Ans = " << sum << std::endl;
}

void solvePartTwo() {
    int len = input.size();
    std::vector<int> numDig(len, 0), isNumEnd(len, 0), isNumBeg(len, 0), numVal(len, 0);
    for (int i = 0; i < len; i++) {
        int isNxtNum = 0;
        if (i == len - 1) isNxtNum = 0;
        else {
            if (isChrNum(input[i + 1])) isNxtNum = 1; else isNxtNum = 0;
        }
        if (!isNxtNum && isChrNum(input[i])) {
            isNumEnd[i] = 1;
            int leftMostIdx = 0;
            for (int j = i; j >= 0; j--) if (!isChrNum(input[j])) {leftMostIdx = j + 1; break;}
            int val = 0;
            for (int j = leftMostIdx; j <= i; j++) val = val * 10 + input[j] - '0';
            isNumBeg[leftMostIdx] = 1;
            numDig[i] = numDig[leftMostIdx] = i - leftMostIdx + 1;
            numVal[i] = numVal[leftMostIdx] = val;
        }
    }
    long long sum = 0;
    int isEnabled = 1;
    std::string r4 = "", r7 = "";
    for (int i = 1; i < len - 1; i++) {
        if (i >= 3) {
            r4 = "";
            for (int j = i - 3; j <= i; j++) r4.push_back(input[j]);
        }
        if (i >= 6) {
            r7 = "";
            for (int j = i - 6; j <= i; j++) r7.push_back(input[j]);
        }
        if (r4 == "do()") isEnabled = 1;
        if (r7 == "don't()") isEnabled = 0;
        // std::cout << r4 << " " << r7 << " " << isEnabled << std::endl;
        if (input[i] == ',' && isNumEnd[i - 1] && isNumBeg[i + 1] && numDig[i - 1] >= 1 && numDig[i - 1] <= 3 && numDig[i + 1] >= 1 && numDig[i + 3] <= 3) {
            int ok = 1;
            int x = i - numDig[i - 1] - 1;
            ok &= x - 3 >= 0 && input[x] == '(' && input[x - 1] == 'l' && input[x - 2] == 'u' && input[x - 3] == 'm';
            x = i + numDig[i + 1] + 1;
            ok &= x < len && input[x] == ')';
            if (ok && isEnabled) {
                sum += 1ll * numVal[i - 1] * numVal[i + 1];
            }
        }
    }
    std::cout << "Ans = " << sum << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}