float makeIntoDollarsAndCents(int dollars, int cents)
{
    int temp = cents;
    int numDigits = 0;

    if(temp == 0)
        numDigits = 1;
    else
        while(temp != 0)
        {
            numDigits++;
            temp /= 10;
        }

    return dollars + (cents / pow(10.0, (double)numDigits));
}