void
_elf_store_u64L(unsigned long long v, unsigned char *to) {
    ((to)[0]=((unsigned int)((unsigned int)v)),((to))[1]=((unsigned int)((unsigned int)((v)>>8))),((to))[2]=((unsigned int)((unsigned int)((v)>>16))),((to))[3]=((unsigned int)((unsigned int)((v)>>24))),((to))[4]=((unsigned int)((unsigned int)((v)>>32))),((to))[5]=((unsigned int)((unsigned int)((v)>>40))),((to))[6]=((unsigned int)((unsigned int)((v)>>48))),((to))[7]=((unsigned int)((unsigned int)((v)>>56))));
}