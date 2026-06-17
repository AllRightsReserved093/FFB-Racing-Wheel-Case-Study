/*
 * 文件功能：保存 Racing Wheel FFB Controller case study 的 HID report descriptor 通信定义摘录。
 * File purpose: Stores a HID report descriptor communication-definition excerpt for the Racing Wheel FFB Controller case study.
 *
 * 注意：这不是完整固件源文件。它省略了 USB stack 集成、descriptor length constants、
 * endpoint callbacks、report parser code，以及 exposed feature reports 所需的
 * GET_REPORT / SET_REPORT handlers。
 *
 * Note: This is not a complete firmware source file. It omits USB stack integration,
 * descriptor length constants, endpoint callbacks, report parser code, and the
 * GET_REPORT / SET_REPORT handlers required by the exposed feature reports.
 */

#include <stdint.h>

// Complete prototype HID report descriptor for the wheel/FFB communication subset.
// Report ID map:
//   0x01: Wheel input report
//   0x02: PID state input report
//   0x03: Set Effect output report
//   0x04: Set Envelope output report
//   0x05: Set Condition output report
//   0x06: Set Constant Force output report
//   0x07: Set Ramp Force output report
//   0x08: Effect Operation output report
//   0x09: PID Device Control output report
//   0x0A: Device Gain feature report
//   0x0B: PID Block Load feature report
//   0x0C: PID Block Free output report
//   0x0D: PID Pool feature report
//   0x0E: Create New Effect feature report
static const uint8_t wheel_ffb_hid_report_descriptor[] = {
    // --------- Application Collection ---------
    0x05, 0x01,        // Usage Page (Generic Desktop)
    0x09, 0x04,        // Usage (Joystick)
    0xA1, 0x01,        // Collection (Application)

    // --------- Report 0x01: Wheel Input ---------
    0x85, 0x01,        //   Report ID (wheel input)

    // Steering: int16_t, -32768 ~ 32767
    0x05, 0x02,        //   Usage Page (Simulation Controls)
    0x09, 0xC8,        //   Usage (Steering)
    0x16, 0x00, 0x80,  //   Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,  //   Logical Maximum (32767)
    0x75, 0x10,        //   Report Size (16)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x02,        //   Input (Data, Variable, Absolute)

    // Accelerator: uint8_t, 0 ~ 255
    0x09, 0xC4,        //   Usage (Accelerator)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x75, 0x08,        //   Report Size (8)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x02,        //   Input (Data, Variable, Absolute)

    // Brake: uint8_t, 0 ~ 255
    0x09, 0xC5,        //   Usage (Brake)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x75, 0x08,        //   Report Size (8)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x02,        //   Input (Data, Variable, Absolute)

    // Buttons: 8 buttons, 1 byte
    0x05, 0x09,        //   Usage Page (Button)
    0x19, 0x01,        //   Usage Minimum (Button 1)
    0x29, 0x08,        //   Usage Maximum (Button 8)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x08,        //   Report Count (8)
    0x81, 0x02,        //   Input (Data, Variable, Absolute)

    // --------- PID Usage Page ---------
    0x05, 0x0F,        //   Usage Page (Physical Interface Device / PID)

    // --------- Report 0x02: PID State ---------
    0x09, 0x92,        //   Usage (PID State Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x02,        //     Report ID (PID state)

    // Effect Block Index: 7 bits
    0x09, 0x22,        //     Usage (Effect Block Index)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x07,        //     Report Size (7)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data, Variable, Absolute)

    // ROM Flag: 1 bit
    0x09, 0x24,        //     Usage (ROM Flag)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data, Variable, Absolute)

    // 4 status bits
    0x09, 0x94,        //     Usage (Effect Playing)
    0x09, 0xA0,        //     Usage (Actuators Enabled)
    0x09, 0xA4,        //     Usage (Safety Switch)
    0x09, 0xA6,        //     Usage (Actuator Power)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x04,        //     Report Count (4)
    0x81, 0x02,        //     Input (Data, Variable, Absolute)

    // 4 bits padding
    0x75, 0x04,        //     Report Size (4)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x03,        //     Input (Constant, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x03: Set Effect ---------
    0x09, 0x21,        //   Usage (Set Effect Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x03,        //     Report ID (set effect)

    // Effect Block Index: 7 bits
    0x09, 0x22,        //     Usage (Effect Block Index)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x07,        //     Report Size (7)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    // ROM Flag: 1 bit
    0x09, 0x24,        //     Usage (ROM Flag)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x25,        //     Usage (Effect Type)
    0xA1, 0x02,        //     Collection (Logical)
    0x09, 0x26,        //       Usage (ET Constant Force)
    0x09, 0x27,        //       Usage (ET Ramp)
    0x09, 0x40,        //       Usage (ET Spring)
    0x09, 0x41,        //       Usage (ET Damper)
    0x09, 0x42,        //       Usage (ET Inertia)
    0x15, 0x01,        //       Logical Minimum (1)
    0x25, 0x05,        //       Logical Maximum (5)
    0x75, 0x08,        //       Report Size (8)
    0x95, 0x01,        //       Report Count (1)
    0x91, 0x00,        //       Output (Data, Array, Absolute)
    0xC0,              //     End Collection

    0x09, 0x50,        //     Usage (Duration)
    0x09, 0x51,        //     Usage (Sample Period)
    0x09, 0x54,        //     Usage (Trigger Repeat Interval)
    0x09, 0xA7,        //     Usage (Start Delay)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x04,        //     Report Count (4)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x52,        //     Usage (Gain)
    0x09, 0x53,        //     Usage (Trigger Button)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x02,        //     Report Count (2)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x55,        //     Usage (Axes Enable)
    0x09, 0x56,        //     Usage (Direction Enable)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x02,        //     Report Count (2)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)
    0x75, 0x06,        //     Report Size (6)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x03,        //     Output (Constant, Variable, Absolute)

    0x09, 0x57,        //     Usage (Direction)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0x9F, 0x8C,  //     Logical Maximum (35999)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x04: Set Envelope ---------
    0x09, 0x5A,        //   Usage (Set Envelope Report)
    0xA1, 0x02,        //     Collection (Logical)
    0x85, 0x04,        //       Report ID (set envelope)

    0x09, 0x22,        //       Usage (Effect Block Index)
    0x15, 0x01,        //       Logical Minimum (1)
    0x25, 0x7F,        //       Logical Maximum (127)
    0x75, 0x08,        //       Report Size (8)
    0x95, 0x01,        //       Report Count (1)
    0x91, 0x02,        //       Output (Data, Variable, Absolute)

    0x09, 0x5B,        //       Usage (Attack Level)
    0x09, 0x5C,        //       Usage (Attack Time)
    0x09, 0x5D,        //       Usage (Fade Level)
    0x09, 0x5E,        //       Usage (Fade Time)
    0x15, 0x00,        //       Logical Minimum (0)
    0x26, 0xFF, 0x7F,  //       Logical Maximum (32767)
    0x75, 0x10,        //       Report Size (16)
    0x95, 0x04,        //       Report Count (4)
    0x91, 0x02,        //       Output (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x05: Set Condition ---------
    0x09, 0x5F,        //   Usage (Set Condition Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x05,        //     Report ID (set condition)

    0x09, 0x22,        //     Usage (Effect Block Index)
    0x15, 0x01,        //     Logical Minimum (1)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x23,        //     Usage (Parameter Block Offset)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x60,        //     Usage (CP Offset)
    0x09, 0x61,        //     Usage (Positive Coefficient)
    0x09, 0x62,        //     Usage (Negative Coefficient)
    0x16, 0x00, 0x80,  //     Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x03,        //     Report Count (3)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x63,        //     Usage (Positive Saturation)
    0x09, 0x64,        //     Usage (Negative Saturation)
    0x09, 0x65,        //     Usage (Dead Band)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x03,        //     Report Count (3)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x06: Set Constant Force ---------
    0x09, 0x73,        //   Usage (Set Constant Force Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x06,        //     Report ID (set constant force)

    0x09, 0x22,        //     Usage (Effect Block Index)
    0x15, 0x01,        //     Logical Minimum (1)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x70,        //     Usage (Magnitude)
    0x16, 0x00, 0x80,  //     Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x07: Set Ramp Force ---------
    0x09, 0x74,        //   Usage (Set Ramp Force Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x07,        //     Report ID (set ramp force)

    0x09, 0x22,        //     Usage (Effect Block Index)
    0x15, 0x01,        //     Logical Minimum (1)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x75,        //     Usage (Ramp Start)
    0x09, 0x76,        //     Usage (Ramp End)
    0x16, 0x00, 0x80,  //     Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x02,        //     Report Count (2)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x08: Effect Operation ---------
    0x09, 0x77,        //   Usage (Effect Operation Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x08,        //     Report ID (effect operation)

    0x09, 0x22,        //     Usage (Effect Block Index)
    0x15, 0x01,        //     Logical Minimum (1)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)

    0x09, 0x78,        //     Usage (Effect Operation)
    0xA1, 0x02,        //     Collection (Logical)
    0x09, 0x79,        //       Usage (Op Effect Start)
    0x09, 0x7A,        //       Usage (Op Effect Start Solo)
    0x09, 0x7B,        //       Usage (Op Effect Stop)
    0x15, 0x01,        //       Logical Minimum (1)
    0x25, 0x03,        //       Logical Maximum (3)
    0x75, 0x08,        //       Report Size (8)
    0x95, 0x01,        //       Report Count (1)
    0x91, 0x00,        //       Output (Data, Array, Absolute)
    0xC0,              //     End Collection

    0x09, 0x7C,        //     Usage (Loop Count)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x09: PID Device Control ---------
    0x09, 0x95,        //   Usage (PID Device Control Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x09,        //     Report ID (device control)
    0x09, 0x96,        //     Usage (PID Device Control)
    0xA1, 0x02,        //     Collection (Logical)
    0x09, 0x97,        //       Usage (DC Enable Actuators)
    0x09, 0x98,        //       Usage (DC Disable Actuators)
    0x09, 0x99,        //       Usage (DC Stop All Effects)
    0x09, 0x9A,        //       Usage (DC Device Reset)
    0x09, 0x9B,        //       Usage (DC Device Pause)
    0x09, 0x9C,        //       Usage (DC Device Continue)
    0x15, 0x01,        //       Logical Minimum (1)
    0x25, 0x06,        //       Logical Maximum (6)
    0x75, 0x08,        //       Report Size (8)
    0x95, 0x01,        //       Report Count (1)
    0x91, 0x00,        //       Output (Data, Array, Absolute)
    0xC0,              //     End Collection
    0xC0,              //   End Collection

    // --------- Report 0x0A: Device Gain ---------
    0x09, 0x7D,        //   Usage (Device Gain Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x0A,        //     Report ID (device gain)
    0x09, 0x7E,        //     Usage (Device Gain)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0xB1, 0x02,        //     Feature (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x0E: Create New Effect ---------
    0x09, 0xAB,        //   Usage (Create New Effect Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x0E,        //     Report ID (create new effect)

    0x09, 0x25,        //     Usage (Effect Type)
    0xA1, 0x02,        //     Collection (Logical)
    0x09, 0x26,        //       Usage (ET Constant Force)
    0x09, 0x27,        //       Usage (ET Ramp)
    0x09, 0x40,        //       Usage (ET Spring)
    0x09, 0x41,        //       Usage (ET Damper)
    0x09, 0x42,        //       Usage (ET Inertia)
    0x15, 0x01,        //       Logical Minimum (1)
    0x25, 0x05,        //       Logical Maximum (5)
    0x75, 0x08,        //       Report Size (8)
    0x95, 0x01,        //       Report Count (1)
    0xB1, 0x00,        //       Feature (Data, Array, Absolute)
    0xC0,              //     End Collection

    0x05, 0x01,        //     Usage Page (Generic Desktop)
    0x09, 0x3B,        //     Usage (Byte Count)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0xB1, 0x02,        //     Feature (Data, Variable, Absolute)
    0xC0,              //   End Collection

    0x05, 0x0F,        //   Usage Page (Physical Interface Device / PID)

    // --------- Report 0x0B: PID Block Load ---------
    0x09, 0x89,        //   Usage (PID Block Load Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x0B,        //     Report ID (block load)

    0x09, 0x22,        //     Usage (Effect Block Index)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0xB1, 0x02,        //     Feature (Data, Variable, Absolute)

    0x09, 0x8B,        //     Usage (Block Load Status)
    0xA1, 0x02,        //     Collection (Logical)
    0x09, 0x8C,        //       Usage (Block Load Success)
    0x09, 0x8D,        //       Usage (Block Load Full)
    0x09, 0x8E,        //       Usage (Block Load Error)
    0x15, 0x01,        //       Logical Minimum (1)
    0x25, 0x03,        //       Logical Maximum (3)
    0x75, 0x08,        //       Report Size (8)
    0x95, 0x01,        //       Report Count (1)
    0xB1, 0x00,        //       Feature (Data, Array, Absolute)
    0xC0,              //     End Collection

    0x09, 0xAC,        //     Usage (RAM Pool Available)
    0x15, 0x00,        //     Logical Minimum (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,
                       //     Logical Maximum (65535)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0xB1, 0x02,        //     Feature (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x0C: PID Block Free ---------
    0x09, 0x90,        //   Usage (PID Block Free Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x0C,        //     Report ID (block free)
    0x09, 0x8F,        //     Usage (Block Handle)
    0x15, 0x01,        //     Logical Minimum (1)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x01,        //     Report Count (1)
    0x91, 0x02,        //     Output (Data, Variable, Absolute)
    0xC0,              //   End Collection

    // --------- Report 0x0D: PID Pool ---------
    0x09, 0x7F,        //   Usage (PID Pool Report)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x0D,        //     Report ID (PID pool)

    0x09, 0x80,        //     Usage (RAM Pool Size)
    0x09, 0x81,        //     Usage (ROM Pool Size)
    0x09, 0x82,        //     Usage (ROM Effect Block Count)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x03,        //     Report Count (3)
    0xB1, 0x02,        //     Feature (Data, Variable, Absolute)

    0x09, 0x83,        //     Usage (Simultaneous Effects Max)
    0x09, 0x84,        //     Usage (Pool Alignment)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x02,        //     Report Count (2)
    0xB1, 0x02,        //     Feature (Data, Variable, Absolute)

    0x09, 0xA9,        //     Usage (Device Managed Pool)
    0x09, 0xAA,        //     Usage (Shared Parameter Blocks)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x02,        //     Report Count (2)
    0xB1, 0x02,        //     Feature (Data, Variable, Absolute)
    0x75, 0x06,        //     Report Size (6)
    0x95, 0x01,        //     Report Count (1)
    0xB1, 0x03,        //     Feature (Constant, Variable, Absolute)

    0xC0,              //   End PID Pool Collection
    0xC0               // End Application Collection
};

