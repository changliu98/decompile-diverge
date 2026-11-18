void bn_sqr_comba4(BN_ULONG *r, const BN_ULONG *a)
 {
 BN_ULONG t1,t2;
 unsigned long c1,c2,c3;

 c1=0;
 c2=0;
 c3=0;
 do { asm ("mulq %2" : "=a"(t1),"=d"(t2) : "a"(a[0]) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c1),"+d"(t2) : "a"(t1),"g"(0) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c2),"+d"(t2) : "a"(t1),"g"(0) : "cc"); } while (0);
 r[0]=c1;
 c1=0;
 do { asm ("mulq %3" : "=a"(t1),"=d"(t2) : "a"((a)[1]),"m"((a)[0]) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c1) : "r"(0) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c1) : "r"(0) : "cc"); } while (0);
 do { asm ("mulq %2" : "=a"(t1),"=d"(t2) : "a"((a)[1]) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c2),"+d"(t2) : "a"(t1),"g"(0) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c3),"+d"(t2) : "a"(t1),"g"(0) : "cc"); } while (0);
 r[1]=c2;
 c2=0;
 do { asm ("mulq %2" : "=a"(t1),"=d"(t2) : "a"((a)[1]) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c3),"+d"(t2) : "a"(t1),"g"(0) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c2),"+d"(t2) : "a"(t1),"g"(0) : "cc"); } while (0);
 r[2]=c3;
 c3=0;
 do { asm ("mulq %3" : "=a"(t1),"=d"(t2) : "a"((a)[2]),"m"((a)[0]) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c3) : "r"(0) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c3) : "r"(0) : "cc"); } while (0);
 do { asm ("mulq %3" : "=a"(t1),"=d"(t2) : "a"((a)[2]),"m"((a)[1]) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c3) : "r"(0) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c3) : "r"(0) : "cc"); } while (0);
 r[3]=c3;
 c3=0;
 do { asm ("mulq %2" : "=a"(t1),"=d"(t2) : "a"((a)[2]) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c2),"+d"(t2) : "a"(t1),"g"(0) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c3),"+d"(t2) : "a"(t1),"g"(0) : "cc"); } while (0);
 r[4]=c2;
 c2=0;
 do { asm ("mulq %3" : "=a"(t1),"=d"(t2) : "a"((a)[3]),"m"((a)[0]) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c2) : "r"(0) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c2) : "r"(0) : "cc"); } while (0);
 do { asm ("mulq %3" : "=a"(t1),"=d"(t2) : "a"((a)[3]),"m"((a)[1]) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c2) : "r"(0) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c2) : "r"(0) : "cc"); } while (0);
 do { asm ("mulq %3" : "=a"(t1),"=d"(t2) : "a"((a)[3]),"m"((a)[2]) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c2) : "r"(0) : "cc"); asm ("addq %0,%0; adcq %1,%1" : "+d"(t2),"+r"(c2) : "r"(0) : "cc"); } while (0);
 r[5]=c2;
 c2=0;
 do { asm ("mulq %2" : "=a"(t1),"=d"(t2) : "a"((a)[3]) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c3),"+d"(t2) : "a"(t1),"g"(0) : "cc"); asm ("addq %2,%0; adcq %3,%1" : "+r"(c2),"+d"(t2) : "a"(t1),"g"(0) : "cc"); } while (0);
 r[6]=c3;
 r[7]=c2;
 }