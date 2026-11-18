int func0(int n) {
    int largest_power = 0;
    int i = n;
    
    while (i > 0) {
        // A number is a power of 2 if it's greater than 0 and (i & (i - 1)) == 0
        if ((i & (i - 1)) == 0) {
            largest_power = i;
            break;
        }
        i--;
    }
    
    return largest_power;
}