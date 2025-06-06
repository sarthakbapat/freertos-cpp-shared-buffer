#ifndef SHARED_BUFFER_H
#define SHARED_BUFFER_H

#include "SensorUtility.hpp"

class SharedBuffer {
    private:
        std::deque<SensorData> sensorDataSharedBuffer;
        SemaphoreHandle_t xMutex;

        SharedBuffer();
        ~SharedBuffer();

    public:
        // Delete the copy constructor to keep it Singleton.
        SharedBuffer(const SharedBuffer&) = delete;
        // Delete the copy assignment operator.
        SharedBuffer& operator=(const SharedBuffer&) = delete;
        // Method to get a single instance.
        static SharedBuffer& getInstance();
        // write data to the shared buffer.
        void write_to_sharedBuffer(SensorData);
        // Read from the sharedBuffer.
        SensorData read_from_sharedBuffer();

};

#endif