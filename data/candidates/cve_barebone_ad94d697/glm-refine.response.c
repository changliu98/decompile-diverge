void __cdecl ubik_print(netdissect_options *ndo, const u_char *bp)
{
    int ubik_op;
    int32_t temp;
    time_t t;
    tm *tm;
    char str[256];
    const u_char *bp_ptr = bp + 32;

    ubik_op = EXTRACT_32BITS(bp + 28);
    ndo->ndo_printf(ndo, " ubik call %s", tok2str(&ubik_req, "op#%d", ubik_op));

    if (ubik_op == 10000)
    {
        if (bp_ptr + 4 > ndo->ndo_snapend)
            goto trunc;
        temp = EXTRACT_32BITS(bp_ptr);
        bp_ptr += 4;
        ndo->ndo_printf(ndo, " syncsite %s", temp ? "yes" : "no");
        
        ndo->ndo_printf(ndo, " votestart");
        if (bp_ptr + 4 > ndo->ndo_snapend)
            goto trunc;
        t = EXTRACT_32BITS(bp_ptr);
        bp_ptr += 4;
        tm = localtime(&t);
        strftime(str, 0x100uLL, "%Y/%m/%d %H:%M:%S", tm);
        ndo->ndo_printf(ndo, " %s", str);
        
        ndo->ndo_printf(ndo, " dbversion");
        if (bp_ptr + 8 > ndo->ndo_snapend)
            goto trunc;
        ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
        bp_ptr += 8;
        
        ndo->ndo_printf(ndo, " tid");
        if (bp_ptr + 8 > ndo->ndo_snapend)
            goto trunc;
        ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
        return;
    }
    
    if (ubik_op == 10003)
    {
        ndo->ndo_printf(ndo, " site");
        if (bp_ptr + 4 > ndo->ndo_snapend)
            goto trunc;
        ndo->ndo_printf(ndo, " %lu", (unsigned long)EXTRACT_32BITS(bp_ptr));
        return;
    }

    if ((unsigned int)(ubik_op - 20000) < 2 || (unsigned int)(ubik_op - 20007) < 2 || ubik_op == 20010)
    {
        ndo->ndo_printf(ndo, " tid");
        if (bp_ptr + 8 > ndo->ndo_snapend)
            goto trunc;
        ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
        return;
    }

    switch (ubik_op)
    {
        case 20002:
            ndo->ndo_printf(ndo, " tid");
            if (bp_ptr + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
            bp_ptr += 8;
            
            ndo->ndo_printf(ndo, " file");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            bp_ptr += 4;
            
            ndo->ndo_printf(ndo, " pos");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            bp_ptr += 4;
            
            ndo->ndo_printf(ndo, " length");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            bp_ptr += 4;
            
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            tok2str(&ubik_lock_types, "type %d", EXTRACT_32BITS(bp_ptr));
            return;

        case 20003:
            ndo->ndo_printf(ndo, " tid");
            if (bp_ptr + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
            bp_ptr += 8;
            
            ndo->ndo_printf(ndo, " file");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            bp_ptr += 4;
            
            ndo->ndo_printf(ndo, " pos");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            return;

        case 20005:
            ndo->ndo_printf(ndo, " file");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            return;

        case 20006:
            ndo->ndo_printf(ndo, " file");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            bp_ptr += 4;
            
            ndo->ndo_printf(ndo, " length");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            bp_ptr += 4;
            
            ndo->ndo_printf(ndo, " dbversion");
            if (bp_ptr + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
            return;

        case 20009:
            ndo->ndo_printf(ndo, " tid");
            if (bp_ptr + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
            bp_ptr += 8;
            
            ndo->ndo_printf(ndo, " file");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            bp_ptr += 4;
            
            ndo->ndo_printf(ndo, " length");
            if (bp_ptr + 4 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d", EXTRACT_32BITS(bp_ptr));
            return;

        case 20012:
            ndo->ndo_printf(ndo, " tid");
            if (bp_ptr + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
            bp_ptr += 8;
            
            ndo->ndo_printf(ndo, " oldversion");
            if (bp_ptr + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
            bp_ptr += 8;
            
            ndo->ndo_printf(ndo, " newversion");
            if (bp_ptr + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, " %d.%d", EXTRACT_32BITS(bp_ptr), EXTRACT_32BITS(bp_ptr + 4));
            return;
    }

trunc:
    ndo->ndo_printf(ndo, " [|ubik]");
}