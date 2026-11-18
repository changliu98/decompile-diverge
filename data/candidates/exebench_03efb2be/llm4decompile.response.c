void swap(int *array)
{
    int i,j,temp;
    int *pmin,*pmax;
    pmin=pmax=array;
    for(i=0;i<5;i++)
        for(j=i;j<5;j++)
        {
            if(*(array+i*5+j)>*pmax)
                pmax=array+i*5+j;
            if(*(array+i*5+j)<*pmin)
                pmin=array+i*5+j;
        }
    temp=*(array+12);
    *(array+12)=*pmax;
    *pmax=temp;

    temp=*pmin;
    *pmin=*(array+4);
    *(array+4)=temp;

    pmin=array+1;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
        {
            if(i==0&&j==0)
                continue;
            if(*(array+i*5+j)<*pmin)
                pmin=array+i*5+j;
        }
    temp=*pmin;
    *pmin=*(array+20);
    *(array+20)=temp;

    pmin=array+1;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
        {
            if((i==0&&j==0)||(i==0&&j==4))
                continue;
            if(*(array+i*5+j)<*pmin)
                pmin=array+i*5+j;
        }
    temp=*pmin;
    *pmin=*(array+24);
    *(array+24)=temp;

    pmin=array+1;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
        {
            if((i==0&&j==0)||(i==0&&j==4)||(i==4&&j==0))
                continue;
            if(*(array+i*5+j)<*pmin)
                pmin=array+i*5+j;
        }
    temp=*pmin;
    *pmin=*(array+28);
    *(array+28)=temp;
}