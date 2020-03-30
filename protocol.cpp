#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#define W 64
#define T 9
using namespace std;

typedef unsigned long long int INT;
typedef unsigned long long int LINT;
const INT INTMAX=(((((INT)1<<63)-1)<<1)+1);
const INT HIGHBIT = (INT)1<<63;
struct number{
    INT* nums;// T+1
    int sign; // 0 ==0 -1 == - 1 == +
    int len; // 0 ==
};
/*
 brief : a struct holding number
 param nums : 64bit array
 param sign 1  : +
 param sign 0  : 0
 param sign -1 : -
 param len : length of the array ( 1 base )
 */
struct dot{
    number* x;
    number* y;
    int inf;
};
/*
 brief : a struct that represents a dot on an elliptic curve
 param x,y : the coordinate of the dot
 param inf : if it is a point at infinity, 1 else 0
 */
INT memo[1000000];
INT* now=memo;
number p,coa,cob,order,zero;
dot base_point,zero_point;
FILE* client_in = fopen("client.txt","rb");
FILE* client_out = fopen("client.txt","wb");
FILE* server_in = fopen("server.txt","rb");
FILE* server_out = fopen("server.txt","wb");

void swapnum(number &a,number &b);
/*
 brief : swaps number a and b
 param a : a number pointer
 param b : a number pointer
 */
int numcomparison(number* a,number* b);
/*
 brief : compares number a and b
 param a : a number pointer
 param b : a number pointer
 return 1  : a > b
 return 0  : a = b
 return -1 : a < b
 */
int numabscomparison(number* a,number* b);
/*
 brief : compares absolute value of number a and b
 param a : a number pointer
 param b : a number pointer
 return 1  : |a| > |b|
 return 0  : |a| = |b|
 return -1 : |a| < |b|
 */
int dotcomparison(dot* a,dot* b);
/*
 brief : compares dot a and b
 param a : a dot pointer
 param b : a dot pointer
 return 1 : a==b
 return -1 : a == -b
 return 0 : else
 */
int isone(number* a);
/*
 brief : compares a and 1
 param a : a number pointer
 return 1  : a == 1
 return 0  : a != 1
 */
int iszero(number* a);
/*
 brief : compares a and 0
 param a : a number pointer
 return 1  : a == 0
 return 0  : a != 0
 */
int copynum(number* a,number* b);
/*
 brief : copys number b to a
 param a : a number pointer
 param b : a number pointer
 return 1  : successful
 return 0  : error
 */
int copydot(dot* a,dot* b);
/*
 brief : copys dot b to a
 param a : a dot pointer
 param b : a dot pointer
 return 1  : successful
 return 0  : error
 */
int clearnum(number* a);
/*
 brief : clears number a
 process 1 : makes number a 0
 process 2 : erases lenth of a and sign of a
 param a : a number pointer
 return 1  : successful
 return 0  : error
 */
int cleardot(dot* a);
/*
 brief : clears dot a
 process 1 : makes dot a inf
 param a : a dot pointer
 return 1  : successful
 return 0  : error
 */
int lshift(number *a,number *b);
/*
 brief : leftshifts a(a*2) and puts the value in b
 process 1 : clearnum b
 process 2 : leftshifts a and put the value in b
 param a : a number pointer
 param b : a number pointer
 return 1  : successful
 return 0  : error
 */
int rshift(number *a,number *b);
/*
 brief : rightshifts a(a/2) and puts the value in b
 process 1 : clearnum b
 process 2 : rightshifts a and put the value in b
 param a : a number pointer
 param b : a number pointer
 return 1  : successful
 return 0  : error
 */
int baseaddition(number* a,number* b,number * c);
/*
 brief : calculates |a|+|b| and returns it in c
 process 1 : check the parameter
 process 2 : calculates |a|+|b| and returns it in c
 param a : a number pointer
 param b : a number pointer
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int basesubtraction(number* a,number* b,number * c);
/*
 brief : calculates |a|-|b| and returns it in c
 process 1 : check the parameter
 process 2 : calculates |a|-|b| and returns it in c
 param a : a number pointer |a|>=|b|
 param b : a number pointer |a|>=|b|
 param c : a number pointer
 return 1  : successful
 return 0  : error (|a|<|b|)
 */
int signaddition(number* a,number* b,number * c);
/*
 brief : calculates a+b and returns it in c
 process 1 : check the sign
 process 2 : calculates a+b using base operations and returns it in c
 param a : a number pointer
 param b : a number pointer
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int signsubtraction(number* a,number* b,number * c);
/*
 brief : calculates a-b and returns it in c
 process 1 : check the sign
 process 2 : calculates a-b using base operations and returns it in c
 param a : a number pointer
 param b : a number pointer
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int finiteaddition(number* a,number* b,number * c);
/*
 brief : calculates a+b (mod p) and returns it in c
 process 1 : calculates a+b using sign operations
 process 2 : modular a+b and returns it in c
 param a : a number pointer
 param b : a number pointer
 param c : a number pointer (it will be in [0,p))
 return 1  : successful
 return 0  : error
 */
int finitesubtraction(number* a,number* b,number * c);
/*
 brief : calculates a-b (mod p) and returns it in c
 process 1 : calculates a-b using sign operations
 process 2 : modular a-b and returns it in c
 param a : a number pointer
 param b : a number pointer
 param c : a number pointer (it will be in [0,p))
 return 1  : successful
 return 0  : error
 */
