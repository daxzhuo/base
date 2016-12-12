#include <stdio.h>
#include <string.h>
#include <queue>
#include <math.h>

using namespace std;
#define N 15
int id[N];
int T,n,m;
int k[N], level[N], a[N][10];
long long c[N][N], p[N];
long long res = 0;

int nob(int x){
    int res = 0;
    while (x) {
        res ++;
        x &= (x-1);
    }
    return res;
}
void dfs(int x, long long sum, int left) {
	res = max(sum, res);
	if (x == 8)
		return;
	if (x && sum + p[7] - p[x-1] <= res)
		return;
	dfs(x+1, sum, left);
	for (int i = level[id[x]] + 1; i <= k[id[x]]; ++i) {
		if (left < c[id[x]][i])
			break;
		dfs(x+1, sum + a[id[x]][i] - a[id[x]][level[id[x]]], left - c[id[x]][i]);
	}
}
int main(){
    scanf("%d",&T);
    for(int z = 1;z<=T;z++){
        scanf("%d %d",&m, &n);
        for (int i = 0; i < n; ++i) {
        	scanf("%d %d", &k[i], &level[i]);
        	for (int j = 1; j <= k[i]; ++j) {
        		scanf("%d", &a[i][j]);
        	}
        	for (int j = 2; j <= k[i]; ++j)
        		scanf("%lld", &c[i][j]);
        	for (int j = level[i]+2; j <= k[i]; ++j)
        		c[i][j] += c[i][j-1]; // become level[i] to level j's cost
        }
        // can use permutation

        for (int i = (1<<8)-1; i < (1<<n); ++i) {
        	if (nob(i) == 8) {
        		for (int j = 0, t = 0; j < n; ++j) {
        			if (1<<j & i) {
        				id[t] = j;
        				++t;
        			}
        		}
        	}
        	long long sum = 0;
        	for (int j = 0; j < 8; ++j) {
        		sum += a[id[j]][level[id[j]]];
        	}
        	// top update to cost
        	p[0] = a[id[0]][k[id[0]]] - a[id[0]][level[id[0]]];
        	for (int j = 1; j < 8; ++j)
        		p[j] = p[j-1] + a[id[j]][k[id[j]]] - a[id[j]][level[id[j]]];
        	dfs(0, sum, m);
        }

        printf("Case #%d: %lld\n",z,res);
        res = 0;
    }
    return 0;
}
