void math_matrix_copy(float *from, float *to){
    int i;

    for(i = 0; i < 16; i++){
        to[i] = from[i];
    }
}