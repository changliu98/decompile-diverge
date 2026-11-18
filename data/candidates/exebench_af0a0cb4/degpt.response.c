// Function to swap the values of two integers pointed to by x and y
void vertausche(int *firstValue, int *secondValue) {
    int temporaryValue = *firstValue; // Store the value of x in a temporary variable
    *firstValue = *secondValue;       // Assign the value of y to x
    *secondValue = temporaryValue;     // Assign the stored value of x to y
}