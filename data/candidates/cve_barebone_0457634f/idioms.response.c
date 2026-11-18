void vector64_dst_append(struct rstrbuf *sb, struct csh *handle, struct cs_insn *insn, int n, int i)
{
    struct cs_arm64_op op = insn->detail->arm64.operands[n];
    if (op.vector_index != -1)
        i = op.vector_index;
    if (op.vas != arm64_vas::ARM64_VAS_INVALID && i != -1)
    {
        int size = arm64_vector_size(&op);
        int shift = i * size;
        char *regc = "l";
        unsigned long mask;
        unsigned long index = (size > 0 ? (size - 1) : 0) % (sizeof(unsigned long) * 8);
        if (index >= (sizeof(unsigned long) * 8))
            index = 0;
        mask = bitmask_by_width[index];
        if (shift >= (sizeof(unsigned long) * 8))
        {
            shift -= (sizeof(unsigned long) * 8);
            regc = "h";
        }
        if (shift > 0 && shift < (sizeof(unsigned long) * 8))
        {
            struct rstrbuf *buf = sb;
            char *reg = regname(handle, insn->detail->arm64.operands[n].reg);
            char *regl = regnamel(reg);
            unsigned long maskl = ~(bitmask_by_width[size - 1] << shift);
            char *regll = regnamel(reg);
            rstrbuf_appendf(buf, "%d,SWAP,0x%lx,&,<<,%s%s,0x%lx,&,|,%s%s",
                shift, mask, regl, regc, maskl, regll, regc);
        }
        else
        {
            struct rstrbuf *buf = sb;
            char *reg = regname(handle, insn->detail->arm64.operands[n].reg);
            char *regl = regnamel(reg);
            unsigned long maskl = ~(bitmask_by_width[size % (sizeof(unsigned long) * 8) - 1] << shift);
            char *regll = regnamel(reg);
            rstrbuf_appendf(buf, "0x%lx,&,%s%s,0x%lx,&,|,%s%s",
                mask, regl, regc, maskl, regll, regc);
        }
    }
    else
    {
        struct rstrbuf *buf = sb;
        char *reg = regname(handle, insn->detail->arm64.operands[n].reg);
        char *regl = regnamel(reg);
        rstrbuf_appendf(buf, "%s", regl);
    }
}