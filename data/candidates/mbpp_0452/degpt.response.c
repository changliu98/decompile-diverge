// Calculates the profit by subtracting the actual cost from the sale amount.
// If the actual cost is greater than or equal to the sale amount, returns 0.
int func0(int cost, int revenue)
{
    // Returns the difference if sale_amount is greater than actual_cost, otherwise returns 0
    return cost < revenue ? revenue - cost : 0;
}