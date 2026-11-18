float _RGB(float H,float M1,float M2)
{
    float val;

    if(H<0.0)
        H+=1.0;
    else if(H>1.0)
        H-=1.0;

    if(H<1.0/6.0)
        val=M1+(M2-M1)*H*6.0;
    else if(H<3.0/6.0)
        val=M2;
    else if(H<4.0/6.0)
        val=M1+(M2-M1)*(4.0/6.0-H)*6.0;
    else
        val=M1;

    return val;
}