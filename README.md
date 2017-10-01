# FreeRTOS Examples

This project contains examples for
[FreeRTOS](http://www.freertos.org/Documentation/RTOS_book.html)

# Build (cmake)

The CMake build is mainly taken from:
https://github.com/ryankurte/efm32-base


# Build Status (Travis)

[![Build Status](https://travis-ci.org/LukasWoodtli/FreeRtosExamples.svg?branch=master)](https://travis-ci.org/LukasWoodtli/FreeRtosExamples)


# Examples

## Chapter 1 Task Management

| Example    | Description                                           | Done |
|------------|-------------------------------------------------------|------|
| Example 1. | Creating tasks                                        |   ✓  |
| Example 2. | Using the task parameter                              |   ✓  |
| Example 3. | Experimenting with priorities                         |   ✓  |
| Example 4. | Using the Blocked state to create a delay             |   ✓  |
| Example 5. | Converting the example tasks to use vTaskDelayUntil() |   ✓  |
| Example 6. | Combining blocking and non-blocking tasks             |   ✓  |
| Example 7. | Defining an idle task hook function                   |   ✓  |
| Example 8. | Changing task priorities                              |   ✓  |
| Example 9. | Deleting tasks                                        |   ✓  |


## Chapter 2 Queue Management

| Example     | Description                                                       | Done |
|-------------|-------------------------------------------------------------------|------|
| Example 10. | Blocking when receiving from a queue                              |   ✓  |
| Example 11. | Blocking when sending to a queue or sending structures on a queue |   ✓  |


## Chapter 3 Interrupt Management

| Example     | Description                                                        | Done |
|-------------|--------------------------------------------------------------------|------|
| Example 12. | Using a binary semaphore to synchronize a task with an interrupt   |   ✓  |
| Example 13. | Using a counting semaphore to synchronize a task with an interrupt |   ✓  |
| Example 14. | Sending and receiving on a queue from within an interrupt          |   ✓  |


## Chapter 4 Resource Management

| Example     | Description                                           | Done |
|-------------|-------------------------------------------------------|------|
| Example 15. | Rewriting vPrintString() to use a semaphore           |      |
| Example 16. | Re-writing vPrintString() to use a gatekeeper task    |      |
