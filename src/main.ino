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

#include <avr/wdt.h>

#define         DRY_RUN         1
// Pins etc.
#define         TONE_PIN        2
#define         LED_PIN         3
#define         PUFF_PIN        11
#define         SENSOR_PIN      A5
#define         TONE_FREQ       4500
#define         PUFF_DURATION  50

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
bool reboot_ = false;

unsigned long currentTime( )
{
    return millis() - trial_start_time_;
}

/*-----------------------------------------------------------------------------
 *  WATCH DOG
 *-----------------------------------------------------------------------------*/
/**
 * @brief Interrupt serviving routine.
 *
 * @param _vect
 */
ISR(WDT_vect)
{
    // Handle interuppts here.
    // Nothing to handle.
}

void reset_watchdog( )
{
    if( not reboot_ )
        wdt_reset( );
}


/**
 * @brief  Read a command from command line. Consume when character is matched.
 *
 * @param command
 *
 * @return False when not mactched. If first character is matched, it is
 * consumed, second character is left in  the buffer.
 */
bool is_command_read( char command, bool consume = true )
{
    if( ! Serial.available() )
        return false;

    // Peek for the first character.
    if( command == Serial.peek( ) )
    {
        if( consume )
            Serial.read( );
        return true;
    }

    return false;
}

/**
 * @brief Write data line to Serial port.
 *   NOTE: Use python dictionary format. It can't be written at baud rate of
 *   38400 at least.
 * @param data
 * @param timestamp
 */
void write_data_line( )
{
    reset_watchdog( );
    int data = analogRead( SENSOR_PIN );
    int tone = analogRead( TONE_PIN );
    int puff = analogRead( PUFF_PIN );
    int led = analogRead( LED_PIN );
    unsigned long timestamp = millis() - trial_start_time_;
    
    sprintf(msg_  
            , "%lu,%d,%d,%d,%d,%d,%s"
            , timestamp, data, trial_count_
            , tone, puff, led
            , trial_state_
            );
    Serial.println(msg_);
    Serial.flush( );
}

void check_for_reset( void )
{
    if( is_command_read( 'r', true ) )
    {
        Serial.println( ">>> Reboot in 2 seconds" );
        reboot_ = true;
    }
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
    reset_watchdog( );
    check_for_reset( );
    unsigned long toneStart = millis();
    while( millis() - toneStart <= period )
    {
        write_data_line();
        if( millis() - toneStart <= (period * duty_cycle) )
            tone( TONE_PIN, TONE_FREQ );
        else
            noTone( TONE_PIN );
    }
}


/**
 * @brief Play puff for given duration.
 *
 * @param duration
 */
void play_puff( unsigned long duration )
{
    check_for_reset( );
    stamp_ = millis();
    while( millis() - stamp_ <= duration )
    {
        digitalWrite( PUFF_PIN, HIGH);
        write_data_line( );
    }
    digitalWrite( PUFF_PIN, LOW );
    write_data_line( );
}


/**
 * @brief Configure the experiment here. All parameters needs to be set must be
 * done here.
 */
void configure_experiment( )
{
    // While this is not answered, keep looping 
    Serial.println( "?? Please configure your experiment" );
    Serial.println( "Session type: Press 0 for 0.5 sec trace, 1 for 1 sec trace ? " );
    while( true )
    {
        incoming_byte_ = Serial.read( ) - '0';
        if( incoming_byte_ < 0 )
        {
            Serial.println( ">>> ... Waiting for response" );
            delay( 1000 );
        }
        else if( incoming_byte_ == 0 )
        {
            Serial.print( ">>> Valid response. Got " );
            Serial.println( incoming_byte_  );
            Serial.flush( );
            tsubtype_ = first;
            return;
        }
        else if( incoming_byte_ == 1 )
        {
            Serial.print( ">>> Valid response. Got " );
            Serial.println( incoming_byte_ );
            Serial.flush( );
            tsubtype_ = second;
            return;
        }
        else
        {
            Serial.print( ">>> Unexpected response, recieved : " );
            Serial.println( incoming_byte_ - '0' );
            delay( 100 );
        }
    }
}


/**
 * @brief Wait for trial to start.
 */
void wait_for_start( )
{
    sprintf( trial_state_, "INVA" , 4);
    while( true )
    {
        write_data_line( );
        if( is_command_read( 's', true ) )
        {
            Serial.println( ">>> Start" );
            break;
        }
        else if( is_command_read( 'p', true ) ) 
        {
            Serial.println( ">>> Playing puff" );
            play_puff( PUFF_DURATION );
        }
        else
        {
            //Serial.print( "Got this character " );
            Serial.print( Serial.read( ) );
        }
    }
}


void setup()
{
    Serial.begin( 38400 );

    // setup watchdog. If not reset in 2 seconds, it reboots the system.
    wdt_enable( WDTO_2S );
    wdt_reset();
    stamp_ = 0;

    pinMode( TONE_PIN, OUTPUT );
    pinMode( PUFF_PIN, OUTPUT );

    digitalWrite( PUFF_PIN, LOW );
    digitalWrite( TONE_PIN, LOW );

    configure_experiment( );
    Serial.println( ">>> Waiting for 's' to be pressed" );
    wait_for_start( );
}


/**
 * @brief Do a single trial.
 *
 * @param trial_num. Index of the trial.
 * @param ttype. Type of the trial.
 */
void do_trial( unsigned int trial_num, trial_type_t_ ttype)
{
    reset_watchdog( );
    check_for_reset( );

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
    {
        check_for_reset( );
        write_data_line( );
    }

    /*-----------------------------------------------------------------------------
     *  PUFF, only when ttype is not probe
     *-----------------------------------------------------------------------------*/
    if( probe != ttype  )
    {
        //Serial.println( "PUFF" );
        sprintf( trial_state_, "PUFF", 4 );
        play_puff( PUFF_DURATION );
        delay( 1 );
    }
    
    /*-----------------------------------------------------------------------------
     *  POST, flexible duration till trial is over.
     *-----------------------------------------------------------------------------*/
    // Last phase is post. If we are here just spend rest of time here.
    sprintf( trial_state_, "POST", 4 );
    stamp_ = millis( );
    while( millis( ) - trial_start_time_ <= trial_duration_ )
    {
        check_for_reset( );
        write_data_line( );
    }

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
    reset_watchdog( );

    for (size_t i = 0; i <= 100; i++) 
    {
        reset_watchdog( );
        if( i % 10 == 0 )
            do_trial( i, probe );
        else
            do_trial( i, type );
    }
    // We are done with all trials. Nothing to do.
    reset_watchdog( );
    Serial.println( "All done. Party!" );
    Serial.flush( );
    delay( 100 );
    exit( 0 );
}
