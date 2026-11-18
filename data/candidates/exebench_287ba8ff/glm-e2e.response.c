void ft_25_lines(const char *str, float *f1, float *f2, struct s_data *data) {
    // movsbl (%rax),%ecx ; sub $0x30,%ecx
    data->digit = *(const int8_t *)str - '0';

    // cmpl $0x0,0x4(%rax) ; jl 17f3
    // cmpl $0x9,0x4(%rax) ; jg 17f3
    if (data->digit >= 0 && data->digit <= 9) {
        // cmpl $0x1,(%rax) ; jne 17be
        if (data->field1 == 1) {
            // cvtss2sd ; divsd 0x85e(%rip) ; cvtsd2ss
            *f1 = (float)((double)*f1 / 100.0);
        }
        
        // cvtsi2ssl 0x4(%rax),%xmm1 ; cvtss2sd %xmm1,%xmm1
        // mulsd 0x831(%rip),%xmm0 ; addsd %xmm1,%xmm0 ; cvtsd2ss
        *f2 = (float)((double)*f2 * 100.0 + (double)data->digit);
    }
}