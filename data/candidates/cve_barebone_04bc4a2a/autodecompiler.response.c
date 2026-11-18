static char *gdb_to_rz_profile(char *data) {
 if (!data) {
  return NULL;
 }
 RzStrBuf *sb = rz_strbuf_new ("");
 if (!sb) {
  return NULL;
 }
 int type, number, rel, offset, size, groups, bits;
 char name[128];
 char type_name[16];
 char groups_name[128];
 char *line, *next_line;
 int i, j, k, l, ret, type_bits;
 char *res;

next_line:
 line = rz_str_trim_head_ro (data);
 if (rz_str_startswith (line, "Name")) {
  line = strchr (line, '\n');
  if (!line) {
   rz_strbuf_free (sb);
   return NULL;
  }
  line++;
 }

 while (1) {
  while (___ctype_b_loc ()[(int)((unsigned char)(*line))] & 0x2000) {
   line++;
  }
  if (!*line) {
   break;
  }
  next_line = strchr (line, '\n');
  if (next_line) {
   *next_line = '\0';
  } else {
   fprintf (stderr, "Could not parse line: %s (missing \\n)\n", line);
   rz_strbuf_free (sb);
   return NULL;
  }
  ret = ___isoc99_sscanf (line, " %s %d %d %d %d %s %s",
   type_name, &number, &rel, &offset, &size,
   name, groups_name);
  if (ret < 7) {
   switch (*line) {
   case '*':
    line = next_line + 1;
    continue;
   default:
    fprintf (stderr, "Could not parse line: %s\n", line);
    rz_strbuf_free (sb);
    return NULL;
   }
  }
  if (rz_str_startswith (name, "''")) {
   if (next_line) {
    line = next_line + 1;
   } else {
    break;
   }
   continue;
  }
  if (!size) {
   if (next_line) {
    line = next_line + 1;
   } else {
    break;
   }
   continue;
  }
  type_bits = 0;
  if (ret >= 8) {
   char *comma, *group;
   for (group = groups_name; group; ) {
    comma = strchr (group, ',');
    if (comma) {
     *comma = '\0';
    }
    if (rz_str_startswith (group, "general")) {
     type_bits |= 2;
    } else if (rz_str_startswith (group, "all")) {
     type_bits |= 1;
    } else if (rz_str_startswith (group, "save")) {
     type_bits |= 4;
    } else if (rz_str_startswith (group, "restore")) {
     type_bits |= 8;
    } else if (rz_str_startswith (group, "float")) {
     type_bits |= 16;
    } else if (rz_str_startswith (group, "sse")) {
     type_bits |= 32;
    } else if (rz_str_startswith (group, "mmx")) {
     type_bits |= 256;
    } else if (rz_str_startswith (group, "vector")) {
     type_bits |= 64;
    } else if (rz_str_startswith (group, "system")) {
     type_bits |= 128;
    }
    if (comma) {
     group = comma + 1;
    } else {
     break;
    }
   }
  } else {
   if (!type) {
    if (next_line) {
     line = next_line + 1;
    } else {
     break;
    }
    continue;
   }
   if (!(type_bits & 32) && !(type_bits & 16)) {
    type_bits |= 2;
   }
  }
  rz_strbuf_appendf (sb, "%s\t%s\t.%d\t%d\t0\n",
   (type_bits & 256 || type_bits & 16 || type_bits & 32)? "fpu": "gpr",
   name, size * 8, offset);
  if (next_line) {
   line = next_line + 1;
  } else {
   break;
  }
 }
 res = rz_strbuf_drain (sb);
 return res;
}