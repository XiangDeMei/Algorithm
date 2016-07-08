// 循环不变式： A[l] <= key &  A[r] > key
// 边界: |r - l| = 1
// 输入: A[l .... r-1]
int BinarySearch(int A[], int l, int r, int key)
{
    int m;
    while( r - l > 1 )
    {
        m = l + (r-l)/2;

        if( A[m] <= key )
            l = m;
        else
            r = m;
    }
    if( A[l] == key )
        return l;
    else
        return -1;
}