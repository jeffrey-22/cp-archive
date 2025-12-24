std::vector<long long> testVal;
std::vector<std::vector<long long>> num;

void readInput() {
    std::string line;
    testVal.clear(); num.clear();
    while (getline(cin, line)) {
        std::string rep = "";
        for (auto c : line) if (c != ':') rep.push_back(c);
        std::stringstream sin(rep);
        long long val;
        sin >> val; testVal.push_back(val);
        std::vector<long long> curNum = {};
        while (sin >> val) curNum.push_back(val);
        num.push_back(curNum);
    }
}

long long operate(int opter, long long lhs, long long rhs) {
    if (opter == 0) return lhs + rhs; else return lhs * rhs;
}

void solvePartOne() {
    long long ans = 0;
    for (int eqID = 0; eqID < testVal.size(); eqID++) {
        std::vector<long long> curNum = num[eqID];
        int nNum = curNum.size();
        long long curTestVal = testVal[eqID];
        std::vector<int> opter(nNum - 1);
        int existOp = 0;
        for (int opterMsk = 0; opterMsk < (1 << (nNum - 1)); opterMsk++) {
            for (int i = 0; i < nNum - 1; i++)
                opter[i] = ((opterMsk & (1 << i)) > 0) ? 1 : 0;
            long long curVal = operate(opter[0], curNum[0], curNum[1]);
            for (int i = 2; i < nNum; i++) curVal = operate(opter[i - 1], curVal, curNum[i]);
            if (curVal == curTestVal) {existOp = 1; break;}
        }
        if (existOp) ans += curTestVal;
    }
    std::cout << "Ans = " << ans << std::endl;
}

long long iPow10(int n) {
    long long ret = 1;
    while (n--) ret *= 10;
    return ret;
}

long long operate3(int opter, long long lhs, long long rhs) {
    if (opter == 0) return lhs + rhs; 
    else if (opter == 1) return lhs * rhs;
    else {
        int dRight = 0;
        for (int d = 1; ; d++) {
            long long left = iPow10(d - 1);
            long long right = iPow10(d) - 1;
            if (left <= rhs && rhs <= right) {dRight = d; break;}
        }
        return lhs * iPow10(dRight) + rhs;
    } 
}

int pow3(int n) {
    int ret = 1;
    while (n--) ret *= 3;
    return ret;
}

void solvePartTwo() {
    long long ans = 0;
    for (int eqID = 0; eqID < testVal.size(); eqID++) {
        std::vector<long long> curNum = num[eqID];
        int nNum = curNum.size();
        long long curTestVal = testVal[eqID];
        std::vector<int> opter(nNum - 1);
        int existOp = 0;
        for (int opterMsk = 0; opterMsk < (1 << (nNum - 1)); opterMsk++) {
            for (int i = 0; i < nNum - 1; i++)
                opter[i] = ((opterMsk & (1 << i)) > 0) ? 1 : 0;
            long long curVal = operate(opter[0], curNum[0], curNum[1]);
            for (int i = 2; i < nNum; i++) curVal = operate(opter[i - 1], curVal, curNum[i]);
            if (curVal == curTestVal) {existOp = 1; break;}
        }
        if (!existOp) {
            for (int opterMsk = 0; opterMsk < pow3(nNum - 1); opterMsk++) {
                int msk = opterMsk;
                for (int i = 0; i < nNum - 1; i++) {
                    opter[i] = msk % 3;
                    msk /= 3;
                }
                long long curVal = operate3(opter[0], curNum[0], curNum[1]);
                for (int i = 2; i < nNum; i++) curVal = operate3(opter[i - 1], curVal, curNum[i]);
                if (curVal == curTestVal) {existOp = 1; break;}
            }
        }
        if (existOp) ans += curTestVal;
        // std::cout << nNum - 1 << std::endl;
    }
    std::cout << "Ans = " << ans << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}