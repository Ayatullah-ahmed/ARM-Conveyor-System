set(INCLUDE_LIST ${INCLUDE_LIST}
        ${PROJECT_PATH}/STM32-base/startup
        ${PROJECT_PATH}/STM32-base-STM32Cube/CMSIS/ARM/inc
        ${PROJECT_PATH}/STM32-base-STM32Cube/CMSIS/${SERIES_FOLDER}/inc
        ${PROJECT_PATH}/include
        ${PROJECT_PATH}/Lib
        ${PROJECT_PATH}/RCC
        ${PROJECT_PATH}/Gpio
        ${PROJECT_PATH}/LCD
        ${PROJECT_PATH}/Exti
        ${PROJECT_PATH}/ADC
        ${PROJECT_PATH}/PWM
        ${PROJECT_PATH}/ObjectDetection
        ${PROJECT_PATH}/Timer

)

if (USE_HAL)
    set(INCLUDE_LIST ${INCLUDE_LIST} ${PROJECT_PATH}/STM32-base-STM32Cube/HAL/${SERIES_FOLDER}/inc)
endif ()