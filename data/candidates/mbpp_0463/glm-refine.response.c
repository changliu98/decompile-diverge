int __cdecl func0(int *arr, int n)
{
    int temp;
    int i;
    int has_positive;       // flag: indicates if we've encountered at least one positive number
    int max_so_far;         // stores the overall maximum product found
    int min_ending_here;    // stores the minimum product ending at the current position
    int max_ending_here;    // stores the maximum product ending at the current position

    max_ending_here = 1;
    min_ending_here = 1;
    max_so_far = 0;
    has_positive = 0;
    
    for (i = 0; i < n; ++i)
    {
        if (arr[i] > 0)
        {
            // For a positive number, the max product grows.
            max_ending_here *= arr[i];
            
            // The min product also grows (becomes less negative or stays at 1).
            if (arr[i] * min_ending_here >= 1)
                min_ending_here = 1;
            else
                min_ending_here = arr[i] * min_ending_here;
                
            has_positive = 1;
        }
        else if (arr[i] < 0)
        {
            // For a negative number, max and min products swap roles.
            temp = max_ending_here;
            
            // The new max product could be formed by multiplying the negative number 
            // with the previous min product. If it drops to 1 or below, reset to 1.
            if (arr[i] * min_ending_here <= 1)
                max_ending_here = 1;
            else
                max_ending_here = arr[i] * min_ending_here;
                
            // The new min product is formed by multiplying the negative number 
            // with the previous max product.
            min_ending_here = arr[i] * temp;
        }
        else // arr[i] == 0
        {
            // A zero resets the running products because any subarray including 0 has a product of 0.
            max_ending_here = 1;
            min_ending_here = 1;
        }
        
        // Update the global maximum if the current running max is greater.
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
    }
    
    // If we never saw a positive number and the max_so_far remained 0 
    // (meaning no negative subarray yielded a product > 0), return 0.
    if (has_positive || max_so_far)
        return max_so_far;
    else
        return 0;
}