void numpar(double *param, int *len, int *out)
{
    int i=-1,j=0,k=0;
    int jump[*len];
    int count=-1;
    double diff=0;
    while(i<(*len-1)) {
        i++;
        for(j=0; j<count; j++)
            if(i==jump[j]) i++;
        k = i+1;
        while(k<*len) {
            for(j=0; j<count; j++)
                if(k==jump[j]) k++;
            diff = param[i]-param[k];
            if(diff<0) diff *= (-1);
            if(diff==0) {
                count++;
                jump[count] = k;
                (*out) = (*out)-1;
            }
            k++;
        }
    }
}