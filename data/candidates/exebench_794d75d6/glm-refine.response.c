void __cdecl AdjustSpan2(int *start, int *u, int *len, int max)
{
    // Step 1: Clamp the lower bound
    // If the start is negative, shift the span to 0.
    if (*start < 0)
    {
        // Decrease the length by the negative overlap.
        *len += *start; 
        
        // Advance the offset 'u' to compensate for the shift. 
        // (e.g., if start is -5, we move 5 units forward)
        *u -= *start;   
        
        // Reset the start boundary to 0.
        *start = 0;
    }

    // Step 2: Clamp the upper bound
    // If the span exceeds the maximum boundary, truncate the length.
    if (*start + *len > max)
    {
        *len = max - *start;
    }
}