// Clears the interrupt request flag by setting the 6th byte of the flags array to '0'
void clearIRQflag(char *interruptFlags)
{
  interruptFlags[5] = '0';
}