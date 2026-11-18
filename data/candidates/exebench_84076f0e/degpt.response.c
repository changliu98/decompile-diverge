int calculate_income_tax(double income, double *calculated_tax, double *tax_rate)
{
    // Check if amount is negative or exceeds the highest tax bracket threshold
    if ((income < 0.0) || (bracket_one_limit < income)) {
        // Check if amount is within the first tax bracket or exceeds the second bracket threshold
        if ((income <= bracket_one_limit) || (bracket_two_limit < income)) {
            // Check if amount is within the second tax bracket
            if (income <= bracket_two_limit) {
                // Invalid range or error condition
                return 1;
            }
            // Apply tax rate for the third tax bracket
            *tax_rate = rate_three;
        }
        else {
            // Apply tax rate for the fourth tax bracket
            *tax_rate = rate_four;
        }
    }
    else {
        // Apply tax rate for the first tax bracket (amount is between 0 and DAT_00102008)
        *tax_rate = rate_one;
    }
    // Calculate the tax amount based on the determined rate and input amount
    *calculated_tax = *tax_rate * income;
    // Return success status
    return 0;
}