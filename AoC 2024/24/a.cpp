#include <bits/stdc++.h>
std::map<std::string, int> nameMap;
std::map<int, std::string> revNameMap;
int totNode;
std::vector<bool> isGiven;
std::vector<int> initVal, nID, givenType;
std::vector<std::tuple<int, int, int>> gate; // op, a, b. 0 and / 1 or / 2 xor
std::vector<int> xNode, yNode, zNode;

int getNodeID(std::string name, bool isInPart1) {
    if (nameMap.count(name))
        return nameMap[name];
    nameMap[name] = totNode++;
    revNameMap[totNode - 1] = name;
    nID.push_back(0);
    givenType.push_back(0);
    if (name[0] == 'x') {
        int id = (name[1] - '0') * 10 + name[2] - '0';
        while ((int)(xNode.size()) - 1 < id) xNode.push_back(-1);
        xNode[id] = totNode - 1;
        nID[nID.size() - 1] = id;
        givenType[givenType.size() - 1] = 1;
    }
    if (name[0] == 'y') {
        int id = (name[1] - '0') * 10 + name[2] - '0';
        while ((int)(yNode.size()) - 1 < id) yNode.push_back(-1);
        yNode[id] = totNode - 1;
        nID[nID.size() - 1] = id;
        givenType[givenType.size() - 1] = 2;
    }
    if (name[0] == 'z') {
        int id = (name[1] - '0') * 10 + name[2] - '0';
        while ((int)(zNode.size()) - 1 < id) zNode.push_back(-1);
        zNode[id] = totNode - 1;
        nID[nID.size() - 1] = id;
        givenType[givenType.size() - 1] = 4;
    }
    if (isInPart1)
        isGiven.push_back(true);
    else
        isGiven.push_back(false);
    gate.push_back({0, 0, 0});
    initVal.push_back(0);
    return totNode -1 ;
}
void readInput() {
    bool isPart2 = false;
    std::string line;
    while (getline(std::cin, line)) {
        if (line.size() == 0) {
            isPart2 = true;
            continue;
        }
        if (!isPart2) {
            std::string nodeName = ""; 
            for (int i = 0; i <= 2; i++) nodeName.push_back(line[i]);
            int u = getNodeID(nodeName, true);
            initVal[u] = line.back() - '0';
        } else {
            std::stringstream sin(line);
            std::string op1, op2, opter, tmp, res;
            sin >> op1 >> opter >> op2 >> tmp >> res;
            int u = getNodeID(res, false);
            int v1 = getNodeID(op1, false);
            int v2 = getNodeID(op2, false);
            int opID = 0;
            if (opter == "AND") opID = 0; else if (opter == "OR") opID = 1; else opID = 2;
            gate[u] = {opID, v1, v2};
        }
    }
    for (auto node : zNode) assert(node != -1);
}

std::vector<int> value;
std::vector<bool> isProcessed;
int recFindValue(int u) {
    if (isProcessed[u]) return value[u];
    if (isGiven[u]) return initVal[u];
    auto [op, v1, v2] = gate[u];
    int val1 = recFindValue(v1);
    int val2 = recFindValue(v2);
    if (op == 0) value[u] = val1 & val2;
    else if (op == 1) value[u] = val1 | val2;
    else value[u] = val1 ^ val2;
    
    isProcessed[u] = true;
    return value[u];
}
void solvePartOne() {
    value = std::vector<int>(totNode, 0);
    isProcessed = std::vector<bool>(totNode, false);
    std::vector<int> binNum = {};
    for (int zNodeID : zNode) {
        binNum.push_back(recFindValue(zNodeID));
        // std::cout << "got bin num: " << binNum.back() << std::endl;
    }
    std::reverse(binNum.begin(), binNum.end());

    long long answer = 0;
    for (auto v : binNum) answer = answer * 2 + v;
    std::cout << "Answer = " << answer << std::endl;
}

