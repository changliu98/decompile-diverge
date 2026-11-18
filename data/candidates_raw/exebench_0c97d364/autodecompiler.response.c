static void add_64(struct CPU *cpu) {
    do{ if(0) printf__bench("ADD R64\n"); } while(0);
    cpu->reg_AF.w += 8;
}