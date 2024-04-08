#include "bluetooth_handler.h"

extern volatile float kp, ki, kd;

void BluetoothHandler::setup(){
    bluetooth_serial.begin("ESP32test"); //Bluetooth device name
    //Serial.println("O modulo bluetooth esta pronto para conectar");
}

float new_kp, new_ki, new_kd;
void BluetoothHandler::message_handler(String message){
    bluetooth_serial.println("Message received:");
    bluetooth_serial.println(message);
    // Serial.println("Message received:");
    // Serial.println(message);

    switch(state){
        case(STOP_STATE):
            if(message == "start"){
                bluetooth_serial.println("Starting...");
                state = START_STATE;
            }

            else if(message == "set_pid"){
                bluetooth_serial.println("Input Kp: ");
                state = SET_KP_STATE;
            }

            else if(message == "calibrate"){
                bluetooth_serial.println("Calibrating...");
                state = CALIBRATE_STATE;
            }
            break;

        case(CALIBRATE_STATE):
            break;

        case(START_STATE):
            if(message == "stop"){
                bluetooth_serial.println("Stoping!");
                state = STOP_STATE;
            }
            break;

        case(SET_KP_STATE):
            kp = message.toFloat();
            bluetooth_serial.println("Input Ki: ");
            state = SET_KI_STATE;
            break;
        
        case(SET_KI_STATE):
            ki = message.toFloat();
            bluetooth_serial.println("Input Kd: ");
            state = SET_KD_STATE;
            break;
        
        case(SET_KD_STATE):
            kd = message.toFloat();
            bluetooth_serial.println("PID values:");
            bluetooth_serial.print("Kp: ");
            bluetooth_serial.println(kp);
            bluetooth_serial.print("Ki: ");
            bluetooth_serial.println(ki);
            bluetooth_serial.print("Kd: ");
            bluetooth_serial.println(kd);
            state = STOP_STATE;
            break;
        
        case(SET_SPEED_STATE):
            break;
        
        default:
            bluetooth_serial.println("Erro bluetooth handler!!");
            break;
    }
}

void BluetoothHandler::clear_buffer(){
    while(bluetooth_serial.available()) bluetooth_serial.read();
}

bluetooth_state_t BluetoothHandler::get_state(){
    return state;
}
int BluetoothHandler::available(){
    return bluetooth_serial.available();
}
int BluetoothHandler::read(){
    return bluetooth_serial.read();
}
void BluetoothHandler::println(String message){
    bluetooth_serial.println(message);
}
void BluetoothHandler::print(String message){
    bluetooth_serial.print(message);
}