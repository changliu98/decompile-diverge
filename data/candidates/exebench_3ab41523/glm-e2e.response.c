void point_computing(double *w, double *p1, double *p2, double *out1, double *out2) {
    // Calculate the sum of the weights (w[0] + w[1] + w[2] + w[3])
    double w_sum = w[0] + w[1] + w[2] + w[3];

    // Calculate the weighted average for the first point (p1)
    *out1 = (w[0] * p1[0] + w[1] * p1[1] + w[2] * p1[2] + w[3] * p1[3]) / w_sum;

    // Calculate the weighted average for the second point (p2)
    *out2 = (w[0] * p2[0] + w[1] * p2[1] + w[2] * p2[2] + w[3] * p2[3]) / w_sum;
}