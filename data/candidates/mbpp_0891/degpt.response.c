_Bool func0(int numerator, int denominator) {
    // Loop until either A or B becomes zero
    while (numerator > 0 && denominator > 0) {
        // Remove the last digit from A
        numerator /= 10;
        // Remove the last digit from B
        denominator /= 10;
    }
    // Return true if both A and B are zero, false otherwise
    return numerator == 0 && denominator == 0;
}