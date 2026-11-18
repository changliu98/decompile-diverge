void bn_mul_comba4(BN_ULONG *r, BN_ULONG *a, BN_ULONG *b)
 {
 BN_ULONG c1,c2,c3;

 c1=0;
 c2=0;
 c3=0;
 { unsigned long l,h; h=(((unsigned long)(a[0]))*((unsigned long)(b[0]))); l=((unsigned long)(a[0])*(unsigned long)(b[0])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 r[0]=c1;
 c1=0;
 { unsigned long l,h; h=(((unsigned long)(a[0]))*((unsigned long)(b[1]))); l=((unsigned long)(a[0])*(unsigned long)(b[1])); asm ("add %2,%0; adc %3,%1" : "+r"(c2),"+r"(c3) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[1]))*((unsigned long)(b[0]))); l=((unsigned long)(a[1])*(unsigned long)(b[0])); asm ("add %2,%0; adc %3,%1" : "+r"(c2),"+r"(c3) : "l"(l),"g"(h)); };
 r[1]=c2;
 c2=0;
 { unsigned long l,h; h=(((unsigned long)(a[2]))*((unsigned long)(b[0]))); l=((unsigned long)(a[2])*(unsigned long)(b[0])); asm ("add %2,%0; adc %3,%1" : "+r"(c3),"+r"(c1) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[1]))*((unsigned long)(b[1]))); l=((unsigned long)(a[1])*(unsigned long)(b[1])); asm ("add %2,%0; adc %3,%1" : "+r"(c3),"+r"(c1) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[0]))*((unsigned long)(b[2]))); l=((unsigned long)(a[0])*(unsigned long)(b[2])); asm ("add %2,%0; adc %3,%1" : "+r"(c3),"+r"(c1) : "l"(l),"g"(h)); };
 r[2]=c3;
 c3=0;
 { unsigned long l,h; h=(((unsigned long)(a[0]))*((unsigned long)(b[3]))); l=((unsigned long)(a[0])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[3]))*((unsigned long)(b[0]))); l=((unsigned long)(a[3])*(unsigned long)(b[0])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[2]))*((unsigned long)(b[1]))); l=((unsigned long)(a[2])*(unsigned long)(b[1])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[1]))*((unsigned long)(b[2]))); l=((unsigned long)(a[1])*(unsigned long)(b[2])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[0]))*((unsigned long)(b[3]))); l=((unsigned long)(a[0])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 r[3]=c1;
 c1=0;
 { unsigned long l,h; h=(((unsigned long)(a[1]))*((unsigned long)(b[3]))); l=((unsigned long)(a[1])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c2),"+r"(c3) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[2]))*((unsigned long)(b[2]))); l=((unsigned long)(a[2])*(unsigned long)(b[2])); asm ("add %2,%0; adc %3,%1" : "+r"(c2),"+r"(c3) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[3]))*((unsigned long)(b[1]))); l=((unsigned long)(a[3])*(unsigned long)(b[1])); asm ("add %2,%0; adc %3,%1" : "+r"(c2),"+r"(c3) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[3]))*((unsigned long)(b[0]))); l=((unsigned long)(a[3])*(unsigned long)(b[0])); asm ("add %2,%0; adc %3,%1" : "+r"(c2),"+r"(c3) : "l"(l),"g"(h)); };
 r[4]=c2;
 c2=0;
 { unsigned long l,h; h=(((unsigned long)(a[2]))*((unsigned long)(b[3]))); l=((unsigned long)(a[2])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c3),"+r"(c1) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[3]))*((unsigned long)(b[2]))); l=((unsigned long)(a[3])*(unsigned long)(b[2])); asm ("add %2,%0; adc %3,%1" : "+r"(c3),"+r"(c1) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[1]))*((unsigned long)(b[3]))); l=((unsigned long)(a[1])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c3),"+r"(c1) : "l"(l),"g"(h)); };
 r[5]=c3;
 c3=0;
 { unsigned long l,h; h=(((unsigned long)(a[3]))*((unsigned long)(b[3]))); l=((unsigned long)(a[3])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[2]))*((unsigned long)(b[3]))); l=((unsigned long)(a[2])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[1]))*((unsigned long)(b[3]))); l=((unsigned long)(a[1])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 { unsigned long l,h; h=(((unsigned long)(a[0]))*((unsigned long)(b[3]))); l=((unsigned long)(a[0])*(unsigned long)(b[3])); asm ("add %2,%0; adc %3,%1" : "+r"(c1),"+r"(c2) : "l"(l),"g"(h)); };
 r[6]=c1;
 }