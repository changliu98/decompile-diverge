void __cdecl check_supported(item *a1)
{
    const char **allowed_params;
    uschar buffer[256];
    paramstr *param;
    tree_node *tn;
    int mid;
    int top;
    int bot;
    int cmp;
    item *current_item;

    current_item = a1;
    cmp = -1;
    bot = 0;
    top = supported_elements_count;
    
    // Binary search for the item's name in the supported_elements array
    while ( top > bot )
    {
        mid = (bot + top) / 2;
        cmp = strcmp(current_item->name, supported_elements[2 * mid]);
        if ( !cmp )
            break;
        if ( cmp >= 0 )
            bot = mid + 1;
        else
            top = mid;
    }
    
    // If the element name is found (cmp == 0)
    if ( !cmp )
    {
        // Iterate over all parameters of the item
        for ( param = current_item->p.param; ; param = param->next )
        {
            if ( !param )
                return;
                
            // Ignore parameters starting with '#' (ASCII 35)
            if ( param->name[0] != 35 )
            {
                // Check for "revisionflag" parameter
                if ( !strcmp(param->name, "revisionflag") )
                {
                    if ( !strcmp(param->value, "changed") )
                        continue;
                        
                    sprintf((char *)buffer, "+%s=%s:%s", param->name, param->value, current_item->name);
                    goto LABEL_24;
                }
                
                // Check if the parameter is in the list of allowed parameters for this element
                allowed_params = supported_elements[2 * mid + 1];
                if ( !allowed_params )
                    goto LABEL_23;
                    
                if ( strcmp(*allowed_params, "*") ) // If not a wildcard "*"
                {
                    while ( *allowed_params && strcmp(*allowed_params, param->name) )
                        ++allowed_params;
                        
                    if ( !*allowed_params )
                    {
LABEL_23:
                        sprintf((char *)buffer, "+%s:%s", param->name, current_item->name);
LABEL_24:
                        tn = tree_search(unknown_element_tree, (const char *)buffer);
                        if ( !tn )
                        {
                            tn = (tree_node *)misc_malloc(strlen((const char *)buffer) + 32);
                            strcpy(tn->name, (const char *)buffer);
                            tree_insertnode(&unknown_element_tree, tn);
                        }
                        continue;
                    }
                }
            }
        }
    }
    
    // If the element name was NOT found in supported_elements, add the element name itself to the tree
    if ( !tree_search(unknown_element_tree, current_item->name) )
    {
        tn = (tree_node *)misc_malloc(strlen(current_item->name) + 32);
        strcpy(tn->name, current_item->name);
        tree_insertnode(&unknown_element_tree, tn);
    }
}