void sseround(BTESH2_CpuState *cpu, BTESH2_Opcode *op)
{
 u32 i, j, k;
 i=cpu->fregs[op->rn];
 j=((u32)(s32)((s16)i));
 k=((u32)(s32)((s32)i));
 k=(k&0x7FFFFFFF)|((i>>31)&0x80000000);
 cpu->fregs[op->rn]=k;
}