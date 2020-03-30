#include <bits/stdc++.h>
#include "smj.h"

number cmessage,PIN,cenc_message,chash_message,cenc_private_key,cr,cs,crand_num,cy2,cs_a,cs_b,cs_x,ckey,caccess_key,cA,cprivate_key;

void client1(){
    assignnumber(&cenc_private_key,(T+1)*2);
    getnum("2009DED0887002CE43AD59FF28D5C465F2B485751E2FB525273589F47FA7FF9BE2830755A34931915BD549164DA39CE61A591F2682C7EA65C5EF1B1B46524C44F28",&cenc_private_key);
    FILE* m1 = fopen("message.txt","rb");
    FILE* pin = fopen("pin.txt","rb");
    assignnumber(&cmessage,(T+1)*2);
    assignnumber(&chash_message,(T+1)*2);
    assignnumber(&PIN,(T+1)*2);
    fgetnum(m1,&cmessage,66);
    fgetnum(pin,&PIN,66);
    fclose(m1);
    fclose(pin);
    num_sha512(&cmessage,&chash_message);
}

void client2(){
    assignnumber(&crand_num,(T+1)*2);
    assignnumber(&cs_a,(T+1)*2);
    assignnumber(&cs_b,(T+1)*2);
    assignnumber(&cy2,(T+1)*2);
    FILE* client_in = fopen("server.txt","rb");
    fgetnum(client_in,&crand_num,66);
    fclose(client_in);
    num_sha512(&PIN,&cs_a);
    hmac(&crand_num,&cs_a,&cy2);
    num_sha512(&PIN,&cs_b);
    FILE* client_out = fopen("client.txt","wb");
    fwritenum(client_out,&cy2,66);
    fclose(client_out);
}

void client3(){
    assignnumber(&cs_x,(T+1)*2);
    assignnumber(&ckey,(T+1)*2);
    assignnumber(&cA,(T+1)*2);
    assignnumber(&caccess_key,(T+1)*2);
    assignnumber(&cprivate_key,(T+1)*2);
    assignnumber(&cenc_message,(T+1)*2);
    assignnumber(&cr,(T+1)*2);
    assignnumber(&cs,(T+1)*2);
    FILE* client_in = fopen("server.txt","rb");
    fgetnum(client_in,&cs_x,66);
    fgetnum(client_in,&ckey,66);
    fclose(client_in);
    decryption(&cs_x,&cs_b,&cA);
    num_sha512(&cA,&caccess_key);
    decryption(&cenc_private_key,&caccess_key,&cprivate_key);
    encryption(&cmessage,&ckey,&cenc_message);
    get_signature(&cprivate_key,&chash_message,&cr,&cs);
    FILE* client_out = fopen("client.txt","wb");
    fwritenum(client_out,&cenc_message,66);
    fwritenum(client_out,&cr,66);
    fwritenum(client_out,&cs,66);
    fwritenum(client_out,&chash_message,66);
    fclose(client_out);
}

