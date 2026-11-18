int __cdecl setLoopIters(double tMin, double tScale, double threshold_hi, unsigned int *NLOOP)
{
    // Cast once to signed 32-bit to match the original arithmetic semantics
    int current_loops = (int)*NLOOP;
    
    // Calculate the total time based on the minimum time per iteration, 
    // a scaling factor, and the number of iterations.
    double total_time = tMin * tScale * (double)current_loops;

    // If the estimated total time exceeds the upper threshold, scale down the loops
    if (total_time > threshold_hi)
    {
        // Calculate the new number of loops proportionally based on the threshold
        int new_loops = (int)((double)current_loops * threshold_hi / total_time);

        // Enforce a minimum loop count of 2 to prevent infinite or zero-length loops
        if (new_loops < 2) {
            new_loops = 2;
        }

        // Write the adjusted loop count back to the pointer
        *NLOOP = (unsigned int)new_loops;
    }

    return 0;
}