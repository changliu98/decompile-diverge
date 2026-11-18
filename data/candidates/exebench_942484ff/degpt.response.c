void complexMultiplication(double aReal, double aImag, double bReal, double bImag, double *resultReal, double *resultImag)
{
    // Calculate the real part of the product: (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    *resultReal = aReal * bReal - aImag * bImag;
    // Calculate the imaginary part of the product
    *resultImag = aReal * bImag + aImag * bReal;
}