int multiplication(number* a,number* b,number* c);
/*
 brief : calculates a*b  and returns it in c
 process 1 : scans a and b
 process 2 : consider its sign
 param a : a number pointer
 param b : a number pointer
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int division(number* a,number* b,number* c);
/*
 brief : calculates a/b  and returns it in c
 process 1 : leftshifts b while b is smaller than a
 process 2 : if a is subtractable by b, subtract a with b and add proper value into c
 process 3 : rightshift b, and check it if it is smaller than the original b
 process 4 : if it is smaller, return c, if it is larger, go to process 2
 param a : a number pointer
 param b : a number pointer which is not 0
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int modular(number* a,number* b,number* c);
/*
 brief : calculates a/b  and returns it in c
 process 1 : leftshifts b while b is smaller than a
 process 2 : if a is subtractable by b, subtract a with b
 process 3 : rightshift b, and check it if it is smaller than the original b
 process 4 : if it is smaller, put a into c and return, if it is larger, go to process 2
 param a : a number pointer
 param b : a number pointer which is not 0
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int numgcd(number* a,number* b,number* c);
/*
 brief : calculates (a,b)  and returns it in c
 param a : a number pointer which is not 0
 param b : a number pointer which is not 0
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int numinv(number* a,number* b,number* c);
/*
 brief : calculates a^(-1) mod b  and returns it in c
 param a : a number pointer which is not 0
 param b : a number pointer which is not 0 , prime
 param c : a number pointer
 return 1  : successful
 return 0  : error
 */
int adddot(dot* a,dot* b,dot* c);
/*
 brief : calculates a + b and returns it in c
 param a : a dot pointer
 param b : a dot pointer
 param c : a dot pointer
 return 1 : successsful
 return 0 : error
 
 */
int doubledot(dot* a,dot* b);
/*
 brief : calculates 2*a and returns it in b
 param a : a dot pointer
 param b : a dot pointer
 return 1 : successful
 return 0 : error
 */
int scaladot(number* a,dot* b,dot* c);
/*
 brief : calculates a*b and returns it in c
 param a : a number pointer
 param b : a dot pointer
 param c : a dot pointer
 return 1 : successful
 return 0 : error
 */
void makeknapsack(dot* a,number b[]);
/*
 brief : makes knapsack array with a and returns it in b
 param a : a dot pointer
 param b : a number array
 */
void printnum_nospace(number* a);
/*
 brief : prints number a with no space(for debugging)
 param a : a number pointer
 */
void printnum(number* a);
/*
 brief : prints number a(for debugging)
 param a : a number pointer
 */
void printdot_nospace(dot* a);
/*
 brief : prints dot a with no space(for debugging)
 param a : a number pointer
 */
void printdot(dot* a);
/*
 brief : prints dot a(for debugging)
 param a : a number pointer
 */
void fprintnum(FILE* f,number *a);
/*
 brief : prints number a(for debugging)
 param f : a file to print
 param a : a number pointer
 */
void fprintdot(FILE* f,dot *a);
/*
 brief : prints dot a(for debugging)
 param f : a file to print
 param a : a dot pointer
 */
int fgetnum(FILE *f,number *a,int len);
/*
 brief: reads valnue from f, length of len and put value in a
 param f : a file pointer
 param a : a number pointer
 param len : a length to read( if can't, pad 100000000)
 */
void fwritenum(FILE *f,number *a,int len);
/*
 brief : writes number a in f (binary)
 param f : a file pointer
 param a : a number pointer
 param len : a length to write
 */
void fwritepoint(FILE *f,dot * a,int len);
/*
 brief : writes dot a in f (binary)
 param f : a file pointer
 param a : a dot pointer
 param len : a length to write
 */
void fwritenum_pad(FILE *f,number *a,int len);
/*
 brief : writes number a in f with no pad(binary)
 param f : a file pointer
 param a : a number pointer
 param len : a length to write
 */
void fwritepoint_pad(FILE *f,dot * a,int len);
/*
 brief : writes dot a in f with no pad(binary)
 param f : a file pointer
 param a : a dot pointer
 param len : a length to write
 */
void getnum(string a,number* b);
/*
 brief : puts value of string a to number b(for debigging)
 param a : a hexadecimal string
 param b : a number pointer
 */
void assignnumber(number* num,int a);
/*
 brief : assigns an array
 process 1 : goes up the memo pointer
 param num : the pointer where the array is assigned
 param a : length of the new number pointer
 return : a new number pointer assigned a num array with size of a
 */
void get_signature(number* d_a,number* m,number* r,number* s);
/*
 brief : puts signature value into r,s
 param d_a : private_key
 param m : message
 param r : signature value 1
 param s : signature value 2
*/
int verify_signature(dot* Q_a,number* m,number* r,number* s);
/*
 brief : verifys signature value and if correct returns 1 if not returns 0
 param Q_a : public_key
 param m : message
 param r : signature value 1
 param s : signature value 2
*/




