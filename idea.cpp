
#include<iostream>
#include <bitset>
using namespace std;

string leftshift(string key)
{
    string sh="";
    for(int i=6;i<key.length();i++)
    sh+=key[i];
    for(int i=0;i<6;i++)
    sh+=key[i];
    return sh;
}
string mul(string s1,string s2)
{
    int a=stoi(s1,nullptr,2);
    int b=stoi(s2,nullptr,2);
    a=(a*b)%17;
    return bitset<4>(a).to_string();
}
string xoring(string s1,string s2)
{
        int a=stoi(s1,nullptr,2);
    int b=stoi(s2,nullptr,2);
    a=(a^b);
    return bitset<4>(a).to_string();
}
string adding(string s1,string s2)
{
    int a=stoi(s1,nullptr,2);
    int b=stoi(s2,nullptr,2);
    a=(a+b)%16;
    return bitset<4>(a).to_string();
}
string round(string input,string* key)
{
    string x[4];
        for(int i=0;i<4;i++)
    {
        for(int j=4*i;j<4*i+4;j++)
        {
            x[i]+=input[j];
        }
    }
    string s1=mul(x[0],key[0]);
    string s2=adding(x[1],key[1]);
    string s3=adding(x[2],key[2]);
    string s4=mul(x[3],key[3]);
    string s5=xoring(s1,s3);
    string s6=xoring(s2,s4);
    string s7=mul(s5,key[4]);
    string s8=adding(s6,s7);
    string s9=mul(s8,key[5]);
    string s10=adding(s7,s9);
    string s11=xoring(s1,s9);
    string s12=xoring(s3,s9);
    string s13=xoring(s2,s10);
    string s14=xoring(s4,s10);
    string output=s11+s13+s12+s14;
    return output;
}
void keygen(string mat[][6],string key)
{
    for(int i=0;i<6;i++)
    {
        for(int j=4*i;j<4*i+4;j++)
        {
            mat[0][i]+=key[j];
        }
    }
    for(int j=24;j<28;j++)
        {
            mat[1][0]+=key[j];
        }
    for(int j=28;j<32;j++)
        {
            mat[1][1]+=key[j];
        }
    key=leftshift(key);
        for(int i=0;i<4;i++)
    {
        for(int j=4*i;j<4*i+4;j++)
        {
            mat[1][i+2]+=key[j];
        }
    }
        for(int i=0;i<4;i++)
    {
        for(int j=4*i+16;j<4*i+20;j++)
        {
            mat[2][i]+=key[j];
        }
    }
        key=leftshift(key);
for(int i=4;i<6;i++)
    {
        for(int j=4*(i-4);j<4*i-12;j++)
        {
            mat[2][i]+=key[j];
        }
    }
    for(int i=0;i<6;i++)
    {
        for(int j=4*i+8;j<4*i+12;j++)
        {
            mat[3][i]+=key[j];
        }
    }
        key=leftshift(key);
            for(int i=0;i<4;i++)
    {
        for(int j=4*i;j<4*i+4;j++)
        {
            mat[4][i]+=key[j];
        }
    }
        
}
string modInverse(string bits)
{
    int a=stoi(bits,nullptr,2);
    for (int x = 1; x < 17; x++)
        if (((a%17) * (x%17)) % 17 == 1)
            return bitset<4>(x).to_string();
}

string addInverse(string bits)
{
    int a=stoi(bits,nullptr,2);
    return bitset<4>(16-a).to_string();
}
void invkey(string mat[][6])
{
    string temp[5][6];
    for(int i=0;i<4;i++)
    {
        temp[i][0]=modInverse(mat[4-i][0]);
    temp[i][1]=addInverse(mat[4-i][1]);
    temp[i][2]=addInverse(mat[4-i][2]);
    temp[i][3]=modInverse(mat[4-i][3]);
    temp[i][4]=mat[4-i-1][4];
    temp[i][5]=mat[4-i-1][5];   
    }
    temp[4][0]=modInverse(mat[0][0]);
    temp[4][1]=addInverse(mat[0][1]);
    temp[4][2]=addInverse(mat[0][2]);
    temp[4][3]=modInverse(mat[0][3]);
    for(int i=0;i<5;i++)
    {
for(int j=0;j<6;j++)
    {
mat[i][j]=temp[i][j];
    }
    }
}
string halfround(string input,string* key)
{
    string x[4];
        for(int i=0;i<4;i++)
    {
        for(int j=4*i;j<4*i+4;j++)
        {
            x[i]+=input[j];
        }
    }
    string s1=mul(x[0],key[0]);
    string s2=adding(x[1],key[1]);
    string s3=adding(x[2],key[2]);
    string s4=mul(x[3],key[3]);
    string output=s1+s2+s3+s4;
    return output;
}
void pf(string bits)
{
    for(int i=0;i<bits.length();i++)
    {
        cout<<bits[i];
    if(i%4==3)
    cout<<" ";
    }       
    cout<<"\n";
}
string encrypt(string input,string key)
{
        string keys[5][6];
    keygen(keys,key);
    
    for(int i=0;i<4;i++)
    {
        input=round(input,keys[i]);
    }

string  output=halfround(input,keys[4]);
return output;
}
string decrypt(string input,string key)
{
        string keys[5][6];
    keygen(keys,key);
    invkey(keys);
    for(int i=0;i<4;i++)
    {
        input=round(input,keys[i]);
    }
string  output=halfround(input,keys[4]);
return output;
}
int main()
{
    string key="11011101011001010011111101011001";
    string msg="1011010010111100";
    cout<<"\nMessage bits are:  ";
    pf(msg);
    string output=encrypt(msg,key);
    cout<<"\nEncrypted bits are: ";
pf(output);
    cout<<"\nDecrypted bits are: ";
    pf(decrypt(output,key));

    return 0;
}

