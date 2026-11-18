// Sets the 6th bit of the flags array to '1' to indicate an IRQ flag is set.
void setIRQflag(char *irq_status)
{
  irq_status[5] = '1';
}