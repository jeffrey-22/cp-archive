int T, K;
std::vector<std::pair<std::vector<int>, int>> outputCode;

void readInput() {
    std::string line;
    while (getline(std::cin, line)) {
        T++;
        std::vector<int> codeOrder = {};
        for (auto c : line) 
            if (c == 'A') codeOrder.push_back(10); else codeOrder.push_back(c - '0');
        line.pop_back();
        int num;
        if (line[0] != 'A') num = stoi(line); else num = 1;
        outputCode.push_back({codeOrder, num});
    }
}

// x01
// 234
// ^ 0, A 1, < 2, v 3, > 4
int robotKeyMove(int curKeyPos, int moveDir) {
    if (moveDir == 0) {
        if (curKeyPos == 3) return 0;
        if (curKeyPos == 4) return 1;
        return -1;
    } else if (moveDir == 2) {
        if (curKeyPos == 1) return 0;
        if (curKeyPos == 3) return 2;
        if (curKeyPos == 4) return 3;
        return -1;
    } else if (moveDir == 3) {
        if (curKeyPos == 0) return 3;
        if (curKeyPos == 1) return 4;
        return -1;
    } else if (moveDir == 4) {
        if (curKeyPos == 0) return 1;
        if (curKeyPos == 2) return 3;
        if (curKeyPos == 3) return 4;
        return -1;
    }
    assert(false); return 0;
}

// 789
// 456
// 123
// x0A
// ^ 0, A 1, < 2, v 3, > 4
int doorKeyMove(int curKeyPos, int moveDir) {
    if (moveDir == 0) {
        if (curKeyPos >= 1 && curKeyPos <= 6) return curKeyPos + 3;
        if (curKeyPos == 0) return 2;
        if (curKeyPos == 10) return 3;
        return -1;
    } else if (moveDir == 2) {
        if (curKeyPos >= 1 && curKeyPos <= 9 && curKeyPos % 3 != 1) return curKeyPos - 1;
        if (curKeyPos == 10) return 0;
        return -1;
    } else if (moveDir == 3) {
        if (curKeyPos >= 4 && curKeyPos <= 9) return curKeyPos - 3;
        if (curKeyPos == 2) return 0;
        if (curKeyPos == 3) return 10;
        return -1;
    } else if (moveDir == 4) {
        if (curKeyPos >= 1 && curKeyPos <= 9 && curKeyPos % 3 > 0) return curKeyPos + 1;
        if (curKeyPos == 0) return 10;
        return -1;
    }
    assert(false); return 0;
}

