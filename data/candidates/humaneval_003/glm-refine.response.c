bool func0(const int *operations, int size)
{
    int running_sum = 0;

    for (int i = 0; i < size; ++i)
    {
        running_sum += operations[i];
        
        // If the running sum ever drops below zero, return 1 (true)
        if (running_sum < 0)
            return 1;
    }
    
    // If the loop finishes without the sum dropping below zero, return 0 (false)
    return 0;
}