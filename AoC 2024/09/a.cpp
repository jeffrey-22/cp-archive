std::vector<int> disk;
std::vector<int> fileSize;

void readInput() {
    int fileID = 1;
    std::string line;
    while (getline(cin, line)) {
        for (int i = 0; i < line.size(); i++) {
            int val = line[i] - '0';
            if (i % 2 == 0) {
                assert(val > 0);
                for (int j = 0; j < val; j++) {
                    disk.push_back(fileID);
                    fileSize.push_back(val);
                }
                fileID++;
            } else {
                for (int j = 0; j < val; j++) {
                    disk.push_back(0);
                    fileSize.push_back(val);
                }
            }
        }
    }
}

void solvePartOne() {
    int p = 0;
    int q = disk.size() - 1;
    while (p < q) {
        while (p < q && disk[p] != 0) p++;
        while (p < q && disk[q] == 0) q--;
        if (p < q) {
            swap(disk[p], disk[q]);
            p++; q--;
        }
    }
    long long answer = 0;
    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] == 0) continue;
        answer += 1ll * i * (disk[i] - 1);
    }
    std::cout << "Answer = " << answer << std::endl;
}

std::vector<std::set<int>> ind;
void insert(int p, int sz) {
    ind[sz].insert(p);
}
void remove(int p, int sz) {
    ind[sz].erase(p);
}
std::pair<int, int> query(int minspace) {
    int smallestIdx = INT_MAX;
    int curSpace;
    for (int space = minspace; space < ind.size(); space++)
        if (!ind[space].empty()) {
            int curBestIdx = *ind[space].begin();
            if (curBestIdx < smallestIdx) {
                smallestIdx = curBestIdx;
                curSpace = space;
            }
        }
    return {smallestIdx, curSpace};
}

void solvePartTwo() {
    // (space, idx): query for smallest idx such that space >= val
    ind = std::vector<std::set<int>>(10, std::set<int>());
    // Collect spaces
    int p = 0;
    while (p < disk.size()) {
        while (p < disk.size() && disk[p] >= 1) p++;
        if (p >= disk.size()) break;
        insert(p, fileSize[p]);
        p += fileSize[p];
    }
    // Fit files
    int curDiskID = disk[disk.size() - 1];
    int q = disk.size() - 1;
    // for (auto v : disk) std::cout << v << " "; std::cout << std::endl;
    while (1) {
        while (q >= 0 && (disk[q] == 0 || disk[q] != curDiskID)) q--;
        if (q < 0) break;
        q = q - fileSize[q] + 1;
        int ogSpace;
        tie(p, ogSpace) = query(fileSize[q]);
        if (p >= q) {q--; curDiskID--; continue;}
        for (int t = 0; t < fileSize[q]; t++)
            swap(disk[p + t], disk[q + t]);
        remove(p, ogSpace);
        int newSpace = ogSpace - fileSize[q];
        if (newSpace > 0) {
            insert(p + fileSize[q], newSpace);
        }
        q--; curDiskID--;
        // std::cout << "q = " << q << std::endl;
        // for (auto v : disk) std::cout << v << " "; std::cout << std::endl;
    }
    long long answer = 0;
    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] == 0) continue;
        answer += 1ll * i * (disk[i] - 1);
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