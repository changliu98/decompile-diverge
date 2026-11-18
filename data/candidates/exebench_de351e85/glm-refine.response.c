void __cdecl P_stats(
        float *prcp,
        int *rain_hrs,
        int *conseq_hrs,
        int *st_hr,
        float *max_p,
        int *max_hr,
        int mo,          // Unused parameter
        int *pflag)
{
    int current_streak = 0;
    int i;

    // Initialize output pointers
    *rain_hrs = 0;
    *max_hr = 0;
    *max_p = 0.0f;
    *conseq_hrs = 0;
    *st_hr = 0;

    // Pass 1: Calculate total rain hours and find the hour with maximum precipitation
    for (i = 0; i < 24; ++i)
    {
        if (prcp[i] > 0.0f)
        {
            ++(*rain_hrs);
            if (prcp[i] > *max_p)
            {
                *max_p = prcp[i];
                *max_hr = i;
            }
        }
    }

    // Pass 2: Build precipitation flag array and find the longest consecutive dry spell
    for (i = 0; i < 24; ++i)
    {
        pflag[i] = 0;
        
        if (prcp[i] <= 0.0f)
        {
            // Dry hour: increment dry streak
            ++current_streak;
        }
        else
        {
            // Rain hour: mark flag and reset dry streak
            pflag[i] = 1;
            current_streak = 0;
        }

        // Update maximum consecutive dry hours if the current streak is longer
        // (Note: This evaluates on every iteration, matching the original logic)
        if (current_streak > *conseq_hrs)
        {
            *conseq_hrs = current_streak;
            *st_hr = i - *conseq_hrs + 1; // Start hour of the dry spell
        }
    }
}