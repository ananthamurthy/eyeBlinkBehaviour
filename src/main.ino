/***
 *       Filename:  main.ino
 *
 *    Description:  Protocol for EyeBlinkConditioning.
 *
 *        Version:  0.0.1
 *        Created:  2017-04-11

 *         Author:  Dilawar Singh <dilawars@ncbs.res.in>
 *   Organization:  NCBS Bangalore
 *
 *        License:  GNU GPL2
 */

#include <avr/wdt.h>

// Pins etc.
#define         TONE_PIN                    2
#define         LED_PIN                     3
#define         MOTION1_PIN                 4
#define         MOTION2_PIN                 7

// These pins are more than 7.
#define         CAMERA_TTL_PIN              10
#define         PUFF_PIN                    11
#define         IMAGING_TRIGGER_PIN         13

#define         SENSOR_PIN                  A5

#define         TONE_FREQ_HIGH              4500

#define         PUFF_DURATION               50
#define         TONE_DURATION               50
#define         LED_DURATION               50


unsigned long stamp_            = 0;
unsigned dt_                    = 2;
unsigned write_dt_              = 2;
unsigned trial_count_           = 0;

char msg_[80];

unsigned long trial_start_time_ = 0;


char trial_state_[5]            = "PRE_";

/*-----------------------------------------------------------------------------
 *  User response
 *-----------------------------------------------------------------------------*/
int incoming_byte_              = 0;
bool reboot_                    = false;


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

    // Just read the registers where pin data is saved.
    int t = digitalRead( TONE_PIN );
    int led = digitalRead( LED_PIN ); 

    int puff = digitalRead( PUFF_PIN ); 
    int microscope = digitalRead( IMAGING_TRIGGER_PIN);
    int camera = digitalRead( CAMERA_TTL_PIN ); 

    unsigned long timestamp = millis() - trial_start_time_;

    int motion1 = analogRead( MOTION1_PIN );
    int motion2 = analogRead( MOTION2_PIN );
    
    sprintf(msg_  
            , "%lu,%d,%d,%d,%d,%d,%d,%d,%d,%s"
            , timestamp, trial_count_, puff, t, led
            , motion1, motion2, camera, microscope, trial_state_
            );
    Serial.println(msg_);
    Serial.flush( );
}

