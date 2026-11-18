void dhmm_copy(DHMM *source_hmm, DHMM *target_hmm)
{
    int state_idx, target_idx, obs_idx;

    // Copy the number of hidden states
    target_hmm->N = source_hmm->N;
    // Allocate memory for the number of observations per state
    target_hmm->nN = cvector(1, target_hmm->N);
    // Copy the number of observations per state
    for (state_idx = 1; state_idx <= target_hmm->N; state_idx++) {
        target_hmm->nN[state_idx] = source_hmm->nN[state_idx];
    }

    // Copy the number of observation symbols
    target_hmm->M = source_hmm->M;
    // Allocate memory for the number of observation symbols per state
    target_hmm->nM = cvector(1, target_hmm->M);
    // Copy the number of observation symbols per state
    for (state_idx = 1; state_idx <= target_hmm->M; state_idx++) {
        target_hmm->nM[state_idx] = source_hmm->nM[state_idx];
    }

    // Allocate memory for the state transition matrix
    target_hmm->A = dmatrix(1, target_hmm->N, 1, target_hmm->N);
    // Copy the state transition matrix
    for (state_idx = 1; state_idx <= target_hmm->N; state_idx++) {
        for (target_idx = 1; target_idx <= target_hmm->N; target_idx++) {
            target_hmm->A[state_idx][target_idx] = source_hmm->A[state_idx][target_idx];
        }
    }

    // Allocate memory for the observation probability matrix
    target_hmm->B = dmatrix(1, target_hmm->N, 1, target_hmm->M);
    // Copy the observation probability matrix
    for (target_idx = 1; target_idx <= target_hmm->N; target_idx++) {
        for (obs_idx = 1; obs_idx <= target_hmm->M; obs_idx++) {
            target_hmm->B[target_idx][obs_idx] = source_hmm->B[target_idx][obs_idx];
        }
    }

    // Allocate memory for the initial state distribution
    target_hmm->pi = dvector(1, target_hmm->N);
    // Copy the initial state distribution
    for (state_idx = 1; state_idx <= target_hmm->N; state_idx++) {
        target_hmm->pi[state_idx] = source_hmm->pi[state_idx];
    }
}