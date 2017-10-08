#include "function.h"

int main () {
	cout << "请输入明文：";
	string s;
	getline(cin, s, '\n');
	cout << "请输入8位密钥：";
	string k;
	getline(cin, k, '\n');
	k = k.substr(0, 8);
	vector<string> result = subStr(s);
	bitset<64> key = charToBitset(k.c_str());
	vector<bitset<48> > subKey = keysCome(key);
	vector<bitset<64> > allCipher;
	cout << "加密后的密文位：";
	for (int i = 0; i < result.size(); i++) {
		bitset<64> plain = charToBitset(result[i].c_str());
		bitset<64> cipher = encrypt(plain, subKey);
		allCipher.push_back(cipher);
		printCipher(cipher);
	}
	cout << endl << "解密后的密文位为：";
	for (int i = 0; i < allCipher.size(); i++) {
		bitset<64> plain = decrypt(allCipher[i], subKey);
		printCipher(plain);
	}
	cout << endl;
	system("pause");
}