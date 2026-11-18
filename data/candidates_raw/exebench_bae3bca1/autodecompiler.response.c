void bn_sqr_comba8(BN_ULONG *r, const BN_ULONG *a)
 {
 BN_ULONG t1,t2;
 unsigned long c1,c2,c3;

 c1=0;
 c2=0;
 c3=0;
 do { asm ("mulq %2" : "=a"(t1),"=d"(t2) : "a"(a[0]) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c1),"+d"(t2) : "a"(t1),"g"(0) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c2),"+r"(c3) : "d"(t2),"g"(0) : "cc"); } while (0);
 r[0]=c1;
 c1=0;
 do { asm ("mulq %3" : "=a"(t1),"=d"(t2) : "a"((a[1])),"g"((a[0])) : "cc"); asm ("addq %0,%0; adcq %2,%1" : "+d"(