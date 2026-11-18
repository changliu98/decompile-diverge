int func0(int a, int b) {
    int lcm;
    if (a > b) {
        lcm = a;
    } else {
        lcm = b;
    }
    
    while (lcm % a != 0 || lcm % b != 0) {
        lcm++;
    }
    
    return lcm;
}