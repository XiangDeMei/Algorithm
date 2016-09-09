//快速幂取模B^LmodP(O(logb))
// a^b % c = (a^2)^(b/2) % c  b为偶数
// a^b % c = (a^2)^(b/2)*a % c  b为奇数
typedef long long ll;
int power(int B, int L, int P) {
  int acc = 1, q;
  for (q = L; q; q >>= 1) {
    if (q & 1)
      acc = (ll)acc * B % P;
    B = (ll)B * B % P;
  }
  return acc;
}

typedef long long ll;
int power(ll a, ll b, int mod) {
  ll res = 1;
  ll base = a % mod;
  while (b) {
    if (b & 1)
      res = (res * base) % mod;
    base = (base * base) % mod;
    b >>= 1;
  }
  return res;
}
