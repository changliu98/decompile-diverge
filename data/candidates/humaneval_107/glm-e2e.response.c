Counts* func0(int n) {
    Counts* counts = (Counts*)malloc(sizeof(Counts));
    counts->even_count = 0;
    counts->odd_count = 0;
    
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        int temp = i;
        
        while (temp != 0) {
            sum += temp % 10;
            temp /= 10;
        }
        
        if (i == sum) { // Check if the number is equal to the sum of its digits (always true for base 10)
            if (i % 2 == 0) {
                counts->even_count++;
            } else {
                counts->odd_count++;
            }
        }
    }
    
    return counts;
}