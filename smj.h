#define W 64
#define T 9
#define FRED 1
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
struct Qnumber{
    number* up;
    number* down;
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
struct jdot{
    number* x;
    number* y;
    number* z;
    int inf;
};
/*
 brief : a struct that represents a affine point on an elliptic curve on jacobian coordinates
 param x,y,z : the jacobian coordinate of the dot
*/
struct Qdot{
    Qnumber* x;
    Qnumber* y;
    int inf;
};

void client1();
void client2();
void client3();
void server1();
int server2();
int server3();

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
int fred_p521(number *a,number *b);
/*
 brief : fast reduction on p_521(2^521 - 1)
 param a : a number pointer(input)
 param b : a number pointer(output)
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
void make_rand(number* a);
/*
 brief : makes random number and returns to a
*/
void num_sha512(number* a,number* b);
/*
 brief : returns sha512(a) and returns to b
 param a : the value wants to be hashed
 param b : sha512(a)
*/
void encryption(number* a,number* b,number* c);
/*
 brief : encrypts a by b and returns to c
 param a : the value wants to be encrpted
 param b : the encryption key
 param c : the encrpted value
*/
void decryption(number* a,number* b,number* c);
/*
 brief : decrypts a by b and returns to c
 param a : the value wants to be decrpted
 param b : the decryption key
 param c : the decrpted value
*/
void hmac(number* a,number* b,number* c);
/*
 brief :  returns hmac(a,b) to c
 param a : the value going to be hmac
 param b : the value going to be hmac
 param c : hmac(a,b)
*/
void scalajdot(number* a,jdot* b,jdot* c,int k);
void addjdot(jdot* a,jdot* b,jdot* c);
void doublejdot(jdot* a,jdot* b);
int clearjdot(jdot* a);
void printjdot(jdot* a);
void trans_jdot_dot(jdot* a,dot* b);
void trans_dot_jdot(dot* a,jdot* b);
int jdotcomparison(jdot* a,jdot* b);
void trans_Qnum_num(Qnumber* a,number* b);
void trans_num_Qnum(number* a,Qnumber* b);
void trans_Qdot_dot(Qdot* a,dot* b);
void trans_dot_Qdot(dot* a,Qdot* b);
void finiteQaddition(Qnumber* a,Qnumber* b,Qnumber * c);
void finiteQsubtraction(Qnumber* a,Qnumber* b,Qnumber * c);
void Qmultiplication(Qnumber *a,Qnumber *b,Qnumber *c);
void Qnuminv(Qnumber *a,Qnumber *b);
void Qmodular(Qnumber *a,Qnumber *b);
