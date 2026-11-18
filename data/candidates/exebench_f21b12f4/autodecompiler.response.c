void
nm_writel(unsigned long v, unsigned char *to) {
    ((((char*)(to))[7]=((unsigned int)((unsigned long)(v) >> 56) & 0xff)), (((char*)(to))[6]=((unsigned int)((unsigned long)(v) >> 48) & 0xff)), (((char*)(to))[5]=((unsigned int)((unsigned long)(v) >> 40) & 0xff)), (((char*)(to))[4]=((unsigned int)((unsigned long)(v) >> 32) & 0xff)), (((char*)(to))[3]=((unsigned int)((unsigned int)v)>>(24))), (((char*)(to))[2]=((unsigned int)((unsigned int)v)>>(16))), (((char*)(to))[1]=((unsigned int)((unsigned int)v)>>(8))), (((char*)(to))[0]=((unsigned int)((unsigned int)v)>>(0))));
}