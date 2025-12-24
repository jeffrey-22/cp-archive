int mapN, mapM, startX, startY;
std::vector<std::vector<int>> isWall;
std::vector<std::vector<int>> hasVis;

void readInput() {
    mapN = mapM = 0;
    std::string line;
    isWall.clear();
    hasVis.clear();
    while (getline(cin, line)) {
        mapN++;
        mapM = line.size();
        std::vector<int> row(mapM, 0);
        for (int i = 0; i < mapM; i++) row[i] = (line[i] == '#') ? 1 : 0;
        for (int i = 0; i < mapM; i++) if (line[i] == '^') {
            startX = mapN - 1;
            startY = i;
        }
        isWall.push_back(row);
        std::vector<int> empVis(mapM, 0);
        hasVis.push_back(empVis);
    }
}

bool inBound(int curX, int curY) {return curX >= 0 && curX < mapN && curY >= 0 && curY < mapM;}

void solvePartOne() {
    std::vector<std::pair<int, int>> diffDir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // clkwise
    int curX = startX, curY = startY, nextX, nextY;
    int dir = 0;
    int totVis = 0;
    while (1) {
        if (!hasVis[curX][curY]) {
            hasVis[curX][curY] = 1;
            totVis++;
        }
        // std::cout << curX << " " << curY << " " << dir << std::endl;
        int exitProcess = 0;
        while (1) {
            auto [dx, dy] = diffDir[dir];
            nextX = curX + dx; nextY = curY + dy;
            if (!inBound(nextX, nextY)) {exitProcess = 1; break;}
            if (!isWall[nextX][nextY]) break;
            dir++; dir %= 4;
        }
        if (exitProcess) break;
        curX = nextX; curY = nextY;
    }
    std::cout << mapN << " x " << mapM << std::endl;
    std::cout << "Ans = " << totVis << std::endl;
}

bool checkLoop() {
    std::vector<std::pair<int, int>> diffDir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // clkwise
    int curX = startX, curY = startY, nextX, nextY;
    hasVis = std::vector<std::vector<int>>(mapN, std::vector<int>(mapM, 0));
    int dir = 0;
    while (1) {
        if (hasVis[curX][curY] & (1 << dir)) {
            return 1;
        } else {
            hasVis[curX][curY] |= (1 << dir);
        }
        // std::cout << curX << " " << curY << " " << dir << std::endl;
        int exitProcess = 0;
        while (1) {
            auto [dx, dy] = diffDir[dir];
            nextX = curX + dx; nextY = curY + dy;
            if (!inBound(nextX, nextY)) return 0;
            if (!isWall[nextX][nextY]) break;
            dir++; dir %= 4;
        }
        curX = nextX; curY = nextY;
    }
}

std::vector<std::pair<int, int>> findCand() {
    std::vector<std::pair<int, int>> cand; cand.clear();
    std::vector<std::pair<int, int>> diffDir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // clkwise
    int curX = startX, curY = startY, nextX, nextY;
    int dir = 0;
    int totVis = 0;
    hasVis = std::vector<std::vector<int>>(mapN, std::vector<int>(mapM, 0));
    while (1) {
        if (!hasVis[curX][curY]) {
            if (curX == startX && curY == startY) ; else cand.push_back({curX, curY});
            hasVis[curX][curY] = 1;
            totVis++;
        }
        int exitProcess = 0;
        while (1) {
            auto [dx, dy] = diffDir[dir];
            nextX = curX + dx; nextY = curY + dy;
            if (!inBound(nextX, nextY)) {exitProcess = 1; break;}
            if (!isWall[nextX][nextY]) break;
            dir++; dir %= 4;
        }
        if (exitProcess) break;
        curX = nextX; curY = nextY;
    }
    return cand;
}

void solvePartTwo() {
    int totBlock = 0;
    auto cand = findCand();
    for (auto [x, y] : cand) {
        isWall[x][y] = 1;
        if (checkLoop()) totBlock++;
        isWall[x][y] = 0;
    }
    std::cout << "Ans = " << totBlock << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}