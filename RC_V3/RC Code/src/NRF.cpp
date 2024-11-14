#include "NRF.h"
#include "Globals.h"

// Initialize the radio and addresses
RF24 radio(49, 4); // CE, CSN
bool radioNumber = 0;

unsigned long rc_send_interval = 50;

// Initialize the data packages
RC_Control_Data_Package rc_control_data;
RC_Settings_Data_Package rc_settings_data;
Hexapod_Settings_Data_Package hex_settings_data;
Hexapod_Sensor_Data_Package hex_sensor_data;

void setupNRF() {
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setPayloadSize(32);
    radio.setChannel(124);
    radio.enableAckPayload();
    radio.setRetries(5, 5);
    radio.openWritingPipe(nrfAddress);

    rc_control_data.type = RC_CONTROL_DATA;

    rc_control_data.joy1_X = 127;
    rc_control_data.joy1_Y = 127;
    rc_control_data.joy1_Button = UNPRESSED;

    rc_control_data.joy2_X = 127;
    rc_control_data.joy2_Y = 127;
    rc_control_data.joy2_Button = UNPRESSED;

    rc_control_data.slider1 = 50;
    rc_control_data.slider2 = 50;

    rc_control_data.pushButton1 = UNPRESSED;
    rc_control_data.pushButton2 = UNPRESSED;

    rc_control_data.dynamic_stride_length = dynamicStrideLength;


    rc_settings_data.type = RC_SETTINGS_DATA;
    

    for (int i = 0; i < 18; i++) {
        rc_settings_data.offsets[i] = 0;
    }
}

void sendNRFData(PackageType type) {
    every(rc_send_interval) {
        bool report = false;

        if (type == RC_CONTROL_DATA) {
            report = radio.write(&rc_control_data, sizeof(rc_control_data)); // Send control data
        } else if (type == RC_SETTINGS_DATA) {
            report = radio.write(&rc_settings_data, sizeof(rc_settings_data)); // Send settings data
        }

        if (report) {
            if (radio.isAckPayloadAvailable()) {
                byte ackType;
                radio.read(&ackType, sizeof(ackType));

                if (ackType == HEXAPOD_SETTINGS_DATA) {
                    radio.read(&hex_settings_data, sizeof(hex_settings_data));
                    
                    for (int i = 0; i < 18; i++) {
                        hexSavedOffsets[i] = hex_settings_data.offsets[i];
                    }
                    
                } else if (ackType == HEXAPOD_SENSOR_DATA) {
                    radio.read(&hex_sensor_data, sizeof(hex_sensor_data));


                    current_sensor_value = hex_sensor_data.current_sensor_value;
                    for (int i = 0; i < 6; i++) {
                        foot_positions[i] = hex_sensor_data.foot_positions[i];
                    }
                }

                //no data is being received
                else{
                    current_sensor_value = 0;
                    for (int i = 0; i < 6; i++) {
                        foot_positions[i] = Vector2int(0,0);
                    }
                }
            }
        }
    }
}