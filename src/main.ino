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

// Pins etc.
#define         TONE_PIN        2
#define         LED_PIN         3
#define         PUFF_PIN        11

#define         SENSOR_PIN      A5

#define         TONE_FREQ       11000

unsigned long stamp_ = 0;
unsigned dt_ = 2;
unsigned write_dt_ = 2;
unsigned trial_count_ = 0;
char msg_[40];

unsigned long trial_start_time_ = 0;
unsigned long trial_end_time_ = 0;

/**
 * @brief Duration of each trial.
 */
const unsigned trial_duration_ = 18000;

char trial_state_[5] = "PRE_";

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
trial_type_t_ ttype_ = type;

enum trial_subtype_t_ { first, second };
trial_subtype_t_ tsubtype_ = first;


/*-----------------------------------------------------------------------------
 *  User response
 *-----------------------------------------------------------------------------*/
int incoming_byte_ = 0;

unsigned long currentTime( )
{
    return millis() - trial_start_time_;
}


/**
 * @brief Write data line to Serial port.
 * NOTE: Don't specify a delay, let's get the best possible output arduino.
 *
 * @param data
 * @param timestamp
 */
void write_data_line( )
{
    int data = analogRead( SENSOR_PIN );
    int tone = analogRead( TONE_PIN );
    int puff = analogRead( PUFF_PIN );
    int led = analogRead( LED_PIN );
    unsigned long timestamp = millis() - trial_start_time_;
    
    sprintf(msg_, "%6lu,%5d,%3d,%1d,%1d,%1d,%s"
            , timestamp, data, trial_count_
            , tone, puff, led
            , trial_state_
            );
    Serial.println(msg_);
}

/**
 * @brief Play tone for given period and duty cycle. 
 *
 * NOTE: We can not block the arduino using delay, since we have to write the
 * values onto Serial as well.
 *
 * @param period
 * @param duty_cycle
 */
void play_tone( unsigned long period, double duty_cycle = 0.5 )
{
    unsigned long toneStart = millis();
    while( millis() - toneStart <= period )
    {
        write_data_line();
        if( millis() - toneStart <= (period * duty_cycle) )
            tone( TONE_PIN, TONE_FREQ );
            //digitalWrite( TONE_PIN, HIGH );
        else
            noTone( TONE_PIN );
            //digitalWrite( TONE_PIN, LOW );
    }
}

void configure( )
{
    // While this is not answered, keep looping 
    Serial.println( "?? Please configure your experiment" );
    Serial.println( "Session type: Press 0 for 0.5 sec trace, 1 for 1 sec trace ? " );
    while( true )
    {
        incoming_byte_ = Serial.read( );
        if( incoming_byte_ == -1 )
        {
            delay( 1000 );
            Serial.println( "... Waiting for response" );
            delay( 1000 );
        }
        else if( incoming_byte_ == 48 )
        {
            Serial.print( "Recieved : " );
            Serial.println( incoming_byte_ );
            tsubtype_ = first;
            break;
        }
        else if( incoming_byte_ == 49 )
        {
            Serial.print( "Recieved : " );
            Serial.println( incoming_byte_ );
            tsubtype_ = second;
            break;
        }
        else
        {
            Serial.print( "Unexpected response, recieved : " );
            Serial.println( incoming_byte_ - '0' );
            delay( 100 );
        }
    }
}

/**
 * @brief  Read a command from command line. Consume when character is matched.
 *
 * @param command
 *
 * @return False when not mactched. If first character is matched, it is
 * consumed, second character is left in  the buffer.
 */
bool read_command( char* command )
{
    int first, second;
    if( Serial.available( ) > 0 )
    {
        first = Serial.peek( );
        delay( 1 );
        if( first == command[0] )
        {
            incoming_byte_ = Serial.read();     /* Remove it. */
            delay( 1 );

            while( Serial.available( ) <= 0 )
            { }

            second = Serial.peek( );
            if( second == command[1] )
            {
                incoming_byte_ = Serial.read(); /* Remove it */
                delay( 1 );
                return true;
            }
        }

    }
    return false;
}

void wait_for_start( )
{
    while( false == read_command( "ss" ) )
    {
        sprintf( trial_state_, "INVA" , 4);
        delay( dt_ );
        write_data_line( );
    }
}


void setup()
{
    Serial.begin( 38400 );
    stamp_ = 0;
    pinMode( TONE_PIN, OUTPUT );
    pinMode( PUFF_PIN, OUTPUT );

    digitalWrite( PUFF_PIN, LOW );
    digitalWrite( TONE_PIN, LOW );

    configure( );
    wait_for_start( );
}

void do_trial( unsigned int trial_num, trial_type_t_ ttype)
{
    trial_start_time_ = millis( );

    /*-----------------------------------------------------------------------------
     *  PRE
     *-----------------------------------------------------------------------------*/
    sprintf( trial_state_, "PRE_", 4 );
    write_data_line( );
    while( millis( ) - trial_start_time_ <= 5000 )
        write_data_line( );

    /*-----------------------------------------------------------------------------
     *  TONE
     *-----------------------------------------------------------------------------*/
    unsigned toneDuration = 1000 * (3 + random( 5 ));
    stamp_ = millis();
    sprintf( trial_state_, "TONE", 4);
    while( millis( ) - stamp_ <= toneDuration )
        play_tone( 100, 0.5 );

    /*-----------------------------------------------------------------------------
     *  TRACE
     *-----------------------------------------------------------------------------*/
    unsigned traceDuration = 500;
    if( tsubtype_ == second )
        unsigned traceDuration = 1000;

    stamp_ = millis( );
    sprintf( trial_state_, "TRAC", 4 );
    while( millis( ) - stamp_ < traceDuration )
        write_data_line( );

    /*-----------------------------------------------------------------------------
     *  PUFF
     *-----------------------------------------------------------------------------*/
    //Serial.println( "PUFF" );
    sprintf( trial_state_, "PUFF", 4 );
    unsigned long puffDuration = 50;
    stamp_ = millis();
    while( millis() - stamp_ <= puffDuration )
    {
        digitalWrite( PUFF_PIN, HIGH);
        write_data_line( );
    }

    // Switch OFF the puff.
    digitalWrite( PUFF_PIN, LOW );
    delay( 1 );
    
    /*-----------------------------------------------------------------------------
     *  POST, flexible duration till trial is over.
     *-----------------------------------------------------------------------------*/
    // Last phase is post. If we are here just spend rest of time here.
    sprintf( trial_state_, "POST", 4 );
    stamp_ = millis( );
    while( millis( ) - trial_start_time_ <= trial_duration_ )
        write_data_line( );

    /*-----------------------------------------------------------------------------
     *  End trial.
     *-----------------------------------------------------------------------------*/
    if( millis() - trial_start_time_ >= trial_duration_ )
    {
        Serial.print( ">>END Trial " );
        Serial.print( trial_count_ );
        Serial.println( " is over. Starting new");
        trial_count_ += 1;
    }
}

void loop()
{
    for (size_t i = 0; i < 10; i++) 
    {
        if( i % 10 == 0 )
            do_trial( i, probe );
        else
            do_trial( i, type );
    }
    // We are done with all trials. Nothing to do.
    Serial.println( "All done. Party!" );
    Serial.flush( );
    delay( 100 );
    exit( 0 );

}
