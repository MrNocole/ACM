//组合数（含逆元）
ll qp(ll b ,ll p){
	ll res = 1;
	while (p){
		if (p%2)res=res*b%mod;
		p /= 2;
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
