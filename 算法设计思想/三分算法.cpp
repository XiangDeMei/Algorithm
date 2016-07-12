三分算法

综合于大牛们的总结：

三分算法解决凸形或者凹形函数的极值；

二分解决具有单调性的函数的极值；



mid = (Left + Right) / 2

midmid = (mid + Right) / 2;

如果mid靠近极值点，则Right = midmid；

否则(即midmid靠近极值点)，则Left = mid;

 

程序模版如下：

double cal(Type a)
{
    /* 根据题目的意思计算 */
}

void solve()
{
    double Left, Right;
    double mid, midmid;
    double mid_value, midmid_value;
    Left = MIN; Right = MAX;
    while (Left + EPS <= Right)
    {
        mid = (Left + Right) / 2;
        midmid = (mid + Right) / 2;
        if (cal(mid)>=cal(midmid)) 

            Right = midmid;
        else Left = mid;
    }
}