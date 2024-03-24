#include <iostream>
#include <fstream>

using namespace std;

int init_perm[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
int straight_perm[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
int key_perm1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
int key_perm2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

void keygen(bool (&x)[56], bool (&y)[48], int t){
    bool temp, temp2;
    if (t==1||t==2||t==9||t==16) {
        temp=x[0];
        for (int j=1; j<28; j++) x[j-1]=x[j];
        x[27]=temp;
        temp=x[28];
        for (int j=29; j<56; j++) x[j-1]=x[j];
        x[55]=temp;
        /*for (int j=0; j<28; j++) cout << perm_key[j];
        cout << endl;
        for (int j=28; j<56; j++) cout << perm_key[j];
        cout << endl << endl;*/
    }
    else {
        temp=x[0]; temp2=x[1];
        for (int j=2; j<28; j++) x[j-2]=x[j];
        x[26]=temp; x[27]=temp2; 
        temp=x[28]; temp2=x[29];
        for (int j=30; j<56; j++) x[j-2]=x[j];
        x[54]=temp; x[55]=temp2;
    };
    for (int j=0; j<48; j++) y[j]=x[key_perm2[j]-1];
}

void round_func(bool (&x)[64], bool y[48]){
    bool half_1[48]; int count = -1;
    for (int i=0; i<32; i++) {
        if (i%6==0) {count+=2};
        half_1[i+count]=x[i];
    }
}

void DES_alg(bool x[64], bool y[64], bool (&z)[64]){ //x is plaintext, y is key, z is cyphertext
    bool perm_key[56]; bool temp; bool temp2; bool xor_key[48]; 
    for (int i=0; i<56; i++) perm_key[i]=y[key_perm1[i]-1]; //key initial permutation
    for (int i=0; i<56; i++) cout << perm_key[i]; 
    cout << endl;
    for (int i=0; i<64; i++) z[i]=x[init_perm[i]-1]; //plaintext initial permutation
    for (int i=1; i<=16; i++) {
        keygen(perm_key,xor_key,i);
        round_func(z,xor_key);
        /*for (int j=0; j<28; j++) cout << perm_key[j];
        cout << endl;
        for (int j=28; j<56; j++) cout << perm_key[j];
        cout << endl << endl;*/
        for (int j=0; j<48; j++) cout << xor_key[j];
        cout << endl;
    }
}

void toBitstream(bool (&x)[64], string y){
    int temp, count;
    for (int i=0; i<y.length(); i++) {
        temp = (int)y[i];
        count = 8;
        while (count) {
            count--;
            x[8*i+count]=temp%2;
            temp/=2;
        }
    }
}

void toBitstream2(bool (&x)[64], string y){
    int count = 0;
    int count2 = 0;
    while (count<64||count2<y.length()) {
        switch (y[count2]) {
            case '0': {x[count]=0; count++; break;}
            case '1': {x[count]=1; count++; break;}
            default: {break;}
        }
        count2++;
    }
}

string readkey(){
    ifstream f; string x;
    f.open("DES_key");
    getline(f, x);
    f.close();
    return x;
}

int main(){
    string s,key;
    cout << "Enter Plaintext (8 characters): ";
    cin >> s;
    bool P[64]
    bool k[64];
    bool C[64];
    toBitstream(P,s);
    for (int i=0; i<64; i++) cout << P[i] << " ";
    cout << endl;
    key = readkey();
    toBitstream2(k,key);
    for (int i=0; i<64; i++) cout << k[i] << " ";
    cout << endl;
    DES_alg(P,k,C);
    for (int i=0; i<56; i++) cout << C[i]; 
    cout << endl;
    return 0;
}