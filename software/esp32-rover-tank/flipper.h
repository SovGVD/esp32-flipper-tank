#define ROIPOINTS 4

#define T1 280
#define T4 270

typedef struct {
  SFEVL53L1X sensor;
  Servo servo;
  uint8_t sensorId;
  uint8_t roiList[ROIPOINTS];
  uint8_t status[ROIPOINTS];
  uint16_t distance[ROIPOINTS];
  uint8_t roiIndex;
  int ang;
  bool inverted;
} flipper;
