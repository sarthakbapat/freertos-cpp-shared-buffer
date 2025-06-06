#include "SharedBuffer.hpp"

SharedBuffer::SharedBuffer()
{
    // Create a FreeRTOS mutex object on construction.
    xMutex = xSemaphoreCreateMutex();
    std::cout << "SharedBuffer instance initialized\n";
}

SharedBuffer::~SharedBuffer()
{
    // Delete the mutex object during destruction.
    vSemaphoreDelete(xMutex);
    std::cout << "SharedBuffer instance destroyed\n";
}

SharedBuffer& SharedBuffer::getInstance()
{
    static SharedBuffer instance;
    return instance;
}

void SharedBuffer::write_to_sharedBuffer(SensorData data)
{
    if( xMutex != NULL )
    {
        /* See if we can obtain the semaphore. If the semaphore is not
           available wait 10 ticks to see if it becomes free. */
        if( xSemaphoreTake( xMutex, ( TickType_t ) 10 ) == pdTRUE )
        {
            /* We were able to obtain the semaphore and can now access the
               shared resource. */

               sensorDataSharedBuffer.push_back(data);
               std::cout << "SharedBuffer Size: " << sensorDataSharedBuffer.size() << std::endl;

            /* We have finished accessing the shared resource. Release the
               semaphore. */
            xSemaphoreGive( xMutex );
        }
        else
        {
            /* We could not obtain the semaphore and can therefore not access
               the shared resource safely. */
            std::cout << "Failed to acquire the mutex and thus could not write data to SharedBuffer\n";
        }
    }
}

SensorData SharedBuffer::read_from_sharedBuffer()
{
    SensorData data;

    data =  sensorDataSharedBuffer.front();
    sensorDataSharedBuffer.pop_front();
    std::cout << data.sensorId << ", " << data.sensorReading << ", " << data.timeStamp << std::endl;
    std::cout << "SharedBuffer Size after reading: " << sensorDataSharedBuffer.size() << std::endl;
    return data;
}