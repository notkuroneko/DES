#include <iostream>
#include <fstream>

using namespace std;

int init_perm[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
int straight_perm[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
int final_perm[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
int key_perm1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
int key_perm2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
int e_bit[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
int s_table[8][4][16] = {{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

                    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

                    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

                    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

                    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

                    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
                    
                    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                    {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

                    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
                };

void keygen(bool (&x)[56], bool (&y)[48], int t){
    bool temp, temp2;
    if (t==1||t==2||t==9||t==16) {
        temp=x[0];
        for (int j=1; j<28; j++) x[j-1]=x[j];
        x[27]=temp;
        temp=x[28];
        for (int j=29; j<56; j++) x[j-1]=x[j];
        x[55]=temp;
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
    bool plaintext_l[32]; bool plaintext_r[48]; bool e[32]; int temp,r,c;
    for (int i=0; i<32; i++) {plaintext_l[i]=x[i]; x[i]=x[i+32];}
    for (int i=0; i<48; i++) {
        plaintext_r[i]=x[e_bit[i]-1+32];
        plaintext_r[i]=plaintext_r[i]^y[i];
    }
    for (int i=0; i<8; i++) {
        r = plaintext_r[6*i] * 2 + plaintext_r[6*i+5];
        c = plaintext_r[6*i+1] * 8 + plaintext_r[6*i+2] * 4 + plaintext_r[6*i+3] * 2 + plaintext_r[6*i+4];
        temp = s_table[i][r][c];
        for (int j=3; j>=0; j--){
            e[4*i+j]=temp%2;
            temp/=2;
        }
    }
    for (int i=0; i<32; i++) x[i+32]=plaintext_l[i]^e[straight_perm[i]-1];
}

void DES_alg(bool x[64], bool y[64], bool (&z)[64]){ //x is plaintext, y is key, z is cyphertext
    bool perm_key[56]; bool temp; bool temp2; bool xor_key[48]; bool cypher[64]; 
    for (int i=0; i<56; i++) perm_key[i]=y[key_perm1[i]-1]; //key initial permutation
    for (int i=0; i<64; i++) cypher[i]=x[init_perm[i]-1]; //plaintext initial permutation
    for (int i=1; i<=16; i++) {
        keygen(perm_key,xor_key,i);
        round_func(cypher,xor_key);
    }
    for (int i=0; i<32; i++) {temp=cypher[i]; cypher[i]=cypher[i+32]; cypher[i+32]=temp;}
    for (int i=0; i<64; i++) z[i]=cypher[final_perm[i]-1];
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
    bool P[64]; /*= {0,0,0,0, 0,0,0,1, 0,0,1,0, 0,0,1,1, 
                0,1,0,0, 0,1,0,1, 0,1,1,0, 0,1,1,1, 
                1,0,0,0, 1,0,0,1, 1,0,1,0, 1,0,1,1, 
                1,1,0,0, 1,1,0,1, 1,1,1,0, 1,1,1,1};*/
    bool k[64];
    bool C[64];
    toBitstream(P,s);
    key = readkey();
    toBitstream2(k,key);
    DES_alg(P,k,C);
    ofstream f;
    f.open("DES_output",  ios::out | ios::trunc);
    for (int i=0; i<64; i++) {if (!(i%4)) f << " "; f << C[i];}
    cout << "Cyphertext transfered to DES_output.txt" << endl;
    return 0;
}

