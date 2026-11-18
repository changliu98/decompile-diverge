void shiftarray(int* a) {
    int i;
    for (i=0; i<10 -1; i++) *(a+i)=*(a+i+1);
    *(a+10 -1)=-1;
}