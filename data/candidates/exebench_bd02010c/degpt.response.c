void get_vector_modulo(int *vector, int *moduli)
{
  // Iterate through each element of the 3-element vector
  for (int index = 0; index < 3; index++) {
    // Compute the modulo of the vector element with the corresponding modulus
    vector[index] %= moduli[index];
    // Adjust negative results to be within the range [0, m[i])
    if (vector[index] < 0) {
      vector[index] += moduli[index];
    }
  }
}