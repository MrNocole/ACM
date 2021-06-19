#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<cstdio>
#include<stack>
#include<algorithm>
#define ll long long
// #define int long long
using namespace std;
const int INF = 2e9 , mod = 1e9+9;
const int N = 101000 , T = 101000;
// num划分树  cnt[i][j]第i层的第j个位置的前面有多少个节点进入了左子树（小）  sorted排序后数组
int n , m , num[20][N] , cnt[20][N] , sorted[N]; 

void build(int l ,int r ,int level) {
    if (l == r){return;}
    int m = (l+r)/2 , same = m-l+1;
    for (int i = l ; i <= r ; i ++){
        if (num[level][i] < sorted[m]) same --;
    }
    int ln = l , rn = m+1;
    for (int i = l ; i <= r ; i ++) {
        if (i == l) cnt[level][i] = 0;
        else cnt[level][i] = cnt[level][i-1];
        if (num[level][i] < sorted[m] || ((num[level][i] == sorted[m]) && same)) {
            num[level+1][ln++] = num[level][i];
            cnt[level][i] ++;
            if (num[level][i] == sorted[m]) {
                same --;
            }
        } else {
            num[level+1][rn++] = num[level][i];
        }
    }
    build(l,m,level+1);
    build(m+1,r,level+1);
}
// s-t 树上范围  l-r求解范围  
// 求[l,r]的第x大元素
int query(int level , int s , int t , int l , int r , int x){
    if (s == t) return num[level][s];
    int left;
    if (l==s) left = 0;
    else left=cnt[level][l-1];
    int tot = cnt[level][r]-left;
    if (tot >= x) {
        return query(level+1,s,(s+t)/2,s+left,s+cnt[level][r]-1,x);
    } else {
        int tmp = (s+t)/2+1+(l-s-left);
        return query(level+1,(s+t)/2+1,t,tmp,tmp+r-l+1-tot-1,x-tot);
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 1 ; i <= n ; i ++) {
        scanf("%d",&num[0][i]);
        sorted[i] = num[0][i];
    }
    sort(sorted+1,sorted+1+n);
    build(1,n,0);
    // for (int i = 0 ; i <= 10 ; i ++) {
        // for (int j = 1 ; j <= n ; j ++) {
            // printf("%d ",num[i][j]);
        // }
        // printf("\n");
        // for (int j = 1 ; j <= n ; j ++) {
            // printf("%d ",cnt[i][j]);
        // }
        // printf("\n");
    // }
    int l , r , x;
    for (int i = 1 ; i <= m ; i ++) {
        scanf("%d%d%d",&l,&r,&x);
        printf("%d\n",query(0,1,n,l,r,x));
    }
}
