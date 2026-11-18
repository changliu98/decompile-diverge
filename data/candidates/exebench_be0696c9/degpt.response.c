// Returns the input variable if the current fixed value is less than the previous fixed value.
// Updates the previous fixed value to the current fixed value in this case.
// Otherwise, returns 0.0f.
float get_near_num(float current_value, float *current_fixed, float *previous_fixed) {
    // Check if the current fixed value is less than the previous fixed value
    if (current_fixed < previous_fixed) {
        // Update the previous fixed value to the current fixed value
        *previous_fixed = *current_fixed;
        // Return the input variable
        return current_value;
    }
    // Return 0.0f if the condition is not met
    return 0.0f;
}