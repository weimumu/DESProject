#pragma once
#include <iostream>  
#include <bitset>  
#include <string>
#include <vector>
using namespace std;

// 初始置换表IP  
int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9,  1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5,
63, 55, 47, 39, 31, 23, 15, 7 };

// 结尾置换表IP-1  
int IP_1[] = { 40, 8, 48, 16, 56, 24, 64, 32,
39, 7, 47, 15, 55, 23, 63, 31,
38, 6, 46, 14, 54, 22, 62, 30,
37, 5, 45, 13, 53, 21, 61, 29,
36, 4, 44, 12, 52, 20, 60, 28,
35, 3, 43, 11, 51, 19, 59, 27,
34, 2, 42, 10, 50, 18, 58, 26,
33, 1, 41,  9, 49, 17, 57, 25 };


// 密钥置换表，将64位密钥变成56位  
int PC_1[] = { 57, 49, 41, 33, 25, 17, 9,
1, 58, 50, 42, 34, 26, 18,
10,  2, 59, 51, 43, 35, 27,
19, 11,  3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7, 62, 54, 46, 38, 30, 22,
14,  6, 61, 53, 45, 37, 29,
21, 13,  5, 28, 20, 12, 4 };

// 压缩置换，将56位密钥压缩成48位子密钥  
int PC_2[] = { 14, 17, 11, 24,  1,  5,
3, 28, 15,  6, 21, 10,
23, 19, 12,  4, 26,  8,
16,  7, 27, 20, 13,  2,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32 };

// 产生密钥过程中每轮左移的位数  
int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };


// 扩展置换表，将 32位 扩展至 48位  
int E[] = { 32,  1,  2,  3,  4,  5,
4,  5,  6,  7,  8,  9,
8,  9, 10, 11, 12, 13,
12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32,  1 };

