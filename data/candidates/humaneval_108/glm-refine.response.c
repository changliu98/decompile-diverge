int __cdecl func0(int *n, int size)
{
    int count = 0;
    
    for (int i = 0; i < size; ++i)
    {
        if (n[i] > 0) {
            ++count;
        } 
        else {
            int digit_sum = sum_of_digits(n[i]);
            int leftmost_digit = abs(n[i]);
            
            // Find the leftmost digit
            while (leftmost_digit >= 10) {
                leftmost_digit /= 10;
            }
            
            // Equivalent to the original (digit_sum - leftmost_digit > 0)
            if (digit_sum > leftmost_digit) {
                ++count;
            }
        }
    }
    
    return count;
}