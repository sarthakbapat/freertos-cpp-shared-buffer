#ifndef SENSOR_H
#define SENSOR_H

#include "SharedBuffer.hpp"

// Base class for various sensors.
class SensorBase {
    public:
        virtual ~SensorBase() = default;

        void startTask(const char* name, UBaseType_t uxPriority);

        virtual void run() = 0;

    private:
        // This is a connection func between C++ application and FreeRTOS which expects C style func ptr as input.
        // Making this func static makes it independent of implicit this pointer and can be passed to task create FreeRTOS API.
        static void taskWrapper(void* params);

};

// Class for temperature sensor. Pass the SharedBuffer singleton instance here.
class TempSensor: public SensorBase {
    private:
        SharedBuffer& buffer;
    public:
        TempSensor(SharedBuffer& b) : buffer(b) {}
        void run();
};

// Class for Pressure Sensor.
class PressureSensor: public SensorBase {
    private:
        SharedBuffer& buffer;
    public:
        PressureSensor(SharedBuffer& b) : buffer(b) {}
        void run();
};

// Class for logger (Derive it from SensorBase for simplicity).
class Logger: public SensorBase {
    private:
        SharedBuffer& buffer;
    public:
        Logger(SharedBuffer& b) : buffer(b) {}
        void run();
};

// A SensorFactory class to create Sensor objects based on type. Factory design pattern technique.
class SensorFactory {
    public:
        static SensorBase* createSensor(SensorType type, SharedBuffer& buffer);
};


#endif