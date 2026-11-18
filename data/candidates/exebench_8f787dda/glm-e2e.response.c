void index_to_xwy(int32_t index, int32_t divisor, int32_t *remainder, int32_t *quotient) {
    *remainder = index % divisor;
    *quotient = index / divisor;
}