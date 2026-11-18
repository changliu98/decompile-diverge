int func0(int first_param, int second_param, int third_param)
{
    // Determine the smaller of a and b
    int smaller_value = (first_param < second_param) ? first_param : second_param;
    // Determine the larger of a and b
    int larger_value = (first_param > second_param) ? first_param : second_param;

    // If d is less than the maximum value
    if (third_param < larger_value) {
        // If d is zero, return 0
        if (third_param == 0) {
            return 0;
        } 
        // If d equals the minimum value, return 1
        else if (third_param == smaller_value) {
            return 1;
        } 
        // Otherwise, return 2
        else {
            return 2;
        }
    } 
    // If d is greater than or equal to the maximum value
    else {
        // Calculate and return the ceiling of d divided by max_val
        return (third_param + larger_value - 1) / larger_value;
    }
}