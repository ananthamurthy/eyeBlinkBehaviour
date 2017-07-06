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
#include "config.h"

//#define USE_MOUSE 
#ifdef USE_MOUSE
#include "arduino-ps2-mouse/PS2Mouse.h"
#endif

// Pins etc.
#define         TONE_PIN                    2
#define         LED_PIN                     3

// These pins are more than 7.
#define         CAMERA_TTL_PIN              10
#define         PUFF_PIN                    11
#define         IMAGING_TRIGGER_PIN         13

#define         SENSOR_PIN                  A5

#define         TONE_FREQ                   4500

#define         PUFF_DURATION               50
#define         TONE_DURATION               350
#define         LED_DURATION                50

#ifdef USE_MOUSE
// Motion detection related.
#define         CLOCK_PIN                 6
#define         DATA_PIN                  7
#else
#define         MOTION1_PIN                 6
#define         MOTION2_PIN                 7
#endif 


// Motion detection based on motor
#define         MOTOR_OUT              A1

// What kind of stimulus is given.
#define         SOUND                   0
#define         LIGHT                   1
#define         MIXED                   2


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

/*
 * MOUSE
 */
#ifdef USE_MOUSE
PS2Mouse mouse( CLOCK_PIN, DATA_PIN );
#endif

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
    int tone = digitalRead( TONE_PIN );
    int led = digitalRead( LED_PIN ); 

    int puff = digitalRead( PUFF_PIN ); 
    int microscope = digitalRead( IMAGING_TRIGGER_PIN);
    int camera = digitalRead( CAMERA_TTL_PIN ); 

    unsigned long timestamp = millis() - trial_start_time_;

    int motion1;
    int motion2;

#ifdef USE_MOUSE
    // Read mouse data.
    MouseData data = mouse.readData( );
    motion1 = data.position.x;
    motion2 = data.position.y;
#else
    motion1 = digitalRead( MOTION1_PIN );
    motion2 = digitalRead( MOTION2_PIN );
#endif
    
    sprintf(msg_  
            , "%lu,%d,%d,%d,%d,%3d,%3d,%d,%d,%s"
            , timestamp, trial_count_, puff, tone, led
            , motion1, motion2, camera, microscope, trial_state_
            );
    Serial.println(msg_);
    Serial.flush( );
    //delay( 3 );
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
            Serial.println( ">>>Received r. Start" );
            break;                              /* Only START can break the loop */
        }
        else if( is_command_read( 'p', true ) ) 
        {
            Serial.println( ">>>Received p. Playing puff" );
            play_puff( PUFF_DURATION );
        }
        else if( is_command_read( 't', true ) ) 
        {
            Serial.println( ">>>Received t. Playing tone" );
            play_tone( TONE_DURATION, 1.0);
        }
        else if( is_command_read( 'l', true ) ) 
        {
            Serial.println( ">>>Received l. LED ON" );
            led_on( LED_DURATION );
        }
        else
        {
            char c = Serial.read( );
            if( c != -1 )
            {
                Serial.print( ">>> Unknown command : " );
                Serial.println( c );
            }
        }
    }
}

void print_trial_info( )
{
    Serial.print( ">> ANIMAL NAME: " );
    Serial.print( ANIMAL_NAME );
    Serial.print( " SESSION NUM: " );
    Serial.print( SESSION_NUM );
    Serial.print( " SESSION TYPE: " );
    Serial.println( SESSION_TYPE );
}

void setup()
{
    Serial.begin( 38400 );

    // Random seed.
    randomSeed( analogRead(A5) );

    //esetup watchdog. If not reset in 2 seconds, it reboots the system.
    wdt_enable( WDTO_2S );
    wdt_reset();
    stamp_ = millis( );

    pinMode( TONE_PIN, OUTPUT );
    pinMode( PUFF_PIN, OUTPUT );
    pinMode( LED_PIN, OUTPUT );

    pinMode( CAMERA_TTL_PIN, OUTPUT );
    pinMode( IMAGING_TRIGGER_PIN, OUTPUT );



#ifdef USE_MOUSE
    // Configure mouse here
    mouse.initialize( );
    Serial.println( "Stuck in setup() ... mostly due to MOUSE" );
#else
    Serial.println( "Using LED/DIODE pair" );
    pinMode( MOTION1_PIN, INPUT );
    pinMode( MOTION2_PIN, INPUT );
#endif

    print_trial_info( );
    wait_for_start( );
}

void do_zero_trial( )
{
    return;
}

void do_first_trial( )
{
    return;
}

/**
 * @brief Just for testing.
 *
 * @param duration
 */
void do_empty_trial( size_t trial_num, int duration = 10 )
{
    Serial.print( ">> TRIAL NUM: " );
    Serial.println( trial_num );
    //print_trial_info( );
    delay( duration );
    Serial.println( ">>     TRIAL OVER." );
}

/**
 * @brief Do a single trial.
 *
 * @param trial_num. Index of the trial.
 * @param ttype. Type of the trial.
 */
