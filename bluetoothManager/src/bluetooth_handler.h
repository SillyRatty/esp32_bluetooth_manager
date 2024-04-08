#ifndef bluetooth_handler_h
#define bluetooth_handler_h

#include "BluetoothSerial.h"
#include <Arduino.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

typedef enum BT_STATES{
    STOP_STATE,
    CALIBRATE_STATE,
    START_STATE,
    SET_KP_STATE,
    SET_KI_STATE,
    SET_KD_STATE,
    SET_SPEED_STATE
} bluetooth_state_t;

class BluetoothHandler{
    public:
        void setup();
        void message_handler(String message);
        void clear_buffer();
        bluetooth_state_t state;
        
        virtual int available();
        virtual int read();
        void println(String message);
        void print(String message);

        bluetooth_state_t get_state();

    private:
        BluetoothSerial bluetooth_serial;
};

#endif