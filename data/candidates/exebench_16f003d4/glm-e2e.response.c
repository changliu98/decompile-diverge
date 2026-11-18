void calc_speed(double *pos, double *speed, double *accel, double dt) {
    for (int i = 0; i <= 18; i += 6) {
        for (int j = 0; j < 3; j++) {
            int idx = i + j;
            
            // Calculate the derivative of position (velocity)
            double d_pos = (accel[idx] - pos[idx]) / 2.0;
            
            // Calculate the derivative of velocity (acceleration)
            double d_speed = (accel[idx] + pos[idx]) / 2.0 - speed[idx];
            
            // Update the speed array using Euler integration
            speed[idx + 3] = (2.0 * d_speed + d_pos) / dt;
        }
    }
}