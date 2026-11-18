float mayorDif(float *arrayLineal){
    float mayor=0;
    float diferencia=0;
    int i=0;
    while(arrayLineal[i+1]!=0){
        diferencia=arrayLineal[i]-arrayLineal[i+1];
        if(diferencia<0)
            diferencia=-diferencia;
        if(diferencia>mayor)
            mayor=diferencia;
        i++;
    }
    return mayor;
}