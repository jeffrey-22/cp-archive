int n, m, sx, sy, ex, ey;
int DX[4] = {-1, 0, 1, 0}, DY[4] = {0, 1, 0, -1};
std::vector<std::vector<int>> block;

void readInput() {
    std::string line;
    while (getline(std::cin, line)) {
        n++;
        m = line.size();
        std::vector<int> row(m, 0);
        for (int i = 0; i < m; i++)
            if (line[i] == '#') row[i] = 1;
            else if (line[i] == 'S') {sx = n - 1; sy = i;}
            else if (line[i] == 'E') {ex = n - 1; ey = i;}
        block.push_back(row);
    }
}

void bfsdist(std::vector<std::vector<int>>& dist, int sx, int sy) {
    dist = std::vector<std::vector<int>>(n, std::vector<int>(m, -1));
    dist[sx][sy] = 0;
    std::queue<std::tuple<int, int>> q = {};
    q.push({sx, sy});
    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        for (int dir = 0; dir < 4; dir++) {
            int nx = cx + DX[dir], ny = cy + DY[dir];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (block[nx][ny]) continue;
            if (dist[nx][ny] == -1 || dist[cx][cy] + 1 < dist[nx][ny]) {
                dist[nx][ny] = dist[cx][cy] + 1;
                q.push({nx, ny});
            }
        }
    }
}

void solvePartOne() {
    std::cout << n << "x" << m << std::endl;
    std::vector<std::vector<int>> ds, de;
    bfsdist(ds, sx, sy);
    bfsdist(de, ex, ey);
    int mainDist = ds[ex][ey];
    long long answer = 0;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++) {
            for (int dir = 0; dir < 4; dir++) {
                int nx1 = x + DX[dir], ny1 = y + DY[dir];
                int nx2 = nx1 + DX[dir], ny2 = ny1 + DY[dir];
                if (nx2 < 0 || ny2 < 0 || nx2 >= n || ny2 >= m) continue;
                if (block[nx1][ny1] && !block[x][y] && !block[nx2][ny2]) {
                    if (ds[x][y] >= 0 && de[nx2][ny2] >= 0) {
                        int gotTime = mainDist - (ds[x][y] + de[nx2][ny2] + 2);
                        // if (gotTime >= 0) std::cout << gotTime << std::endl;
                        if (gotTime >= 100)
                            answer++;
                    }
                }
            }
        }
    std::cout << "Answer = " << answer << std::endl;
}

void solvePartTwo() {
    std::vector<std::vector<int>> ds, de;
    bfsdist(ds, sx, sy);
    bfsdist(de, ex, ey);
    int mainDist = ds[ex][ey];
    long long answer = 0;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++) {
            if (block[x][y]) continue;
            for (int dx = -20; dx <= 20; dx++) {
                int cheatTimeLeft = 20 - abs(dx);
                for (int dy = -cheatTimeLeft; dy <= cheatTimeLeft; dy++) {
                    int cheatTime = abs(dx) + abs(dy);
                    int nx = x + dx, ny = y + dy;
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                    if (block[nx][ny]) continue;
                    int gotTime = mainDist - (ds[x][y] + de[nx][ny] + cheatTime);
                    // if (gotTime == 68) std::cout << "!" << std::endl;
                    if (gotTime >= 100) answer++;
                }
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