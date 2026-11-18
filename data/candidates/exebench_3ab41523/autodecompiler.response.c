void point_computing(double weights[4], double x[4], double y[4], double *xc, double *yc)
{
 double sumWeights = weights[0] + weights[1] + weights[2] + weights[3];
 *xc = (weights[0]*x[0] + weights[1]*x[1] + weights[2]*x[2] + weights[3]*x[3])/sumWeights;
 *yc = (weights[0]*y[0] + weights[1]*y[1] + weights[2]*y[2] + weights[3]*y[3])/sumWeights;
}