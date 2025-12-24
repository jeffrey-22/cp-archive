std::vector<std::vector<int>> lvl;

void readInput() {
    std::string line;
    lvl.clear();
    while(getline(cin, line)) {
        std::stringstream sin(line);
        std::vector<int> currentLine;
        currentLine.clear();
        int val;
        while (sin >> val) {
            currentLine.push_back(val);
        }
        lvl.push_back(currentLine);
    }
}

void solvePartOne() {
    int sum = 0;
    for (auto a : lvl) {
        int isInc = 1, isDec = 1, isDifOK = 1;
        for (int i = 1; i < a.size(); i++) {
            if (a[i] >= a[i - 1]) isDec = 0;
            if (a[i] <= a[i - 1]) isInc = 0;
            int diff = abs(a[i] - a[i - 1]);
            if (diff < 1 || diff > 3) isDifOK = 0;
        }
        if ((isInc || isDec) && isDifOK) sum++;
    }
    std::cout << "Ans = " << sum << std::endl;
}

void solvePartTwo() {
    int sum = 0;
    for (auto vec : lvl) {
        std::vector<int> a;
        int isOK = 0;
        for (int x = 0; x < vec.size(); x++) {
            a.clear();
            for (int i = 0; i < vec.size(); i++)
                if (i != x) a.push_back(vec[i]);
            int isInc = 1, isDec = 1, isDifOK = 1;
            for (int i = 1; i < a.size(); i++) {
                if (a[i] >= a[i - 1]) isDec = 0;
                if (a[i] <= a[i - 1]) isInc = 0;
                int diff = abs(a[i] - a[i - 1]);
                if (diff < 1 || diff > 3) isDifOK = 0;
            }
            if ((isInc || isDec) && isDifOK) {isOK = 1; break;}
        }
        if (isOK) sum++;
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