#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clock.h"

// function set_tod_from_secs: accepts time of day in seconds as an argument and modifies the
// struct pointed at by tod to fill in its hours, minutes,
// etc. fields.  If time_of_day_sec is invalid (negative or larger
// than the number of seconds in a day) does nothing to tod and
// returns 1 to indicate an error. Otherwise returns 0 to indicate
// success. This function DOES NOT modify any global variables

/*int set_tod_from_secs(int time_of_day, tod_t *tod){
    if(time_of_day <0 || time_of_day > 86400){
        return 1;
    }
    int hours = time_of_day/3600;
    int sec = time_of_day -(hours * 3600);
    int minute = sec/60;
    sec = sec - (minute*60);
    tod->hours = hours;
    tod->seconds = sec;
    tod->minutes = minute;
    if (tod->hours == 0){
        tod->hours = 12;
    }
    if(tod->hours > 12){ //if statement that ensures times greater then noon stays within bounds
        tod->hours = tod->hours -12;
    }
    if (time_of_day >= 43200){
        tod->ispm = 1; // time is pm
    } else{
        tod->ispm = 0; //time is am
    }
    return 0;

} */

// Function: set_display_bits_from_tod takes a tod and alters the bits in the int pointed at by display
// to reflect how the clock should appear. If any fields of tod are
// negative or too large (e.g. bigger than 12 for hours, bigger than
// 59 for min/sec), no change is made to display and 1 is returned to
// indicate an error. Otherwise returns 0 to indicate success. This
// function DOES NOT modify any global variables

/*
int set_display_bits_from_tod(tod_t tod, int *display){
    if(tod.hours > 12 || tod.seconds > 59 || tod.minutes >59 || tod.hours <0 || tod.seconds<0 || tod.minutes < 0){
        return 1;
    }
    int arr[] = {0b0111111,0b0000110, 0b1011011, 0b1001111, 0b1100110,
     0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111}; //array of bits from digits
    int score = tod.minutes;
    int min_ones = score%10; //calculates 1s position of displays minutes
    score /=10;
    int min_tens = score%10; //calculates 10s position of displays minutes
    int score2 = tod.hours;
    int hr_ones = score2%10; //calculates 1s position of displays hours
    score2 /= 10;
    int hr_tens = score2%10; //calculates 10s position of displays hours
    int state = 0b0000000;
    state = (arr[min_ones]) | state; // bitwise or operation to set state
    state = (arr[min_tens] << 7) | state; // shifts the array value's bits by 7 and uses bitwise or to set state
    state = (arr[hr_ones] << 14) | state;// shifts the array value's bits by 14 and uses bitwise or to set state
    if(tod.hours > 9){ //if and else statement to check check to add leading 0 in display
        state = (arr[hr_tens] << 21) | state; //shifts the array value's bits by 21 and uses bitwise or to set state
    } else{
        state = (0b0000000 <<21) | state;
    }
    if(tod.ispm == 1){ //i f and else statement to set am or pm for display
        state = (1 << 29) | state;
    } else{
        state = (1 << 28) | state;
    }
    *display = (state);
    return 0;
}
*/

// function clock_update: Examines the TIME_OF_DAY_SEC global variable to determine hour,
// minute, and am/pm.  Sets the global variable CLOCK_DISPLAY_PORT bits
// to show the proper time.  If TIME_OF_DAY_SEC appears to be in error
// (to large/small) makes no change to CLOCK_DISPLAY_PORT and returns 1
// to indicate an error. Otherwise returns 0 to indicate success.
//
/*
int clock_update(){
    tod_t t;
    int success = set_tod_from_secs(TIME_OF_DAY_SEC, &t); // checks for success of function. Will return 1 if out of range.
    if(success == 1){
        return 1;
    } else{
        set_display_bits_from_tod(t, &CLOCK_DISPLAY_PORT);
        return 0;
    }
}
*/
