int calculate_income_tax(double income, double *tax, double *rate)
{
    if (income >= 0 && income <= 1500)
    {
        *rate = 0.05;
    }
    else if (income > 1500 && income <= 4500)
    {
        *rate = 0.10;
    }
    else if (income > 4500)
    {
        *rate = 0.15;
    }
    else
    {
        return 1;
    }

    *tax = *rate * income;

    return 0;
}