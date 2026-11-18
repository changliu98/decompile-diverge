void sun_gpstime2mjulianday(int gps_week, double gps_seconds, long *out) {
    long modified_julian_day;
    
    // Calculate the Modified Julian Day (MJD)
    // 0x7 is 7 (days in a week)
    // 0xe14(%rip) loads a double constant, which is 86400.0 (seconds in a day)
    // 0xacd4 is 44244 (the Modified Julian Day for the GPS epoch: January 6, 1980)
    
    modified_julian_day = (long)gps_week * 7 + (long)(gps_seconds / 86400.0) + 44244;
    
    // Store the result into the pointer provided in the 3rd argument
    *out = modified_julian_day;
}