#include <stdbool.h>

// Helper function to encapsulate the string parsing logic
static void parse_fraction(const char *str, int *numerator, int *denominator) {
    char buffer[101];
    int i = 0, j = 0;
    
    // Extract numerator (up to the '/' character)
    while (str[i] != '/') {
        buffer[i] = str[i];
        i++;
    }
    buffer[i] = '\0';
    *numerator = atoi(buffer);
    
    // Skip the '/' character
    i++;
    
    // Extract denominator (the rest of the string)
    while (str[i] != '\0') {
        buffer[j++] = str[i++];
    }
    buffer[j] = '\0';
    *denominator = atoi(buffer);
}

bool is_fraction_product_integer_multiple(const char *frac1, const char *frac2)
{
    int a, b, c, d;

    // Parse the two fraction strings
    parse_fraction(frac1, &a, &b);
    parse_fraction(frac2, &c, &d);

    // Check if (a * c) is perfectly divisible by (b * d)
    return (a * c) % (b * d) == 0;
}