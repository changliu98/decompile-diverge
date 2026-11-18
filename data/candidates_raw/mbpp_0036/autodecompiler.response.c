int mystery( unsigned int a, unsigned int b, int c )
{
    int result;

    while(c > 0)
    {
        --c;
        a *= 10;
        result = a / b;
        a %= b;
    }

return result;
}