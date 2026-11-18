void increment(unsigned int* n){
    unsigned int x = *n;
    unsigned int w = 1;
    while(x&w){
        x = x^w;
        w<<=1;
    }x = x^w;
    *n = x;

}