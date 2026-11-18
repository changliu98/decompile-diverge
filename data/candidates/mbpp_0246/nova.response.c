double func0(double x) {
    double y;
    if (x == 0)
        y = -INFINITY;
    else
        for (y = x / 17.0; y!= (y = (y + x / y) / 2.0);)
            ;
    return y;
}