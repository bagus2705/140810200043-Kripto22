/**
 * Nama :Johanes Bagus Prasetyo
 * NPM :140810200043
 * Kelas :A
 */
#include<iostream>
#include<string.h>
using namespace std;
void enkripsi(string msg,int key){
   char ch;
   for(int i = 0; msg[i] != '\0'; ++i) {
         ch = msg[i];
         if (ch >= 'a' && ch <= 'z'){
            ch = ch + key;
            if (ch > 'z') {
               ch = ch - 'z' + 'a' - 1;
            }  
            msg[i] = ch;
         }
            else if (ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            if (ch > 'Z'){
               ch = ch - 'Z' + 'A' - 1;
            }
            msg[i] = ch;
         }
} cout<<"Pesan Enkripsi :" <<msg;
}
void dekripsi(string msg,int key){
char ch;
      for(int i = 0; msg[i] != '\0'; ++i) {
         ch = msg[i];
         if(ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if(ch < 'a'){
               ch = ch + 'z' - 'a' + 1;
            }
            msg[i] = ch;
         }
         else if(ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            if(ch < 'A') {
               ch = ch + 'Z' - 'A' + 1;
            }
            msg[i] = ch;
         }
      }
      cout<<"Pesan Dekripsi :" <<msg;
}
int main() {
   cout<<"Masukan Pesan:\n";
   char pesan[100];
   cin >> pesan; 
   int i, j, panjang,pilihan,key;
   char ch;
   cout << "Masukan key: ";
   cin >> key; 
   panjang = strlen(pesan);
   cout<<"Masukan  pilihan \n1. Enkripsi \n2. Dekripsi \n";
   cin>>pilihan;
   if (pilihan==1){ 
      enkripsi(pesan,key);
}
   else if (pilihan == 2) { 
      dekripsi(pesan,key);
   }
}
