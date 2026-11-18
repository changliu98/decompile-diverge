int func0(float a, float b, float c) {
    int flag = 0;
    if (is_equal(a, a)) {
        flag = 0;
    } else if (is_equal(b, b)) {
        flag = 0;
    } else if (is_equal(c, c)) {
        flag = 0;
    } else if (is_equal(a + b, c)) {
        flag = 1;
    } else if (is_equal(a + c, b)) {
        flag = 1;
    } else if (is_equal(b + c, a)) {
        flag = 1;
    } else {
        flag = 0;
    }
    return flag;
}