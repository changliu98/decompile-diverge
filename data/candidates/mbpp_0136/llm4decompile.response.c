double func0(int units)
{
    int surcharge;
    double amount;

    if (units < 50) {
        surcharge = 25;
        amount = units * 0.60;
    } else if (units < 101) {
        surcharge = 35;
        amount = 50 * 0.60 + (units - 50) * 0.90;
    } else if (units < 201) {
        surcharge = 45;
        amount = 50 * 0.60 + 100 * 0.90 + (units - 100) * 1.20;
    } else {
        surcharge = 75;
        amount = 50 * 0.60 + 100 * 0.90 + 200 * 1.20 + (units - 200) * 1.50;
    }

    return amount + surcharge;
}