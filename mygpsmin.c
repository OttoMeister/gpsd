// gcc -o mygps mygps.c -lm -lgps
 
#include <gps.h>
 
int main() {
  // define gps struct
  struct gps_data_t gps_data;
  // opens the daemon socket
  gps_open(GPSD_SHARED_MEMORY,NULL,&gps_data);
  // Blocking read for data from the daemon socket
  gps_read(&gps_data);
  // prints position
  printf("latitude: %f°, longitude: %f°, ",gps_data.fix.latitude,gps_data.fix.longitude);
  // prints speed
  printf("speed: %f km/h\n",3.6 * gps_data.fix.speed);
  // Close the daemon socket and end the session.
  gps_close(&gps_data);
}
