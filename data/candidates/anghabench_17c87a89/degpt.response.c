double KernelBessel_Q1(double x)
{
    // Initialize numerator polynomial coefficient with the highest degree term
    double numerator_poly = KernelBessel_Q1::Pone[5];
    // Initialize denominator polynomial coefficient with the highest degree term
    double denominator_poly = KernelBessel_Q1::Qone[5];
    // Horner's method to evaluate the rational approximation of the Bessel function
    for (int coeff_index = 4; coeff_index >= 0; coeff_index--) {
        // Update numerator: p = p * (constant/x)^2 + next_coefficient
        numerator_poly = numerator_poly * (bessel_constant / x) * (bessel_constant / x) + KernelBessel_Q1::Pone[coeff_index];
        // Update denominator: q = q * (constant/x)^2 + next_coefficient
        denominator_poly = denominator_poly * (bessel_constant / x) * (bessel_constant / x) + KernelBessel_Q1::Qone[coeff_index];
    }
    // Return the ratio of the evaluated numerator to denominator
    return numerator_poly / denominator_poly;
}