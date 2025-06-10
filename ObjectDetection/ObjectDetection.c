#include "ObjectDetection.h"
#include "GPIO.h"
#include "LCD.h"

// Private variables
static volatile uint32 object_count = 0;

// Button sensor variables (PC1)
static uint8 prev_button_state = 1;  // Assume HIGH initially (no object)

// IR Module sensor variables (PC7)
static uint8 prev_module_state = 1;  // Assume HIGH initially (no object)

// Private function prototypes
static uint8 ReadButtonSensor(void);
static uint8 ReadModuleSensor(void);
static void UpdateObjectCountOnLCD(void);

void ObjectDetection_Init(void) {
    // Initialize IR sensor pin (simulated by push button) - PC1
    Gpio_Init(GPIO_C, IR_SENSOR_PIN, GPIO_INPUT, GPIO_PULL_UP);
    
    // Initialize IR sensor module - PC7 (no pull-up needed as module has internal pull-up)
    Gpio_Init(GPIO_C, IR_MODULE_PIN, GPIO_INPUT, GPIO_NO_PULL);
    
    // Initialize previous states
    prev_button_state = ReadButtonSensor();
    prev_module_state = ReadModuleSensor();
    
    // Initialize object count to 0
    object_count = 0;
}

void ObjectDetection_Process(void) {
    uint8 current_button_state = ReadButtonSensor();
    uint8 current_module_state = ReadModuleSensor();
    
    // Detect falling edge for button sensor (HIGH → LOW transition)
    if (prev_button_state == 1 && current_button_state == 0) {
        object_count++;
    }
    
    // Detect falling edge for IR module sensor (HIGH → LOW transition)
    if (prev_module_state == 1 && current_module_state == 0) {
        object_count++;
    }
    
    // Update previous states for next iteration
    prev_button_state = current_button_state;
    prev_module_state = current_module_state;
}

uint32 ObjectDetection_GetCount(void) {
    return object_count;
}

void ObjectDetection_Reset(void) {
    object_count = 0;
    UpdateObjectCountOnLCD();
}

static uint8 ReadButtonSensor(void) {
    return Gpio_ReadPin(GPIO_C, IR_SENSOR_PIN);
}

static uint8 ReadModuleSensor(void) {
    return Gpio_ReadPin(GPIO_C, IR_MODULE_PIN);
}

static void UpdateObjectCountOnLCD(void) {
    // Function kept for compatibility but LCD updates handled by main
    // This prevents LCD access conflicts between modules
}
