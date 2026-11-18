void quad_2_grad(double *gradient, double *linear_coefficients, double *hessian_matrix, double *position_vector)
{
    // Compute the gradient components for a quadratic function
    // grad[0] = g[0] + H[0]*r[0] + H[1]*r[1]
    gradient[0] = linear_coefficients[0] + hessian_matrix[0] * position_vector[0] + hessian_matrix[1] * position_vector[1];
    // grad[1] = g[1] + H[1]*r[0] + H[2]*r[1]
    gradient[1] = linear_coefficients[1] + hessian_matrix[1] * position_vector[0] + hessian_matrix[2] * position_vector[1];
}