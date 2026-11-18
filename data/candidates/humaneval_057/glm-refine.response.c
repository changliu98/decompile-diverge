#include <stdbool.h>

bool __cdecl is_monotonic(float *arr, int size) {
    bool increasing = false;
    bool decreasing = false;

    for (int i = 1; i < size; ++i) {
        if (arr[i] > arr[i - 1]) {
            increasing = true;
        }
        if (arr[i - 1] > arr[i]) {
            decreasing = true;
        }
    }

    // The array is monotonic if it doesn't contain both increasing and decreasing elements.
    return !(increasing && decreasing);
}