void __cdecl IdealTrack(unsigned __int64 total_tracks, unsigned __int64 top_count, unsigned __int64 bot_count, unsigned __int64 *out_ideal)
{
    unsigned __int64 denominator = bot_count + top_count;

    if (denominator != 0)
    {
        // Original expression: ((top_count + 1) * bot_count + (total_tracks - bot_count) * top_count) / denominator
        //
        // Algebraic expansion of the numerator:
        //   (top_count * bot_count + bot_count) + (total_tracks * top_count - bot_count * top_count)
        // 
        // The (top_count * bot_count) and (- bot_count * top_count) terms cancel each other out, leaving:
        //   bot_count + (total_tracks * top_count)
        //
        // This reveals that the function computes a simple weighted average:
        //   (bot_count * 1 + top_count * total_tracks) / (top_count + bot_count)
        *out_ideal = (bot_count + total_tracks * top_count) / denominator;
    }
    else
    {
        // Fallback to avoid division by zero when both counts are 0
        *out_ideal = 1LL;
    }
}