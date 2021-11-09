/*
 * @Author: your name
 * @Date: 2021-11-09 07:55:41
 * @LastEditTime: 2021-11-09 08:24:19
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /ACM/组合、快速幂、逆元.cpp
 */
//组合数（含逆元）
ll qp(ll b ,ll p){
	ll res = 1;
	while (p){
		if (p&1)res=(res*b)%mod;
		p >>= 1;
		b = (b*b)%mod;
	}
	return res;
}

ll ny(long long x){
	return qp(x,mod-2);
}

ll C(ll n , ll k){
	ll res = 1;
	for (ll i = 1 ; i <= k ; i ++){
		res = res*(n-i+1)%mod*ny(i)%mod;
	}
	return res%mod;
}
//C是入口，n是全集大小，k是要选出的数。

用一个二维数组C[N][N]来表示组合。
for (int i = 0; i < n; ++i) {
  for (int j = 0; j <= i; ++j) {
    if (!j) C[i][j] = 1;
    else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]);
  }
}
