
void unpack_dxt(unsigned char mask, unsigned short col1, unsigned short col2,
                unsigned char *target)
{
    unsigned short r1,g1,b1,r2,g2,b2;
    r1=8*(col1&31); g1=4*((col1>>5)&63); b1=8*(col1>>11);
    r2=8*(col2&31); g2=4*((col2>>5)&63); b2=8*(col2>>11);

    switch (mask) {
        case 0: target[0]=r1; target[1]=g1; target[2]=b1; break;
        case 1: target[0]=r2; target[1]=g2; target[2]=b2; break;
        case 2:
            if (col1>col2) {
                target[0]=(2*r1+r2)/3; target[1]=(2*g1+g2)/3; target[2]=(2*b1+b2)/3;
            } else {
                target[0]=(r1+r2)/2; target[1]=(g1+g2)/2; target[2]=(b1+b2)/2;
            } break;
        case 3:
            if (col1>col2) {
                target[0]=(r1+2*r2)/3; target[1]=(g1+2*g2)/3; target[2]=(b1+2*b2)/3;
            } else {
                target[0]=target[1]=target[2]=0;
            } break;
    }
}
