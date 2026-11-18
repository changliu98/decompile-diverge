// Performs a diagonal matrix-vector multiplication and accumulation
// num_elem: Number of elements to process
// in_amp:   Input amplitude array
// out_amp:  Output amplitude array (accumulated result)
// matr:     Diagonal matrix elements array
void pn_diag_SD_contr(int num_elements,double *input_amplitude,double *output_amplitude,double *diagonal_matrix)
{
  // Loop through each element
  while (num_elements--) {
    // Multiply input amplitude by diagonal matrix element and accumulate to output
    *output_amplitude = *diagonal_matrix * *input_amplitude + *output_amplitude;
    // Advance pointers to next elements
    diagonal_matrix++;
    output_amplitude++;
    input_amplitude++;
  }
}