__cdecl is omitted as it is the default x64 calling convention
int getPossibleCount(int *candidates, int *last_valid_candidate) 
{
    int valid_count = 0;
    
    // Iterate through exactly 9 candidates (typical for a Sudoku row, column, or 3x3 box)
    for (int i = 0; i < 9; ++i) 
    {
        // A non-zero value indicates a valid candidate
        if (candidates[i]) 
        {
            ++valid_count;
            
            // Continuously overwrite the output pointer with the latest found candidate.
            // If exactly one candidate is found, 'last_valid_candidate' will point to it.
            // If multiple are found, it will point to the last one in the array.
            *last_valid_candidate = candidates[i];
        }
    }
    
    return valid_count;
}