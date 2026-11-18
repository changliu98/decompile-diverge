// Calculates the loss amount if the sale amount is less than the actual cost.
// Returns the difference (actual_cost - sale_amount) if a loss occurred.
// Returns -1 if there was no loss (sale_amount >= actual_cost).
int func0(int cost_price, int selling_price)
{
    return selling_price < cost_price ? cost_price - selling_price : -1;
}