void __cdecl GetLims(double *times, double t_start, double t_end, int Q, int *q_start, int *q_end)
{
    bool found_start = false;
    bool found_end = false;

    // If the array is empty, return an invalid range
    if (Q <= 0)
    {
        *q_start = 0;
        *q_end = -1;
        return;
    }

    for (int q = 0; q < Q; ++q)
    {
        double cur_time = times[q];

        // If the very first element is already past t_end, the range is empty
        if (!found_start && cur_time >= t_end)
        {
            *q_start = 0;
            *q_end = -1;
            found_start = true;
            found_end = true;
        }
        // Mark the start of the range when we hit or exceed t_start
        else if (!found_start && cur_time >= t_start)
        {
            *q_start = q;
            found_start = true;
        }
        // Mark the end of the range when we hit or exceed t_end
        else if (!found_end && cur_time >= t_end)
        {
            *q_end = q - 1;
            found_end = true;
        }
    }

    // Post-loop adjustments based on what we found
    if (found_start)
    {
        // If we found a start but never hit t_end, the range extends to the end of the array
        if (!found_end)
        {
            *q_end = Q - 1;
        }
    }
    else
    {
        // If we never found a start, the range is empty
        *q_start = 0;
        *q_end = -1;
    }
}