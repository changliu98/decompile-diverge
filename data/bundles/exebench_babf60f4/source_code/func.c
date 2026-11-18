
void matmult(float* A,float* B,float *C){

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            C[i+j*4]=0.0;
            for(int k=0;k<4;k++){
                C[i+j*4]+=A[i+k*4]*B[k+j*4];

            }
        }
    }
}
