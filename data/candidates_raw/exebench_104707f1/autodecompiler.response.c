void cpu_srl_r8(struct cpu* cpu, int ri) {
  unsigned char a=cpu_get_r8(cpu, ri);
  unsigned char t=a >> 1;

  unsigned char z=t ? 0 : ((unsigned char)(0x80));
  unsigned char n=0;
  unsigned char h=0;
  unsigned char c=a & 0x01 ? ((unsigned char)(0x10)) : 0;

  cpu_set_r8(cpu, ri, t);
  cpu_set_r8(cpu, (0), z | n | h | c);

  cpu->busy = 4;
}