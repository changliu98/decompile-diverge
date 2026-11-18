
float v_inner(float *v1,float *v2,int n)
{
    int i;
    float innerprod;

    for(i=0,innerprod=0.0; i < n; i++)
        innerprod += v1[i] * v2[i];
    return(innerprod);
}
