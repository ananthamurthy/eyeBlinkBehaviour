/***
 *       Filename:  main.ino
 *
 *    Description:  Anamika Protocol for EyeBlinkConditioning.
 *
 *        Version:  0.0.1
 *        Created:  2016-09-29

 *       Revision:  none
 *
 *         Author:  Dilawar Singh <dilawars@ncbs.res.in>
 *   Organization:  NCBS Bangalore
 *
 *        License:  GNU GPL2
 */

#define         DRY_RUN         1

unsigned long stamp_ = 0;
unsigned dt_ = 2;
unsigned trial_count_ = 0;

unsigned long trial_start_time_ = 0;
unsigned long trial_end_time_ = 0;

/**
 * @brief Duration of each trial.
 */
const unsigned trial_duration_ = 18000;

enum enum_states_ {  pre_, tone_, trace_, puff_, post_ };

/**
 * @brief There are 4 types of trail. Table is below.
 *  --------------------------------------------------------+
 *  Puff (present or absent) | Trace period | name          |
 *  -------------------------+--------------+---------------+
 *  1                        | 0.5          | type, first   |
 *  1                        | 1.0          | type, second  |
 *  0                        | 0.5          | probe, first  |
 *  0                        | 1.0          | probe, second |
 *  -------------------------+--------------+---------------+
 */
enum trial_type_t_ { type, probe };
enum trial_subtype_t_ { first, second };


enum_states_ current_state_;

unsigned long currentTime( )
{
    return millis() - trial_start_time_;
}

void setup()
{
    Serial.begin( 19200 );
    stamp_ = 0;
    current_state_ = pre_;
}

void do_trial( unsigned int trial_num
        , trial_type_t_ ttype
        , trial_subtype_t_ tsubtype
        )
{
    trial_start_time_ = millis( );

    /*-----------------------------------------------------------------------------
     *  PRE
     *-----------------------------------------------------------------------------*/
    Serial.println( "PRE" );
    while( millis( ) - trial_start_time_ <= 5000 )
    {
        delay( dt_ );
    }

    /*-----------------------------------------------------------------------------
     *  TONE
     *-----------------------------------------------------------------------------*/
    unsigned toneDuration = 1000 * (3 + random( 5 ));
    stamp_ = millis();
    Serial.println( "TONE" );
    while( millis( ) - stamp_ <= toneDuration )
    {
        delay( dt_ );
    }

    /*-----------------------------------------------------------------------------
     *  TRACE
     *-----------------------------------------------------------------------------*/
    unsigned traceDuration = 500;
    if( tsubtype == second )
        unsigned traceDuration = 1000;

    stamp_ = millis( );
    Serial.println( "TRACE" );
    while( millis( ) - stamp_ < traceDuration )
    {
        delay( dt_ );
    }

    /*-----------------------------------------------------------------------------
     *  PUFF
     *-----------------------------------------------------------------------------*/
    stamp_ = millis();
    unsigned long puffDuration = 50;
    Serial.println( "PUFF" );
    while( millis() - trial_start_time_ < puffDuration )
    {
        delay( dt_ );
    }
    
    /*-----------------------------------------------------------------------------
     *  POST, flexible duration till trial is over.
     *-----------------------------------------------------------------------------*/
    // Last phase is post. If we are here just spend rest of time here.
    Serial.println( "POST" );
    stamp_ = millis( );
    while( millis( ) - trial_start_time_ < trial_duration_ )
    {
        delay( dt_ );
    }

    /*-----------------------------------------------------------------------------
     *  End trial.
     *-----------------------------------------------------------------------------*/
    if( millis() - trial_start_time_ >= trial_duration_ )
    {
        Serial.print( "Trial " );
        Serial.print( trial_count_ );
        Serial.println( " is over. Starting new");
        trial_count_ += 1;
    }
}

void loop()
{
    for (size_t i = 0; i < 3; i++) 
    {
        if( i % 10 == 0 )
            do_trial( i, probe, first );
        else
            do_trial( i, type, first );
    }
    // We are done with all trials. Nothing to do.
    Serial.println( "All done. Party!" );
    Serial.flush( );
    delay( 100 );
    exit( 0 );

}