// ^ 0, A 1, < 2, v 3, > 4
std::vector<std::tuple<int, int, int, int>> genNb(int cntCodeEntered, int keyDoor, int keyRobotA, int keyRobotB, std::vector<int>& codeOrder) {
    std::vector<std::tuple<int, int, int, int>> ret = {};
    int newKeyB;
    newKeyB = robotKeyMove(keyRobotB, 0);
    if (newKeyB != -1) ret.push_back({cntCodeEntered, keyDoor, keyRobotA, newKeyB});
    newKeyB = robotKeyMove(keyRobotB, 2);
    if (newKeyB != -1) ret.push_back({cntCodeEntered, keyDoor, keyRobotA, newKeyB});
    newKeyB = robotKeyMove(keyRobotB, 3);
    if (newKeyB != -1) ret.push_back({cntCodeEntered, keyDoor, keyRobotA, newKeyB});
    newKeyB = robotKeyMove(keyRobotB, 4);
    if (newKeyB != -1) ret.push_back({cntCodeEntered, keyDoor, keyRobotA, newKeyB});
    if (keyRobotB != 1) {
        int newKeyA = robotKeyMove(keyRobotA, keyRobotB);
        if (newKeyA != -1) ret.push_back({cntCodeEntered, keyDoor, newKeyA, keyRobotB});
    } else {
        if (keyRobotA != 1) {
            int newDoorKey = doorKeyMove(keyDoor, keyRobotA);
            if (newDoorKey != -1) ret.push_back({cntCodeEntered, newDoorKey, keyRobotA, keyRobotB});
        } else {
            int enteredDoorKey = keyDoor;
            if (cntCodeEntered < codeOrder.size() && enteredDoorKey == codeOrder[cntCodeEntered])
                ret.push_back({cntCodeEntered + 1, keyDoor, keyRobotA, keyRobotB});
        }
    }
    return ret;
}
int bfs(std::vector<int>& codeOrder) {
    // {cntCodeEntered, keyDoor, keyRobot, keyRobot}
    // ^ 0, A 1, < 2, v 3, > 4
    std::queue<std::tuple<int, int, int, int>> q = {};
    std::tuple<int, int, int, int> initPos = {0, 10, 1, 1};
    std::vector<std::vector<std::vector<std::vector<int>>>> dist = std::vector<std::vector<std::vector<std::vector<int>>>>(codeOrder.size() + 1, std::vector<std::vector<std::vector<int>>>(11, std::vector<std::vector<int>>(5, std::vector<int>(5, -1))));
    dist[0][10][1][1] = 0;
    q.push(initPos);
    while (!q.empty()) {
        auto curPos = q.front();
        auto [cntCodeEntered, keyDoor, keyRobotA, keyRobotB] = curPos;
        int curDist = dist[cntCodeEntered][keyDoor][keyRobotA][keyRobotB];
        // std::cout << curDist << " " << cntCodeEntered << " " << keyDoor << " " << keyRobotA << " " << keyRobotB << std::endl;
        q.pop();
        if (cntCodeEntered == codeOrder.size()) {
            return curDist;
        }
        int nxtDist = curDist + 1;
        for (auto nxtPos : genNb(cntCodeEntered, keyDoor, keyRobotA, keyRobotB, codeOrder)) {
            auto [nxt1, nxt2, nxt3, nxt4] = nxtPos;
            if (dist[nxt1][nxt2][nxt3][nxt4] == -1) {
                dist[nxt1][nxt2][nxt3][nxt4] = nxtDist;
                q.push(nxtPos);
            }
        }
    }
    assert(false); return -1;
}

void solvePartOne() {
    long long answer = 0;
    for (auto [codeOrder, num] : outputCode) {
        int totSteps = 0;
        totSteps = bfs(codeOrder);
        std::cout << totSteps << std::endl;
        answer += 1ll * totSteps * num;
    }
    std::cout << "Answer = " << answer << std::endl;
}

// ^ 0, A 1, < 2, v 3, > 4
// a1,a2,a3,a4 -> a1,a2,a3,a4

std::vector<std::vector<std::vector<std::vector<int>>>> movSeqTable = {
    {{{}}, {{4}}, {{3, 2}}, {{3}}, {{3, 4}, {4, 3}}},
    {{{2}}, {{}}, {{2, 3, 2}, {3, 2, 2}}, {{2, 3}, {3, 2}}, {{3}}},
    {{{4, 0}}, {{4, 0, 4}, {4, 4, 0}}, {{}}, {{4}}, {{4, 4}}},
    {{{0}}, {{4, 0}, {0, 4}}, {{2}}, {{}}, {{4}}},
    {{{2, 0}, {0, 2}}, {{0}}, {{2, 2}}, {{2}}, {{}}},
};

std::vector<std::vector<std::vector<long long>>> F;
std::vector<std::tuple<long long, int, int, int>> genNb2(int cntCodeEntered, int keyDoor, int keyRobot, std::vector<int>& codeOrder) {
    std::vector<std::tuple<long long, int, int, int>> ret = {};
    for (int newKeyRobot = 0; newKeyRobot <= 4; newKeyRobot++) {
        if (newKeyRobot == keyRobot) continue;
        ret.push_back({F[keyRobot][newKeyRobot][K - 1], cntCodeEntered, keyDoor, newKeyRobot});
    }
    if (keyRobot != 1) {
        int newDoorKey = doorKeyMove(keyDoor, keyRobot);
        if (newDoorKey != -1) ret.push_back({1, cntCodeEntered, newDoorKey, keyRobot});
    } else {
        int enteredDoorKey = keyDoor;
        if (cntCodeEntered < codeOrder.size() && enteredDoorKey == codeOrder[cntCodeEntered])
            ret.push_back({1, cntCodeEntered + 1, keyDoor, keyRobot});
    }
    return ret;
}
     
