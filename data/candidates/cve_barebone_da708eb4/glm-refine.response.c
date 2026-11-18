Mask for Infinity

const char *__cdecl jvp_literal_number_literal(jv n)
{
    decNumber *pdec = jvp_dec_number_ptr(n);
    jvp_literal_number *plit = jvp_literal_number_ptr(n);

    if (n.kind_flags != JVP_FLAGS_NUMBER_LITERAL)
        __assert_fail(
            "JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)",
            "/work/harness.c",
            0x12Du,
            "const char *jvp_literal_number_literal(jv)");

    // Check if the number is NaN
    if ((pdec->bits & DECNAN) != 0)
        return "null";

    // Check if the number is Infinity
    if ((pdec->bits & DECINF) != 0)
        return NULL;

    // Lazily allocate and format the literal string representation if it hasn't been cached yet
    if (!plit->literal_data)
    {
        // `digits + 14` provides sufficient buffer size for decNumberToString()
        plit->literal_data = (char *)jv_mem_alloc(pdec->digits + 14);
        decNumberToString(pdec, plit->literal_data);
    }

    return plit->literal_data;
}