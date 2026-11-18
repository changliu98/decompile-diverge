// Updates alpha/beta bounds and returns true if a cutoff should occur
// score: current evaluation score
// alpha: pointer to current alpha value (best score for maximizer)
// beta: pointer to current beta value (best score for minimizer)
// max: boolean flag indicating if current node is a maximizer node
int alphabeta_cutoff(int evaluation_score, int *best_maximizer_score, int *best_minimizer_score, int is_maximizer_node)
{
    // If this is a minimizer node and score is below beta, update beta
    if (is_maximizer_node == 0 && evaluation_score < *best_minimizer_score) {
        *best_minimizer_score = evaluation_score;
    } 
    // If this is a maximizer node and score is above alpha, update alpha
    else if (evaluation_score > *best_maximizer_score) {
        *best_maximizer_score = evaluation_score;
    }
    // Return true if alpha >= beta, indicating a cutoff should occur
    return *best_minimizer_score <= *best_maximizer_score;
}