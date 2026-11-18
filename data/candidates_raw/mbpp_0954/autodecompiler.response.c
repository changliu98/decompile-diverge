int check(int actual_cost, int sale_amount)
{
    int result;
    if (actual_cost > sale_amount)
    {
        result = actual_cost - sale_amount;
    }
    else
    {
        result = -1;
    }
    return result;
}