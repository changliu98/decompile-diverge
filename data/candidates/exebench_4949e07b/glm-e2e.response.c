void cftx020(double *ptr) {
    double temp1 = ptr[0] - ptr[2];
    double temp2 = ptr[1] - ptr[3];
    
    ptr[0] += ptr[2];
    ptr[1] += ptr[3];
    
    ptr[2] = temp1;
    ptr[3] = temp2;
}