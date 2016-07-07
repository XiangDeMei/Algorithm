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