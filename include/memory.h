#ifndef _MEMORY
#define _MEMORY

struct Memory
{
    int position;
    int size;
    int *arr;
};
void initializeMemory(struct Memory *m);
void memoryShowData(struct Memory *m);
void memoryAddReading(struct Memory *m, int reading);
void memorySaveMotorVariables();
void memoryRetrieveMotorVariables();
void memorySaveSensorVariables();
void memoryRetrieveSensorVariables();

#endif //_MEMORY