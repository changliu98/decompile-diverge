void func0(int *program) {
    int pc = 0;

    while (1) {
        int opcode = program[pc];
        int a = program[program[pc] & 0xffffff];
        int b = program[program[pc + 1] & 0xffffff];
        int c = program[program[pc + 2] & 0xffffff];

        switch (opcode) {
        case 1:
            program[c] = a + b;
            break;
        case 2:
            program[c] = a * b;
            break;
        case 99:
            return;
        }

        pc += 4;
    }
}