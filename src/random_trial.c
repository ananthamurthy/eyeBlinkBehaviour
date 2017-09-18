#include "random_trial.h"

int main(int argc, const char *argv[])
{
    random_trial( 7, 2 );

    for (unsigned int i = 0; i < NUM_MAX_TRIALS; i++) 
        printf( "%d ", trials_[i] );

    return 0;
}
