int hexagon_v6_op(AnalOp *op, void *buf, const void *code, int size, int opt1, int opt2) {
    unsigned char instruction[4];
    int ret;
    int word;

    memset(instruction, 0, 4);
    
    word = r_read_le32(code);
    
    ret = hexagon_disasm_instruction(word, instruction, size);
    op->size = ret; // offset 0x8 corresponds to 'size' in this struct layout
    
    if (ret <= 0) {
        return ret;
    }
    
    op->ptr1 = buf; // offset 0x0 corresponds to 'ptr1'
    
    return hexagon_anal_instruction(op, instruction);
}