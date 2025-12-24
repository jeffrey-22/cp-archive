int gridN, gridM, totType;
std::vector<std::vector<int>> grid;
std::map<char, int> chrMp;

void readInput() {
    gridN = gridM = totType = 0; grid.clear();
    std::string line;
    chrMp.clear();
    while (getline(cin, line)) {
        gridN++;
        gridM = line.size();
        std::vector<int> row(gridM, 0);
        for (int i = 0; i < gridM; i++) {
            if (line[i] == '.') row[i] = 0;
            else {
                if (chrMp.count(line[i]) > 0)
                    row[i] = chrMp[line[i]] + 1;
                else {
                    chrMp[line[i]] = totType++;
                    row[i] = chrMp[line[i]] + 1;
                }
            }
        }
        grid.push_back(row);
    }
}

bool inBound(int x, int y) {
    return x >= 0 && x < gridN && y >= 0 && y < gridM;
}
std::pair<int, int> genNew(int ax, int ay, int bx, int by) {
    // ax, ay - bx, by - newx, newy
    return {bx * 2 - ax, by * 2 - ay};
}

void solvePartOne() {
    std::cout << gridN << "x" << gridM << " with " << totType << " types " << std::endl;
    std::vector<std::vector<int>> hasAnt(gridN, std::vector<int>(gridM, 0));
    std::vector<std::vector<std::pair<int, int>>> antPos(totType, std::vector<std::pair<int, int>>());
    int initSum = 0;
    for (int x = 0; x < gridN; x++)
        for (int y = 0; y < gridM; y++) {
            if (grid[x][y] > 0) {
                antPos[grid[x][y] - 1].push_back({x, y});
                initSum++;
            }
        }
    // std::cout << "prep done!" << std::endl;
    for (int t = 0; t < totType; t++) {
        std::map<std::pair<int, int>, bool> visited = {};
        std::vector<std::pair<int, int>> pos = antPos[t];
        for (auto ogPos : pos) visited[ogPos] = 1;
        std::vector<std::pair<int, int>> toAddPos = {};
        for (int i = 0; i < pos.size(); i++)
            for (int j = 0; j < pos.size(); j++) {
                auto [ax, ay] = pos[i];
                auto [bx, by] = pos[j];
                auto [x, y] = genNew(ax, ay, bx, by);
                if (inBound(x, y) && !visited[{x, y}]) {
                    visited[{x, y}] = 1;
                    toAddPos.push_back({x, y});
                }
            }
        for (auto [x, y] : toAddPos) hasAnt[x][y]++;
        while (toAddPos.size() > 0) {
            auto [ax, ay] = toAddPos.back(); toAddPos.pop_back();
            /*for (int i = 0; i < pos.size(); i++) {
                auto [bx, by] = pos[i];
                {
                    auto [x, y] = genNew(ax, ay, bx, by);
                    if (inBound(x, y) && !visited[{x, y}]) {
                        visited[{x, y}] = 1;
                        toAddPos.push_back({x, y});
                    }
                }
                {
                    auto [x, y] = genNew(bx, by, ax, ay);
                    if (inBound(x, y) && !visited[{x, y}]) {
                        visited[{x, y}] = 1;
                        toAddPos.push_back({x, y});
                    }
                }
            }*/
            pos.push_back({ax, ay});
        }
        
    }
    int sum = 0;
    for (int x = 0; x < gridN; x++) {
        for (int y = 0; y < gridM; y++)
            if (hasAnt[x][y])
                sum++;
    }/*
    for (int x = 0; x < gridN; x++) {
        for (int y = 0; y < gridM; y++) {
            std::cout << hasAnt[x][y];
        }
        std::cout << std::endl;
    }*/
    std::cout << "Ans = " << sum << std::endl;
}

std::vector<std::pair<int, int>> genNew2(int ax, int ay, int bx, int by) {
    int dx = bx - ax;
    int dy = by - ay;
    if (dx == 0 && dy == 0) return {{ax, ay}};
    std::vector<std::pair<int, int>> ret = {};
    for (int i = 0; ; i++) {
        int nx = bx + dx * i;
        int ny = by + dy * i;
        if (!inBound(nx, ny)) break;
        ret.push_back({nx, ny});
    }
    return ret;
}

void solvePartTwo() {
    std::cout << gridN << "x" << gridM << " with " << totType << " types " << std::endl;
    std::vector<std::vector<int>> hasAnt(gridN, std::vector<int>(gridM, 0));
    std::vector<std::vector<std::pair<int, int>>> antPos(totType, std::vector<std::pair<int, int>>());
    int initSum = 0;
    for (int x = 0; x < gridN; x++)
        for (int y = 0; y < gridM; y++) {
            if (grid[x][y] > 0) {
                antPos[grid[x][y] - 1].push_back({x, y});
                initSum++;
            }
        }
    // std::cout << "prep done!" << std::endl;
    for (int t = 0; t < totType; t++) {
        std::map<std::pair<int, int>, bool> visited = {};
        std::vector<std::pair<int, int>> pos = antPos[t];
        // for (auto ogPos : pos) visited[ogPos] = 1;
        std::vector<std::pair<int, int>> toAddPos = {};
        for (int i = 0; i < pos.size(); i++)
            for (int j = 0; j < pos.size(); j++) {
                auto [ax, ay] = pos[i];
                auto [bx, by] = pos[j];
                for (auto [x, y]: genNew2(ax, ay, bx, by))
                    if (inBound(x, y) && !visited[{x, y}]) {
                        visited[{x, y}] = 1;
                        toAddPos.push_back({x, y});
                    }
            }
        for (auto [x, y] : toAddPos) hasAnt[x][y]++;
        while (toAddPos.size() > 0) {
            auto [ax, ay] = toAddPos.back(); toAddPos.pop_back();
            /*for (int i = 0; i < pos.size(); i++) {
                auto [bx, by] = pos[i];
                {
                    auto [x, y] = genNew(ax, ay, bx, by);
                    if (inBound(x, y) && !visited[{x, y}]) {
                        visited[{x, y}] = 1;
                        toAddPos.push_back({x, y});
                    }
                }
                {
                    auto [x, y] = genNew(bx, by, ax, ay);
                    if (inBound(x, y) && !visited[{x, y}]) {
                        visited[{x, y}] = 1;
                        toAddPos.push_back({x, y});
                    }
                }
            }*/
            pos.push_back({ax, ay});
        }
        
    }
    int sum = 0;
    for (int x = 0; x < gridN; x++) {
        for (int y = 0; y < gridM; y++)
            if (hasAnt[x][y])
                sum++;
    }
    /*
    for (int x = 0; x < gridN; x++) {
        for (int y = 0; y < gridM; y++) {
            std::cout << hasAnt[x][y];
        }
        std::cout << std::endl;
    }
    */
    std::cout << "Ans = " << sum << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}