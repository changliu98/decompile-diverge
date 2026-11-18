int MD5_Init (MD5_CTX *c)
 {
 c->A=(unsigned long)0x67452301L;
 c->B=(unsigned long)0xefcdab89L;
 c->C=(unsigned long)0x98badcfeL;
 c->D=(unsigned long)0x10325476L;

 c->Nl=0;
 c->Nh=0;
 c->num=0;
 return 1;
 }