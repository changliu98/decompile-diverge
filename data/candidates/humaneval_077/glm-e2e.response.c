int func0(int n) {
    int i = 0;
    int result;

    while (1) {
        int cube = i * i * i;
        
        if (cube > abs(n)) {
            result = 0;
            break;
        }
        
        if (cube == abs(n)) {
            result = 1;
            break;
        }
        
        i++;
    }
    
    return result;
}