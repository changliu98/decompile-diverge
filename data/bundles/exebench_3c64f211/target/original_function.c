void jpq_cpuid_custom(int CPUInfo[4],int InfoType){
    __asm__ __volatile__ (
                          "cpuid":
                          "=a" (CPUInfo[0]),
                          "=b" (CPUInfo[1]),
                          "=c" (CPUInfo[2]),
                          "=d" (CPUInfo[3]) :
                          "a" (InfoType), "c" (0)
                          );
}