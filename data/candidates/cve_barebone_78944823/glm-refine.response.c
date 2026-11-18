int __cdecl sample_conv_regsub(const arg *arg_p, sample *smp, void *a3)
{
  regmatch_t pmatch[10];
  int flag = 0;
  
  my_regex *reg = arg_p->data.reg;
  buffer *trash = get_trash_chunk();
  char *start = smp->data.u.str.area;
  char *end = &start[smp->data.u.str.data];

  while (1)
  {
    int found = 0;
    
    // Execute regex match if it's the first iteration or if global matching is enabled
    if ((arg_p->type_flags & 2) != 0 || (flag & 1) == 0)
      found = regex_exec_match2(reg, start, (int)(end - start), 0xAuLL, pmatch, flag);
      
    flag |= 1u; // Set flag to indicate first iteration has passed

    // If no match was found, set the end of the match to the end of the string
    if (!found)
      pmatch[0].rm_so = (int)(end - start);

    // Copy the part of the string before the match into the trash buffer
    int max = (int)trash->size - (int)trash->data;
    if (max > 0 && pmatch[0].rm_so > 0)
    {
      if (max > pmatch[0].rm_so)
        max = pmatch[0].rm_so;
        
      memcpy(&trash->area[trash->data], start, max);
      trash->data += max;
    }

    // Break if no match was found
    if (!found)
      break;

    // Allocate a temporary output buffer for the replacement
    buffer *output = alloc_trash_chunk();
    if (!output)
      break;

    // Perform the regex substitution and store the length in output->data
    output->data = exp_replace(output->area, output->size, start, arg_p[1].data.str.area, pmatch);

    // Copy the replacement string into the trash buffer
    int maxa = (int)output->size - (int)output->data;
    if (maxa > 0)
    {
      if (maxa > output->data)
        maxa = output->data;
        
      memcpy(&trash->area[trash->data], output->area, maxa);
      trash->data += maxa;
    }
    
    free_trash_chunk(output);

    // Break if we've reached the end of the string
    if (start >= end)
      break;

    // Handle zero-length matches to avoid infinite loops
    if (pmatch[0].rm_eo == 0)
    {
      if (trash->data < trash->size)
      {
        trash->area[trash->data] = start[pmatch[0].rm_eo];
        trash->data++;
      }
      pmatch[0].rm_eo++;
    }
    
    // Advance the start pointer past the matched portion
    start += pmatch[0].rm_eo;
  }

  // Update the sample with the modified buffer
  smp->data.u = (sample_value)*trash;
  
  return 1;
}