class Solution {
public:
  int minPushBox(vector<vector<char>> &grid) {
    // bfs with person and box, the person can move in the free cells
    // person must be able to walk to the box.
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>>
        q; // store the next valid box position: it shall store: player,box,
    unordered_set<string> v;
    int src = 0, dst = 0, player = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 'S') {
          player = i * n + j;
          grid[i][j] = '.';
        }
        if (grid[i][j] == 'B') {
          src = i * n + j;
          grid[i][j] = '.';
        }
        if (grid[i][j] == 'T') {
          dst = i * n + j;
          grid[i][j] = '.';
        }
      }
    }
    if (src == dst)
      return 0;
    q.push({src, player});
    int step = 0;
    int dir[][4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (q.size()) {
      int sz = q.size();
      while (sz--) {
        auto pos = q.front();
        q.pop();
        int box = pos.first, player = pos.second;
        if (box == dst)
          return step;
        int xb = box / n, yb = box % n;
        for (auto d : dir) {
          int x = xb + d[0], y = yb + d[1]; // new box position
          int xp = xb - d[0], yp = yb - d[1];
          if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] == '#')
            continue;
          if (xp < 0 || yp < 0 || xp >= m || yp >= n || grid[xp][yp] == '#')
            continue;
          string s = to_string(box) + "," +
                     to_string(xp * n + yp); // box pos+person pos
          if (v.count(s))
            continue;
          if (can_access(grid, player, xp * n + yp, box)) {
            q.push({x * n + y,
                    box}); // make a push, box move to new, p moves to box
            v.insert(s);
          }
        }
      }
      step++;
    }
    return -1;
  }
  bool can_access(vector<vector<char>> &g, int src, int dst, int box) {
    int m = g.size(), n = g[0].size();
    // bfs shall be better than dfs
    queue<int> q;
    vector<bool> v(m * n);
    q.push(src);
    v[src] = 1;
    int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    g[box / n][box % n] = '#';
    while (q.size()) {
      int sz = q.size();
      while (sz--) {
        int p = q.front();
        q.pop();
        if (p == dst) {
          g[box / n][box % n] = '.';
          return 1;
        }
        int x0 = p / n, y0 = p % n;
        for (auto d : dir) {
          int x = x0 + d[0], y = y0 + d[1];
          if (x < 0 || y < 0 || x >= m || y >= n || g[x][y] != '.' ||
              v[x * n + y])
            continue;
          v[x * n + y] = 1;
          q.push(x * n + y);
        }
      }
    }
    g[box / n][box % n] = '.';
    return 0;
  }
};
