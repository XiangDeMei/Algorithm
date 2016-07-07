//快速幂取模B^LmodP(O(logb))
typedef long long ll;
int power(int B, int L, int P)
{
	int acc = 1, q;
	for(q = L; q; q >>= 1)
	{
		if(q & 1)	acc = (ll)acc * B % P;
		B = (ll)B * B % P;
	}
	return acc;
}