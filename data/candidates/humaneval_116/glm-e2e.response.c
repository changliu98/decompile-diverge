int func0(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int count1 = 0;
            int val1 = arr[i];
            int val2 = arr[j];
            
            // Count set bits in val1
            while (val1 > 0) {
                count1 += val1 & 1;
                val1 >>= 1;
            }
            val1 = count1;
            
            // Count set bits in val2
            int count2 = 0;
            while (val2 > 0) {
                count2 += val2 & 1;
                val2 >>= 1;
            }
            val2 = count2;
            
            // Swap if val2 is strictly less than val1, 
            // or if they are equal but arr[j] < arr[i]
            if (val2 < val1 || (val2 == val1 && arr[j] < arr[i])) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return 0;
}