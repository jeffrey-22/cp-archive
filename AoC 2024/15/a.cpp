int n, m, sx, sy;
std::vector<std::vector<int>> zone;
std::vector<int> moves; // ^ > v <
int deltaX[4] = {-1, 0, 1, 0}, deltaY[4] = {0, 1, 0, -1};
/*
void readInput() {
    bool isPart2 = false;
    std::string line;
    while (getline(std::cin, line)) {
        if (line.size() == 0) {
            isPart2 = true;
            continue;
        }
        if (!isPart2) {
            m = line.size();
            n++;
            std::vector<int> row(m, 0);
            for (int i = 0; i < m; i++) {
                if (line[i] == '#') row[i] = 1; else if (line[i] == 'O') row[i] = 2; else {
                    if (line[i] == '@') {sx = n - 1; sy = i;}
                }
            }
            zone.push_back(row);
        } else {
            for (auto c : line) {
                int val = -1;
                if (c == '^') val = 0; else if (c == '>') val = 1; else if (c == 'v') val = 2; else if (c == '<') val = 3;
                assert(val != -1);
                moves.push_back(val);
            }
        }
    }
}
*/
void readInput() {
    bool isPart2 = false;
    std::string line;
    while (getline(std::cin, line)) {
        if (line.size() == 0) {
            isPart2 = true;
            continue;
        }
        if (!isPart2) {
            m = line.size();
            n++;
            std::vector<int> row(m * 2, 0);
            for (int i = 0; i < m; i++) {
                if (line[i] == '#') row[i * 2] = row[i * 2 + 1] = 1; else if (line[i] == 'O') row[i * 2] = 2, row[i * 2 + 1] = 3; else {
                    if (line[i] == '@') {sx = n - 1; sy = i * 2;}
                }
            }
            zone.push_back(row);
        } else {
            for (auto c : line) {
                int val = -1;
                if (c == '^') val = 0; else if (c == '>') val = 1; else if (c == 'v') val = 2; else if (c == '<') val = 3;
                assert(val != -1);
                moves.push_back(val);
            }
        }
    }
    m *= 2;
}

bool pushFrom(int x, int y, int dir) {
    int dx = deltaX[dir];
    int dy = deltaY[dir];
    int curx = x + dx;
    int cury = y + dy;
    std::vector<std::pair<int, int>> pushedBox = {};
    while (1) {
        if (zone[curx][cury] == 1) {return false;} // failed
        if (zone[curx][cury] == 2) {pushedBox.push_back({curx, cury}); curx += dx, cury += dy;}
        if (zone[curx][cury] == 0) {
            std::reverse(pushedBox.begin(), pushedBox.end());
            for (auto [bx, by] : pushedBox) {
                std::swap(zone[bx][by], zone[bx + dx][by + dy]);
            }
            return true;
        }
    }
    return false;
}

void solvePartOne() {
    for (auto dir : moves) {
        int dx = deltaX[dir];
        int dy = deltaY[dir];
        bool pushRes = pushFrom(sx, sy, dir);
        if (pushRes) {
            sx += dx;
            sy += dy;
        }
    }
    long long answer = 0;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++) {
            if (zone[x][y] == 2) {
                answer += 100ll * x + y;
            }
        }

    
    std::cout << "Answer = " << answer << std::endl;
}

bool pushFrom2(int x, int y, int dir) {
    int dx = deltaX[dir];
    int dy = deltaY[dir];
    int curx = x + dx;
    int cury = y + dy;
    std::vector<std::pair<int, int>> pushedBox = {};
    if (dy != 0) {
        while (1) {
            if (zone[curx][cury] == 1) {return false;} // failed
            if (zone[curx][cury] >= 2) {pushedBox.push_back({curx, cury}); curx += dx, cury += dy;}
            if (zone[curx][cury] == 0) {
                std::reverse(pushedBox.begin(), pushedBox.end());
                for (auto [bx, by] : pushedBox) {
                    std::swap(zone[bx][by], zone[bx + dx][by + dy]);
                }
                return true;
            }
        }
        return false;
    }
    std::set<int> conY = {cury};
    while (1) {
        for (auto y : conY) if (zone[curx][y] == 1) {return false;} // failed
        bool allEmpty = true;
        for (auto y : conY) if (zone[curx][y] != 0) {allEmpty = false; break;} // not all empty
        if (allEmpty) {
            std::reverse(pushedBox.begin(), pushedBox.end());
            for (auto [bx, by] : pushedBox) {
                std::swap(zone[bx][by], zone[bx + dx][by + dy]);
            }
            return true;
        }
        std::set<int> newY = {};
        for (auto y : conY) {
            if (zone[curx][y] == 2) {newY.insert(y); newY.insert(y + 1);}
            else if (zone[curx][y] == 3) {newY.insert(y - 1); newY.insert(y);}
        }
        conY = newY;
        for (auto y : newY) pushedBox.push_back({curx, y});
        curx += dx;
        // std::cout << "now solving " << curx << " " << cury << std::endl;
    }
    return false;
}

void solvePartTwo() {
    for (auto dir : moves) {
        int dx = deltaX[dir];
        int dy = deltaY[dir];
        bool pushRes = pushFrom2(sx, sy, dir);
        if (pushRes) {
            sx += dx;
            sy += dy;
        }
    }
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (zone[x][y] == 2) {
                std::cout << '[';
            }
            if (zone[x][y] == 3) {
                std::cout << ']';
            }
            if (zone[x][y] == 1) {
                std::cout << '#';
            }
            if (zone[x][y] == 0) {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
    long long answer = 0;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++) {
            if (zone[x][y] == 2) {
                answer += 100ll * x + y;
            }
        }
    std::cout << "Answer = " << answer << std::endl;
}

int main() {
    readInput();
    // std::cout << "Solving Part One:" << std::endl;
    // solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}