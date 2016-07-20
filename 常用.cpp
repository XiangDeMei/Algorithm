
//求反正弦, arg∈[-1, 1], 返回值∈[-pi/2, +pi/2] 
double asin( double arg ); 
//求正弦, arg为弧度, 弧度=角度*Pi/180.0, 返回值∈[-1, 1] 
double sin( double arg ); 
//求e的arg次方 
double exp( double arg );

/*取模运算*/
(a + b) % p = (a % p + b % p) % p 
(a * b) % p = (a % p * b % p) % p 
(a ^ b) % p = ((a % p)^b) % p 
/*
	所有数位相加
	1234 -> 1+2+3+4=10 -> 1+0=1
*/
int dig(int x) { return (x + 8) % 9 + 1; }
//最大公约数，最小公倍数
//__gcd(a,b)  GNU库函数神器好吧  
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
//组合数C(n, r)
int com(int n, int r){ // return C(n, r)
	if( n-r > r ) r = n-r; // C(n, r) = C(n, n-r)
	int i, j, s = 1;
	for( i=0, j=1; i < r; ++i ){
		s *= (n-i);
		for( ; j <= r && s%j == 0; ++j ) 
			s /= j;
	}
	return s;
}