void check_for_reset( void )
{
    if( is_command_read( 'r', true ) )
    {
        Serial.println( ">>>Received r. Reboot in 2 seconds" );
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
void play_tone( unsigned long period, unsigned freq, double duty_cycle = 0.5 )
{
    reset_watchdog( );
    check_for_reset( );
    unsigned long toneStart = millis();
    while( millis() - toneStart <= period )
    {
        write_data_line();
        if( millis() - toneStart <= (period * duty_cycle) )
            tone( TONE_PIN, freq );
        else
            noTone( TONE_PIN );
    }
    noTone( TONE_PIN );
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
}

void led_on( unsigned int duration )
{
    stamp_ = millis( );
    while( millis() - stamp_ <= duration )
    {
        digitalWrite( LED_PIN, HIGH );
        write_data_line( );
    }
    digitalWrite( LED_PIN, LOW );
}


/**
 * @brief Configure the experiment here. All parameters needs to be set must be
 * done here.
 */
void configure_experiment( )
{
    // While this is not answered, keep looping 
    Serial.println( "?? Please configure your experiment" );
    Serial.println( "NOTE: This has been disabled" );
    while( true )
    {
        break;
#if 0
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
#endif
    }
}


/**
 * @brief Wait for trial to start.
 */
void wait_for_start( )
{
    sprintf( trial_state_, "INVA" );
    while( true )
    {

        /*-----------------------------------------------------------------------------
         *  Make sure each after reading command, we send >>>Received to serial
         *  port. The python client waits for it.
         *-----------------------------------------------------------------------------*/
        write_data_line( );
        if( is_command_read( 's', true ) )
        {
            Serial.println( ">>>Received s. Start" );
            break;                              /* Only START can break the loop */
        }
        else if( is_command_read( 'p', true ) ) 
        {
            Serial.println( ">>>Received p. Playing puff" );
            play_puff( 50 );                 /* Play puff of 10 second for instrument to record. */
        }
        else if( is_command_read( 't', true ) ) 
        {
            Serial.println( ">>>Received t. Playing tone" );
            play_tone( 350, 1.0);             /* Play tone for 10 seconds for instruments to record */
        }
#if 0
        else if( is_command_read( 'l', true ) ) 
        {
            Serial.println( ">>>Received l. LED ON" );
            led_on( LED_DURATION );
        }
#endif
        else
        {
            char c = Serial.read( );
            if( c != -1 )
            {
                Serial.print( ">>> Unknown command : " );
                Serial.println( c );
                delay( 1000 );
            }
        }
    }
}


void setup()
{
    Serial.begin( 38400 );

    // Random seed.
    randomSeed( analogRead(0) );

    //esetup watchdog. If not reset in 2 seconds, it reboots the system.
    wdt_enable( WDTO_2S );
    wdt_reset();
    stamp_ = millis( );

    pinMode( TONE_PIN, OUTPUT );
    pinMode( PUFF_PIN, OUTPUT );
    pinMode( LED_PIN, OUTPUT );

    pinMode( CAMERA_TTL_PIN, OUTPUT );
    pinMode( IMAGING_TRIGGER_PIN, OUTPUT );

    /*  Pins set by sensors */
    pinMode( MOTION1_PIN, INPUT );
    pinMode( MOTION2_PIN, INPUT );

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
void do_trial( bool isporobe = false )
{
    reset_watchdog( );
    check_for_reset( );

    trial_start_time_ = millis( );

    /*-----------------------------------------------------------------------------
     *  PRE. Start imaging for 10 seconds.
     *-----------------------------------------------------------------------------*/

    sprintf( trial_state_, "PRE_" );
    digitalWrite( IMAGING_TRIGGER_PIN, HIGH);   /* Start imaging. */

    digitalWrite( CAMERA_TTL_PIN, LOW );
    digitalWrite( LED_PIN, LOW );

    unsigned duration = 5000;
    stamp_ = millis( );
    while( (millis( ) - stamp_) < duration ) /* PRE_ time */
    {
        // 500 ms before the PRE_ ends, start camera pin high. We start
        // recording as well.
        if( (millis( ) - stamp_) >= (duration - 1500 ) )
            digitalWrite( CAMERA_TTL_PIN, HIGH );
        else
            digitalWrite( CAMERA_TTL_PIN, LOW );

        write_data_line( );
    }
    stamp_ = millis( );

    /*-----------------------------------------------------------------------------
     *  CS: 350 ms duration. Tone is played here.
     *-----------------------------------------------------------------------------*/
    duration = 350;
    sprintf( trial_state_, "TONE" );
    play_tone( duration, TONE_FREQ_HIGH, 1.0 );
    stamp_ = millis( );

    /*-----------------------------------------------------------------------------
     *  TRACE. The duration of trace varies from trial to trial.
     *-----------------------------------------------------------------------------*/
    duration = 250;
    sprintf( trial_state_, "TRAC" );
    while( (millis( ) - stamp_) <= duration )
    {
        check_for_reset( );
        write_data_line( );
    }
    stamp_ = millis( );

    /*-----------------------------------------------------------------------------
     *  PUFF for PUFF_DURATION ms.
     *-----------------------------------------------------------------------------*/
    duration = PUFF_DURATION;
    if( isporobe )
    {
        sprintf( trial_state_, "PROB" );
        while( (millis( ) - stamp_) <= duration )
            write_data_line( );
    }
    else
    {
        sprintf( trial_state_, "PUFF" );
        play_puff( duration );
    }

    stamp_ = millis( );
    
    /*-----------------------------------------------------------------------------
     *  POST, flexible duration till trial is over. It is 10 second long.
     *-----------------------------------------------------------------------------*/
    // Last phase is post. If we are here just spend rest of time here.
    duration = 5000;
    sprintf( trial_state_, "POST" );
    while( (millis( ) - stamp_) <= duration )
    {
        write_data_line( );
        // Switch camera OFF after 1500 ms into POST.
        if( (millis() - stamp_) >= 1500 )
            digitalWrite( CAMERA_TTL_PIN, LOW );

    }

    /*-----------------------------------------------------------------------------
     *  End trial.
     *-----------------------------------------------------------------------------*/
    digitalWrite( IMAGING_TRIGGER_PIN, LOW ); /* Shut down the imaging. */
    Serial.print( ">>END Trial " );
    Serial.print( trial_count_ );
    Serial.println( " is over. Starting new");
}

void loop()
{
    reset_watchdog( );
    // The probe trial occurs every 7th trial with +/- of 2 trials.
    unsigned numProbeTrials = 0;

    // random number from uniform([10-var,10+var])
    unsigned var = 2;
    unsigned nextProbbeTrialIndex = random(10-var, 10+var+1);

    for (size_t i = 1; i <= 101; i++) 
    {
        reset_watchdog( );

         // Probe trial.
        if( i == nextProbbeTrialIndex )
        {
            do_trial( true );
            numProbeTrials +=1 ;
            nextProbbeTrialIndex = random( 
                    (numProbeTrials+1)*10-var, (numProbeTrials+1)*10+var+1
                    );
        }
        else
            do_trial( false );

        
        /*-----------------------------------------------------------------------------
         *  ITI.
         *-----------------------------------------------------------------------------*/
        unsigned long rduration = random( 10000, 15001);
        stamp_ = millis( );
        sprintf( trial_state_, "ITI_" );
        while((millis( ) - stamp_) <= rduration )
        {
            reset_watchdog( );
            delay( 10 );
        }
        trial_count_ += 1;
    }

    // Do do anything once trails are over.
    while( true )
    {
        reset_watchdog( );
        Serial.println( ">>> All done" );
        delay( 1000 );
    }
}