long long bfs2(std::vector<int>& codeOrder) {
    // {cntCodeEntered, keyDoor, keyRobot}
    // ^ 0, A 1, < 2, v 3, > 4
    std::priority_queue<std::tuple<long long, int, int, int>> pq = {};
    std::vector<std::vector<std::vector<long long>>> dist = std::vector<std::vector<std::vector<long long>>>(codeOrder.size() + 1, std::vector<std::vector<long long>>(11, std::vector<long long>(5, -1)));
    dist[0][10][1] = 0;
    pq.push({0, 0, 10, 1});
    while (!pq.empty()) {
        auto curPos = pq.top();
        auto [curDist, cntCodeEntered, keyDoor, keyRobot] = curPos; curDist *= -1;
        pq.pop();
        if (curDist > dist[cntCodeEntered][keyDoor][keyRobot]) continue;
        // std::cout << curDist << " " << cntCodeEntered << " " << keyDoor << " " << keyRobot << std::endl;
        if (cntCodeEntered == codeOrder.size()) {
            return curDist;
        }
        for (auto nxtPos : genNb2(cntCodeEntered, keyDoor, keyRobot, codeOrder)) {
            auto [deltaDist, nxt1, nxt2, nxt3] = nxtPos;
            // std::cout << "neighbor: " << deltaDist << " " << nxt1 << " " << nxt2 << " " << nxt3 << std::endl;
            assert(deltaDist >= 0);
            long long nxtDist = curDist + deltaDist;
            if (dist[nxt1][nxt2][nxt3] == -1 || nxtDist < dist[nxt1][nxt2][nxt3]) {
                dist[nxt1][nxt2][nxt3] = nxtDist;
                pq.push({-nxtDist, nxt1, nxt2, nxt3});
            }
        }
    }
    assert(false); return -1;
}
void solvePartTwo() {
    // K = 25;
    K = 25;
    F = std::vector<std::vector<std::vector<long long>>>(5, std::vector<std::vector<long long>>(5, std::vector<long long>(K, LLONG_MAX / 2)));
    // k = 0:
    for (int x = 0; x <= 4; x++) F[x][x][0] = 0;
    for (int moveDir = 0; moveDir <= 4; moveDir++) {
        if (moveDir == 1) continue;
        for (int x = 0; x <= 4; x++) {
            int y = robotKeyMove(x, moveDir);
            if (y != -1) F[x][y][0] = 1;
        }
    }
    for (int z = 0; z <= 4; z++)
        for (int x = 0; x <= 4; x++)
            for (int y = 0; y <= 4; y++)
                F[x][y][0] = std::min(F[x][y][0], F[x][z][0] + F[z][y][0]);
    for (int t = 1; t < K; t++) {
        // to move from xAAA -> yAAA on t-th robot, require AAA -> >AA -> ^AA -> AAA
        for (int x = 0; x <= 4; x++) {
            for (int y = 0; y <= 4; y++) {
                if (x == y) {F[x][y][t] = 0; continue;}
                long long bestMoveCost = LLONG_MAX;
                for (auto movSeqOption : movSeqTable[x][y]) {
                    long long curMoveCost = F[1][movSeqOption[0]][t - 1];
                    for (int i = 1; i < movSeqOption.size(); i++)
                        curMoveCost += F[movSeqOption[i - 1]][movSeqOption[i]][t - 1];
                    curMoveCost += F[movSeqOption.back()][1][t - 1];
                    bestMoveCost = std::min(bestMoveCost, curMoveCost + (int)(movSeqOption.size()));
                }
                F[x][y][t] = bestMoveCost;
            }
        }
    }
    
// x01
// 234
    // for (int x = 0; x <= 4; x++)
    //     for (int y = 0; y <= 4; y++) {
    //         std::cout << x << " - " << y << " cost: " << F[x][y][1] << std::endl;
    //     }
            
    long long answer = 0;
    for (auto [codeOrder, num] : outputCode) {
        long long totSteps = 0;
        totSteps = bfs2(codeOrder);
        std::cout << "Tot steps = " << totSteps << std::endl;
        answer += 1ll * totSteps * num;
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