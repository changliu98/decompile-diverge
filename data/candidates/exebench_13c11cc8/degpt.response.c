void sort_three(int *first, int *second, int *third)
{
    // Ensure v1 <= v2 by swapping if necessary
    if (*second < *first) {
        int temp = *second;
        *second = *first;
        *first = temp;
    }
    // Ensure v1 <= v3 by swapping if necessary
    if (*third < *first) {
        int temp = *third;
        *third = *first;
        *first = temp;
    }
    // Ensure v2 <= v3 by swapping if necessary
    if (*third < *second) {
        int temp = *third;
        *third = *second;
        *second = temp;
    }
}