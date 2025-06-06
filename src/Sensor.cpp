#include "Sensor.hpp"


void SensorBase::startTask(const char* name, UBaseType_t uxPriority)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                    taskWrapper,                /* Function that implements the task. */
                    name,                       /* Text name for the task. */
                    configMINIMAL_STACK_SIZE,   /* Stack size in words, not bytes. */
                    this,                       /* Pass this pointer to the taskWrapper. */
                    uxPriority,                 /* Priority at which the task is created. */
                    &xHandle );                 /* Used to pass out the created task's handle. */

    if( xReturned == pdPASS )
    {
        std::cout << "Task " << name << " created successfully\n";
    }
    else
    {
        std::cout << "Failed to create task " << name << ". Trapping now ...\n";
        while(1);   // Trap here.
    }
}

void SensorBase::taskWrapper(void* params)
{
    SensorBase* wrapper = static_cast<SensorBase*>(params);
    wrapper->run();
}

uint32_t _generateRandom(uint32_t min, uint32_t max)
{
    uint8_t random = 0;
    srand(time(0));

    random = (rand() % (max - min + 1)) + min;

    return random;
}

void TempSensor::run()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    SensorData data;
    time_t now;
    memset(&data, 0 , sizeof(SensorData));

    while (1)
    {
        data.sensorId = TEMPERATURE;
        data.sensorReading = _generateRandom(20, 50);
        now = time(NULL);
        data.timeStamp = now;

        std::cout << data.sensorId << ", " << data.sensorReading << ", " << data.timeStamp << std::endl;

        // Access the sharedbuffer and write the data. This is thread safe.
        buffer.write_to_sharedBuffer(data);

        // Call the task delay until API to make this task periodic.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

    }
}

void PressureSensor::run()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    SensorData data;
    time_t now;

    memset(&data, 0 , sizeof(SensorData));

    while (1)
    {
        data.sensorId = SensorType::PRESSURE;
        data.sensorReading = _generateRandom(0, 100);
        now = time(NULL);
        data.timeStamp = now;

        std::cout << data.sensorId << ", " << data.sensorReading << ", " << data.timeStamp << std::endl;
        // Access the sharedbuffer and write the data. This is thread safe.
        buffer.write_to_sharedBuffer(data);

        // Call the task delay until API to make this task periodic.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

    }

}

void Logger::run()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 50;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    SensorData data;

    while (1)
    {
        // Access the sharedbuffer and read the data. This is thread safe since there is only 1 task consuming.
        data = buffer.read_from_sharedBuffer();
        // Call the task delay until API to make this task periodic.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

    }
}

// SensorFactory class createSensor method to create various sensor objects.
SensorBase* SensorFactory::createSensor(SensorType type, SharedBuffer& buffer)
{
    switch (type)
    {
    case TEMPERATURE:
        return new TempSensor(buffer);
    case PRESSURE:
        return new PressureSensor(buffer);
    case LOGGER:
        return new Logger(buffer);
    }

}