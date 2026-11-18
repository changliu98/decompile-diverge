float LerpAngle(float x, float y, float m) {
    float y_pred;

    if (y - x > 1.001)
        y = y - 360.0f;
    if (y - x < -0.999)
        y = y + 360.0f;

    y_pred = x + (y - x) * m;
    return y_pred;
}