std::vector<int> sp;
void printNode(int u) {
    if (isGiven[u]) {
        if (givenType[u] == 1) std::cout << "x"; else std::cout << "y";
        std::cout << nID[u];
        return;
    }
    if (sp[u]) {
        if (sp[u] == 1) std::cout << "A"; 
        else if (sp[u] == 2) std::cout << "B";
        else if (sp[u] == 4) std::cout << "C";
        else if (sp[u] == 8) std::cout << "D";
        std::cout << nID[u];
        return;
    }
    auto [op, v1, v2] = gate[u];
    std::cout << "(";
    printNode(v1);
    if (op == 0) std::cout << "&"; else if (op == 1) std::cout << "|"; else std::cout << "^";
    printNode(v2);
    std::cout << ")";
}
void solvePartTwo() {
    std::swap(gate[104], gate[261]);
    std::swap(gate[157], gate[258]);
    std::swap(gate[160], gate[152]);
    std::swap(gate[180], gate[305]);
    
    sp = std::vector<int>(totNode, 0);
    std::cout << "total node = " << totNode << std::endl;
    int cntGiven = 0;
    for (auto v : isGiven) cntGiven += v;
    std::cout << "given node = " << cntGiven << "; wired node = " << totNode - cntGiven << std::endl;
    std::vector<int> A = {}, B = {};
    for (int u = 0; u < cntGiven / 2; u++) A.push_back(0), B.push_back(0);
    for (int u = 0; u < totNode; u++) {
        if (isGiven[u]) continue;
        auto [op, v1, v2] = gate[u];
        if (op == 2 && (givenType[v1] | givenType[v2]) == 3 && nID[v1] == nID[v2])
            A[nID[v1]] = u, sp[u] = 1, nID[u] = nID[v1];
        else if (op == 0 && (givenType[v1] | givenType[v2]) == 3 && nID[v1] == nID[v2])
            B[nID[v1]] = u, sp[u] = 2, nID[u] = nID[v1];
    }
    sp[B[0]] = 4;
    std::vector<int> C = {B[0]}, D = {0};
    for (int u = 0; u < cntGiven / 2 - 1; u++) C.push_back(0), D.push_back(0);
    for (int iter = 1; iter < cntGiven / 2; iter++) {
        for (int u = 0; u < totNode; u++) {
            if (isGiven[u]) continue;
            auto [op, v1, v2] = gate[u];
            if (sp[v1] > sp[v2]) std::swap(v1, v2);
            if (op == 0 && (sp[v1] | sp[v2]) == 5 && nID[v1] == nID[v2] + 1 && nID[v1] == iter)
                D[nID[v1]] = u, sp[u] = 8, nID[u] = nID[v1];
        }
        for (int u = 0; u < totNode; u++) {
            if (isGiven[u]) continue;
            auto [op, v1, v2] = gate[u];
            if (sp[v1] > sp[v2]) std::swap(v1, v2);
            if (op == 1 && (sp[v1] | sp[v2]) == 10 && nID[v1] == nID[v2] && nID[v1] == iter)
                C[nID[v1]] = u, sp[u] = 4, nID[u] = nID[v1];
        }
    }
    for (int u = 0; u < totNode; u++) {
        if (isGiven[u]) continue;
        auto [op, v1, v2] = gate[u];
        if (sp[v1] > sp[v2]) std::swap(v1, v2);
        gate[u] = {op, v1, v2};
    }
    for (int u = 0; u < totNode; u++) {
        if (isGiven[u]) continue;
        auto [op, v1, v2] = gate[u];
        if (op == 2 && (sp[v1] | sp[v2]) == 5 && nID[v1] == nID[v2] + 1 && nID[v1] == 37)
            std::cout << "A37 ^ C36: " << u << std::endl;
        if (op == 0 && (sp[v1] | sp[v2]) == 5 && nID[v1] == nID[v2] + 1 && nID[v1] == 29)
            std::cout << "A29 & C28: " << u << std::endl;
    }
    std::cout << A[33] << " " << B[37] << std::endl;
    for (int i = 0; i < zNode.size(); i++) {
        std::cout << "z" << i << "= ";
        printNode(zNode[i]); std::cout << std::endl;
    }

    /*
    
    std::swap(gate[104], gate[261]);
    std::swap(gate[157], gate[258]);
    std::swap(gate[160], gate[152]);
    std::swap(gate[180], gate[305]);
    */

    std::vector<std::string> impNames = {};
    std::vector<int> impIDs = {104, 261, 157, 258, 160, 152, 180, 305};
    for (auto id : impIDs)
        impNames.push_back(revNameMap[id]);
    std::sort(impNames.begin(), impNames.end());
    for (auto str : impNames) std::cout << str << ",";
}
/* 
z28 correct, 

A28 correct, B27 correct, C27 correct

z29 = A29 ^ C28 = (x29 ^ y29) ^ ((x28 & y28) | (A28 & C27))
but 
z30 = A30(good) & C29
D29 -> A29 ^ C28, should be A29 & C28

z28 = A28 & C27 | A28 ^ C27

z29 should be A29 ^ C28, but =D29
 Ai = xi ^ yi
 Bi = xi & yi
 A 1 / B 2 / C 4 / D 8
 C0 = B0

 Di = Ai and C(i-1)
 Ci = Bi OR Di

 zi = (Ai ^ c(i-1))
*/

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}