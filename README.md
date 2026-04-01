Overview
This project is a professional color detection system based on the STM32F4 Discovery board.
It identifies surface colors using three LDR sensors equipped with Red, Green, and Blue optical filters.
The system provides both instant hardware color detection and precise digital HEX code generation.

How it Works
Hardware Stage: LM324 operational amplifiers and CD4001 NOR gates detect the dominant color instantly.
Digital Stage: The STM32 uses its 12-bit ADC to read analog voltages and calculate the exact #RRGGBB hexadecimal value.
Display: All data is sent via I2C protocol to an LCD 1602 screen for real-time monitoring.

Main Features
Real-time hexadecimal color output for precise matching.
Hardware-level indicators (LEDs) for fast color identification.
Manual calibration using on-board potentiometers for perfect white balance.
Professional-grade firmware written using the STM32 HAL library.

Hardware Components
MCU: STM32F4 Discovery (ARM Cortex-M4).
Analog: LM324 Op-Amps and CD4001 Logic Gates.
Sensors: GL55 LDRs with custom RGB filters.
Output: I2C LCD 1602 Display.
