void __cdecl func0(int current_total, int needed, int available, int *result)
{
    int fulfilled_amount;
    int leftover_amount;

    if (needed <= available)
    {
        // We have enough available to fulfill the need
        fulfilled_amount = needed;
        leftover_amount = available - needed;
    }
    else
    {
        // We can only fulfill up to what is available
        fulfilled_amount = available;
        leftover_amount = 0;
    }

    // Update the output array
    result[0] = current_total + fulfilled_amount;
    result[1] = leftover_amount;
}