int main(){
    cout<<"start\n";
    float start = clock();
    assignnumber(&p,(T+1)*2);
    assignnumber(&coa, (T+1)*2);
    assignnumber(&cob,(T+1)*2);
    p.nums[0]=0xFFFFFFFFFFFFFFFF;
    p.nums[1]=0xFFFFFFFFFFFFFFFF;
    p.nums[2]=0xFFFFFFFFFFFFFFFF;
    p.nums[3]=0xFFFFFFFFFFFFFFFF;
    p.nums[4]=0xFFFFFFFFFFFFFFFF;
    p.nums[5]=0xFFFFFFFFFFFFFFFF;
    p.nums[6]=0xFFFFFFFFFFFFFFFF;
    p.nums[7]=0xFFFFFFFFFFFFFFFF;
    p.nums[8]=0x1FF;
    p.sign=1;
    p.len=9;
    number arr[512];
    for(int i = 0;i<512;i++){
        assignnumber(arr+i,(T+1)*2);
    }
    getnum("00c6858e06b70404e9cd9e3ecb662395b4429c648139053fb521f828af606b4d3dbaa14b5e77efe75928fe1dc127a2ffa8de3348b3c1856a429bf97e7e31c2e5bd66",base_point.x);
    getnum("011839296a789a3bc0045c8a5fb42c7d1bd998f54449579b446817afbd17273e662c97ee72995ef42640c550b9013fad0761353c7086a272c24088be94769fd16650",base_point.y);
    getnum("01fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffa51868783bf2f966b7fcc0148f709a5d03bb5c9b8899c47aebb6fb71e91386409",&order);

    




    number x1,y1,x2,y2,x3,y3,sign_private_key,message,r,s;
    assignnumber(&x1,(T+1)*2);
    assignnumber(&y1,(T+1)*2);
    assignnumber(&x2,(T+1)*2);
    assignnumber(&y2,(T+1)*2);
    assignnumber(&x3,(T+1)*2);
    assignnumber(&y3,(T+1)*2);
    assignnumber(&order,(T+1)*2);
    assignnumber(&zero,(T+1)*2);
    assignnumber(&sign_private_key,(T+1)*2);
    assignnumber(&message,(T+1)*2);
    assignnumber(&r,(T+1)*2);
    assignnumber(&s,(T+1)*2);
    dot P,sign_public_key;
    base_point.x = &x1;
    base_point.y = &y1;
    sign_public_key.x = &x2;
    sign_public_key.y = &y2;
    zero_point.x = &x3;
    zero_point.y = &y3;
    cleardot(&base_point);
    base_point.inf = 0;
    cleardot(&sign_public_key);
    sign_public_key.inf=0;
    cleardot(&zero_point);
    zero_point.inf=1;

    getnum("01ffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffa51868783bf2f966b6fcc0148f709a5d03bb5c9b8899c47aebb6fb71e91386409",&sign_private_key);
    getnum("0",&zero);
    getnum("1BEFE202A7BE69C3150B51DE2BBE18990EE2D9AEF262842573738386C8DE67382A1F25A5B0EE8C5BE0C81896FD4A3A72587F92E42311DFC86F574E0760653ECA3CE",sign_public_key.x);
    getnum("1F51D4C215212E34B322BF01F9D7BBD2B23928E44E87DC88E88E98B658867EF4B28A4AD1F8B4A22D05DDC7F364EFE2EA612DC6F25575C757578F0430F8AAD287D99",sign_public_key.y);
    getnum("11434234131243212313133212333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333",&message);
    get_signature(&sign_private_key,&message,&r,&s);
    float mid=clock();
    if(verify_signature(&sign_public_key,&message,&r,&s)) cout<<"Yes\n";
    else cout<<"No\n";
    float end=clock();
    cout<<mid-start<<" "<<end-mid<<"\n";
    cout<<"end\n";
}
void client1(){
    FILE* m = fopen("message.txt","rb");
    FILE* pin = fopen("pin.txt","rb");
    number enc_private_key, message;
    assignnumber(&enc_private_key,(T+1)*2);
    getnum("01ffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffa51868783bf2f966b6fcc0148f709a5d03bb5c9b8899c47aebb6fb71e91386409",&enc_private_key);
    

}

