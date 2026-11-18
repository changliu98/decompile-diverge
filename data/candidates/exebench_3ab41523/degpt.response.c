void point_computing(double *weights, double *x_coords, double *y_coords, double *result_x, double *result_y)
{
    // Calculate the sum of all blending weights
    double weight_sum = *weights + weights[1] + weights[2] + weights[3];
    
    // Compute the weighted average x-coordinate using blending weights and point coordinates
    *result_x = (weights[3] * x_coords[3] + weights[2] * x_coords[2] + *weights * *x_coords + weights[1] * x_coords[1]) / weight_sum;
    
    // Compute the weighted average y-coordinate using blending weights and point coordinates
    *result_y = (weights[3] * y_coords[3] + weights[2] * y_coords[2] + *weights * *y_coords + weights[1] * y_coords[1]) / weight_sum;
}