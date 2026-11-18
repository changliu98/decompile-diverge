char base64_encode_value(signed char v) {
    char result;
    if (v > 63) {
        result = '=';
    } else {
        result = base64_encode_value_encoding[v];
    }
    return result;
}