#include<bits/stdc++.h>
using namespace std;


string padKunci(string str, string kunci)
{
	int x = str.size();

	for (int i = 0; ; i++)
	{
		if (x == i)
			i = 0;
		if (kunci.size() == str.size())
			break;
		kunci.push_back(kunci[i]);
	}
	return kunci;
}

string encrypt(string str, string kunci)
{
	string cipher_text;

	for (int i = 0; i < str.size(); i++)
	{
		
		char x = (str[i] + kunci[i]) %26;

		x += 'A';

		cipher_text.push_back(x);
	}
	return cipher_text;
}


string decrypt(string cipher_text, string kunci)
{
	string orig_text;

	for (int i = 0 ; i < cipher_text.size(); i++)
	{
		
		char x = (cipher_text[i] - kunci[i] + 26) %26;

		x += 'A';
		orig_text.push_back(x);
	}
	return orig_text;
}

int main()
{
    string str,kunci;
    cout<<"Masukan String yang pengen di encode :";
    cin>>str;
    cout<<"Masukkan Key yang ingin digunakan :";
    cin>>kunci;


	string kuncipad = padKunci(str, kunci);
	string cipher_text = encrypt(str, kuncipad);

	cout << "Hasil Enkripsi : "
		<< cipher_text << "\n";

	cout << "Hasil Dekripsi  : "
		<< decrypt(cipher_text, kuncipad);
	return 0;
}
