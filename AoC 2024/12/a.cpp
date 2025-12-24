int mapN, mapM;
std::vector<std::vector<int>> plant;

void readInput() {
    std::vector<int> row;
    std::string line;
    while (getline(cin, line)) {
        row.clear();
        mapN++; mapM = line.size();
        for (int i = 0; i < mapM; i++)
            row.push_back(line[i] - 'A' + 1);
        plant.push_back(row);
    }
}

std::vector<int> deltaX = {-1, 0, 1, 0}, deltaY = {0, -1, 0, 1};
std::vector<std::vector<int>> vis;

bool inBound(int x, int y) {return x >= 0 && x < mapN && y >= 0 && y < mapM; }
void dfsCount(int x, int y, long long &area, long long &perim) {
    vis[x][y] = 1;
    area++;
    for (int d = 0; d < 4; d++) {
        int nx = x + deltaX[d];
        int ny = y + deltaY[d];
        if (!inBound(nx, ny)) {
            perim++;
            continue;
        }
        if (plant[nx][ny] == plant[x][y]) {
            if (!vis[nx][ny]) dfsCount(nx, ny, area, perim);
            continue;
        }
        perim++;
    }
}

void solvePartOne() {
    vis = std::vector<std::vector<int>>(mapN, std::vector<int>(mapM, 0));

    long long answer = 0;
    for (int x = 0; x < mapN; x++)
        for (int y = 0; y < mapM; y++)
            if (!vis[x][y]) {
                long long area = 0, perim = 0;
                dfsCount(x, y, area, perim);
                answer += area * perim;
            }
    
    std::cout << "Answer = " << answer << std::endl;
}

void dfsCount2(int x, int y, long long &area, std::vector<std::tuple<int, int, int>> &fence) {
    vis[x][y] = 1;
    area++;
    for (int d = 0; d < 4; d++) {
        int nx = x + deltaX[d];
        int ny = y + deltaY[d];
        if (!inBound(nx, ny)) {
            fence.push_back({x, y, d});
            continue;
        }
        if (plant[nx][ny] == plant[x][y]) {
            if (!vis[nx][ny]) dfsCount2(nx, ny, area, fence);
            continue;
        }
        fence.push_back({x, y, d});
    }
}

void solvePartTwo() {
    std::cout << mapN << "x" << mapM << std::endl;
    vis = std::vector<std::vector<int>>(mapN, std::vector<int>(mapM, 0));

    long long answer = 0;
    for (int x = 0; x < mapN; x++)
        for (int y = 0; y < mapM; y++)
            if (!vis[x][y]) {
                long long area = 0;
                std::vector<std::tuple<int, int, int>> fence = {};
                dfsCount2(x, y, area, fence);
                long long sideCount = 0;
                
                std::set<std::tuple<int, int, int>> fenceSet = {};
                for (auto v : fence) fenceSet.insert(v);
                for (auto [ax, ay, dir] : fence) {
                    int nxtDir = (dir + 1) % 4;
                    int bx = ax + deltaX[nxtDir];
                    int by = ay + deltaY[nxtDir];
                    if (fenceSet.count({bx, by, dir}) == 0) sideCount++;
                }
                
                
                answer += area * sideCount;
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