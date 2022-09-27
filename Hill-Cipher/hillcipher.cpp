#include <iostream>
#include<bits/stdc++.h>
using namespace std ;
 
int key[3][3] ; 
 
int mod26(int x) //cari mod 26 
{
    return x >= 0 ? (x%26) : 26-(abs(x)%26) ; 
}
 

int cariDet(int m[3][3] , int n)//cari determinan matriks
{
    int det;
    if(n == 2) 
    {
        det = m[0][0] * m[1][1] - m[0][1]*m[1][0] ;
    }
    return mod26(det);
}
 
int cariDetInverse(int R , int D = 26) //cari inverse determinan
{
    int i = 0 ;
    int p[100] = {0,1};
    int q[100] = {0} ; 
 
    while(R!=0) 
    {
        q[i] = D/R ;
        int oldD = D ;
        D = R ;
        R = oldD%R ;
        if(i>1)
        {
            p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
        }
        i++ ;
    }
    if (i == 1) return 1;
    else return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
}

int gcd(int m, int n){//cari gcd
    if (n > m)
        swap(m,n);
    do{
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);
    
    return m;
}
 
void multiplyMatrices(int a[1000][3] , int baris1 , int kolom1 ,  int b[1000][3] , int baris2 , int kolom2 , int hasil[1000][3])//kali matriks
{
    for(int i=0 ; i < baris1 ; i++)
    {
        for(int j=0 ; j < kolom2 ; j++)
        {
            for(int k=0 ; k < baris2 ; k++)
            {
                hasil[i][j] += a[i][k]*b[k][j] ;
            }
            hasil[i][j] = mod26(hasil[i][j]) ;
        }
    }
}


void cariInverse(int m[3][3] , int n , int m_inverse[3][3] )//cari inverse matriks
{
    int adj[3][3] = {0};//inisiasi
 
    int det = cariDet(m , n); 
    int detInverse = cariDetInverse(det);
 
    if(n==2) //buat adjoin
    {
        adj[0][0] = m[1][1];
        adj[1][1] = m[0][0];
        adj[0][1] = -m[0][1];
        adj[1][0] = -m[1][0];
    }
 
    for(int i=0; i<n ; i++)
    {
        for(int j=0; j<n ; j++)
        {
            m_inverse[i][j] = mod26(adj[i][j] * detInverse) ;//buat inverse
        }
    }
}
 

string encrypt(string pt, int n)//enkripsi
{
    int P[1000][3] = {0} ; 
    int C[1000][3] = {0} ; 
    int ptIter = 0  ;//iteasi
 
    while(pt.length()%n != 0)//padding
    {
        pt += "x" ;  
    }
    int row = (pt.length())/n; 
 
    for(int i=0; i<row ; i++)
    {
        for(int j=0; j<n; j++)
        {
            P[i][j] = pt[ptIter++]-'a' ;
        }
    }
 
 
    multiplyMatrices(P, row , n , key , n , n , C) ;
 
    string ct = "" ;//hasil cipher
    for(int i=0 ; i<row ; i++)
    {
        for(int j=0 ; j<n ;j++)
        {
            ct += (C[i][j] + 'a');
        }
    }//matriks ditambah a buat jadi huruf
    return ct ;
}
 

