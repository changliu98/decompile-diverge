int func0(int n) {
    int count = 0;
    int power_of_2 = 1;
    
    while (power_of_2 < n + 1) {
        if ((n & power_of_2) == 0) {
            count++;
        }
        power_of_2 <<= 1;
    }
    
    return count;
}