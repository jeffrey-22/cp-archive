#include <bits/stdc++.h>

using namespace std;

int n;
int m;
int a_arr[100000 + 10];
int b_arr[100000 + 10];

int pollution_tick[100000 + 10];

unordered_map<int, vector<int>> edges;

unordered_map<int, unordered_map<int, int>> flow_edges;
unordered_map<int, unordered_map<int, int>> residual;
unordered_set<int> sources;
unordered_set<int> sinks;

unordered_set<int> unpolluted;

unordered_set<int> dfs_visited;

int maxmax = 100000;

bool dfs(int node, int end, vector<int> &path) {

  if (node == end) {
    return true;
  }
  if (dfs_visited.count(node) > 0) {
    return false;
  }
  dfs_visited.emplace(node);

  for (auto [other, res] : residual[node]) {
    if (res > 0) {
      path.push_back(other);
      if (dfs(other, end, path)) {
        return true;
      }
      path.pop_back();
    }
  }

  return false;
}

void max_flow() {

  // let 2*n be source, 2*n+1 be sinks
  // link them
  int source = 2*n;
  int sink = 2*n + 1;
  for (auto s : sources) {
    flow_edges[source][s + n] = a_arr[s];
    flow_edges[s + n][source] = 0;

    flow_edges[s + n][s] = a_arr[s];
    flow_edges[s][s + n] = 0;
  }

  for (auto s : sinks) {
    flow_edges[s][sink] = b_arr[s];
    flow_edges[sink][s] = 0;
  }

  // make none polluted nodes sinks
  for (auto u : unpolluted) {
    flow_edges[u][sink] = maxmax;
    flow_edges[sink][u] = 0;
  }

  // create residual, all flow edges have inf cap
  residual = flow_edges;

  int count = 0;
  while (true) {
    dfs_visited.clear();
    vector<int> path{source};
    bool ok = dfs(source, sink, path);
    if (!ok) {
      break;
    }

    // visit path
    int flow = INT_MAX;
    for (int i = 1; i < path.size(); ++i) {
      flow = min(flow, residual[path[i - 1]][path[i]]);
    }

    for (int i = 1; i < path.size(); ++i) {
      // update both directions
      residual[path[i - 1]][path[i]] -= flow;
      residual[path[i]][path[i - 1]] += flow;
    }

    count += flow;
  }

  cout << count;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    cin >> a_arr[i];
    pollution_tick[i] = INT_MAX;
  }
  for (int i = 0; i < n; ++i) {
    cin >> b_arr[i];
  }

  for (int i = 0; i < m; ++i) {
    int a;
    int b;
    cin >> a >> b;
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  // bfs from pollution to everything else
  unordered_set<int> pollution;
  queue<pair<int, int>> next;
  for (int i = 0; i < n; ++i) {
    if (b_arr[i] == -1) {
      next.push({0, i});
    }
  }

  while (!next.empty()) {
    auto [depth, node] = next.front();
    next.pop();

    if (pollution.count(node) > 0)
      continue;

    pollution_tick[node] = depth;
    pollution.emplace(node);

    for (auto other : edges[node]) {
      next.push({depth + 1, other});
    }
  }

  for (int i = 0; i < n; ++i) {
    if (pollution.count(i) == 0) {
      unpolluted.emplace(i);
    }
  }

  // pollution_tick[i] is the number of seconds for pollution to reach i

  for (int i = 0; i < n; ++i) {
    if (a_arr[i] > 0) {
      sources.emplace(i);
    }

    if (b_arr[i] > 0) {
      sinks.emplace(i);
    }
  }

  for (auto start : sources) {
    unordered_set<int> visited;
    queue<tuple<int, int, int>> people;
    people.push({0, start, start});
    while (!people.empty()) {
      auto [depth, node, source] = people.front();
      people.pop();

      if (visited.count(node) > 0)
        continue;

      visited.emplace(node);

      // check if can reach
      if (depth < pollution_tick[node]) {
        if (source != node) {
          flow_edges[source + n][node] = maxmax;
          flow_edges[node][source + n] = 0;
        }
      } else {
        continue;
      }

      for (auto other : edges[node]) {
        people.push({depth + 1, other, source});
      }
    }
  }

  max_flow();

  return 0;
}