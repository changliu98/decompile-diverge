float constrain(float value, float min, float max) {
    if (value > max) {
        return value;
    } else if (max > min) {
        return min;
    } else {
        return max;
    }
}