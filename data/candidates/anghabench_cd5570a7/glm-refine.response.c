unsigned __int64 it_advance(unsigned __int64 cpsr)
{
    const unsigned __int64 PSR_IT_MASK = 0x06001C00;

    // Check if any IT state bits are active
    if ((cpsr & PSR_IT_MASK) != 0)
    {
        unsigned __int64 it_state = cpsr & PSR_IT_MASK;
        unsigned __int64 next_state = (it_state << 1) | (it_state >> 16);

        // Clear the old IT state and set the new advanced state
        return (cpsr & ~PSR_IT_MASK) | (next_state & PSR_IT_MASK);
    }
    else
    {
        // No IT state active, clear the mask entirely
        return cpsr & ~PSR_IT_MASK;
    }
}