int fgetnum(FILE *f,number *a,int len){
    unsigned char buff[67];
    clearnum(a);
    int all = 1;
    int temp = (int)fread(buff, sizeof(char), len, f);
    if(temp<len){
        buff[temp] = 0x80;
        for(int i= temp+1;i<len;i++){
            buff[i] = 0x00;
        }
        all = 0;
    }
    for(int i = 0;i<len;i++){
        a->nums[(len - i - 1)/8]|=(INT)buff[i]<<(((len - i -1)%8)*8);
    }
    for(int i =(len-1)/8;i>=0;i--){
        if(a->nums[i]!=0){
            a->len = i+1;
            break;
        }
    }
    if(a->len != 0) a->sign = 1;
    return all;
}
void fwritenum(FILE *f,number *a,int len){
    unsigned char buff[67];
    for(int i = 0;i<len;i++){
        buff[i] = (a->nums[(len-i-1)/8] &((INT)0xff<<(((len-i-1)%8)*8)))>>(((len-i-1)%8)*8);
        //printf("%x\n",buff[i]);
    }
    
    fwrite(buff,sizeof(char),len,f);
}
void fwritepoint(FILE *f,dot * a,int len){
    fwritenum(f,a->x,len);
    fwritenum(f, a->y,len);
}
void fwritenum_pad(FILE *f,number *a,int len){
    unsigned char buff[67];
    for(int i = 0;i<len;i++){
        buff[i] = (a->nums[(len-i-1)/8] &((INT)0xff<<(((len-i-1)%8)*8)))>>(((len-i-1)%8)*8);
        //printf("%x\n",buff[i]);
    }
    int toprint = len;
    for(int i=len - 1;i>=0;i--){
        if(buff[i]==0x80){
            toprint = i;
            break;
        }
        else if(buff[i] == 0x00){
            toprint = i;
        }
        else break;
    }
    fwrite(buff,sizeof(char),toprint,f);
}
void fwritepoint_pad(FILE *f,dot * a,int len){
    fwritenum_pad(f,a->x,len);
    fwritenum_pad(f, a->y,len);
}
void fprintnum(FILE* f,number *a){
    if(a->sign == -1) fprintf(f,"-");
    fprintf(f,"0x0");
    for(int i=a->len-1;i>=0;i--){
        fprintf(f,"%016llX",a->nums[i]);
    }
    fprintf(f,"\n");
}
void fprintdot(FILE* f,dot *a){
    fprintnum(f,a->x);
    fprintnum(f,a->y);
}
void printnum_nospace(number* a){
    printf("sign : %d len : %d\n",a->sign,a->len);
    for(int i=a->len-1;i>=0;i--){
        printf("%016llX",a->nums[i]);
    }
    printf("\n");
}
void printnum(number* a){
    printf("sign : %d len : %d\n",a->sign,a->len);
    for(int i=a->len-1;i>=0;i--){
        printf("%016llX ",a->nums[i]);
        if(i%2 ==0 ) printf("\n");
    }
}
void printdot_nospace(dot* a){
    printnum_nospace(a->x);
    printnum_nospace(a->y);
}
void printdot(dot* a){
    printnum(a->x);
    printnum(a->y);
}
void getnum(string a,number* b){
    clearnum(b);
    b->len = ((int)a.length()-1)/16 + 1;
    for(auto i : a){
        for(int j=0;j<4;j++) lshift(b,b);
        if('a'<=i&&i<='z'){
            i+=-'a'+'A';
        }
        if('A'<=i&&i<='Z'){
            b->nums[0]+=i-'A'+10;
        }
        else{
            b->nums[0]+=i-'0';
        }
    }
    b->sign = 1;
    return;
}
void swapnum(number &a,number &b){
    number c;
    c = a;
    a = b;
    b = c;
}
int numcomparison(number* a,number* b){
    if(a->sign!=b->sign){
        return a->sign>b->sign?1:-1;
    }
    if(a->len!=b->len){
        return a->len>b->len?1*a->sign:-1*a->sign;
    }
    int now=a->len-1;
    while(now>=0&&a->nums[now]==b->nums[now]){
        now--;
    }
    if(now<=-1) return 0;
    return a->nums[now]>b->nums[now]?1*a->sign:-1*a->sign;
}
int numabscomparison(number* a,number* b){
    if(a->len!=b->len){
        return a->len>b->len?1:-1;
    }
    int now=a->len-1;
    while(now>=0&&a->nums[now]==b->nums[now]){
        now--;
    }
    if(now<=-1) return 0;
    return a->nums[now]>b->nums[now]?1:-1;
}
int dotcomparison(dot* a,dot* b){
    if(numcomparison(a->x, b->x)==0&&numcomparison(a->y, b->y)==0){
        return 1;
    }
    if(numcomparison(a->x, b->x)==0) return -1;
    return 0;
}
int isone(number* a){
    return (int)(a->len == 1&&a->sign == 1&&a->nums[0] == 1);
}
int iszero(number* a){
    return (int)(a->len == 0&&a->sign == 0&&a->nums[0] == 0);
}
int copynum(number* a,number* b){
    clearnum(a);
    a->len=b->len;
    a->sign= b->sign;
    for(int i=0;i<b->len;i++) a->nums[i]=b->nums[i];
    return 1;
}
int copydot(dot* a,dot* b){
    int successful = 1;
    successful&=cleardot(a);
    successful&=copynum(a->x,b->x);
    successful&=copynum(a->y, b->y);
    a->inf = b->inf;
    return successful;
}
int cleardot(dot* a){
    int successful = 1;
    successful&=clearnum(a->x);
    successful&=clearnum(a->y);
    a->inf = 1;
    return successful;
}
int clearnum(number * a){
    for(int i=0;i<(T+1)*2;i++) a->nums[i]=0;
    a->sign=0;
    a->len=0;
    return 1;
}
int lshift(number *a,number *b){
    int successful = 1;
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    successful&=copynum(&t1_p, a);
    int temp=0,ttemp=0;
    for(int i=0;i<t1_p.len;i++){
        ttemp = (t1_p.nums[i]&HIGHBIT)>0?1:0;
        t1_p.nums[i]<<=1;
        t1_p.nums[i]+=temp;
        temp = ttemp;
    }
    if(temp!=0) {t1_p.nums[t1_p.len]=1; t1_p.len++;}
    successful&=copynum(b,&t1_p);
    return successful;
}
int rshift(number *a,number *b){
    int successful = 1;
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    successful&=copynum(&t1_p, a);
    int temp=0,ttemp=0;
    for(int i=t1_p.len-1;i>=0;i--){
        ttemp = t1_p.nums[i]&1;
        t1_p.nums[i]>>=1;
        t1_p.nums[i]+=temp*HIGHBIT;
        temp = ttemp;
    }
    if(t1_p.len ==0 ){
        t1_p.sign=0;
        return copynum(b,&t1_p);
    }
    if(t1_p.nums[t1_p.len-1]==0) t1_p.len--;
    if(t1_p.len==0) t1_p.sign=0;
    successful&=copynum(b, &t1_p);
    return successful;
}

