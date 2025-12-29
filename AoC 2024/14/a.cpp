#include <bits/stdc++.h>
int mapN, mapM;
std::vector<std::pair<int, int>> pos, vel;

void readInput() {
    std::string line;
    while (getline(std::cin, line)) {
        std::replace(line.begin(), line.end(), 'p', ' ');
        std::replace(line.begin(), line.end(), '=', ' ');
        std::replace(line.begin(), line.end(), 'v', ' ');
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream sin(line);
        int px, py, vx, vy;
        sin >> px >> py >> vx >> vy;
        pos.push_back({px, py});
        vel.push_back({vx, vy});
    }
}

int quadrantID(int x, int y) {
    if (x < mapM / 2 && y < mapN / 2) return 1;
    if (x > mapM / 2 && y < mapN / 2) return 2;
    if (x < mapM / 2 && y > mapN / 2) return 3;
    if (x > mapM / 2 && y > mapN / 2) return 4;
    return 0;
}

void solvePartOne() {
    mapN = 103; mapM = 101;
    // mapN = 7; mapM = 11;
    int sec = 100;
    std::vector<long long> qcnt(5, 0);
    for (int id = 0; id < pos.size(); id++) {
        auto [px, py] = pos[id];
        auto [vx, vy] = vel[id];
        // swap(px, py); swap(vx, vy);
        px += vx * sec; px %= mapM; px += mapM; px %= mapM;
        py += vy * sec; py %= mapN; py += mapN; py %= mapN;
        int qid = quadrantID(px, py);
        // std::cout << px << " " << py << " " << qid << std::endl;
        if (qid > 0) qcnt[qid]++;
    }
    long long answer = 0;
    answer = qcnt[1] * qcnt[2] * qcnt[3] * qcnt[4];
    std::cout << "Answer = " << answer << std::endl;
}

std::vector<std::vector<int>> grid, vis;
void dfs(int x, int y) {
    vis[y][x] = 1;
    for (int dx = -3; dx <= 3; dx++)
        for (int dy = -3; dy <= 3; dy++) {
            int ax = x + dx, ay = y + dy;
            if (ax < 0 || ay < 0 || ax > mapM || ay > mapN) continue;
            if (vis[ay][ax] || !grid[ay][ax]) continue;
            dfs(ax, ay);
        }
}

void solvePartTwo() {
    mapN = 103; mapM = 101;
    // mapN = 7; mapM = 11;
    std::vector<long long> qcnt(5, 0);
    int mincomp = INT_MAX;
    int critsec;
    for (int sec = 0; sec <= 2000000; sec++) {
        // std::cout << "Sec = " << sec << std::endl;
        grid = std::vector<std::vector<int>> (mapN + 9, std::vector<int>(mapN + 9, 0));
        vis = std::vector<std::vector<int>> (mapN + 9, std::vector<int>(mapN + 9, 0));
        bool hasOverlap = false;
        for (int id = 0; id < pos.size(); id++) {
            auto [px, py] = pos[id];
            auto [vx, vy] = vel[id];
            px += vx * sec; px %= mapM; px += mapM; px %= mapM;
            py += vy * sec; py %= mapN; py += mapN; py %= mapN;
            grid[py][px]++;
            if (grid[py][px] >= 2) {hasOverlap = true; break;}
        }
        if (hasOverlap) continue;
        int ncomp = 0;
        for (int x = 0; x < mapM; x++)
            for (int y = 0; y < mapN; y++)
                if (!vis[y][x] && grid[y][x]) {
                    dfs(x, y);
                    ncomp++;
                }
        if (ncomp < mincomp) {
            mincomp = ncomp;
            critsec = sec;
        }
        if (sec == 7569) {
            for (int x = 0; x < mapM; x++) {
                for (int y = 0; y < mapN; y++)
                    std::cout << grid[y][x];
                std::cout << std::endl;
            }

        }
        // std::cout << ncomp << std::endl;
    }
        std::cout << mincomp << " " << critsec << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}