/**
 * Computes the product of two complex numbers.
 *
 * @param zReal Pointer to store the real part of the result.
 * @param zImag Pointer to store the imaginary part of the result.
 * @param xReal Real part of the first complex number (x).
 * @param xImag Imaginary part of the first complex number (x).
 * @param yReal Real part of the second complex number (y).
 * @param yImag Imaginary part of the second complex number (y).
 *
 * The multiplication follows the formula:
 * (xReal + i*xImag) * (yReal + i*yImag) = (xReal*yReal - xImag*yImag) + i*(xReal*yImag + xImag*yReal)
 */
void complexMultiplicationRI(double *resultReal, double *resultImag, double xRealPart, double xImagPart, double yRealPart, double yImagPart)
{
    // Calculate the real part of the product: Re(x)*Re(y) - Im(x)*Im(y)
    *resultReal = xRealPart * yRealPart - xImagPart * yImagPart;
    
    // Calculate the imaginary part of the product: Re(x)*Im(y) + Im(x)*Re(y)
    *resultImag = xRealPart * yImagPart + xImagPart * yRealPart;
}