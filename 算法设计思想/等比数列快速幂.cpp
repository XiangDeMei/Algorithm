#define MOD 1000000007
typedef long long LL;

LL a_b_MOD_c(LL a,LL b,LL mod){
	LL ret = 1;
	a %= mod;
	while(b){
		if(b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}
//等比数列求和
//留意a=0的情况
LL dbsum(LL a,LL b,LL mod){
	if(b==0)
		return 1;
	if(b&1)
		return (a_b_MOD_c(a,(b+1)/2,MOD)+1)*dbsum(a,b/2,MOD)%MOD;
	else
		return ((a_b_MOD_c(a,b/2,MOD)+1)*dbsum(a,(b-1)/2,MOD)%MOD + a_b_MOD_c(a,b,MOD))%MOD;
} 