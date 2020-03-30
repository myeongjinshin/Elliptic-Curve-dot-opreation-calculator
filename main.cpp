#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "smj.h"
#include "sha512.h"
INT memo[1000000];
INT* now=memo;
number p,coa,order,zero;
dot base_point,zero_point,public_key,bin_dot[522],pub_bin_dot[522];
jdot jbin_dot[522],jpub_bin_dot[522],jtemp;

int main(){
    cout<<"start\n";
    number x1,y1,x2,y2,x3,y3,temp,temp1,temp2;
    dot tempdot;
    assignnumber(&temp,(T+1)*2);
    assignnumber(&temp1,(T+1)*2);
    assignnumber(&temp2,(T+1)*2);
    assignnumber(&p,(T+1)*2);
    assignnumber(&coa, (T+1)*2);
    assignnumber(&x1,(T+1)*2);
    assignnumber(&y1,(T+1)*2);
    assignnumber(&x2,(T+1)*2);
    assignnumber(&y2,(T+1)*2);
    assignnumber(&x3,(T+1)*2);
    assignnumber(&y3,(T+1)*2);
    assignnumber(&order,(T+1)*2);
    assignnumber(&zero,(T+1)*2);
    base_point.x = &x1;
    base_point.y = &y1;
    zero_point.x = &x2;
    zero_point.y = &y2;
    public_key.x = &x3;
    public_key.y = &y3;
    tempdot.x = &temp1;
    tempdot.y = &temp2;
    cleardot(&tempdot);
    cleardot(&base_point);
    base_point.inf = 0;
    cleardot(&zero_point);
    zero_point.inf = 1;
    coa.nums[0] =3;
    coa.sign = -1;
    coa.len = 1;
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
    getnum("00c6858e06b70404e9cd9e3ecb662395b4429c648139053fb521f828af606b4d3dbaa14b5e77efe75928fe1dc127a2ffa8de3348b3c1856a429bf97e7e31c2e5bd66",base_point.x);
    getnum("011839296a789a3bc0045c8a5fb42c7d1bd998f54449579b446817afbd17273e662c97ee72995ef42640c550b9013fad0761353c7086a272c24088be94769fd16650",base_point.y);
    getnum("01fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffa51868783bf2f966b7fcc0148f709a5d03bb5c9b8899c47aebb6fb71e91386409",&order);
    getnum("1BEFE202A7BE69C3150B51DE2BBE18990EE2D9AEF262842573738386C8DE67382A1F25A5B0EE8C5BE0C81896FD4A3A72587F92E42311DFC86F574E0760653ECA3CE",public_key.x);
    getnum("1F51D4C215212E34B322BF01F9D7BBD2B23928E44E87DC88E88E98B658867EF4B28A4AD1F8B4A22D05DDC7F364EFE2EA612DC6F25575C757578F0430F8AAD287D99",public_key.y);
    getnum("0",&zero);
    zero.sign=0;
    number jbx1[522],jby1[522],jbz1[522];
    assignnumber(&jbx1[0],(T+1)*2);
    assignnumber(&jby1[0],(T+1)*2);
    assignnumber(&jbz1[0],(T+1)*2);
    jtemp.x = &jbx1[0];
    jtemp.y = &jby1[0];
    jtemp.z = &jbz1[0];
    clearjdot(&jtemp);
    jtemp.inf = 0;
    /*string s1;
    cin>>s1;*/
    FILE* rjbin = fopen("jbin_dot.txt","rb");
    FILE* rjpbin = fopen("jpub_bin_dot.txt","rb");
    number jbx[522],jby[522],jbz[522];
    for(int i=0;i<522;i++){
        assignnumber(&jbx[i],(T+1)*2);
        assignnumber(&jby[i],(T+1)*2);
        assignnumber(&jbz[i],(T+1)*2);
        jbin_dot[i].x = &jbx[i];
        jbin_dot[i].y = &jby[i];
        jbin_dot[i].z = &jbz[i];
        clearjdot(&jbin_dot[i]);
        jbin_dot[i].inf = 0;
        fgetnum(rjbin,jbin_dot[i].x,66);
        fgetnum(rjbin,jbin_dot[i].y,66);
        fgetnum(rjbin,jbin_dot[i].z,66);
        trans_jdot_dot(&jbin_dot[i],&tempdot);
        trans_dot_jdot(&tempdot,&jbin_dot[i]);
    }
    /*number jpbx[522],jpby[522],jpbz[522];
    for(int i=0;i<522;i++){
        assignnumber(&jpbx[i],(T+1)*2);
        assignnumber(&jpby[i],(T+1)*2);
        assignnumber(&jpbz[i],(T+1)*2);
        jpub_bin_dot[i].x = &jpbx[i];
        jpub_bin_dot[i].y = &jpby[i];
        jpub_bin_dot[i].z = &jpbz[i];
        clearjdot(&jpub_bin_dot[i]);
        jpub_bin_dot[i].inf = 0;
        fgetnum(rjpbin,jpub_bin_dot[i].x,66);
        fgetnum(rjpbin,jpub_bin_dot[i].y,66);
        fgetnum(rjpbin,jpub_bin_dot[i].z,66);
        trans_jdot_dot(&jpub_bin_dot[i],&tempdot);
        trans_dot_jdot(&tempdot,&jpub_bin_dot[i]);
    }*/
    /*getnum(s1,&temp);
    FILE* pout = fopen("pin.txt","wb");
    fwritenum(pout,&temp,66);
    fclose(pout);
    client1();
    cout<<"1c\n";
    server1();
    cout<<"1s\n";
    client2();
    cout<<"2c\n";
    if(server2()) cout<<"2s\n";
    else{
        cout<<"pin wrong";
        return 0;
    }
    client3();
    cout<<"3c\n";
    if(server3()) cout<<"3s\n";
    else{
        cout<<"signature wrong";
        return 0;
    }*/
    //scaladot(public_key.x,&base_point,&base_point);
    //adddot(&base_point,&zero_point,&zero_point);
    //trans_dot_jdot(&base_point,&jtemp);
    /*scalajdot(&zero,&jtemp,&jtemp);
    trans_jdot_dot(&jtemp,&zero_point);*/
    //multiplication(public_key.x,public_key.x,public_key.x);
    /*float suma=0,sumb=0;
    for(int i=0;i<3;i++){
        clearnum(&zero);
        make_rand(&zero);
        fred_p521(&zero,&zero);
        float start = clock();
        trans_dot_jdot(&base_point,&jtemp);
        scalajdot(&zero,&jtemp,&jtemp,0);
        trans_jdot_dot(&jtemp,&zero_point);
        cleardot(&zero_point);
        clearjdot(&jtemp);
        float mid=clock();
        trans_dot_jdot(&base_point,&jtemp);
        scalajdot(&zero,&jtemp,&jtemp,1);
        trans_jdot_dot(&jtemp,&zero_point);
        cleardot(&zero_point);
        clearjdot(&jtemp);
        float end=clock();
        suma+=mid-start;
        sumb+=end-mid;
    }
    cout<<"end\n";
    cout<<suma<<" "<<sumb<<"\n";*/
    long long N;
    scanf("%lld",&N);
    printf("%lld",(long long)sqrt(N));
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
void printjdot(jdot* a){
    printnum(a->x);
    printnum(a->y);
    printnum(a->z);
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
int jdotcomparison(jdot* a,jdot* b){
    if(numcomparison(a->x, b->x)==0&&numcomparison(a->y, b->y)==0&&numcomparison(a->z,b->z)==0){
        return 1;
    }
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
int copyjdot(jdot* a,jdot* b){
    int successful = 1;
    successful&=clearjdot(a);
    successful&=copynum(a->x,b->x);
    successful&=copynum(a->y, b->y);
    successful&=copynum(a->z, b->z);
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
int clearjdot(jdot* a){
    int successful = 1;
    successful&=clearnum(a->x);
    successful&=clearnum(a->y);
    successful&=clearnum(a->z);
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
            INT c1=(a2*b1)<<32;
            INT c2=(a1*b2)<<32;
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
int fred_p521(number *a,number *b){
    int successful = 1;
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    successful&=clearnum(&t1_p);
    successful&=clearnum(&t2_p);
    int nowbit;
    for(nowbit=0;nowbit/64<a->len;nowbit++){
       if(!(a->nums[nowbit/64]&((INT)1<<(nowbit%64)))) continue;
       if(nowbit<521){
          t1_p.nums[nowbit/64]|=((INT)1<<(nowbit%64));
          t1_p.len = nowbit / 64 + 1;
       }
       else{
          t2_p.nums[(nowbit-521)/64]|=((INT)1<<((nowbit-521)%64));
          t2_p.len = (nowbit-521) / 64 + 1;
       }
    }
    baseaddition(&t1_p,&t2_p,&t1_p);
    if(t1_p.len==0) t1_p.sign = 0;
    else t1_p.sign = a->sign;
    return successful&=modular(&t1_p,&p,b);
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
    successful&=fred_p521(&t4_p, &t4_p);
    successful&=numinv(&t4_p, &p, &t4_p);
    successful&=multiplication(&t3_p, &t4_p, &t3_p);
    successful&=fred_p521(&t3_p,&t3_p);
    successful&=multiplication(&t3_p,&t3_p, d1_p.x);
    successful&=fred_p521(d1_p.x,d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=signsubtraction(d1_p.x, b->x, d1_p.x);
    successful&=fred_p521(d1_p.x,d1_p.x);
    successful&=signsubtraction(a->x, d1_p.x, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, d1_p.y);
    successful&=signsubtraction(d1_p.y, a->y, d1_p.y);
    successful&=fred_p521(d1_p.y,d1_p.y);
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
    successful&=fred_p521(&t3_p, &t3_p);
    successful&=multiplication(&t3_p, a->x, &t3_p);
    successful&=signaddition(&coa, &t3_p, &t3_p);
    successful&=fred_p521(&t3_p, &t3_p);
    successful&=multiplication(&t4_p, a->y, &t4_p);
    successful&=fred_p521(&t4_p, &t4_p);    
    successful&=numinv(&t4_p, &p, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, &t3_p);
    successful&=fred_p521(&t3_p,&t3_p);
    successful&=multiplication(&t3_p, &t3_p, d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=fred_p521(d1_p.x, d1_p.x);
    successful&=signsubtraction(a->x, d1_p.x, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, d1_p.y);
    successful&=signsubtraction(d1_p.y, a->y, d1_p.y);
    successful&=fred_p521(d1_p.y, d1_p.y);
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
    d1_p.inf = 1;
    successful&=copynum(&t3_p,a);
    modular(&t3_p,&order,&t3_p);
    INT mask;
    /*if(dotcomparison(b,&base_point)==1){
        int cnt = 0;
        for(int i=0;i<=t3_p.len-1;i++){
            mask = 1;
            while(1){
                if(mask&t3_p.nums[i]) successful&=adddot(&d1_p,&bin_dot[cnt],&d1_p);
                cnt++;
                if(mask==HIGHBIT) break;
                mask<<=1;
            }
        }
        successful&=copydot(c, &d1_p);
        return successful;
    }*/
    /*if(dotcomparison(b,&pub_bin_dot[0])==1){
        int cnt = 0;
        for(int i=0;i<=t3_p.len-1;i++){
            mask = 1;
            while(1){
                if(mask&t3_p.nums[i]) successful&=adddot(&d1_p,&pub_bin_dot[cnt],&d1_p);
                cnt++;
                if(mask==HIGHBIT) break;
                mask<<=1;
            }
        }
        successful&=copydot(c, &d1_p);
        return successful;
    }*/
    for(int i=t3_p.len-1;i>=0;i--){
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

/*void get_signature(number* d_a,number* m,number* r,number* s){
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
    for(int i=1;i<=9;i++) temp.nums[i]=rand();
    temp.sign = 1;
    temp.len = 9;
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
    jdot jd1_p;
    number t4_p;
    INT temparr7[(T+1)*2];
    t4_p.nums = temparr7;
    number t5_p;
    INT temparr8[(T+1)*2];
    t5_p.nums = temparr8;
    number t6_p;
    INT temparr9[(T+1)*2];
    t6_p.nums = temparr9;
    jd1_p.x = &t4_p;
    jd1_p.y = &t5_p;
    jd1_p.z = &t6_p;  
    clearjdot(&jd1_p);
    clearnum(&t3_p);
    copynum(&k,&temp);
    modular(&k,&order,&k);
    trans_dot_jdot(&base_point,&jd1_p);
    scalajdot(&k,&jd1_p,&jd1_p);
    trans_jdot_dot(&jd1_p,&d1_p);
    modular(d1_p.x,&order,r);
    numinv(&k,&order,&k);
    multiplication(r,d_a,&t3_p);
    modular(&t3_p,&order,&t3_p);
    baseaddition(&z,&t3_p,&t3_p);
    modular(&t3_p,&order,&t3_p);
    multiplication(&k,&t3_p,&t3_p);
    modular(&t3_p,&order,s);
    return; 
}*/

/*int verify_signature(dot* Q_a,number* m,number* r,number* s){
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
    scaladot(&order,Q_a,&d1_p);
    if(!dotcomparison(&d1_p,&zero_point)) return 0;
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
    jdot jd1_p,jd2_p;
    number t9_p;
    INT temparr9[(T+1)*2];
    t9_p.nums = temparr9;
    number t10_p;
    INT temparr10[(T+1)*2];
    t10_p.nums = temparr10;
    number t11_p;
    INT temparr11[(T+1)*2];
    t11_p.nums = temparr11;
    number t12_p;
    INT temparr12[(T+1)*2];
    t12_p.nums = temparr12;
    number t13_p;
    INT temparr13[(T+1)*2];
    t13_p.nums = temparr13;
    number t14_p;
    INT temparr14[(T+1)*2];
    t14_p.nums = temparr14;
    jd1_p.x = &t9_p;
    jd1_p.y = &t10_p;
    jd1_p.z = &t11_p;  
    jd2_p.x = &t12_p;
    jd2_p.y = &t13_p;
    jd2_p.z = &t14_p;  
    clearjdot(&jd1_p);
    clearjdot(&jd2_p);
    trans_dot_jdot(&base_point,&jd1_p);
    scalajdot(&t4_p,&jd1_p,&jd1_p);
    trans_dot_jdot(Q_a,&jd2_p);
    scalajdot(&t5_p,&jd2_p,&jd2_p);
    addjdot(&jd1_p,&jd2_p,&jd1_p);
    trans_jdot_dot(&jd1_p,&d1_p);
    modular(d1_p.x,&order,d1_p.x);
    if(numcomparison(d1_p.x,r)) return 0;    
    return 1;
}*/

void make_rand(number* a){
    srand(time(0));
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    clearnum(&t1_p);
    t1_p.len = 9;
    t1_p.sign = 1;
    for(int i=0;i<9;i++){
         t1_p.nums[i] = (INT)rand()*rand()*rand()*(rand()%100);
    }
    copynum(a,&t1_p);
}

void num_sha512(number* a,number* b){
    string s;
    for(int i=a->len-1;i>=0;i--){
        INT temp = a->nums[i];
        while(temp){
            int t = temp%16;
            if(t>9){
                s+=('a'+t-10);
            }
            else{
                s+=('0'+t);
            }
            temp/=16;
        }
    }
    getnum(sha512(s),b);
}

void encryption(number* a,number* b,number* c){
    baseaddition(a,b,c);
}

void decryption(number* a,number* b,number* c){
    basesubtraction(a,b,c);
}

void hmac(number* a,number* b,number* c){
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    baseaddition(a,b,&t1_p);
    num_sha512(&t1_p,c);
}

void addjdot(jdot* a,jdot* b,jdot* c){
    if(a->inf == 1){
        copyjdot(c,b);
        return;
    }
    if(b->inf == 1){
        copyjdot(c,a);
        return;
    }
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    clearnum(&t1_p);
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    clearnum(&t2_p);
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    clearnum(&t3_p);
    number t4_p;
    INT temparr4[(T+1)*2];
    t4_p.nums = temparr4;
    number t5_p;
    INT temparr5[(T+1)*2];
    t5_p.nums = temparr5;
    clearnum(&t5_p);
    number t6_p;
    INT temparr6[(T+1)*2];
    t6_p.nums = temparr6;
    clearnum(&t6_p);
    number t7_p;
    INT temparr7[(T+1)*2];
    t7_p.nums = temparr7;
    clearnum(&t7_p);
    number t8_p;
    INT temparr8[(T+1)*2];
    t8_p.nums = temparr8;
    number t9_p;
    INT temparr9[(T+1)*2];
    t9_p.nums = temparr9;
    number t10_p;
    INT temparr10[(T+1)*2];
    t10_p.nums = temparr10;
    number t11_p;
    INT temparr11[(T+1)*2];
    t11_p.nums = temparr11;
    number t12_p;
    INT temparr12[(T+1)*2];
    t12_p.nums = temparr12;
    jdot d1_p;
    d1_p.x = &t10_p;
    d1_p.y = &t11_p;
    d1_p.z = &t12_p;
    multiplication(b->z,b->z,&t1_p);
    fred_p521(&t1_p,&t1_p);
    multiplication(a->z,a->z,&t2_p);
    fred_p521(&t2_p,&t2_p);
    multiplication(&t1_p,a->x,&t3_p);
    fred_p521(&t3_p,&t3_p);//u1
    multiplication(&t2_p,b->x,&t4_p);
    fred_p521(&t4_p,&t4_p);//u2 
    multiplication(&t1_p,b->z,&t1_p);
    fred_p521(&t1_p,&t1_p);
    multiplication(&t2_p,a->z,&t2_p);
    fred_p521(&t2_p,&t2_p);
    multiplication(&t1_p,a->y,&t1_p);
    fred_p521(&t1_p,&t1_p);//s1
    multiplication(&t2_p,b->y,&t2_p);
    fred_p521(&t2_p,&t2_p);//s2
    if(numcomparison(&t3_p,&t4_p)==0){
        if(numcomparison(&t1_p,&t2_p)){
            clearjdot(c);
            c->inf = 1;
            return;
        }
        else{
            doublejdot(a,c);
            return;
        }
    }
    clearjdot(&d1_p);
    d1_p.inf=0;
    signsubtraction(&t4_p,&t3_p,&t5_p);
    fred_p521(&t5_p,&t5_p);//h
    signsubtraction(&t2_p,&t1_p,&t6_p);
    fred_p521(&t6_p,&t6_p);//r
    multiplication(&t6_p,&t6_p,&t2_p);
    fred_p521(&t2_p,&t2_p);//r^2
    multiplication(&t5_p,&t5_p,&t4_p);
    fred_p521(&t4_p,&t4_p);//h^2
    multiplication(&t4_p,&t5_p,&t7_p);
    fred_p521(&t7_p,&t7_p);//h^3
    signsubtraction(&t2_p,&t7_p,&t8_p);
    fred_p521(&t8_p,&t8_p);
    multiplication(&t4_p,&t3_p,&t9_p);
    fred_p521(&t9_p,&t9_p);
    lshift(&t9_p,&t9_p);
    fred_p521(&t9_p,&t9_p);
    signsubtraction(&t8_p,&t9_p,&t8_p);
    fred_p521(&t8_p,&t8_p);
    copynum(d1_p.x,&t8_p);
    multiplication(&t3_p,&t4_p,&t8_p);
    fred_p521(&t8_p,&t8_p);
    signsubtraction(&t8_p,d1_p.x,&t8_p);
    multiplication(&t8_p,&t6_p,&t8_p);
    fred_p521(&t8_p,&t8_p);
    multiplication(&t7_p,&t1_p,&t9_p);
    fred_p521(&t9_p,&t9_p);
    signsubtraction(&t8_p,&t9_p,&t9_p);
    fred_p521(&t9_p,&t9_p);
    copynum(d1_p.y,&t9_p);
    multiplication(&t5_p,a->z,&t9_p);
    fred_p521(&t9_p,&t9_p);
    multiplication(&t9_p,b->z,&t9_p);
    fred_p521(&t9_p,&t9_p);
    copynum(d1_p.z,&t9_p);
    copyjdot(c,&d1_p);
    return;
}

void doublejdot(jdot* a,jdot* b){
    if(!numcomparison(a->y,&zero)||a->inf==1){
        clearjdot(b);
        copyjdot(b,a);
        return;
    }
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    clearnum(&t1_p);
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    clearnum(&t2_p);
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    clearnum(&t3_p);
    number t4_p;
    INT temparr4[(T+1)*2];
    t4_p.nums = temparr4;
    number t5_p;
    INT temparr5[(T+1)*2];
    t5_p.nums = temparr5;
    clearnum(&t5_p);
    number t6_p;
    INT temparr6[(T+1)*2];
    t6_p.nums = temparr6;
    clearnum(&t6_p);
    number t7_p;
    INT temparr7[(T+1)*2];
    t7_p.nums = temparr7;
    clearnum(&t7_p);
    number t8_p;
    INT temparr8[(T+1)*2];
    t8_p.nums = temparr8;
    clearnum(&t8_p);
    multiplication(a->y,a->z,&t8_p);
    fred_p521(&t8_p,&t8_p);
    lshift(&t8_p,&t8_p);
    fred_p521(&t8_p,&t8_p);//z'
    lshift(a->y,&t1_p);
    fred_p521(&t1_p,&t1_p);
    multiplication(&t1_p,&t1_p,&t2_p);
    fred_p521(&t2_p,&t2_p);
    multiplication(&t2_p,a->x,&t2_p);
    fred_p521(&t2_p,&t2_p);//S
    multiplication(a->z,a->z,&t3_p);
    baseaddition(a->x,&t3_p,&t4_p);
    fred_p521(&t4_p,&t4_p);
    signsubtraction(a->x,&t3_p,&t5_p);
    fred_p521(&t5_p,&t5_p);
    multiplication(&t4_p,&t5_p,&t5_p);
    fred_p521(&t5_p,&t5_p);
    t6_p.nums[0]=3;
    t6_p.len=1;
    t6_p.sign=1;
    multiplication(&t6_p,&t5_p,&t5_p);
    fred_p521(&t5_p,&t5_p);//M
    multiplication(&t5_p,&t5_p,&t1_p);
    fred_p521(&t1_p,&t1_p);
    lshift(&t2_p,&t3_p);
    signsubtraction(&t1_p,&t3_p,&t3_p);
    fred_p521(&t3_p,&t3_p);//x'
    signsubtraction(&t2_p,&t3_p,&t2_p);
    multiplication(&t2_p,&t5_p,&t2_p);
    fred_p521(&t2_p,&t2_p);
    multiplication(a->y,a->y,&t7_p);
    fred_p521(&t7_p,&t7_p);
    multiplication(&t7_p,&t7_p,&t7_p);
    fred_p521(&t7_p,&t7_p);
    t6_p.nums[0]=8;
    t6_p.len=1;
    t6_p.sign=1;
    multiplication(&t7_p,&t6_p,&t7_p);
    fred_p521(&t7_p,&t7_p);
    signsubtraction(&t2_p,&t7_p,&t7_p);
    fred_p521(&t7_p,&t7_p);//y'
    jdot d1_p;
    d1_p.x = &t3_p;
    d1_p.y = &t7_p;
    d1_p.z = &t8_p;
    copyjdot(b,&d1_p);
    return;
}
void scalajdot(number* a,jdot* b,jdot* c,int k){
    int successful = 1;
    jdot d1_p;
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
    t3_p.nums[0] = 1;
    t3_p.len = 1;
    t3_p.sign = 1;
    d1_p.z = &t3_p;
    d1_p.inf = 1;
    successful&=copynum(&t4_p,a);
    modular(&t4_p,&order,&t4_p);
    dot d2_p;
    number t5_p;
    INT temparr5[(T+1)*2];
    t5_p.nums = temparr5;
    number t6_p;
    INT temparr6[(T+1)*2];
    t6_p.nums = temparr6;
    d2_p.x = &t5_p;
    d2_p.y = &t6_p;
    cleardot(&d2_p);
    INT mask;
    vector<int> v;
    int dp[580][2],chk[580][2],s[580],ad[580];
    if(jdotcomparison(b,&jbin_dot[0])==1){
        int cnt = 0;
        for(int i=0;i<=t4_p.len-1;i++){
            mask = 1;
            while(1){
                if(mask&t4_p.nums[i]){
                    if(k==0) addjdot(&d1_p,&jbin_dot[cnt],&d1_p);
                    v.push_back(1);
                    //cout<<"1";
                }
                else{
                    //cout<<"0";
                    v.push_back(0);
                }
                cnt++;
                if(mask==HIGHBIT) break;
                mask<<=1;
            }
        }
        if(k==0){
            copyjdot(c, &d1_p);
            return;
        }
        //cout<<"\n";
        int n = v.size();
        s[0]=ad[0]=0;
        for(int i=1;i<=n;i++){
            ad[i]=0;
            s[i]=s[i-1]+v[i-1];
        }
        dp[0][0]=dp[0][1]=0;
        for(int i=1;i<=n;i++){
            dp[i][0]=dp[i][1]=580;
            for(int j=0;j<i;j++){
                int t1=dp[j][1]+s[i]-s[j];
                int t2=dp[j][0]+(i-j)-(s[i]-s[j])+2;
                if(t1<dp[i][0]){
                    dp[i][0]=t1;
                    chk[i][0]=j;
                }
                if(t2<dp[i][1]){
                    dp[i][1]=t2;
                    chk[i][1]=j;
                }
            }
        }
        int st = 0,now = n;
        if(dp[n][1]<dp[n][0]) st=1;
        while(now!=0){
            int pre=now;
            now=chk[now][st];
            if(st==1){
                for(int i=now;i<pre;i++){
                    ad[i]-=1-v[i];
                }
                ad[pre]++;
                ad[now]--;
            }
            else{
                for(int i=now;i<pre;i++){
                    ad[i]+=v[i];
                }
            }
            st=1-st;
        }
        for(int i=0;i<=n+1;i++){
            ad[i+1]+=ad[i]/2;
            ad[i]=ad[i]%2;
            if(ad[i]==-1&&ad[i+1]==1){
                ad[i]=1;
                ad[i+1]=0;
            }
            if(ad[i]==1&&ad[i+1]==-1){
                ad[i]=-1;
                ad[i+1]=0;
            }
            //cout<<ad[i];
            if(ad[i]<0){
                jbin_dot[i].y->sign = -jbin_dot[i].y->sign;
            }
            if(ad[i]) addjdot(&d1_p,&jbin_dot[i],&d1_p);
        }

        copyjdot(c, &d1_p);
        return;
    }
    if(jdotcomparison(b,&jpub_bin_dot[0])==1){
        int cnt = 0;
        for(int i=0;i<=t4_p.len-1;i++){
            mask = 1;
            while(1){
                if(mask&t4_p.nums[i]) addjdot(&d1_p,&jpub_bin_dot[cnt],&d1_p);
                cnt++;
                if(mask==HIGHBIT) break;
                mask<<=1;
            }
        }
        copyjdot(c, &d1_p);
        return;
    }
    for(int i=t4_p.len-1;i>=0;i--){
        mask = HIGHBIT;
        while(mask){
            doublejdot(&d1_p,&d1_p);
            if(mask&t4_p.nums[i]) addjdot(&d1_p,b,&d1_p);
            mask>>=1;
        }
    }
    copyjdot(c, &d1_p);
    return;
}

void trans_jdot_dot(jdot* a,dot* b){
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
    dot d1_p;
    d1_p.x = &t3_p;
    d1_p.y = &t4_p;
    cleardot(&d1_p);
    d1_p.inf = a->inf;
    numinv(a->z,&p,&t1_p);
    multiplication(&t1_p,&t1_p,&t2_p);
    fred_p521(&t2_p,&t2_p);
    multiplication(a->x,&t2_p,&t3_p);
    fred_p521(&t3_p,&t3_p);
    multiplication(&t2_p,&t1_p,&t2_p);
    fred_p521(&t2_p,&t2_p);
    multiplication(a->y,&t2_p,&t4_p);
    fred_p521(&t4_p,&t4_p);
    copydot(b,&d1_p);
    return;
}

void trans_dot_jdot(dot* a,jdot* b){
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    clearnum(&t1_p);
    t1_p.nums[0] = 1;
    t1_p.len = 1;
    t1_p.sign = 1;
    jdot d1_p;
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    number t3_p;
    INT temparr3[(T+1)*2];
    t3_p.nums = temparr3;
    number t4_p;
    INT temparr4[(T+1)*2];
    t4_p.nums = temparr4;
    d1_p.x = &t2_p;
    d1_p.y = &t3_p;
    d1_p.z = &t4_p;
    clearjdot(&d1_p);
    d1_p.inf = a->inf;
    copynum(d1_p.x,a->x);
    copynum(d1_p.y,a->y);
    copynum(d1_p.z,&t1_p);
    copyjdot(b,&d1_p);
}

void finiteQaddition(Qnumber* a,Qnumber* b,Qnumber * c){
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    clearnum(&t1_p);
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    clearnum(&t2_p);
    multiplication(a->up,b->down,&t1_p);
    fred_p521(&t1_p,&t1_p);
    multiplication(a->down,b->up,&t2_p);
    fred_p521(&t2_p,&t2_p);
    finiteaddition(&t1_p,&t2_p,c->up);
    multiplication(a->down,b->down,c->down);
    fred_p521(c->down,c->down);
}

void finiteQsubtraction(Qnumber* a,Qnumber* b,Qnumber * c){
    number t1_p;
    INT temparr1[(T+1)*2];
    t1_p.nums = temparr1;
    clearnum(&t1_p);
    number t2_p;
    INT temparr2[(T+1)*2];
    t2_p.nums = temparr2;
    clearnum(&t2_p);
    multiplication(a->up,b->down,&t1_p);
    fred_p521(&t1_p,&t1_p);
    multiplication(a->down,b->up,&t2_p);
    fred_p521(&t2_p,&t2_p);
    finitesubtraction(&t1_p,&t2_p,c->up);
    multiplication(a->down,b->down,c->down);
    fred_p521(c->down,c->down);
}


void Qmultiplication(Qnumber *a,Qnumber *b,Qnumber *c){
    multiplication(a->up,b->up,c->up);
    fred_p521(c->up,c->up);
    multiplication(a->down,b->down,c->down);
    fred_p521(c->down,c->down);
}

void Qnuminv(Qnumber *a,Qnumber *b){
    copynum(b->up,a->down);
    copynum(b->down,a->up);
}

void Qmodular(Qnumber *a,Qnumber *b){
    fred_p521(a->up,b->up);
    fred_p521(a->down,b->down);
}

/*int addQdot(Qdot* a,Qdot* b,Qdot* c){
    int successful = 1;
    dot d1_p;
    if(Qdotcomparison(a, b)==1){
        return successful&doubleQdot(a,c);
    }
    if(Qdotcomparison(a, b)==-1){
        return successful&clearQdot(c);
    }
    if(a->inf == 1){
        return copyQdot(c,b);
    }
    if(b->inf == 1){
        return copyQdot(c,a);
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
    finiteQsubtraction(b->y, a->y, &t3_p);
    finiteQsubtraction(b->x, a->x, &t4_p);
    Qmodular(&t4_p, &t4_p);
    Qnuminv(&t4_p, &p, &t4_p);
    Qmultiplication(&t3_p, &t4_p, &t3_p);
    Qmodular(&t3_p,&t3_p);
    Qmultiplication(&t3_p,&t3_p, d1_p.x);
    Qmodular(d1_p.x,d1_p.x);
    QfiniteQsubtraction(d1_p.x, a->x, d1_p.x);
    finiteQsubtraction(d1_p.x, b->x, d1_p.x);
    Qmodular(d1_p.x,d1_p.x);
    finiteQsubtraction(a->x, d1_p.x, &t4_p);
    Qmultiplication(&t4_p, &t3_p, d1_p.y);
    Qfinitesubtraction(d1_p.y, a->y, d1_p.y);
    Qmodular(d1_p.y,d1_p.y);
    copyQdot(c, &d1_p);
}
int doubleQdot(Qdot* a,Qdot* b){
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
    successful&=fred_p521(&t3_p, &t3_p);
    successful&=multiplication(&t3_p, a->x, &t3_p);
    successful&=signaddition(&coa, &t3_p, &t3_p);
    successful&=fred_p521(&t3_p, &t3_p);
    successful&=multiplication(&t4_p, a->y, &t4_p);
    successful&=fred_p521(&t4_p, &t4_p);    
    successful&=numinv(&t4_p, &p, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, &t3_p);
    successful&=fred_p521(&t3_p,&t3_p);
    successful&=multiplication(&t3_p, &t3_p, d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=signsubtraction(d1_p.x, a->x, d1_p.x);
    successful&=fred_p521(d1_p.x, d1_p.x);
    successful&=signsubtraction(a->x, d1_p.x, &t4_p);
    successful&=multiplication(&t4_p, &t3_p, d1_p.y);
    successful&=signsubtraction(d1_p.y, a->y, d1_p.y);
    successful&=fred_p521(d1_p.y, d1_p.y);
    successful&=copydot(b,&d1_p);
    return successful;
}*/

