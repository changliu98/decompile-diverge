int bit_array_sub_uint64( bi * binteger, unsigned long subtrahend )
{
    int i;
    char ret;
    unsigned long carry;
    unsigned long old_subtrahend;

    if( subtrahend == 0 )
    {
        ret = 1;
    }
    else if( binteger->data[0] >= subtrahend )
    {
        binteger->data[0] -= subtrahend;
        ret = 1;
    }
    else
    {
        old_subtrahend = subtrahend;
        subtrahend -= binteger->data[0];

        carry = 1;
        i = 1;
        while( carry && i < binteger->num_limbs )
        {
            carry = (binteger->data[i] < subtrahend);
            if( !carry )
            {
                binteger->data[i] -= subtrahend;
            }
            else
            {
                binteger->data[i] = ~0L - subtrahend - 1;
            }
            subtrahend = 0;
            ++i;
        }

        if( carry )
        {
            bi_decrement_limbs( binteger, 1 );
            binteger->data[0] = ~0L - old_subtrahend - 1;
        }

        ret = (i >= binteger->num_limbs);
    }
    return ret;
}