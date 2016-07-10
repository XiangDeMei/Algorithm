void getNext(char* p, int* next)	//计算模式串p的next数组
{
	int i = 0, j = -1;
	int lenp = strlen(p);
	next[0] = -1;
	while (i < lenp)
	{
		if (j == -1 || p[i] == p[j])
		{
			++i;
			++j;
			next[i] = j;
			if (p[i] == p[j]) next[i] = next[j];	//如果回溯后的字符与当前字符一样，则需要继续回溯
		}
		else j = next[j];
	}
}

int kmp(char* s, char* p, int* next)	//在原串s中匹配模式串p，成功则返回起始位置，失败返回-1
{
	getNext(p, next);
	int i = 0, j = 0;
	int lens = strlen(s);
	int lenp = strlen(p);
	while (i < lens)
	{
		if (j == -1 || s[i] == p[j])
		{
			++i;
			++j;
		}
		else j = next[j];
		if (j == lenp) return i - lenp;
	}
	return -1;
}