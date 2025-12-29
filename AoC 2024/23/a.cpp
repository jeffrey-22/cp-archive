int m, totNode;
std::vector<bool> isKey;
std::map<std::string, int> nameMap;
std::map<int, std::string> revNameMap;
std::vector<std::pair<int, int>> edge;
std::vector<std::vector<int>> hasEdge, adj;

void addNode(std::string name) {
    if (nameMap.count(name) == 0) {
        nameMap[name] = totNode++;
        revNameMap[totNode - 1] = name;
        isKey.push_back(name[0] == 't' ? true : false);
    }
}
void readInput() {
    std::string line;
    while (getline(std::cin, line)) {
        std::string tmpLine = "";
        for (auto c : line) if (c == '-') tmpLine.push_back(' '); else tmpLine.push_back(c);
        std::string node1, node2;
        std::stringstream sin(tmpLine);
        sin >> node1 >> node2;
        m++;
        addNode(node1);
        addNode(node2);
        edge.push_back({nameMap[node1], nameMap[node2]});
    }
    hasEdge = std::vector<std::vector<int>>(totNode, std::vector<int>(totNode, 0));
    adj = std::vector<std::vector<int>>(totNode, std::vector<int>());
    for (auto [u, v] : edge) {
        hasEdge[u][v] = hasEdge[v][u] = 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void solvePartOne() {
    std::cout << "Graph Size: " << totNode << " " << edge.size() << std::endl;

    long long answer = 0;
    for (int x = 0; x < totNode; x++)
        for (int y = x + 1; y < totNode; y++)
            for (int z = y + 1; z < totNode; z++)
                if (isKey[x] || isKey[y] || isKey[z]) {
                    if (hasEdge[x][y] && hasEdge[y][z] && hasEdge[z][x]) answer++;
                }
    std::cout << "Answer = " << answer << std::endl;
}


typedef std::vector<std::bitset<520>> vb;
struct MaxClique {
    double limit = 0.025, pk = 0;
    struct Vertex {int i, d = 0;};
    typedef std::vector<Vertex> vv;
    vb e;
    vv V;
    std::vector<std::vector<int>> C;
    std::vector<int> qmax, q, S, old;
    void init(vv& r) {
        for (auto& v : r) v.d = 0;
        for (auto& v : r) for (auto j : r) v.d += e[v.i][j.i];
        std::sort(r.begin(), r.end(), [](auto a, auto b) {return a.d > b.d; });
        int mxD = r[0].d;
        for (int i = 0; i < r.size(); i++) r[i].d = std::min(i, mxD) + 1;
    }
    void expand(vv& R, int lev = 1) {
        S[lev] += S[lev - 1] - old[lev];
        old[lev] = S[lev - 1];
        while (R.size()) {
            if (q.size() + R.back().d <= qmax.size()) return;
            q.push_back(R.back().i);
            vv T;
            for (auto v : R) if (e[R.back().i][v.i]) T.push_back({v.i});
            if (T.size()) {
                if (S[lev]++ / ++pk < limit) init(T);
                int j = 0, mxk = 1, mnk = std::max((int)(qmax.size()) - (int)(q.size()) + 1, 1);
                C[1].clear(), C[2].clear();
                for (auto v : T) {
                    int k = 1;
                    auto f = [&](int i) {return e[v.i][i];};
                    while (any_of(C[k].begin(), C[k].end(), f)) k++;
                    if (k > mxk) mxk = k, C[mxk + 1].clear();
                    if (k < mnk) T[j++].i = v.i;
                    C[k].push_back(v.i);
                }
                if (j > 0) T[j - 1].d = 0;
                for (int k = mnk; k < mxk + 1; k++)
                    for (int i : C[k])
                        T[j].i = i, T[j++].d = k;
                expand(T, lev + 1);
            } else if (q.size() > qmax.size()) qmax = q;
            q.pop_back(), R.pop_back();
        }
    }
    std::vector<int> maxClique() {init(V), expand(V); return qmax;}
    MaxClique(vb conn) : e(conn), C(e.size() + 1), S(C.size()), old(S) {
        for (int i = 0; i < e.size(); i++) V.push_back({i});
    }
};

void solvePartTwo() {
    vb graph(totNode);
    for (auto [u, v] : edge)
        graph[u][v] = graph[v][u] = 1;
    MaxClique MC(graph);
    std::vector<int> maxC = MC.maxClique();
    std::vector<std::string> names = {};
    for (auto id : maxC)
        names.push_back(revNameMap[id]);
    std::sort(names.begin(), names.end());
    for (auto s : names)
        std::cout << s << ",";
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}