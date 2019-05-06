/*
 * Headerdatei mit den Funktionen für die lokalen Sensoren 
 * (können direkt am Arduino angeschlossen werden)
 * Leonardo Braguinski, 5. PK Physik/Informatik
 */

#include "globals.h"

//*** Kalibrierung des Hall-Sensors  ****
#define HALL_M -52.695
#define HALL_N -3.1673
#ifndef UNO
#define HALL_A_REF 435
#else
#define HALL_A_REF 320
#endif
//***                                ****

#include "werkzeuge.h"

#include "temperatur.h"
#include "hallsensor.h"

#ifndef UNO
#include "h_bestimmung.h"
#include "spannungsteiler.h"
#include "kondensator.h"
#endif

#include "pendel.h"
#include "schall.h"
#include "luftdruck.h"
 
#if defined(WLAN)
#include "wetter.h"
#endif
