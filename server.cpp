#include <bits/stdc++.h>
#include "smj.h"

number s_a,s_x,rand_num,y1,y2,r,s,enc_message,hash_message1,hash_message2,message,key;
dot sign_public_key;

void server1(){
    assignnumber(&s_x,(T+1)*2);
    assignnumber(&s_a,(T+1)*2);
    assignnumber(&rand_num,(T+1)*2);
    assignnumber(&y1,(T+1)*2);
    getnum("110690437692D902CFD23005BDA06631D83644899E78DC0A489DA6DC93CB9F9C0CDCD9DD533BC59102DC90155223DF777672328C9149354DE239F48C58F0A1D44A5",&s_x);
    getnum("690437692D902CFD23005BDA16631D83644899E78DC0A489DA6DCA3CB9F9C0CDCD9DD533BC59102DC90155223DF777672328C9149354DE239F48C58F0A1D44A6",&s_a);
    make_rand(&rand_num);
    hmac(&rand_num,&s_a,&y1);
    FILE* server_out = fopen("server.txt","wb");
    fwritenum(server_out,&rand_num,66);
    fclose(server_out);
}

int server2(){
    assignnumber(&key,(T+1)*2);
    assignnumber(&y2,(T+1)*2);
    getnum("1F51D4C215212E34B322BF01F9D7BBD2B23928E44E87DC88E88E98B658867EF4B28A4AD1F8B4A22D05DDC7F364EFE2EA612DC6F25575C757578F0430F8AAD287D99",&key);
    FILE* server_in = fopen("client.txt","rb");
    fgetnum(server_in,&y2,66);
    fclose(server_in);
    if(numcomparison(&y1,&y2)) return 0;
    FILE* server_out = fopen("server.txt","wb");
    fwritenum(server_out,&s_x,66);
    fwritenum(server_out,&key,66);
    fclose(server_out);
    return 1;
}

int server3(){
    number t1,t2;
    assignnumber(&t1,(T+1)*2);
    assignnumber(&t2,(T+1)*2);
    sign_public_key.x= &t1;
    sign_public_key.y= &t2;
    cleardot(&sign_public_key);
    sign_public_key.inf = 0;
    assignnumber(&enc_message,(T+1)*2);
    assignnumber(&r,(T+1)*2);
    assignnumber(&s,(T+1)*2);
    assignnumber(&hash_message1,(T+1)*2);
    assignnumber(&hash_message2,(T+1)*2);
    assignnumber(&enc_message,(T+1)*2);
    assignnumber(&message,(T+1)*2);
    getnum("1BEFE202A7BE69C3150B51DE2BBE18990EE2D9AEF262842573738386C8DE67382A1F25A5B0EE8C5BE0C81896FD4A3A72587F92E42311DFC86F574E0760653ECA3CE",sign_public_key.x);
    getnum("1F51D4C215212E34B322BF01F9D7BBD2B23928E44E87DC88E88E98B658867EF4B28A4AD1F8B4A22D05DDC7F364EFE2EA612DC6F25575C757578F0430F8AAD287D99",sign_public_key.y);
    FILE* server_in = fopen("client.txt","rb");
    fgetnum(server_in,&enc_message,66);
    fgetnum(server_in,&r,66);
    fgetnum(server_in,&s,66);
    fgetnum(server_in,&hash_message2,66);
    fclose(server_in);
    decryption(&enc_message,&key,&message);
    num_sha512(&message,&hash_message1);
    if(numcomparison(&hash_message1,&hash_message2)) return 0;
    if(!verify_signature(&sign_public_key,&hash_message1,&r,&s)) return 0;
    FILE* m2 = fopen("dmessage.txt","wb");
    fwritenum(m2,&message,66);
    return 1;
}

