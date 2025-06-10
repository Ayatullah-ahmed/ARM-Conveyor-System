#include "ObjectDetection.h"
#include "GPIO.h"
#include "LCD.h"

// Private variables
static volatile uint32 object_count = 0;
static uint8 prev_sensor_state = 1;  // Assume HIGH initially (no object)
static uint8 debounce_counter = 0;   // Simple debounce counter

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
    
    // Simple debouncing: require stable LOW for 2 consecutive reads
    if (current_sensor_state == 0) {
        debounce_counter++;
        if (debounce_counter >= 2) {
            debounce_counter = 2; // Cap the counter
        }
    } else {
        debounce_counter = 0; // Reset counter when HIGH
    }
    
    // Detect falling edge (HIGH → LOW transition) with debouncing
    if (prev_sensor_state == 1 && debounce_counter >= 2) {
        object_count++;
        debounce_counter = 0; // Reset debounce after detection
        // LCD update removed - handled by main display function to prevent conflicts
    }
    
    // Update previous state based on debounced value
    prev_sensor_state = (debounce_counter >= 2) ? 0 : 1;
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
    // Function kept for compatibility but LCD updates handled by main
    // This prevents LCD access conflicts between modules
}
