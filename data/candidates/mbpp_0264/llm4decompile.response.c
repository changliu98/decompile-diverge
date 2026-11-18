double func0(int age)
{
    if (age < 0)
        exit(1);

    if (age <= 2)
        return age * 8.5;
    else
        return 23 + (age - 2) * 4;
}