void do_trial( unsigned int trial_num, int cs_type, bool isprobe = false )
{
    reset_watchdog( );
    check_for_reset( );

    print_trial_info( );
    trial_start_time_ = millis( );

    // PRE
    unsigned duration = 10000;
    stamp_ = millis( );

    sprintf( trial_state_, "PRE_" );
    digitalWrite( IMAGING_TRIGGER_PIN, HIGH);   /* Start imaging. */

    digitalWrite( CAMERA_TTL_PIN, LOW );
    digitalWrite( LED_PIN, LOW );

    while( (millis( ) - trial_start_time_ ) <= duration ) /* PRE_ time */
    {
        // 500 ms before the PRE_ ends, start camera pin high. We start
        // recording as well.
        if( (millis( ) - stamp_) >= (duration - 500 ) )
            if( LOW == digitalRead( CAMERA_TTL_PIN ) )
                digitalWrite( CAMERA_TTL_PIN, HIGH );

        write_data_line( );
    }
    stamp_ = millis( );

    /*-----------------------------------------------------------------------------
     *  CS: 50 ms duration. Either LED or TONE depending on trial type.
     *-----------------------------------------------------------------------------*/
    if( cs_type == LIGHT )
    {
        duration = LED_DURATION;
        stamp_ = millis( );
        sprintf( trial_state_, "CS+" );
        led_on( duration );
        stamp_ = millis( );
    }
    else if( cs_type == SOUND )
    {
        duration = TONE_DURATION;
        stamp_ = millis( );
        sprintf( trial_state_, "CS+" );
        play_tone( duration );
        stamp_ = millis( );
    }
    else if( cs_type == MIXED )
    {
        // Mixed type.
    }
    else
    {
        Serial.println( ">> Horror horror. What type of session is that?" );
        Serial.println( ">> We only allow type 0 (SOUND), 1 (LIGHT) or 2 (MIXED)" );
    }

    /*-----------------------------------------------------------------------------
     *  TRACE. The duration of trace varies from trial to trial.
     *-----------------------------------------------------------------------------*/
    duration = 250;
    sprintf( trial_state_, "TRAC" );
    while( (millis( ) - stamp_) <= duration )
        write_data_line( );
    stamp_ = millis( );

    /*-----------------------------------------------------------------------------
     *  PUFF for 50 ms if trial is not a probe type.
     *-----------------------------------------------------------------------------*/
    duration = PUFF_DURATION;
    if( isprobe )
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
    duration = 10000;
    sprintf( trial_state_, "POST" );
    while( (millis( ) - stamp_) <= duration )
    {
        write_data_line( );
        // Switch camera OFF after 500 ms into POST.
        if( (millis() - stamp_) >= 500 )
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
    unsigned nextProbbeTrialIndex = random(5, 10);

    for (size_t i = 1; i <= 81; i++) 
    {

        reset_watchdog( );

        // These are normal trial with either SOUND or LIGHT.
        if( SESSION_TYPE == 0 || SESSION_TYPE == 1 )
        {
            int cs_type = SOUND;
            if( 1 == SESSION_TYPE )
                cs_type = LIGHT;

            bool isprobe = false;

            // Probe trial.
            if( i == nextProbbeTrialIndex )
            {
                isprobe = true;
                numProbeTrials +=1 ;
                nextProbbeTrialIndex = random( 
                        (numProbeTrials+1)*10-2, (numProbeTrials+1)*10+3
                        );
            }
#if DEBUG
            if( isprobe )
            {
                Serial.print( ">> PROBE TRIAL. Index :" );
                Serial.print( i );
                Serial.print( ". Next probe " );
                Serial.println( nextProbbeTrialIndex );
            }
#endif

#if DEBUG
            do_empty_trial( i );
#else
            do_trial( i, cs_type, isprobe );
#endif
        }
	/*************************************************************************
	* MIXED TRIALS
	*************************************************************************/

        else if( 2 == SESSION_TYPE )  // These are mixed trials.
        {
            // Every 5, 10, 15 etc trial is proble trials.
            bool isprobe = false;
            if( i % 5 == 0 )
                isprobe = true;

#if DEBUG
            if( isprobe )
            {
                Serial.print( ">> PROBE TRIAL. Index :" );
                Serial.println( i );
            }
#endif

            // 1-4, 11-14, 21-24 etc are trails with SOUND.
            int cs_type = LIGHT;
            if( i % 10 > 0 && i % 10 <= 5 )
                cs_type = SOUND;
#if DEBUG
            do_empty_trial( i );
#else
            do_trial( i, cs_type, isprobe );
#endif

        }
        else
        {
            Serial.println( ">> Horror horror. What type of session is that?" );
            Serial.println( ">> We only allow type 0 (SOUND), 1 (LIGHT) or 2 (MIXED)" );
        }
        
        /*-----------------------------------------------------------------------------
         *  ITI.
         *-----------------------------------------------------------------------------*/
#if DEBUG
        unsigned long rduration = random( 100, 151);
#else
        unsigned long rduration = random( 10000, 15001);
#endif
        stamp_ = millis( );
        sprintf( trial_state_, "ITI_" );
        while((millis( ) - stamp_) <= rduration )
        {
            reset_watchdog( );
            delay( 10 );
        }

        trial_count_ += 1;
    }

    // Don't do anything once trails are over.
    while( true )
    {
        reset_watchdog( );
        Serial.println( ">>> All done" );
        delay( 1000 );
    }
}
