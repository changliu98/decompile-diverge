void normalize_angle(double *angle) {
    // Loop to reduce the angle until it is <= 360.0
    while (*angle > 360.0) {
        *angle -= 360.0;
    }
    
    // Loop to increase the angle until it is >= 0.0
    while (*angle < 0.0) {
        *angle += 360.0;
    }
}