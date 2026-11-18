void GivensApply(double c, double s, double *x, double *y) {
    double x_val = *x;
    double y_val = *y;
    
    // Apply Givens rotation
    double new_x = c * x_val + s * y_val;
    double new_y = c * (-x_val) + s * y_val;
    
    *y = new_y;
    *x = new_x;
}