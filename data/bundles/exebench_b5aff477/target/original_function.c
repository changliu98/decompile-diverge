float dotprod(float* vector,float* vector2,int len){
    float dot=0;
    for(int i=0;i<len;i++){
        dot+=vector[i]*vector2[i];
    }
    return dot;
}