int baseaddition(number* a,number* b,number *c){
    INT temp=0;
    int short_len,long_len;
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    clearnum(&t1_p);
    if(a->len > b->len){
        number* tp;
        tp = a;
        a = b;
        b = tp;
    }
    short_len = a->len;
    long_len = b->len;
    for(int i=0;i<short_len;i++){
        if(a->nums[i]+b->nums[i]+temp<a->nums[i]||(temp==1&&a->nums[i]+b->nums[i]+temp==a->nums[i])){
            t1_p.nums[i]=a->nums[i]+b->nums[i]+temp;
            temp=1;
            
        }
        else{
            t1_p.nums[i]=a->nums[i]+b->nums[i]+temp;
            temp=0;
        }
        if(t1_p.nums[i]!=0) t1_p.len = i+1;
    }
    for(int i = short_len;i<long_len;i++){
        if(b->nums[i]+temp<b->nums[i]){
            temp=1;
            t1_p.nums[i]=0;
        }
        else{
            t1_p.nums[i]=b->nums[i]+temp;
            temp=0;
        }
        if(t1_p.nums[i]!=0) t1_p.len = i+1;
    }
    t1_p.nums[long_len]=b->nums[long_len]+(long_len==short_len?a->nums[long_len]:0)+temp;
    t1_p.sign=1;
    if(t1_p.nums[long_len]!=0) t1_p.len = long_len+1;
    if(t1_p.len==0) t1_p.sign=0;
    return copynum(c,&t1_p);
}
int basesubtraction(number* a,number* b,number * c){
    INT temp=0;
    if(numabscomparison(a, b) == -1) return 0;
    int short_len,long_len;
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    clearnum(&t1_p);
    short_len = b->len;
    long_len = a->len;
    for(int i=0;i<short_len;i++){
        t1_p.nums[i]=a->nums[i]-b->nums[i]-temp;
        if((INT)(a->nums[i] - temp) > a->nums[i]||t1_p.nums[i] > (INT)(a->nums[i] - temp)){
           temp = 1;
        }
        else {
           temp = 0;
        }
        if(t1_p.nums[i]!=0) t1_p.len = i+1;
    }
    for(int i = short_len ;i <long_len ;i++){
        if(a->nums[i]==0&&temp){
            t1_p.nums[i]=a->nums[i]-temp;
            temp=1;
        }
        else{
            t1_p.nums[i]=a->nums[i]-temp;
            temp=0;
        }
        if(t1_p.nums[i]!=0) t1_p.len = i+1;
    }
    //t1_p->nums[long_len]=a->nums[long_len]-(long_len==short_len?b->nums[long_len]:0)-temp;//should not occur
    t1_p.sign=1;
    if(t1_p.len==0) t1_p.sign=0;
    return copynum(c,&t1_p);
}
int signaddition(number* a,number* b,number * c){
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    clearnum(&t1_p);
    int successful=1;
    if(iszero(b)){
        return successful&copynum(c,a);
    }
    if(iszero(a)){
        return successful&copynum(c,b);
    }
    if(a->sign==b->sign){
        successful&=baseaddition(a, b , &t1_p);
        t1_p.sign = a->sign;
        successful&=copynum(c,&t1_p);
    }
    else{
        if(numabscomparison(a, b)==1){
            successful&=basesubtraction(a, b,&t1_p);
            t1_p.sign=a->sign;
            successful&=copynum(c, &t1_p);
            if(c->len==0) c->sign=0;
        }
        else{
            successful&=basesubtraction(b, a,&t1_p);
            t1_p.sign=b->sign;
            successful&=copynum(c,&t1_p);
            if(c->len==0) c->sign=0;
        }
    }
    
    return successful;
}
int signsubtraction(number* a,number* b,number * c){
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    clearnum(&t1_p);
    int successful=1;
    if(iszero(b)){
        return successful&copynum(c,a);
    }
    if(iszero(a)){
        successful&=copynum(c,b);
        c->sign = -b->sign;
        return successful;
    }
    if(a->sign!=b->sign){
        successful&=baseaddition(a, b ,&t1_p);
        t1_p.sign = a->sign;
        successful&=copynum(c, &t1_p);
        
    }
    else{
        if(numabscomparison(a, b)==1){
            successful&=basesubtraction(a, b, &t1_p);
            t1_p.sign=a->sign;
            successful&=copynum(c, &t1_p);
            
            if(c->len==0) c->sign=0;
        }
        else{
            successful&=basesubtraction(b, a, &t1_p);
            t1_p.sign=-b->sign;
            successful&=copynum(c, &t1_p);
            
            if(c->len==0) c->sign=0;
        }
    }
    
    return successful;
}
int finiteaddition(number* a,number* b,number * c){
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    clearnum(&t1_p);
    int successful=1;
    successful&=signaddition(a, b,&t1_p);
    while(numcomparison(&t1_p, &p)>=0){
        successful&=basesubtraction(&t1_p,&p,&t1_p);
    }
    while(t1_p.sign<0){
        successful&=baseaddition(&t1_p, &p,&t1_p);
    }
    successful&=copynum(c,&t1_p);
    return successful;
    
}
int finitesubtraction(number* a,number* b,number * c){
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    clearnum(&t1_p);
    int successful=1;
    successful&=signsubtraction(a, b,&t1_p);
    while(numcomparison(&t1_p,&p)>=0){
        successful&=basesubtraction(&t1_p,&p,&t1_p);
    }
    while(t1_p.sign<0){
        successful&=baseaddition(&t1_p,&p,&t1_p);
    }
    successful&=copynum(c,&t1_p);
    return successful;
    
}
int multiplication(number* a,number* b,number* c){
    int successful = 1;
    number t1_p;
    INT temparr[(T+1)*2];
    t1_p.nums = temparr;
    successful&=clearnum(&t1_p);
    for(int i=0;i<a->len+b->len;i++) t1_p.nums[i]=0;
    for(int i=0;i<a->len;i++){
        INT U = 0;
        for(int j=0;j<b->len;j++){
            INT a1=(a->nums[i])>>32,a2=(a->nums[i])&(((INT)1<<32)-1);
            INT b1=(b->nums[j])>>32,b2=(b->nums[j])&(((INT)1<<32)-1);
            INT t_s=t1_p.nums[i+j],temp=0;
            if(t_s+U<t_s) temp++;
            t_s+=U;
            INT c1=((a2*b1)&(((INT)1<<32)-1))<<32;
            INT c2=((a1*b2)&(((INT)1<<32)-1))<<32;
            if(t_s+c1<t_s) temp++;
            t_s+=c1;
            if(t_s+c2<t_s) temp++;
            t_s+=c2;
            if(t_s+a2*b2<t_s) temp++;
            t_s+=a2*b2;
            //LINT temp=t1_p.nums[i+j]+(LINT)a->nums[i]*b->nums[j]+U;
            U=a1*b1+(a1*b2>>32)+(a2*b1>>32)+temp;
            t1_p.nums[i+j]=t_s;
            /*U=temp>>64;
            t1_p.nums[i+j] = temp&INTMAX;*/
        }
        t1_p.nums[i+b->len]=U;
    }
    t1_p.len = 0;
    for(int i=a->len+b->len-1;i>=0;i--){
        if(t1_p.nums[i]!=0) { t1_p.len = i +1 ; break;}
    }
    t1_p.sign = a->sign * b->sign;
    //printnum(&t1_p);
    successful&=copynum(c,&t1_p);
    return successful;
}
int division(number* a,number* b,number* c){
    int successful = 1;
    if(b->sign == 0 ) return 0;
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    successful&=copynum(&t1_p, a);
    successful&=copynum(&t2_p, b);
    successful&=clearnum(&t3_p);
    while(numabscomparison(&t1_p,&t2_p)>0) {
        successful&=lshift(&t2_p,&t2_p);
    }
    while(numabscomparison(&t2_p,b)>=0){
        successful&=lshift(&t3_p,&t3_p);
        if(numabscomparison(&t1_p,&t2_p)>=0) {
            successful&=signsubtraction(&t1_p,&t2_p,&t1_p);
            t3_p.nums[0]+=1;
            t3_p.sign=1;
            if(t3_p.len==0) t3_p.len = 1;
        }
        successful&=rshift(&t2_p, &t2_p);
    }
    t3_p.sign = a->sign * b->sign;
    successful&=copynum(c, &t3_p);
    return successful;
}
int modular(number* a,number* b,number* c){
    int successful = 1;
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    successful&=clearnum(&t1_p);
    successful&=clearnum(&t2_p);
    successful&=copynum(&t1_p, a);
    successful&=copynum(&t2_p, b);
    while(numabscomparison(&t1_p,&t2_p)>0) successful&=lshift(&t2_p,&t2_p);
    if(numabscomparison(&t1_p,&t2_p)==0) return successful&clearnum(c);
    while(numabscomparison(&t2_p,b)>=0){
        if(numabscomparison(&t1_p,&t2_p)>=0) {
            if(t1_p.sign >=1){
                successful&=signsubtraction(&t1_p,&t2_p,&t1_p);
            }
            else{
                successful&=signaddition(&t1_p,&t2_p,&t1_p);
            }
        }
        successful&=rshift(&t2_p,&t2_p);
    }
    if(t1_p.sign < 0 ) signaddition(&t1_p, b,&t1_p);
    successful&=copynum(c,&t1_p);
    return successful;
}
int numgcd(number* a,number* b,number* c){
    int successful = 1;
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    successful&=clearnum(&t1_p);
    successful&=clearnum(&t2_p);
    successful&=clearnum(&t3_p);
    successful&=copynum(&t1_p,a);
    successful&=copynum(&t2_p,b);
    t3_p.len = 1;
    t3_p.sign = 1;
    t3_p.nums[0] = 1;
    if(a->sign<=0) successful = 0;
    if(b->sign<=0) successful = 0;
    while((t1_p.nums[0]&1) == 0 &&(t2_p.nums[0]&1) == 0){
        successful&=rshift(&t1_p,&t1_p);
        successful&=rshift(&t2_p,&t2_p);
        successful&=lshift(&t3_p,&t3_p);
    }
    while(t1_p.sign>0){
        while((t1_p.nums[0]&1) == 0) successful&=rshift(&t1_p,&t1_p);
        while((t2_p.nums[0]&1) == 0) successful&=rshift(&t2_p,&t2_p);
        if(numcomparison(&t1_p,&t2_p)>=0) successful&=basesubtraction(&t1_p,&t2_p,&t1_p);
        else successful&=basesubtraction(&t2_p,&t1_p,&t2_p);
    }
    successful&=multiplication(&t2_p, &t3_p, &t3_p);
    successful&=copynum(c,&t3_p);
    return successful;
}

