#ifndef SENSOR_UTILITY_H
#define SENSOR_UTILITY_H

extern "C" {
    #include "FreeRTOS.h"
    #include "task.h"
    #include "semphr.h"
    #include <time.h>
    #include <stdlib.h>
}

#include <iostream>
#include <deque>

// Struct definition to hold the sensor data.
typedef struct SensorData{
    uint32_t sensorId;
    uint32_t sensorReading;
    time_t timeStamp;
}SensorData;

// Sensor types.
typedef enum SensorType {
    TEMPERATURE,
    PRESSURE,
    LOGGER
}SensorType;

uint32_t _generateRandom(uint32_t, uint32_t);

#endif