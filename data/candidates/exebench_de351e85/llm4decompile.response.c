void P_stats(float prcp[24], int *rain_hrs, int *conseq_hrs, int *st_hr,
            float *max_p, int *max_hr, int mo, int *pflag)
# 135 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/Giswater/giswater_models/refs/heads/master/SWMM2D/SWMM/Engine/precip.c"
{
    int i;
    int tmp_hrs = 0;


    *rain_hrs = 0;
    *max_hr = 0;
    *max_p = 0.0;
    *conseq_hrs = 0;
    *st_hr = 0;


    for (i = 0; i < 24; i++)
    {
        if ( prcp[i] > 0.0 )
        {
            (*rain_hrs)++;
            if ( prcp[i] > *max_p )
            {
                *max_p = prcp[i];
                *max_hr = i;
            }
        }
    }


    for (i = 0; i < 24; i++)
    {
        pflag[i] = 0;
        if ( prcp[i] > 0.0 )
        {
            tmp_hrs++;
            pflag[i] = 1;
        }
        else
        {
            if ( tmp_hrs > *conseq_hrs )
            {
                *conseq_hrs = tmp_hrs;
                *st_hr = i - *conseq_hrs;
                tmp_hrs = 0;
            }
        }
    }
    if ( tmp_hrs > *conseq_hrs )
    {
        *conseq_hrs = tmp_hrs;
        *st_hr = i - *conseq_hrs;
    }
}