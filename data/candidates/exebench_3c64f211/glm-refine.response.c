void __cdecl jpq_cpuid_custom(int *CPUInfo, int InfoType)
{
    int eax, ebx, ecx, edx;

    __asm {
        mov eax, InfoType
        cpuid
        mov eax, eax   ; 'mov' is used to capture the output into local C variables
        mov ebx, ebx
        mov ecx, ecx
        mov edx, edx
    }

    // Store the results into the output array
    CPUInfo[0] = eax;
    CPUInfo[1] = ebx;
    CPUInfo[2] = ecx;
    CPUInfo[3] = edx;
}