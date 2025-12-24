int mapN, mapM;
std::vector<std::vector<int>> height;

void readInput() {
    std::string line;
    while (getline(cin, line)) {
        mapN++;
        mapM = line.size();
        std::vector<int> row = {};
        for (int i = 0; i < mapM; i++)
            row.push_back(line[i] - '0');
        height.push_back(row);
    }
}

std::vector<int> deltaX = {-1, 1, 0, 0};
std::vector<int> deltaY = {0, 0, -1, 1};
const int maxCnt = 500;
std::vector<std::vector<std::bitset<maxCnt>>> f;
void solveDP(int x, int y) {
    int h = height[x][y];
    f[x][y] = 0;
    for (int d = 0; d < 4; d++) {
        int nx = x + deltaX[d];
        int ny = y + deltaY[d];
        if (nx >= 0 && ny >= 0 && nx < mapN && ny < mapM) {
            if (height[nx][ny] == h + 1)
                f[x][y] |= f[nx][ny];
        }
    }
}

void solvePartOne() {
    f = std::vector<std::vector<std::bitset<maxCnt>>>(mapN, std::vector<std::bitset<maxCnt>>(mapM, 0));
    long long answer = 0;
    int cnt9 = 0;
    for (int curH = 9; curH >= 0; curH--) {
        for (int x = 0; x < mapN; x++)
            for (int y = 0; y < mapM; y++)
                if (height[x][y] == curH) {
                    if (curH == 9) {
                        f[x][y][cnt9++] = 1;
                    }
                    else {
                        solveDP(x, y);
                        if (curH == 0) answer += (f[x][y]).count();
                    }
                }
    }
    std::cout << "cnt = " << cnt9 << std::endl;
    std::cout << "Answer = " << answer << std::endl;
}

std::vector<std::vector<long long>> f2;
void solveDP2(int x, int y) {
    int h = height[x][y];
    f2[x][y] = 0;
    for (int d = 0; d < 4; d++) {
        int nx = x + deltaX[d];
        int ny = y + deltaY[d];
        if (nx >= 0 && ny >= 0 && nx < mapN && ny < mapM) {
            if (height[nx][ny] == h - 1)
                f2[x][y] += f2[nx][ny];
        }
    }
}

void solvePartTwo() {
    f2 = std::vector<std::vector<long long>>(mapN, std::vector<long long>(mapM, 0ll));
    long long answer = 0;
    for (int curH = 0; curH <= 9; curH++) {
        for (int x = 0; x < mapN; x++)
            for (int y = 0; y < mapM; y++)
                if (height[x][y] == curH) {
                    if (curH == 0) f2[x][y] = 1;
                    else {
                        solveDP2(x, y);
                        if (curH == 9) answer += f2[x][y];
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