string decrypt(string ct, int n)//dekripsi
{
    int P[1000][3] = {0} ; //inisiasi
    int C[1000][3] = {0} ; 
    int ctIter = 0 ;
 
    int row = ct.length()/n; 
 
    for(int i=0; i<row ; i++)
    {
        for(int j=0; j<n; j++)
        {
            C[i][j] = ct[ctIter++]-'a' ;
        }
    }
 
    int k_inverse[3][3] = {0};
 
    cariInverse(key, n , k_inverse);//inverse   
    multiplyMatrices(C, row , n , k_inverse , n , n , P) ;//kali matriks
 
    string pt = "" ;//hasil plain teks
    for(int i = 0 ; i<row ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            pt += (P[i][j] + 'a');
        }
    }//ditambah a buat jadi huruf
    return pt ;
}
void cariKey(){
    string plainteks,cipherteks;//inisiasi
    int key[2][2],det,detInv,adj[2][2],inversPlain[2][2],matriksPlain[2][2],matriksCip[2][2],counter;
    int p,c;
    int transpose[2][2];

    cout << "Masukkan Plainteks (gunakan kata panjang kelipatan 2): ";
    cin.ignore();
    getline(cin,plainteks);
   
    counter = 0;
    for(int i = 0; i < 2; i++){//ubh ke kapital
        for(int j = 0; j < 2; j++){
            p = toupper(plainteks[counter]) - 65;
            matriksPlain[i][j] = p;
            counter++;
        }
    }
    
    
    cout << "Masukkan Cipherteks(gunakan kata panjang kelipatan2) : ";
    getline(cin,cipherteks);
    
    counter = 0;
    for(int i = 0; i < 2; i++){//ubh ke kapital
        for(int j = 0; j < 2; j++){
            c = toupper(cipherteks[counter]) - 65;
            matriksCip[i][j] = c;
            counter++;
        }
    }
    
    det = (matriksPlain[0][0] * matriksPlain[1][1]) - (matriksPlain[0][1] * matriksPlain[1][0]);//determinan
    if(gcd(det,26)==1){
        detInv = cariDetInverse(det, 26);//inverse
        

        adj[0][0] = matriksPlain[1][1];//adjoin
        adj[0][1] = (-1)*matriksPlain[0][1];
        adj[1][0] = (-1)*matriksPlain[1][0];
        adj[1][1] = matriksPlain[0][0];
        
        for(int i = 0; i < 2; i++){//cari invers plain teks
            for(int j = 0; j < 2; j++){
                inversPlain[i][j] = detInv * adj[i][j];
                if(inversPlain[i][j] < 0){
                    inversPlain[i][j] = 26 - (abs(inversPlain[i][j])%26); 
                }else{
                    inversPlain[i][j] = inversPlain[i][j];
                    inversPlain[i][j] = inversPlain[i][j] % 26;
                }
            } 
        }
        
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){//cari key
                key [i][j] = 0;
                for(int k = 0; k < 2; k++){
                    key [i][j] += (inversPlain[i][k] * matriksCip[k][j]);
                }
                key [i][j] %= 26;
            }
        }
        
 
        for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){//transpors key
            transpose[j][i] = key[i][j];
            }
        }
    
        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){//hasil
                cout << (transpose[i][j]) << "\t";
            }
            cout <<endl;
        }       
    }else{
        cout << "Key tidak ditemukan" <<endl<<endl;
    }
}
 
int main(void)
{
    bool menuActive = true;
    string pt, ct;
    int n ;
    int pilih;
 
    while(menuActive){
        cout << "\nProgram Hill Cipher" <<endl;
        cout << "1. Enkripsi" <<endl;
        cout << "2. Dekripsi" <<endl;
        cout << "3. cari Key" <<endl;
        cout << "4. Exit" <<endl;
        cout << "Pilih Menu : "; cin >> pilih;
        switch(pilih){
            case 1:
                    cout << "Masukkan kata : " ;
                    cin >> pt;
                    cout << "Matriks otomatis 2x2 "<<endl;
                    n=2;
 
                    for(int i=0; i<n; i++)
                    {
                        for(int j=0; j<n; j++)
                        {
                            cout<<"Masukkan elemen : "; cin >> key[i][j];
                        }
                    }
 
                    cout << "\nPlaintext  : " << pt << endl;
 
                    ct = encrypt(pt, n) ;
                    cout << "Hasil Enkripsi : " << ct << endl;
                    break;
            case 2:
                    cout << "Masukkan kata   : " ;
                    cin >> ct;
                    
                    cout << "Matriks otomatis 2x2"<<endl;
                    n=2;
 
                    for(int i=0; i<n; i++)
                    {
                        for(int j=0; j<n; j++)
                        {
                            cout<<"Masukkan elemen : "; cin >> key[i][j];
                        }
                    }
 
                    cout << "\nCiipertext  : " << ct << endl;
                    cout << "Hasil Dekripsi : " << decrypt(ct, n)<< endl;
                    break;
            case 3:
                    cout<<endl;
                    cariKey();
                    break;
            case 4:
                    menuActive = false;
                    exit(0);
                    break;
            default:
                    cout << "\nInvalid Input" <<endl;
                    break;
        }
    }
}


