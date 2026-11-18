float _RGB(float x, float y, float z) {
    float a;
    if (x < 0)
        x = x + 3.14;
    else if (x > 3.14)
        x = x - 3.14;
    if (x < -3.14)
        a = y + (x - y) * (z - x) / (3.14 - x);
    else if (x < 3.14 && x > 0)
        a = y + (x - y) * (z - x) / (3.14 - x);
    else
        a = y;
    return a;
}