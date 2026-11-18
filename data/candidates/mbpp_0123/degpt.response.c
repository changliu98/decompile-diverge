int func0(int upper_bound)
{
    // Return -1 if the limit is less than 1, as no valid numbers exist
    if (upper_bound < 1) {
        return -1;
    }

    // Initialize sum to accumulate the total of all amicable numbers found
    int total_amicable_sum = 0;

    // Iterate through each number from 2 up to the given limit
    for (int current_number = 2; current_number <= upper_bound; current_number++) {
        // Calculate the sum of proper divisors of the current number 'num'
        int divisor_sum_first = 0;
        for (int divisor_candidate = 1; divisor_candidate < current_number; divisor_candidate++) {
            if (current_number % divisor_candidate == 0) {
                divisor_sum_first += divisor_candidate;
            }
        }

        // Calculate the sum of proper divisors of the previously calculated sum
        int divisor_sum_second = 0;
        for (int divisor_candidate_second = 1; divisor_candidate_second < divisor_sum_first; divisor_candidate_second++) {
            if (divisor_sum_first % divisor_candidate_second == 0) {
                divisor_sum_second += divisor_candidate_second;
            }
        }

        // Check if the pair is amicable:
        // 1. The sum of divisors of 'num' equals the original number when summed again (sum_fact2 == num)
        // 2. The number is not a perfect number (num != sum_fact)
        if (current_number == divisor_sum_second && current_number != divisor_sum_first) {
            total_amicable_sum += current_number;
        }
    }

    // Return the total sum of all amicable numbers found within the limit
    return total_amicable_sum;
}