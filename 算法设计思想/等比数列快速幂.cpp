#define MOD 1000000007
typedef long long LL;

LL powmod(LL a, LL b, LL mod) {
  LL ret = 1;
  a %= mod;
  while (b) {
    if (b & 1)
      ret = ret * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ret;
}
//等比数列求和
//留意a=0的情况
LL powsummod(LL a, LL b, LL mod) {
  if (b == 0)
    return 1;
  if (b & 1)
    return (powmod(a, (b + 1) / 2, MOD) + 1) * powsummod(a, b / 2, MOD) % MOD;
  else
    return ((powmod(a, b / 2, MOD) + 1) * powsummod(a, (b - 1) / 2, MOD) % MOD +
            powmod(a, b, MOD)) %
           MOD;
}
