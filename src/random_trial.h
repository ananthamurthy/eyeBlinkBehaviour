#ifndef RANDOM_TRIAL_H

#define RANDOM_TRIAL_H

#define NUM_MAX_TRIALS   100

int trials_[ NUM_MAX_TRIALS / 5 ] = {0};

void random_trial( int mean, int std )
{
    for (unsigned int i = 0; i < NUM_MAX_TRIALS / mean; i++) 
    {
        trials_[i] = i*mean;
        // Generate a random number between -2 and 2 and add to the trial.
        int x = random( - std, std + 1 )
        trials_[i] += x;
    }

}



#endif /* end of include guard: RANDOM_TRIAL_H */
