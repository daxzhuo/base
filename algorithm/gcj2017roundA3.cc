#include <stdio.h>
#include <string.h>
#include <queue>
#include <math.h>

using namespace std;
#define N 105
int s[N];
int T,n,m;


int check(double &x){
    double sum = -s[0]*pow((1+x),n);
    for(int i = 1;i<=n;i++)
        sum += s[i] * pow((1+x),n-i);
    if(sum > 1e-13)
        return 1;
    if(sum < -1e-13)
        return -1;
    return 0;
}
int main(){
    scanf("%d",&T);
    for(int z = 1;z<=T;z++){
        scanf("%d",&n);
        for(int i = 0;i<=n;i++)
            scanf("%d",&s[i]);
        double low = -1,high = 1,mid;
        while(high-low >= 1e-13){
            mid = (low+high) * 0.5;
            int j = check(mid);
            if(j<0)
                high = mid;
            else if(j>0)
                low = mid;
            else
                break;
        }
        printf("Case #%d: %.12lf\n",z,mid);
    }
    return 0;
}
