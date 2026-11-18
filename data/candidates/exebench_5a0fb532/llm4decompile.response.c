unsigned char pop(unsigned char *stack,int *position)
{
    unsigned char ret;
    if(*position>=100||*position<0)
        return -1;
    ret=stack[*position];
    *position-=1;
    return ret;
}