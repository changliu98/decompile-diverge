void set_autofs_type_offset(struct cpu* cpu, int rb) {
  unsigned char a=cpu_get_r8(cpu, (1));
  unsigned char b=cpu_get_r8(cpu, rb);
  signed int t=a-b;
  if(cpu_get_r8(cpu, (0)) & ((unsigned char)(0x10)))
    t = t-1;
  cpu_set_r8(cpu, (1), (unsigned char) t);
  cpu_sbc_flags(cpu, a, b, t);
  cpu->busy = 4;
}