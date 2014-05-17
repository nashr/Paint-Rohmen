#include "canvas.h"

#ifndef APP_H
#define APP_H

// App's global variables
extern int exit;

// Functions and procedures prototype
void app_start( void );

void app_handle_input( void );

void app_update( void );

void app_draw( void );

void app_run( void );

const int app_is_exit( void );

void app_set_exit( int val );

#endif