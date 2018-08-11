// gcc -o mygps mygps.c -lm -lgps
#include <gps.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

char gps_text[1000];

void get_gps_text(){
  time_t aclock;
  struct gps_data_t gps_data;
  // opens the daemon socket
  if (gps_open(GPSD_SHARED_MEMORY, NULL, &gps_data) != 0) {
    (void)sprintf(gps_text, "gpsd: no gpsd running or network error: %d, %s\n",
                  errno, gps_errstr(errno));
  } else {
    // Blocking read for gps data from the daemon socket
    gps_read(&gps_data);
    // Start collecting text
    sprintf(gps_text, "GPS data - ");
    // fix cps conditions
    switch (gps_data.fix.mode) {
      case MODE_3D:
        sprintf(gps_text, "%s3d-fix", gps_text);
        break;
      case MODE_2D:
        sprintf(gps_text, "%s2d-fix", gps_text);
        break;
      case MODE_NO_FIX:
        sprintf(gps_text, "%sno-fix", gps_text);
        break;
      default:
        sprintf(gps_text, "%sempty-fix", gps_text);
        break;
    }
    // gps position
    sprintf(gps_text, "%s, lat: %f°", gps_text, gps_data.fix.latitude);
    sprintf(gps_text, "%s%c, ", gps_text,
            (gps_data.fix.latitude < 0) ? 'S' : 'N');
    sprintf(gps_text, "%slon: %f°", gps_text, gps_data.fix.longitude);
    sprintf(gps_text, "%s%c, ", gps_text,
            (gps_data.fix.longitude < 0) ? 'W' : 'E');
    // gps speed
    sprintf(gps_text, "%sspeed: %.2f km/h, ", gps_text,
            3.6 * gps_data.fix.speed);
    // local gps time
    aclock = gps_data.fix.time;
    sprintf(gps_text, "%stime: %s", gps_text, ctime(&aclock));
  }
  gps_close(&gps_data);
}

int main(void) {
get_gps_text();
printf("%s\n",gps_text);
}