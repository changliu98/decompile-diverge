int sample_conv_regsub(arg *args, sample *smp, void *private)
{
    my_regex *reg = args[0].data.reg;
    buffer *trash = get_trash_chunk();
    char *start = smp->data.u.str.area + smp->data.u.str.data;
    char *end = smp->data.u.str.area + smp->data.u.str.size;
    int eflags = 0;
    int found;
    regmatch_t pmatch[10];

    while (1) {
        found = 0;
        if ((args[0].type_flags & 0x02) || !eflags)
            found = regex_exec_match2(reg, start, end - start, 10, pmatch, eflags);
        if (!found)
            pmatch[0].rm_so = end - start;

        if (trash->size - trash->data && pmatch[0].rm_so > 0) {
            int amt = pmatch[0].rm_so;
            if (trash->size - trash->data < amt)
                amt = trash->size - trash->data;
            memcpy(trash->area + trash->data, start, amt);
            trash->data += amt;
        }

        if (!found)
            break;

        {
            buffer *chunk = alloc_trash_chunk();
            if (!chunk)
                break;
            chunk->data = exp_replace(chunk->area, chunk->size, start, args[1].data.str.area, pmatch);
            if (chunk->size - chunk->data) {
                int amt = chunk->data;
                if (chunk->size - chunk->data < amt)
                    amt = chunk->size - chunk->data;
                memcpy(trash->area + trash->data, chunk->area, amt);
                trash->data += amt;
            }
            free_trash_chunk(chunk);
        }

        if (start >= end)
            break;

        if (!pmatch[0].rm_eo) {
            if (trash->data < trash->size)
                trash->area[trash->data++] = *start;
            pmatch[0].rm_eo = 1;
        }
        start += pmatch[0].rm_eo;
        eflags = 1;
    }

    smp->data.u.str = *trash;
    return 1;
}