// S盒，每个S盒是4x16的置换表，6位 -> 4位  
int S_BOX[8][4][16] = {
	{
		{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
		{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
		{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
		{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
	},
	{
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
		{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
		{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
		{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
	},
	{
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
		{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
		{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
		{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
	},
	{
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
		{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
		{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
		{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
	},
	{
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
		{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
		{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
		{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
	},
	{
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
		{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
		{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
		{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
	},
	{
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
		{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
		{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
		{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
	},
	{
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
		{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
		{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
		{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
	}
};

// P置换，32位转32位
int P[] = { 16,  7, 20, 21,
29, 12, 28, 17,
1, 15, 23, 26,
5, 18, 31, 10,
2,  8, 24, 14,
32, 27,  3,  9,
19, 13, 30,  6,
22, 11,  4, 25 };

//Feistel 轮函数
bitset<32> feistel(bitset<32> R, bitset<48> k) {
	bitset<48> ER;
	
	for (int i = 0; i < 48; i++) {
		ER[i] = R[E[i] - 1];
	}

	ER = ER ^ k;
	int round = 0;
	bitset<32> result;
	for (int i = 0; i < 48; i = i + 6) {
		int row = ER[47 - i] * 2 + ER[47 - i - 5];
		int col = ER[47 - i - 1] * 8 + ER[47 - i - 2] * 4 + ER[47 - i - 3] * 2 + ER[47 - i - 4];
		int num = S_BOX[i / 6][row][col];
		bitset<4> fourNum(num);
		result[31 - round] = fourNum[3];
		result[31 - round - 1] = fourNum[2];
		result[31 - round - 2] = fourNum[1];
		result[31 - round - 3] = fourNum[0];
		round += 4;
	}

	bitset<32> temp = result;
	for (int i = 0; i < 32; i++) {
		result[i] = temp[P[i] - 1];
	}
	return result;
}

//密码生成工程的移位函数
bitset<28> Shift(bitset<28> k, int shift) {
	bitset<28> temp = k;
	for (int i = 27; i >= 0; i--) {
		if (i - shift < 0) {
			k[i] = temp[i - shift + 28];
		}
		else {
			k[i] = temp[i - shift];
		}
	}
	return k;
}

//16个48位密码产生的函数
vector<bitset<48> > keysCome(bitset<64> key) {
	bitset<28> leftPart;
	bitset<28> rightPart;
	bitset<48> resultKey;
	bitset<56> initKey;
	vector<bitset<48> > subKey;
	//完成64位密钥变56位的压缩置换
	for (int i = 0; i < 56; i++) {
		initKey[i] = key[PC_1[i] - 1];
	}
	//分割为左右两部分之后进行移位操作
	for (int num = 0; num < 16; num++) {
		for (int i = 0; i < 28; i++) {
			leftPart[i] = initKey[i];
		}
		for (int i = 28; i < 56; i++) {
			rightPart[i - 28] = initKey[i];
		}
		//进行移位操作
		leftPart = Shift(leftPart, shiftBits[num]);
		rightPart = Shift(rightPart, shiftBits[num]);
		for (int i = 0; i < 28; i++) {
			initKey[i] = leftPart[i];
		}
		for (int i = 28; i < 56; i++) {
			initKey[i] = rightPart[i - 28];
		}
		//合并之后之后进行压缩置换
		for (int i = 0; i < 48; i++) {
			resultKey[i] = initKey[PC_2[i] - 1];
		}
		subKey.push_back(resultKey);
	}
	return subKey;
}

//char[8] 转 64位bit
bitset<64> charToBitset(const char s[8]) {
	bitset<64> bits;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bits[i * 8 + j] = ((s[i] >> j) & 1);
		}
	}
	return bits;
}


//加密算法
bitset<64> encrypt(bitset<64>& plain, vector<bitset<48> > subKey) {
	bitset<64> cipher;
	bitset<64> currentBits;
	bitset<32> leftPart;
	bitset<32> rightPart;
	bitset<32> newLeft;
	//初始置换
	for (int i = 0; i < 64; i++) {
		currentBits[i] = plain[IP[i] - 1];
	}
	for (int i = 0; i < 32; i++) {
		leftPart[i] = currentBits[i];
	}
	for (int i = 32; i < 64; i++) {
		rightPart[i - 32] = currentBits[i];
	}
	//16次迭代操作
	for (int num = 0; num < 16; num++) {
		newLeft = rightPart;
		rightPart = leftPart ^ feistel(rightPart, subKey[num]);
		leftPart = newLeft;
	}
	//左右交换
	for (int i = 0; i < 32; i++) {
		cipher[i] = rightPart[i];
	}
	for (int i = 32; i < 64; i++) {
		cipher[i] = leftPart[i - 32];
	}
	//逆置换
	currentBits = cipher;
	for (int i = 0; i < 64; i++) {
		cipher[i] = currentBits[IP_1[i] - 1];
	}
	return cipher;
}

//解密算法
bitset<64> decrypt(bitset<64>& cipher, vector<bitset<48> > subKey) {
	bitset<64> plain;
	bitset<64> currentBits;
	bitset<32> leftPart;
	bitset<32> rightPart;
	bitset<32> newLeft;
	//基本操作与加密过程一样
	for (int i = 0; i < 64; i++) {
		currentBits[i] = cipher[IP[i] - 1];
	}

	for (int i = 0; i < 32; i++) {
		leftPart[i] = currentBits[i];
	}
	for (int i = 32; i < 64; i++) {
		rightPart[i - 32] = currentBits[i];
	}
	//注意这里密钥的顺序与加密的时候是相反的
	for (int num = 0; num < 16; num++) {
		newLeft = rightPart;
		rightPart = leftPart ^ feistel(rightPart, subKey[15 - num]);
		leftPart = newLeft;
	}

	for (int i = 0; i < 32; i++) {
		plain[i] = rightPart[i];
	}
	for (int i = 32; i < 64; i++) {
		plain[i] = leftPart[i - 32];
	}

	currentBits = plain;
	for (int i = 0; i < 64; i++) {
		plain[i] = currentBits[IP_1[i] - 1];
	}
	return plain;
}

//切割明文块
vector<string> subStr(string a) {
	vector<string> result;
	int res = a.size() % 8;
	if (res != 0) {
		string b(8 - res, ' ');
		a += b;
	}
	for (int i = 0; i < a.size(); i = i + 8) {
		string temp = a.substr(i, 8);
		result.push_back(temp);
	}
	return result;
}

//64位bit转char[8] 并且打印
void printCipher(bitset<64> cipher) {
	bitset<8> test;
	for (int i = 0; i < 64; i++) {
		test[i % 8] = cipher[i];
		if (i % 8 == 7) {
			cout << (char)test.to_ulong();
		}
	}
}