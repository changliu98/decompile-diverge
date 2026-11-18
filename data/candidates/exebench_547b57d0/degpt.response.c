/**
 * @brief Adds two complex numbers represented by their real and imaginary parts.
 *
 * This function computes the sum of two complex numbers:
 *   (C1 + i*S1) + (C2 + i*S2) = (C1*C2 - S1*S2) + i*(S1*C2 + C1*S2)
 *
 * Note: The formula used here corresponds to complex multiplication, not addition.
 * For complex addition, the correct formulas would be:
 *   *C = C1 + C2;
 *   *S = S1 + S2;
 *
 * @param C1 Real part of the first complex number.
 * @param S1 Imaginary part of the first complex number.
 * @param C2 Real part of the second complex number.
 * @param S2 Imaginary part of the second complex number.
 * @param C  Pointer to store the real part of the result.
 * @param S  Pointer to store the imaginary part of the result.
 */
void multiply_complex(double real1, double imag1, double real2, double imag2, double *result_real, double *result_imag)
{
  *result_real = real1 * real2 - imag1 * imag2;
  *result_imag = imag1 * real2 + real1 * imag2;
}