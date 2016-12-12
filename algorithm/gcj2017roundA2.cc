#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

struct node {
	int x, y, h;
	node(int x_, int y_, int h_) : x(x_), y(y_), h(h_) {}
};
int T, n, m, res = 0;
int a[51][51], vis[51][51];
auto cmp = [](node& a, node& b) { return a.h > b.h;};
priority_queue<node, vector<node>, decltype(cmp)> pq(cmp);

void rain() {
	for (int i = 0; i < n; ++i) {
		pq.emplace(0, i, a[0][i]);
		pq.emplace(m-1, i, a[m-1][i]);
		vis[0][i] = 1;
		vis[m-1][i] = 1;
	}
	for (int i = 0; i < m; ++i) {
		pq.emplace(i, 0, a[i][0]);
		pq.emplace(i, n-1, a[i][n-1]);
		vis[i][0] = 1;
		vis[i][n-1] = 1;
	}
	int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	while (!pq.empty()) {
		node cur = pq.top();
		pq.pop();
		for (int i = 0; i < 4; ++i) {
			int x = cur.x + dir[i][0];
			int y = cur.y + dir[i][1];
			if (x < 0 || y < 0 || x > m-1 || y > n-1 || vis[x][y]) continue;
			vis[x][y] = 1;
			int h = max(a[x][y], cur.h);
			pq.emplace(x, y, h);
			res += max(0, cur.h - a[x][y]);
		}
	}
}

int main() {
	
	cin >> T;
	
	for (int ts = 0; ts < T; ++ts) {
		cin >> m >> n;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> a[i][j];
			}
		}
		memset(vis, 0, sizeof(a));
		rain();
		cout << res << endl;
		res = 0;
	}

}