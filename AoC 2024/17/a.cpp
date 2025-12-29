long long ra, rb, rc;
std::vector<long long> prog;

void readInput() {
    int nLine = 0;
    std::string line;
    while (getline(std::cin, line)) {
        if (nLine == 0) {
            std::stringstream sin(line); std::string tmp1, tmp2;
            sin >> tmp1 >> tmp2 >> ra;            
        } else if (nLine == 1) {
            std::stringstream sin(line); std::string tmp1, tmp2;
            sin >> tmp1 >> tmp2 >> rb;           
        } else if (nLine == 2) {
            std::stringstream sin(line); std::string tmp1, tmp2;
            sin >> tmp1 >> tmp2 >> rc;           
        } else if (nLine == 4) {
            std::stringstream sin(line); std::string tmp1, tmp2;
            sin >> tmp1 >> tmp2;
            std::string tmp3 = "";
            for (auto c : tmp2) if (c != ',') tmp3.push_back(c); else tmp3.push_back(' ');
            // std::cout << tmp3 << std::endl;
            std::stringstream sin2(tmp3);
            long long val;
            while (sin2 >> val) prog.push_back(val);
        }
        nLine++;
    }
}

void solvePartOne() {
    int pc = 0;
    std::string answer = "";
    while (pc < prog.size()) {
        // std::cout << prog.size() << std::endl;
        long long lv = prog[pc + 1];
        long long cv = prog[pc + 1];
        if (cv == 4) cv = ra; else if (cv == 5) cv = rb; else if (cv == 6) cv = rc;
        // std::cout << pc << " " << prog[pc] << " " << lv << " " << cv << " reg: " << ra << " " << rb << " " << rc << std::endl;
        switch (prog[pc]) {
            case 0:{
                ra = ra / (1ll << cv);
                pc += 2;
                break;}
            case 1:{
                rb ^= lv;
                pc += 2;
                break;}
            case 2:{
                rb = cv % 8;
                pc += 2;
                break;}
            case 3:{
                if (ra == 0) pc += 2; else pc = lv;
                break;}
            case 4:{
                rb ^= rc;
                pc += 2;
                break;}
            case 5:{
                char ch = (char)((cv % 8) + '0');
                answer.push_back(ch); answer.push_back(',');
                pc += 2;
                break;}
            case 6:{
                rb = ra / (1ll << cv);
                pc += 2;
                break;}
            case 7:{
                rc = ra / (1ll << cv);
                pc += 2;
                break;}
        }
        // std::cout << ra << " " << rb << " " << rc << std::endl;
    }
    answer.pop_back();
    std::cout << "Answer = " << answer << std::endl;
}

// minimum A that is x digits and end with y (most recent 16 bits)
long long F[69][100009];
long long func(long long a) {
    long long b, c;
    b = a % 8;
    b ^= 1;
    c = a / (1ll << ((a % 8) ^ 1));
    b ^= 5;
    b = b ^ c;
    return b % 8;
}

void solvePartTwo() {
    long long A = 0;
    for (int i = 1; i <= 63; i++) for (int v = 0; v <= 100000; v++) F[i][v] = LLONG_MAX;
    F[1][0] = 0; F[1][1] = 1; // i: i-th dig
    long long answer = LLONG_MAX;
    vector<long long> target;
    // target = {3, 7, 0};
    target = prog;
    for (int i = 2; i <= 62; i++) {
        for (int oldv = 0; oldv <= 65535; oldv++) {
            for (int newv = 0; newv <= 1; newv++) {
                if (F[i - 1][oldv] == LLONG_MAX) continue;
                long long preval = F[i - 1][oldv];
                long long ext = (1ll << (i - 1)); if (newv == 0) ext = 0;
                long long addval = preval + ext;
                // if (i <= 8 && func(curv) != func(addval)) {std::cout << addval << " " << curv << std::endl;}
                long long curv = addval / (1ll << std::max(0, i - 16));
                int isok = 0;
                // pc = 0: a[1:16], pc = 1: a[4:19], ..., pc = x: a[3*x:3*x+7]
                int x = -1;
                if (i >= 16 && (i - 16) % 3 == 0) x = (i - 16) / 3;
                if (x != -1) {
                    // std::cout << "curv of " << curv << " ?matches " << x << std::endl;
                    long long subval = addval / (1ll << (x * 3));
                    long long fval = func(subval);
                    // std::cout << x << std::endl;
                    if (x >= target.size()) {
                        if (addval / (1ll << (x * 3)) > 0) isok = 0; else isok = 1;
                    } else {
                        if (fval == target[x]) {
                            isok = 1;
                            // std::cout << "curv of " << curv << " matches " << x << std::endl;
                        } else isok = 0;
                    }
                } else isok = 1;
                if (isok) {
                    F[i][curv] = std::min(F[i][curv], addval);
                    // if (x == 3) {
                    // std::cout << i << " " << curv << " " << F[i][curv] << " " << std::endl;
                    // }
                }
                if (i == 62) answer = std::min(answer, F[i][curv]);
                // std::cout << i << std::endl;
            }
        }
    }
    // std::cout << func(112627  ) << std::endl;
    // std::cout << func(112627  / 8) << std::endl;
    // std::cout << func(980511  / 8 / 8) << std::endl;
    
    std::cout << "Answer = " << answer << std::endl;
}

/*
2,4, 1,1, 7,5, 1,5, 4,3, 0,3, 5,5, 3,0
while (a > 0) {
    print ((a % 8) ^ 4 ^ (a / 32)) % 8 // F(a % 256)
    a /= 8;
}

while (a > 0) {
    b = a % 8;
    b ^= 1;
    c = a / ((a % 8) ^ 1);
    b ^= 5;
    b = b ^ c;
    a = a / 8;
}

*/

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}