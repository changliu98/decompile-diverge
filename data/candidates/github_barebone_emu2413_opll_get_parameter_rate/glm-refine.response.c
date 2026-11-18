int __cdecl get_parameter_rate(OPLL_SLOT *slot)
{
    // Early exit: if it's a modulator type and the key is not pressed, rate is 0
    if ((slot->type & 1) == 0 && !slot->key_flag)
        return 0;

    switch (slot->eg_state)
    {
        case STATE_ATTACK:
            return slot->patch->AR;

        case STATE_DECAY:
            return slot->patch->DR;

        case STATE_SUSTAIN:
            // If EG (Envelope Generator) sustain is enabled, rate is 0, otherwise use RR
            return slot->patch->EG ? 0 : slot->patch->RR;

        case STATE_RELEASE:
            if (slot->sus_flag)
                return 5;
            if (slot->patch->EG)
                return slot->patch->RR;
            return 7;

        case STATE_OFF:
            return 12;

        default:
            return 0;
    }
}