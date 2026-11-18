// Computes the Lagrange polynomial interpolation of degree 3 at point t
// using four data points: (temp[0], *q), (temp[1], q[1]), (temp[2], q[2]), (temp[3], q[3])
// temp: array of x-coordinates (nodes)
// q: array of y-coordinates (function values), where q[0] is accessed via *q
// t: the point at which to evaluate the interpolated value
// Returns the interpolated value at t
double lagrange4(double *x_nodes, float *y_values, double eval_point)
{
  // First term: L0(t) * y0, where y0 = *q (i.e., q[0])
  // L0(t) = (t - x1)(t - x2)(t - x3) / ((x0 - x1)(x0 - x2)(x0 - x3))
  return ((double)*y_values * (eval_point - x_nodes[1]) * (eval_point - x_nodes[2]) * (eval_point - x_nodes[3])) /
         ((*x_nodes - x_nodes[1]) * (*x_nodes - x_nodes[2]) * (*x_nodes - x_nodes[3])) +
         // Second term: L1(t) * y1, where y1 = q[1]
         // L1(t) = (t - x0)(t - x2)(t - x3) / ((x1 - x0)(x1 - x2)(x1 - x3))
         ((double)y_values[1] * (eval_point - *x_nodes) * (eval_point - x_nodes[2]) * (eval_point - x_nodes[3])) /
         ((x_nodes[1] - *x_nodes) * (x_nodes[1] - x_nodes[2]) * (x_nodes[1] - x_nodes[3])) +
         // Third term: L2(t) * y2, where y2 = q[2]
         // L2(t) = (t - x0)(t - x1)(t - x3) / ((x2 - x0)(x2 - x1)(x2 - x3))
         ((double)y_values[2] * (eval_point - *x_nodes) * (eval_point - x_nodes[1]) * (eval_point - x_nodes[3])) /
         ((x_nodes[2] - *x_nodes) * (x_nodes[2] - x_nodes[1]) * (x_nodes[2] - x_nodes[3])) +
         // Fourth term: L3(t) * y3, where y3 = q[3]
         // L3(t) = (t - x0)(t - x1)(t - x2) / ((x3 - x0)(x3 - x1)(x3 - x2))
         ((double)y_values[3] * (eval_point - *x_nodes) * (eval_point - x_nodes[1]) * (eval_point - x_nodes[2])) /
         ((x_nodes[3] - *x_nodes) * (x_nodes[3] - x_nodes[1]) * (x_nodes[3] - x_nodes[2]));
}