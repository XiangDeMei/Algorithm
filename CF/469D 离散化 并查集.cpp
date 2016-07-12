题目链接：http://codeforces.com/contest/469/problem/D

题目的意思就是把n个不同的数分成2个集合。。 


If number x belongs to set A, then number a - x must also belong to setA. If number x belongs to set B, then number b - x must also belong to setB.
这问题，一看上去。。应该很是简单。。

当我们看到第一句话的时候，大多数情况下，都这么认为。。

如果x 和a - x 同时存在的话，那么 他们一定属于A集合。。

同理。。。x 和 b -  x 同时存在的话，那么他们一定属于B集合。。。

乍一看，没有什么样的错误。。。。

对于任何的问题，我们需要认真深入的思考。。。。- - 。。

看了题解的思路，以及我们最少应该知道的一些结论。。。

1.如果 x 和 a -  x 同时存在的话， 那么他们不一定是在A集合里面的。。为什么？

比如，如果存在ｘ，ａ－ｘ，ｂ－ｘ，ｂ－ａ＋ｘ，那么他们全部属于Ｂ集合。。。这是没有问题的。。。

这就直接的否定了我们上面的结论。。

也就是说，如果ｘ和ａ－ｘ同时存在，那么，也不一定在A或B中。。

2.如果a - x不存在，那么x一定不在A集合，也就一定在B集合里面。。

为什么？？ 因为，在A中没有与之相对应的a - x。。。。...

同样。。如果b -  x不存在，那么x一定不在B集合里面。

并查集做之。。。

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
using namespace std;

const int N = 1e5 + 5;
map<int, int> m;
int father[N], arr[N];

int find(int x)
{
    if(father[x] == x) return x;
    else return father[x] = find(father[x]);
}

void Union(int x, int y)
{
    int a = find(x), b = find(y);
    if(a == b) return ;
    father[a] = b;
}

int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    for(int i = 1; i <= n; i ++){
        cin >> arr[i];
        m[arr[i]] = i;// 离散化一下就好。。
    }
    for(int i = 1; i <= n + 2; i ++){
        father[i] = i;
    }
    for(int i = 1; i <= n; i ++){
        if(m[a - arr[i]]){
            Union(i, m[a - arr[i]]);// if x and a - x exit, then them is a union.. but not must in A.
        }
        else Union(i, n + 2);// if x exit but a - x not exit, then x not in A. must in B.
        if(m[b - arr[i]]){// if x and b - x exit, then them is a union.. same above
           Union(i, m[b - arr[i]]);
        }
        else Union(i, n + 1);
    }
    if(find(n + 1) == find(n + 2)){
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
        for(int i = 1; i <= n; i ++){
            if(i >= 2) printf(" ");
            if(find(i) ==  find(n + 1)){
                printf("0");
            }
            else printf("1");
        }
        printf("\n");
    }
    return 0;
}