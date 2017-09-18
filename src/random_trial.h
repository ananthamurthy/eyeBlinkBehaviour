#ifndef RANDOM_TRIAL_H
#define RANDOM_TRIAL_H

#define NUM_MAX_TRIALS   100

int probe_trials_[ NUM_MAX_TRIALS ] = {0};

void proble_trial_index_init( int mean, int std )
{
    for (unsigned int i = 1; i <= (NUM_MAX_TRIALS/mean); i++) 
    {
        int x = i* mean + random( - std, std + 1 );
        probe_trials_[x] = 1;
    }
}

#endif /* end of include guard: RANDOM_TRIAL_H */
