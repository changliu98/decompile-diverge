int __cdecl calculate_income_tax(const double amount, double *tax, double *rate)
{
    bool valid_amount = false;

    if (amount >= 0.0 && amount <= 1000.0) {
        *rate = 0.25;
        valid_amount = true;
    } 
    else if (amount > 1000.0 && amount <= 5000.0) {
        *rate = 0.30;
        valid_amount = true;
    } 
    else if (amount > 5000.0) {
        *rate = 0.35;
        valid_amount = true;
    }

    if (valid_amount) {
        *tax = *rate * amount;
        return 0;
    }

    // Returns 1 for negative amounts or NaN
    return 1; 
}