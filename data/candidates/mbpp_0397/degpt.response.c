int func0(int first, int second, int third) {
    // If a is less than or equal to b
    if (first <= second) {
        // If b is less than or equal to c, then a <= b <= c, so b is the middle value
        if (second <= third) return second;
        // If a is less than or equal to c, then a <= c < b, so c is the middle value
        if (first <= third) return third;
        // Otherwise, c < a <= b, so a is the middle value
        return first;
    } else {
        // If a is greater than b
        // If a is less than or equal to c, then b < a <= c, so a is the middle value
        if (first <= third) return first;
        // If b is less than or equal to c, then b <= c < a, so c is the middle value
        if (second <= third) return third;
        // Otherwise, c < b < a, so b is the middle value
        return second;
    }
}