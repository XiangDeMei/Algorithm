/*
	所有数位相加
	1234 -> 1+2+3+4=10 -> 1+0=1
*/
int dig(int x) { return (x + 8) % 9 + 1; }
//最大公约数，最小公倍数
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
int lcm(int a,int b){
	return a*b/gcd(a,b);
}
//快速gcd
int kgcd(int a, int b){
	if (a == 0) return b;
	if (b == 0) return a;	
	if (!(a & 1) && !(b & 1)) return kgcd(a>>1, b>>1) << 1;
	else if (!(b & 1)) return kgcd(a, b>>1);
	else if (!(a & 1)) return kgcd(a>>1, b);
	else return kgcd(abs(a - b), min(a, b));
}
//扩展 gcd 求x, y使得gcd(a, b) = a * x + b * y;
int extgcd(int a, int b, int & x, int & y){
	if (b == 0) { x=1; y=0; return a; }
	int d = extgcd(b, a % b, x, y);	
	int t = x; x = y; y = t - a / b * y;
	return d;
}