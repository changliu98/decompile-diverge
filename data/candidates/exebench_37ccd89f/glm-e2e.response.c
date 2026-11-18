void ft_ultimate_div_mod(int *a, int *b) {
    int div = *a / *b;
    int mod = *a - (div * *b);
    
    *b = mod;
    *a = div;
}