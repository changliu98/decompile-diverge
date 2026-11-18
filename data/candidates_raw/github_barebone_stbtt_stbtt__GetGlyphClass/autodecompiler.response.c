int stbtt_GetGlyphClass(const stbtt_fontinfo *info, int glyph)
{
   stbtt_int32 classdef_offset, classdef_format;
   stbtt_uint16 classdef_end, classdef_start, glyph_index;
   stbtt_uint16 *classdef1_value_array;
   stbtt_classRangeRecord *class_range_records;
   stbtt_classRangeRecord *class_range_record;
   stbtt_uint32 search_range, end_search, start_search;
   int needle, haystack, mid, low, high;
   int result;

   classdef_offset = ttUSHORT(data + 0);
   classdef_format = classdef_offset & 0xFFFF;
   switch (classdef_format) {
      case 1: {
         classdef_start = ttUSHORT(data + 2);
         classdef_end = ttUSHORT(data + 4);
         classdef1_value_array = (stbtt_uint16 *) (data + 6);
         if (glyph >= classdef_start && glyph < classdef_start + classdef_end)
            result = ttUSHORT(classdef1_value_array + (glyph - classdef_start));
         else
            result = 0;
         break;
      }
      case 2: {
         class_range_count = ttUSHORT(data + 2);
         class_range_records = (stbtt_classRangeRecord *)(data + 4);
         low = 0;
         high = class_range_count - 1;
         needle = glyph;
         while (low <= high) {
            mid = (low + high) >> 1;
            class_range_record = class_range_records + mid;
            start_search = ttUSHORT(&class_range_record->start_glyph_id);
            end_search = ttUSHORT(&class_range_record->end_glyph_id);
            if (needle < start_search)
               high = mid - 1;
            else if (needle > end_search)
               low = mid + 1;
            else
               result = ttUSHORT(&class_range_record->class_value);
         }
         break;
      }
      default: return -1;
   }

   return result;
}