long RaiseTo5(int n)
{
    long sum = 0;
    int i;

    for(i=1; ; i++)
    {
        if(i > n)
            break;
        int power = i * 2;
        sum += power * power * power * power * power;
    }
    return sum;
}