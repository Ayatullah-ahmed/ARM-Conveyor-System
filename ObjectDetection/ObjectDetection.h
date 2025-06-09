#ifndef OBJECTDETECTION_H
#define OBJECTDETECTION_H

#include "Std_Types.h"

#define IR_SENSOR_PIN 1         /* PC1 - IR sensor simulation (push button) */

// Function prototypes
void ObjectDetection_Init(void);
void ObjectDetection_Process(void);
uint32 ObjectDetection_GetCount(void);
void ObjectDetection_Reset(void);

#endif /* OBJECTDETECTION_H */
