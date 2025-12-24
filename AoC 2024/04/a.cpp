int matrixN, matrixM;
std::vector<std::vector<int>> matrix;

void readInput() {
    std::string line;
    matrixN = 0; matrixM = 0; matrix.clear();
    while (getline(cin, line)) {
        matrixN++;
        matrixM = line.size();
        std::vector<int> row(matrixM, 0);
        for (int i = 0; i < matrixM; i++)
            if (line[i] == 'X') row[i] = 0;
            else if (line[i] == 'M') row[i] = 1;
            else if (line[i] == 'A') row[i] = 2;
            else if (line[i] == 'S') row[i] = 3;
        matrix.push_back(row);
    }
}

void solvePartOne() {
    std::vector<std::pair<int, int>> dir;
    std::vector<int> requiredWord = {0, 1, 2, 3};
    dir.clear();
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            dir.push_back({dx, dy});
        }
    }
    long long sum = 0;
    for (int sx = 0; sx < matrixN; sx++)
        for (int sy = 0; sy < matrixM; sy++) {
            // start at (sx, sy)
            for (auto [dx, dy] : dir) {
                std::vector<int> spelledWord;
                spelledWord.clear();
                int x = sx, y = sy;
                while (x >= 0 && x < matrixN && y >= 0 && y < matrixM) {
                    spelledWord.push_back(matrix[x][y]);
                    if (spelledWord.size() >= 4) break;
                    x += dx, y += dy;
                }
                if (spelledWord == requiredWord) {
                    sum++;
                }
            }
        }
    std::cout << "Ans = " << sum << std::endl;
}

bool matchLeftRight(int A, int B, int C, int D, int vLeft, int vRight) {
    return A == vLeft && B == vRight && C == vRight && D == vLeft;
}

bool matchUpDown(int A, int B, int C, int D, int vUp, int vDown) {
    return A == vUp && B == vUp && C == vDown && D == vDown;
}

void solvePartTwo() {
    long long sum = 0;
    for (int sx = 1; sx < matrixN - 1; sx++)
        for (int sy = 1; sy < matrixM - 1; sy++) {
            if (matrix[sx][sy] != 2) continue;
            // start at (sx, sy)
            int A, B, C, D; // 4 corners, clkwise
            A = matrix[sx - 1][sy - 1];
            B = matrix[sx - 1][sy + 1];
            C = matrix[sx + 1][sy + 1];
            D = matrix[sx + 1][sy - 1];
            int ok = 0;
            ok |= matchLeftRight(A, B, C, D, 1, 3);
            ok |= matchLeftRight(A, B, C, D, 3, 1);
            ok |= matchUpDown(A, B, C, D, 1, 3);
            ok |= matchUpDown(A, B, C, D, 3, 1);
            if (ok) sum++;
        }
    std::cout << "Ans = " << sum << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}