#include "ObjectDetection.h"
#include "GPIO.h"
#include "LCD.h"

// Private variables
static volatile uint32 object_count = 0;
static uint8 prev_sensor_state = 1;  // Assume HIGH initially (no object)

// Private function prototypes
static uint8 ReadIRSensor(void);
static void UpdateObjectCountOnLCD(void);

void ObjectDetection_Init(void) {
    // Initialize IR sensor pin (simulated by push button)
    Gpio_Init(GPIO_C, IR_SENSOR_PIN, GPIO_INPUT, GPIO_PULL_UP);
    
    // Initialize previous state
    prev_sensor_state = ReadIRSensor();
    
    // Initialize object count to 0
    object_count = 0;
}

void ObjectDetection_Process(void) {
    uint8 current_sensor_state = ReadIRSensor();
    
    // Detect falling edge (HIGH → LOW transition)
    // When button is pressed, it goes from HIGH to LOW (object detected)
    if (prev_sensor_state == 1 && current_sensor_state == 0) {
        object_count++;
        UpdateObjectCountOnLCD();
    }
    
    prev_sensor_state = current_sensor_state;
}

uint32 ObjectDetection_GetCount(void) {
    return object_count;
}

void ObjectDetection_Reset(void) {
    object_count = 0;
    UpdateObjectCountOnLCD();
}

static uint8 ReadIRSensor(void) {
    return Gpio_ReadPin(GPIO_C, IR_SENSOR_PIN);
}

static void UpdateObjectCountOnLCD(void) {
    LCD_Locate(1, 0);
    LCD_PrintText("Objects: ");
    LCD_PrintValue(object_count);
    LCD_PrintText("   "); // Clear any leftover characters
}
