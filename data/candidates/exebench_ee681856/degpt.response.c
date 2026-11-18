void c_saxpy(int count, double scalar, double *source_vector, double *target_vector)
{
    // Perform operation only if n is positive and sa is non-zero or NaN
    if (count > 0 && (scalar != 0.0 || isnan(scalar))) {
        int index;
        // Calculate the number of remaining elements to handle before loop unrolling
        int remainder = count % 4;
        // Handle the first m elements (remainder)
        for (index = 0; index < remainder; index++) {
            target_vector[index] = scalar * source_vector[index] + target_vector[index];
        }
        // Process the remaining elements in chunks of 4 (loop unrolling)
        for (index = remainder; index < count; index += 4) {
            target_vector[index]     = scalar * source_vector[index]     + target_vector[index];
            target_vector[index + 1] = scalar * source_vector[index + 1] + target_vector[index + 1];
            target_vector[index + 2] = scalar * source_vector[index + 2] + target_vector[index + 2];
            target_vector[index + 3] = scalar * source_vector[index + 3] + target_vector[index + 3];
        }
    }
}