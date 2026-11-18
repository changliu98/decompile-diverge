int setLoopIters( double tMin, double tScale, double threshold_hi,
                  unsigned int *NLOOP )
{
    double timeMin;

    timeMin = tMin*tScale*(*NLOOP);
    if( timeMin > threshold_hi ){
        (*NLOOP) = (*NLOOP)*threshold_hi / timeMin;
        if( (*NLOOP) < 2 ) *NLOOP = 2;
    }

    return 0;
}