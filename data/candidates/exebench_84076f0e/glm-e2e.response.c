int calculate_income_tax(double income, double *tax_amount, double *tax_rate) {
    if (income >= 0.0 && income <= 10000.0) {
        *tax_rate = 0.10;
    } else if (income > 10000.0 && income <= 50000.0) {
        *tax_rate = 0.20;
    } else if (income > 50000.0) {
        *tax_rate = 0.30;
    } else {
        // Handles invalid income (e.g., negative values)
        return 1;
    }

    *tax_amount = *tax_rate * income;
    return 0;
}