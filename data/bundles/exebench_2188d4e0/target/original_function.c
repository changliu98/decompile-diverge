void f(int* a, int* b){
    (*a > *b) ? (*a /= 2, *b *= 2) : (*a *= 2, *b /= 2);
}