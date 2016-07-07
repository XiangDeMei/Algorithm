// cf 678D - Iterated Linear Function
// g(n)=A*g(n-1)+B   
// {g(n),B}=A*{g(n-1),B}构造得到A
#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;

const int MAXN = 2;
typedef long long LL;
typedef struct
{
    LL mat[MAXN][MAXN];
} Matrix;
const LL MOD = 1e9+7;
///求得的矩阵
Matrix P;
///单位矩阵
Matrix I = {1, 0,
            0, 1,
           };
///矩阵乘法
Matrix Mul_Matrix(Matrix a, Matrix b)
{
    Matrix c;
    for(int i=0; i<MAXN; i++)
    {
        for(int j=0; j<MAXN; j++)
        {
            c.mat[i][j] = 0;
            for(int k=0; k<MAXN; k++)
            {
                c.mat[i][j] += (a.mat[i][k] * b.mat[k][j]) % MOD;
                c.mat[i][j] %= MOD;
            }
        }
    }
    return c;
}
///矩阵的快速幂
Matrix quick_Mod_Matrix(LL m)
{
    Matrix ans = I, b = P;
    while(m)
    {
        if(m & 1)
            ans = Mul_Matrix(ans, b);
        m>>=1;
        b = Mul_Matrix(b, b);
    }
    return ans;
}
int main()
{
    LL A, B, n, x;
    while(cin>>A>>B>>n>>x)
    {
        P.mat[0][0] = A, P.mat[0][1] = 0;
        P.mat[1][0] = 1, P.mat[1][1] = 1;
        Matrix tmp = quick_Mod_Matrix(n);
        LL ans = (x*tmp.mat[0][0]%MOD + B*tmp.mat[1][0]%MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}