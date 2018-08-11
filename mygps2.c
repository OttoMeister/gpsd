// gcc -o mygps mygps.c -lm -lgps
 
#include <gps.h>
#include <unistd.h>
#include <time.h>
 
int main() {
  // define time struct
  time_t aclock;
  // define gps struct
  struct gps_data_t gps_data;
  // opens the daemon socket
  gps_open(GPSD_SHARED_MEMORY,NULL,&gps_data);
  // loop
  while(1) {
    // Blocking read for data from the daemon socket
    gps_read(&gps_data);
    // prints position
    printf("latitude: %f°, longitude: %f°, ",gps_data.fix.latitude,gps_data.fix.longitude);
    // prints speed
    printf("speed: %f km/h, ",3.6 * gps_data.fix.speed);
    // print local gpstime
    aclock = gps_data.fix.time; printf("time: %s",ctime(&aclock));
 
    // wait 1 sec
    sleep(1);
  }
  // Close the daemon socket and end the session.
  gps_close(&gps_data);
}
