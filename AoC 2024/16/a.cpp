int n, m, sx, sy, ex, ey, sdir;
std::vector<std::vector<int>> zone;
int deltaX[4] = {-1, 0, 1, 0}, deltaY[4] = {0, 1, 0, -1};

void readInput() {
    
    std::string line;
    while (getline(std::cin, line)) {
        n++;
        m = line.size();
        std::vector<int> row(m, 0);
        for (int i = 0; i < m; i++)
            row[i] = (line[i] == '#') ? 1 : 0;
        for (int i = 0; i < m; i++)
            if (line[i] == 'S') {
                sx = n - 1; sy = i;
            } else if (line[i] == 'E') {
                ex = n - 1; ey = i;
            }
        zone.push_back(row);
    }
    sdir = 1;
}

std::vector<std::tuple<int, int, int, int>> findNb(int dis, int x, int y, int dir) {
    // std::cout << x << " " << y << " " << dir << " " << dis << std::endl;
    int dx = deltaX[dir];
    int dy = deltaY[dir];
    std::vector<std::tuple<int, int, int, int>> ret = {};
    // std::cout << x + dx << " " << y + dy << " " << dir << " " << dis << std::endl;
    if (zone[x + dx][y + dy] == 0) ret.push_back({dis + 1, x + dx, y + dy, dir});
    ret.push_back({dis + 1000, x, y, (dir + 1) % 4});
    ret.push_back({dis + 1000, x, y, (dir + 3) % 4});
    return ret;
}
std::vector<std::vector<std::vector<int>>> dist;
std::priority_queue<std::tuple<int, int, int, int>> pq;
void dijkstra(int sx, int sy, int sdir) {
    dist = std::vector<std::vector<std::vector<int>>>(n, std::vector<std::vector<int>>(m, std::vector<int>(4, -1)));
    dist[sx][sy][sdir] = 0;
    pq = {};
    pq.push({0, sx, sy, sdir});
    while (!pq.empty()) {
        auto [curdis, curx, cury, curdir] = pq.top(); pq.pop();
        if (curdis > dist[curx][cury][curdir]) continue;
        // if (curx == ex && cury == ey) return;
        // std::cout << "pop: " << curx << " " << cury << " " << curdir << std::endl;
        for (auto [nxtdis, nxtx, nxty, nxtdir] : findNb(curdis, curx, cury, curdir)) {
            // std::cout << "going over nb" << std::endl;
            if (dist[nxtx][nxty][nxtdir] == -1 || nxtdis < dist[nxtx][nxty][nxtdir]) {
                dist[nxtx][nxty][nxtdir] = nxtdis;
                pq.push({nxtdis, nxtx, nxty, nxtdir});
            }
        }
    }
    
}

std::vector<std::tuple<int, int, int, int>> findNb2(int dis, int x, int y, int dir) {
    // std::cout << x << " " << y << " " << dir << " " << dis << std::endl;
    int dx = deltaX[(dir + 2) % 4];
    int dy = deltaY[(dir + 2) % 4];
    std::vector<std::tuple<int, int, int, int>> ret = {};
    // std::cout << x + dx << " " << y + dy << " " << dir << " " << dis << std::endl;
    if (zone[x + dx][y + dy] == 0) ret.push_back({dis + 1, x + dx, y + dy, dir});
    ret.push_back({dis + 1000, x, y, (dir + 1) % 4});
    ret.push_back({dis + 1000, x, y, (dir + 3) % 4});
    return ret;
}
std::vector<std::vector<std::vector<int>>> dist2;
void revdijkstra(int ex, int ey, int edir, int edist) {
    dist2 = std::vector<std::vector<std::vector<int>>>(n, std::vector<std::vector<int>>(m, std::vector<int>(4, -1)));
    dist2[ex][ey][edir] = 0;
    pq = {};
    pq.push({0, ex, ey, edir});
    while (!pq.empty()) {
        auto [curdis, curx, cury, curdir] = pq.top(); pq.pop();
        if (curdis > dist2[curx][cury][curdir]) continue;
        // if (curx == ex && cury == ey) return;
        // std::cout << "pop: " << curx << " " << cury << " " << curdir << std::endl;
        for (auto [nxtdis, nxtx, nxty, nxtdir] : findNb2(curdis, curx, cury, curdir)) {
            // std::cout << "going over nb" << std::endl;
            if (dist2[nxtx][nxty][nxtdir] == -1 || nxtdis < dist2[nxtx][nxty][nxtdir]) {
                dist2[nxtx][nxty][nxtdir] = nxtdis;
                pq.push({nxtdis, nxtx, nxty, nxtdir});
            }
        }
    }
    
}

void solvePartOne() {
    std::cout << n << "x" << m << std::endl;
    dijkstra(sx, sy, sdir);
    long long answer = INT_MAX;
    for (int dir = 0; dir < 4; dir++)
        if (dist[ex][ey][dir] != -1)
            answer = std::min(answer, 1ll * dist[ex][ey][dir]);
    std::cout << "Answer = " << answer << std::endl;
}

void solvePartTwo() {
    std::cout << n << "x" << m << std::endl;
    dijkstra(sx, sy, sdir);
    int edir;
    long long best = INT_MAX;
    for (int dir = 0; dir < 4; dir++)
        if (dist[ex][ey][dir] != -1)
            if (dist[ex][ey][dir] < best) {
                best = dist[ex][ey][dir];
                edir = dir;
            }
    // std::cout << best << std::endl;
    revdijkstra(ex, ey, edir, best);
    // std::cout << dist2[1][3][1] << std::endl;
    // std::cout << dist2[1][2][1] << std::endl;
    int answer = 0;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++) {
            bool isTile = false;
            // std::cout << x << " " << y << " " << zone[x][y] << std::endl;
            if (zone[x][y] == 1) continue;
            if (x == ex && y == ey) isTile = true;
            // std::cout << x << " " << y << " " << dist[x][y][1] << " " << dist2[x][y][1] << std::endl;
            for (int dir = 0; dir < 4; dir++) {
                if (dist[x][y][dir] == -1) continue;
                for (auto [nxtdis, nxtx, nxty, nxtdir] : findNb(dist[x][y][dir], x, y, dir)) {
                    if (best - nxtdis == dist2[nxtx][nxty][nxtdir]) {
                        isTile = true;
                        break;
                    }
                } 
            }
            if (isTile) {
                // std::cout << x << " " << y << " is good! " << std::endl;
                answer++;
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