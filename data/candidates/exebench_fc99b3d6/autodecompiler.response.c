void cpuid(unsigned int leaf, unsigned int *eax, unsigned int *ebx,
                 unsigned int *ecx, unsigned int *edx)
{
# 56 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/119/aircam-openwrt/refs/heads/0.9.33/build_dir/toolchain-arm_v5te_gcc-linaro_uClibc-0.9.32_eabi/uClibc-0.9.32/libc/syscalls/get_cpuid.c"
    __asm__ ("cpuid\n\t" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) : "0" (leaf));

}