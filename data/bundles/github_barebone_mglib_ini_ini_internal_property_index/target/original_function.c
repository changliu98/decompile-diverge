static int ini_internal_property_index( ini_t const* ini, int section, int property )
    {
    int i;
    int p;

    if( ini && section >= 0 && section < ini->section_count )
        {
        p = 0;
        for( i = 0; i < ini->property_count; ++i )
            {
            if( ini->properties[ i ].section == section )
                {
                if( p == property ) return i;
                ++p;
                }
            }
        }

    return INI_NOT_FOUND;
    }