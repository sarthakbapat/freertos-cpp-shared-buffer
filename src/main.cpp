#include "SharedBuffer.hpp"
#include "Sensor.hpp"

int main()
{
    SharedBuffer& buffer = SharedBuffer::getInstance();

    SensorBase* tempTask = SensorFactory::createSensor(TEMPERATURE, buffer);
    SensorBase* pressTask = SensorFactory::createSensor(PRESSURE, buffer);
    SensorBase* loggerTask = SensorFactory::createSensor(LOGGER, buffer);

    tempTask->startTask("Temp-Task", 2);
    pressTask->startTask("Press-Task", 2);
    loggerTask->startTask("Logger-Task", 1);

    vTaskStartScheduler();
    for (;;); // Should never reach here
    return 0;
}