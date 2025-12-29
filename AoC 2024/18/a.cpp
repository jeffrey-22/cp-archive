int n, m, k, pcnt;
std::vector<std::pair<int, int>> pos;

void readInput() {

    std::string line;
    n = m = 7; pcnt = 12;
    while (getline(std::cin, line)) {
        k++;
        std::string tmpLine = "";
        for (auto c : line) if (c == ',') tmpLine.push_back(' '); else tmpLine.push_back(c);
        std::stringstream sin(tmpLine);
        int x, y; 
        sin >> x >> y;
        if (x > 6) n = m = 71, pcnt = 1024;
        pos.push_back({x, y});
    }
}

std::vector<std::vector<int>> block;
std::vector<std::vector<int>> f;
int DX[4] = {-1, 0, 1, 0}, DY[4] = {0, 1, 0, -1};
int bfs() {
    f = std::vector<std::vector<int>>(n, std::vector<int>(m, -1));
    int sx = 0, sy = 0, st = 0;
    f[sx][sy] = st;
    std::queue<std::tuple<int, int, int>> q = {};
    q.push({sx, sy, st});
    while (!q.empty()) {
        auto [x, y, t] = q.front(); q.pop();
        if (t > f[x][y]) continue;
        for (int dir = 0; dir < 4; dir++) {
            int curx = x + DX[dir], cury = y + DY[dir];
            int newt = t + 1;
            if (curx < 0 || cury < 0 || curx >= n || cury >= m) continue;
            if (block[curx][cury] > 0 && block[curx][cury] <= newt) continue;
            if (f[curx][cury] == -1 || f[curx][cury] > newt) {
                f[curx][cury] = newt;
                q.push({curx, cury, newt});
            }
        }
    }
    return f[n - 1][m - 1];
}
void solvePartOne() {
    block = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
    for (int t = 0; t < pos.size(); t++) {
        auto [x, y] = pos[t];
        block[x][y] = t < pcnt ? 1 : t + 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            std::cout << (block[i][j] == 1) ? '#' : '.';
        std::cout << std::endl;
    }

    long long answer = 0;
    answer = bfs();
    std::cout << "Answer = " << answer << std::endl;
}

void solvePartTwo() {
    block = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
    for (int t = 0; t < pos.size(); t++) {
        auto [x, y] = pos[t];
        block[x][y] = 1;
        if (bfs() == -1) {std::cout << x << "," << y << std::endl; break;}
    }
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}