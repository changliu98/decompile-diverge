void print(double val) {
    // The first call resolves the dynamic "word" or "type" of the value `val`
    int word_type = f_println(val);

    switch (word_type) {
        case 0x7ff9: {
            obj_t obj = global_obj_1;
            int idx = f_write(val);
            // obj is passed as the 1st arg (rdi), idx as the 2nd (rsi)
            printf("%s", word_table[idx]); 
            break;
        }
        case 0x7ffa: {
            obj_t obj = global_obj_2;
            int idx = f_string(val);
            // obj is passed as the 1st arg (rdi), idx as the 2nd (rsi)
            printf("%c", char_table[idx]);
            break;
        }
        case 0x7ffb: {
            obj_t obj = global_obj_3;
            int idx = f_load(val);
            // obj is passed as the 1st arg (rdi), idx as the 2nd (rsi)
            printf("%s", string_table[idx]);
            break;
        }
        case 0x7ffc: {
            printlist(val);
            break;
        }
        case 0x7ffe: {
            obj_t obj = global_obj_4;
            int idx = f_trace(val);
            // obj is passed as the 1st arg (rdi), idx as the 2nd (rsi)
            printf("%d", idx);
            break;
        }
        case 0x7fff: {
            obj_t obj = global_obj_5;
            int idx = f_catch(val);
            // obj is passed as the 1st arg (rdi), idx as the 2nd (rsi)
            printf("%d", idx);
            break;
        }
        case 0xffff: {
            // The RIP-relative address resolution for rdi is obfuscated/missing in the snippet,
            // but it loads a global object into rdi before the call.
            obj_t obj = global_obj_6; 
            printf("%f", val);
            break;
        }
        default: {
            // Fallback for unhandled types
            printf("%f\n", val);
            break;
        }
    }
}