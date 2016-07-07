/*
	求二进制数中1的个数
	复杂度O(M) M为1的个数 
*/ 
int Count(int v){
	int num =  0;
	while(v){
		v &= (v - 1);
		num ++;
	}
	return num;
} 