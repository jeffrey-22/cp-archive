int nMach;
std::vector<std::pair<int, int>> vA, vB, target;

void readInput() {
    int readIdx = 0;
    std::string line, tmp1, tmp2, tmp3, tmp4;
    while (getline(cin, line)) {
        if (line.size() <= 1) {
            nMach++; readIdx = 0;
            continue;
        }
        std::stringstream sin(line);
        // std::cout << "proc: " << line << std::endl;
        if (readIdx == 0) {
            sin >> tmp1 >> tmp2 >> tmp3 >> tmp4;
            tmp3.pop_back(); std::reverse(tmp3.begin(), tmp3.end()); 
            tmp3.pop_back(); tmp3.pop_back(); std::reverse(tmp3.begin(), tmp3.end()); 
            std::reverse(tmp4.begin(), tmp4.end()); 
            tmp4.pop_back(); tmp4.pop_back(); std::reverse(tmp4.begin(), tmp4.end()); 
            auto val1 = stoll(tmp3); auto val2 = stoll(tmp4);
            vA.push_back({val1, val2});
            readIdx++;
        } else if (readIdx == 1) {
            sin >> tmp1 >> tmp2 >> tmp3 >> tmp4;
            tmp3.pop_back(); std::reverse(tmp3.begin(), tmp3.end()); 
            tmp3.pop_back(); tmp3.pop_back(); std::reverse(tmp3.begin(), tmp3.end()); 
            std::reverse(tmp4.begin(), tmp4.end()); 
            tmp4.pop_back(); tmp4.pop_back(); std::reverse(tmp4.begin(), tmp4.end()); 
            auto val1 = stoll(tmp3); auto val2 = stoll(tmp4);
            vB.push_back({val1, val2});
            readIdx++;
        } else {
            sin >> tmp1 >> tmp3 >> tmp4;
            tmp3.pop_back(); std::reverse(tmp3.begin(), tmp3.end()); 
            tmp3.pop_back(); tmp3.pop_back(); std::reverse(tmp3.begin(), tmp3.end()); 
            std::reverse(tmp4.begin(), tmp4.end()); 
            tmp4.pop_back(); tmp4.pop_back(); std::reverse(tmp4.begin(), tmp4.end()); 
            auto val1 = stoll(tmp3); auto val2 = stoll(tmp4);
            target.push_back({val1, val2});
            readIdx = 100;
        }
    }
    nMach = target.size();
    assert(nMach == target.size());
    assert(nMach == vA.size());
    assert(nMach == vB.size());
}

void solvePartOne() {
    
    long long answer = 0;
    for (int id = 0; id < nMach; id++) {
        auto [ax, ay] = vA[id];
        auto [bx, by] = vB[id];
        auto [tx, ty] = target[id];
        long long minToken = LLONG_MAX;
        for (int x = 0; x <= 100; x++)
            for (int y = 0; y <= 100; y++) {
                if (ax * x + bx * y == tx && ay * x + by * y == ty) {
                    // std::cout << "S: " << x << " " << y << std::endl;
                    minToken = std::min(minToken, 1ll * x * 3 + y);
                }
            }
        if (minToken < LLONG_MAX) {
            answer += minToken;
        }
    }
    std::cout << "Answer = " << answer << std::endl;
}

void solvePartTwo() {
    long long answer = 0;
    for (int id = 0; id < nMach; id++) {
        long long ax, ay, bx, by, tx, ty, a, b;
        tie(ax, ay) = vA[id];
        tie(bx, by) = vB[id];
        tie(tx, ty) = target[id];
        tx += 10000000000000ll; ty += 10000000000000ll;
        long long minToken = LLONG_MAX;
        // ax * ay * a + bx * ay * b = tx * ay, ax * ay * a + ax * by * b = ax * ty
        // (bx * ay - ax * by) * b = tx * ay - ax * ty
        long long resA = (bx * ay - ax * by);
        long long resB = tx * ay - ax * ty;
        // std::cout << resB << " " << resA << std::endl;
        if (resA == 0) {
            // a * ax + b * bx = tx
            if (resB == 0) {
                long long g = __gcd(ax, bx);
                if (tx % g == 0) {
                    std::cout << "?" << ax << " " << bx << " " << tx << std::endl;
                    minToken = 0;
                }
            }
        } else if (resB % resA == 0) {
            b = resB / resA;
            // std::cout << "b = " << b << std::endl;
            long long resC, resD;
            resC = ax;
            resD = tx - b * bx;
            if (resD % resC == 0) {
                a = resD / resC;
                if (a >= 0 && b >= 0) {
                    minToken = a * 3 + b;
                }
            }
            // a = (tx - b * bx) / ax
        }
        if (minToken < LLONG_MAX) {
            answer += minToken;
        }
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