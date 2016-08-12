/*
在求周长之前最好线看一下求面积，这样再求周长回好理解很多。
题目是POJ 1177 http://poj.org/problem?id=1177
POJ 1151也是这类问题，不过是求面积的，更简单一些。
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define CL(arr, val) memset(arr, val, sizeof(arr))
#define REP(i, n) for ((i) = 0; (i) < (n); ++(i))
#define FOR(i, l, h) for ((i) = (l); (i) <= (h); ++(i))
#define FORD(i, h, l) for ((i) = (h); (i) >= (l); --(i))
#define L(x) (x) << 1
#define R(x) (x) << 1 | 1
#define MID(l, r) (l + r) >> 1
#define Min(x, y) x < y ? x : y
#define Max(x, y) x < y ? y : x
#define E(x) (1 << (x))

typedef long long LL;
using namespace std;

const int N = 10010;

struct xLine {
  int x; //存放横坐标，对纵坐标表示的进行线段树上的染色操作
  int y1; //
  int y2; // x,y1,y2表示四边型的一条竖边，x是纵坐标，y1，y2表示上下界
  bool f; // f = true表示这条边是这个四边型的左边那条边（入边），f =
  // false表示出边
  bool operator<(const xLine l) const { //重载 <,按x从小到大排序
    return x < l.x;
  }
} Line[N];
struct xnode {
  int l, r;    //线段树的左右边界
  int len;     //线段树所表示的当前线段的长度
  int sum;     //被覆盖的长度
  int lsum;    //被覆盖过的区间数，这个在累加横边长度的时候用到，看下边的代码画画图就ok了
  int cover;   //当前线段被覆盖的次数
  bool lcover; //标记当前线段左端点是否被覆盖
  bool rcover; //标记当前线段右端点是否被覆盖
  xnode() {
    l = r = 0;
    len = sum = cover = lsum = 0;
    lcover = rcover = false;
  }
} node[N << 2];

int ind[N];
int n, m;

void build(int t, int l, int r) { //建树
  node[t].l = l;
  node[t].r = r;
  node[t].len = ind[r] - ind[l];
  node[t].sum = node[t].lsum = node[t].cover = 0;
  node[t].lcover = node[t].rcover = false;
  if (r - l > 1) { //要建成单位为1的线段形式
    int mid = MID(l, r);
    build(L(t), l, mid);
    build(R(t), mid, r);
  }
}

void Up_sum(int t) { //更新区间内被覆盖的长度
  if (node[t].cover > 0)
    node[t].sum = node[t].len;
  else if (node[t].r - node[t].l > 1)
    node[t].sum = node[L(t)].sum + node[R(t)].sum;
  else
    node[t].sum = 0;
}

void Up_lsum(int t) { //更新区间被没覆盖的线段长度
  if (node[t].cover > 0) {
    node[t].lcover = node[t].rcover = true;
    node[t].lsum = 1;
  } else if (node[t].r - node[t].l > 1) {
    node[t].lcover = node[L(t)].lcover;
    node[t].rcover = node[R(t)].rcover;
    node[t].lsum = node[L(t)].lsum + node[R(t)].lsum -
                   node[L(t)].rcover * node[R(t)].lcover;
  } else {
    node[t].lcover = node[t].rcover = false;
    node[t].lsum = 0;
  }
}

void updata(int t, int l, int r,
            bool c) { //更新线段树，c = 1表示插入线段，c = 0表示删除线段
  if (node[t].l == l && node[t].r == r) {
    if (c)
      node[t].cover++;
    else
      node[t].cover--;
    Up_sum(t);
    Up_lsum(t);
    return;
  }
  int mid = MID(node[t].l, node[t].r);
  if (r <= mid)
    updata(L(t), l, r, c);
  else if (l >= mid)
    updata(R(t), l, r, c);
  else {
    updata(L(t), l, mid, c);
    updata(R(t), mid, r, c);
  }
  Up_sum(t);
  Up_lsum(t);
}

inline int iabs(int x) { return x < 0 ? -x : x; }

int find(int x) { //给y轴上的点重新编号，传说中的离散化
  int l = 0, r = m, mid;
  while (l <= r) {
    mid = MID(l, r);
    if (ind[mid] == x)
      return mid;
    else if (ind[mid] > x)
      r = mid - 1;
    else
      l = mid + 1;
  }
  return 0;
}

int main() {
  // freopen("data.in", "r", stdin);

  int i, x1, y1, x2, y2;
  while (~scanf("%d", &n)) {
    CL(Line, 0);
    CL(node, 0);
    REP(i, n) {
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      Line[i * 2].x = x1;
      Line[i * 2].y1 = y1;
      Line[i * 2].y2 = y2;
      Line[i * 2].f = 1; //入边
      Line[i * 2 + 1].x = x2;
      Line[i * 2 + 1].y1 = y1;
      Line[i * 2 + 1].y2 = y2;
      Line[i * 2 + 1].f = 0; //出边
      ind[i * 2] = y1;
      ind[i * 2 + 1] = y2; //这里用来记录y轴上所有的坐标，用来离散话
    }
    sort(ind, ind + n * 2);
    sort(Line, Line + n * 2);
    m = 1;
    for (i = 0; i < n * 2 - 1; ++i) { //删掉多余的点
      if (ind[i] != ind[i + 1])
        ind[m++] = ind[i + 1];
    }
    /*for(i = 0; i < m; ++i)
        printf("%d ", ind[i]);
    cout << endl;*/
    build(1, 0, m - 1); //建树
    int ans = 0;
    int presum = 0;
    for (i = 0; i < 2 * n - 1; ++i) {
      if (Line[i].f)
        updata(1, find(Line[i].y1), find(Line[i].y2), 1); //入边则insert
      else
        updata(1, find(Line[i].y1), find(Line[i].y2), 0); //出边则delete

      ans += node[1].lsum * (Line[i + 1].x - Line[i].x) *
             2; //这个累加平行与x轴的边
      ans +=
          iabs(node[1].sum - presum); //累加平行与y轴的边，画画图就可以看清楚了
      presum = node[1].sum;
    }
    updata(1, find(Line[2 * n - 1].y1), find(Line[2 * n - 1].y2),
           0); //别忘了最后一个出边要删除
    ans += iabs(node[1].sum - presum);
    printf("%d\n", ans);
  }
  return 0;
}