int numinv(number* a,number* b,number* c){
    int successful = 1;
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    number t4_p;
    INT temparr4[(T+1)*2];
    t4_p.nums = temparr4;
    successful&=clearnum(&t1_p);
    successful&=clearnum(&t2_p);
    successful&=clearnum(&t3_p);
    successful&=clearnum(&t4_p);
    successful&=copynum(&t1_p,a);
    successful&=copynum(&t2_p,b);
    t3_p.nums[0] = 1;
    t3_p.sign = 1;
    t3_p.len = 1;
    while(isone(&t1_p)==0&&isone(&t2_p)==0){
        while((t1_p.nums[0]&1) == 0){
            rshift(&t1_p, &t1_p);
            if((t3_p.nums[0]&1) == 0){
                rshift(&t3_p,&t3_p);
            }
            else{
                signaddition(&t3_p, b,&t3_p);
                rshift(&t3_p,&t3_p);
            }
        }
        while((t2_p.nums[0]&1) == 0){
            rshift(&t2_p,&t2_p);
            if((t4_p.nums[0]&1) == 0){
                rshift(&t4_p,&t4_p);
            }
            else{
                signaddition(&t4_p, b,&t4_p);
                rshift(&t4_p,&t4_p);
            }
        }
        if(numcomparison(&t1_p,&t2_p)>=0){
            basesubtraction(&t1_p,&t2_p,&t1_p);
            signsubtraction(&t3_p,&t4_p,&t3_p);
        }
        else{
            basesubtraction(&t2_p,&t1_p,&t2_p);
            signsubtraction(&t4_p,&t3_p,&t4_p);
        }
        
    }
    if(isone(&t1_p)){
        modular(&t3_p, b, c);
    }
    else{
        modular(&t4_p, b, c);
    }
    return successful;
}
int adddot(dot* a,dot* b,dot* c){
    int successful = 1;
    dot d1_p;
    if(dotcomparison(a, b)==1){
        printdot(a);
        printdot(b);
        return successful&doubledot(a,c);
    }
    if(dotcomparison(a, b)==-1){
        return successful&cleardot(c);
    }
    if(a->inf == 1){
        return copydot(c,b);
    }
    if(b->inf == 1){
        return copydot(c,a);
    }
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    number t4_p;
    INT temparr4[(T+1)*2];
    t4_p.nums = temparr4;
    successful&=clearnum(&t1_p);
    successful&=clearnum(&t2_p);
    successful&=clearnum(&t3_p);
    successful&=clearnum(&t4_p);
    d1_p.x = &t1_p;
    d1_p.y = &t2_p;
    d1_p.inf = 0;
    successful&=signsubtraction(b->y, a->y, &t3_p);
    successful&=signsubtraction(b->x, a->x, &t4_p);
    successful&=modular(&t4_p, &p, &t4_p);
    successful&=numinv(&t4_p, &p, &t4_p);
    successful&=multiplication(&t3_p, &t4_p, &t3_p);
    successful&=modular(&t3_p,&p,&t3_p);
    successful&=multiplication(&t3_p,&t3_p, d1_p.x);
    successful&=modular(d1_p.x,&p,d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=signsubtraction(d1_p.x, b->x, d1_p.x);
    successful&=modular(d1_p.x,&p,d1_p.x);
    successful&=signsubtraction(a->x, d1_p.x, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, d1_p.y);
    successful&=signsubtraction(d1_p.y, a->y, d1_p.y);
    successful&=modular(d1_p.y,&p,d1_p.y);
    successful&=copydot(c, &d1_p);
    return successful;
}
int doubledot(dot* a,dot* b){
    int successful = 1;
    if(a->inf == 1) return successful&cleardot(b);
    if(a->y->sign == 0 ) return successful&cleardot(b);
    dot d1_p;
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    number t4_p;
    INT temparr4[(T+1)*2];
    t4_p.nums = temparr4;
    successful&=clearnum(&t1_p);
    successful&=clearnum(&t2_p);
    successful&=clearnum(&t3_p);
    successful&=clearnum(&t4_p);
    d1_p.x = &t1_p;
    d1_p.y = &t2_p;
    d1_p.inf = 0;
    t3_p.len = 1;
    t3_p.sign = 1;
    t3_p.nums[0] = 3;
    t4_p.len = 1;
    t4_p.sign = 1;
    t4_p.nums[0] = 2;
    successful&=multiplication(&t3_p, a->x, &t3_p);
    successful&=modular(&t3_p, &p, &t3_p);
    successful&=multiplication(&t3_p, a->x, &t3_p);
    successful&=signaddition(&coa, &t3_p, &t3_p);
    successful&=modular(&t3_p, &p, &t3_p);
    successful&=multiplication(&t4_p, a->y, &t4_p);
    successful&=numinv(&t4_p, &p, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, &t3_p);
    successful&=modular(&t3_p,&p,&t3_p);
    successful&=multiplication(&t3_p, &t3_p, d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=modular(d1_p.x, &p, d1_p.x);
    successful&=signsubtraction(a->x, d1_p.x, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, d1_p.y);
    successful&=signsubtraction(d1_p.y, a->y, d1_p.y);
    successful&=modular(d1_p.y, &p, d1_p.y);
    successful&=copydot(b,&d1_p);
    return successful;
}
int scaladot(number* a,dot* b,dot* c){
    int successful = 1;
    dot d1_p;
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    successful&=clearnum(&t1_p);
    successful&=clearnum(&t2_p);
    successful&=clearnum(&t3_p);
    d1_p.x = &t1_p;
    d1_p.y = &t2_p;
    d1_p.inf = 0;
    successful&=copynum(&t3_p,a);
    INT mask;
    for(int i = t3_p.len -1;i>=0;i--){
        mask = HIGHBIT;
        while(mask){
            successful&=doubledot(&d1_p,&d1_p);
            if(mask&t3_p.nums[i]) successful&=adddot(&d1_p,b,&d1_p);
            mask>>=1;
        }
    }
    successful&=copydot(c, &d1_p);
    return successful;
}
void makeknapsack(dot* a,number b[]){
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    clearnum(&t1_p);
    clearnum(&t2_p);
    clearnum(&t3_p);
    t1_p.sign = 1;
    t1_p.len = 1;
    t1_p.nums[0] = 1;
    t3_p.sign = 1;
    t3_p.len = 1;
    t3_p.nums[0] = 1;
    for(int i=0;i<512;i++){
        lshift(&t1_p, &t1_p);
        if(a->y->nums[i/64]&1<<(i%64)) baseaddition(&t2_p, &t3_p, &t2_p);
        basesubtraction(&t1_p,&t2_p,b+i);
        //multiplication(b+i, a->x, b+i);
        //modular(b+i, &p, b+i);
        //printnum_nospace(&t1_p);
    }
    
}
void assignnumber(number* num,int len){
    num->nums = now;
    now=now+len;
    num->len = 0 ;
    num->sign = 0 ;
}

void get_signature(number* d_a,number* m,number* r,number* s){
    //hash_function(m,m);
    number z;
    INT temparr1[(T+1)*2];
    z.nums = temparr1;
    clearnum(&z);
    copynum(&z,m);
    srand(time(0));
    number temp;
    INT temparr2[(T+1)*2];
    temp.nums = temparr2;
    clearnum(&temp);
    temp.nums[0] = rand();
    temp.sign = 1;
    temp.len = 1;
    number k;
    INT temparr3[(T+1)*2];
    k.nums = temparr3;
    number t1_p;
    INT temparr4[(T+1)*2];
    t1_p.nums = temparr4;
    number t2_p;
    INT temparr5[(T+1)*2];
    t2_p.nums = temparr5;
    dot d1_p;
    clearnum(&k);
    clearnum(&t1_p);
    clearnum(&t2_p);
    d1_p.x = &t1_p;
    d1_p.y = &t2_p;
    number t3_p;
    INT temparr6[(T+1)*2];
    t3_p.nums = temparr6;
    clearnum(&t3_p);
    multiplication(&temp,&p,&k);
    modular(&k,&order,&k);
    copynum(&k,d_a);
    scaladot(&k,&base_point,&d1_p);
    modular(d1_p.x,&order,r);
    numinv(&k,&order,&k);
    multiplication(r,d_a,&t3_p);
    modular(&t3_p,&order,&t3_p);
    baseaddition(&z,&t3_p,&t3_p);
    modular(&t3_p,&order,&t3_p);
    multiplication(&k,&t3_p,&t3_p);
    modular(&t3_p,&order,s);
    return; 
}

int verify_signature(dot* Q_a,number* m,number* r,number* s){
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    dot d1_p;
    clearnum(&t1_p);
    clearnum(&t2_p);
    d1_p.x = &t1_p;
    d1_p.y = &t2_p;
    if(numcomparison(r,&order)>=0) return 0;
    if(numcomparison(r,&zero)<=0) return 0;
    if(numcomparison(s,&order)>=0) return 0;
    if(numcomparison(r,&zero)<=0) return 0;
    if(dotcomparison(Q_a,&zero_point)) return 0;
    /*scaladot(&order,Q_a,&d1_p);
    if(!dotcomparison(&d1_p,&zero_point)) return 0;*/
    //hash_function(m,m);
    number z;
    INT temparr3[(T+1)*2];
    z.nums = temparr3;
    clearnum(&z);
    copynum(&z,m);
    number t3_p;
    INT temparr4[(T+1)*2];
    t3_p.nums = temparr4;
    number t4_p;
    INT temparr5[(T+1)*2];
    t4_p.nums = temparr5;
    number t5_p;
    INT temparr6[(T+1)*2];
    t5_p.nums = temparr6;
    number t6_p;
    INT temparr7[(T+1)*2];
    t6_p.nums = temparr7;
    number t7_p;
    INT temparr8[(T+1)*2];
    t7_p.nums = temparr8;
    clearnum(&t3_p);
    clearnum(&t4_p);
    clearnum(&t5_p);
    numinv(s,&order,&t3_p);
    multiplication(&t3_p,&z,&t4_p);
    multiplication(&t3_p,r,&t5_p);
    modular(&t4_p,&order,&t4_p);
    modular(&t5_p,&order,&t5_p);
    dot d2_p;
    clearnum(&t6_p);
    clearnum(&t7_p);
    d2_p.x = &t6_p;
    d2_p.y = &t7_p;
    scaladot(&t4_p,&base_point,&d1_p);
    scaladot(&t5_p,Q_a,&d2_p);
    adddot(&d1_p,&d2_p,&d1_p);
    modular(d1_p.x,&order,d1_p.x);
    if(numcomparison(d1_p.x,r)) return 0;    
    return 1;
}

void hash_function(number* m,number* hash_m){
    copynum(hash_m,m);
}
