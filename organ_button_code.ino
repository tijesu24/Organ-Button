#include <string.h> //For the copy function

#define BUTTONS_PER_MUX 12

// Define pins for the Mux'es 
int pin_Out_S0 = 1;
int pin_Out_S1 = 2;
int pin_Out_S2 = 3;
int pin_Out_S3 = 4;
int pin_In_Mux1 = 5;
int pin_In_Mux2 = 7;
int pin_In_Mux3 = 8;

// Map MIDI CC MIDI_CHANNELs to knobs numbered left to right.
int Mux1_cc_values[12] ={185,186,187,188,189,190,191,192,193,194,195,196};
int Mux2_cc_values[12] ={197,198,199,200,201,202,203,204,205,206,207,208};
int Mux3_cc_values[12] ={209,210,211,212,213,214,215,216,217,218,219,220};
int Mux1_State[BUTTONS_PER_MUX], Mux2_State[BUTTONS_PER_MUX], Mux3_State[BUTTONS_PER_MUX]={0};
int Mux1_Old_State[BUTTONS_PER_MUX], Mux2_Old_State[BUTTONS_PER_MUX], Mux3_Old_State[BUTTONS_PER_MUX] = {0};

// Use this MIDI MIDI_CHANNEL.
#define MIDI_CHANNEL 1




void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  pinMode(pin_Out_S3, OUTPUT);
  pinMode(pin_In_Mux1, INPUT_PULLUP);
  pinMode(pin_In_Mux2, INPUT_PULLUP);
  pinMode(pin_In_Mux3, INPUT_PULLUP);

}

void loop() {
  updateMux();
  sendMIDIValues();
}

void updateMux () {
//Copy the former states to another variable
  memcpy(Mux1_Old_State, Mux1_State, sizeof Mux1_Old_State);
  memcpy(Mux2_Old_State, Mux2_State, sizeof Mux2_Old_State);
  memcpy(Mux3_Old_State, Mux3_State, sizeof Mux3_Old_State);

  //To adjust the address pins of the muxes
  for (int i = 0; i < 12; i++){
    digitalWrite(pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (i & B00000100));
    digitalWrite(pin_Out_S2, HIGH && (i & B00001000));

    delayMicroseconds(50); 

    Mux1_State[i] = digitalRead(pin_In_Mux1);
    Mux2_State[i] = digitalRead(pin_In_Mux2);
    Mux3_State[i] = digitalRead(pin_In_Mux3);

  
  }
}

void sendMIDIValues(){
  for (int i = 0; i < 12; i++){
    if(Mux1_Old_State[i] != Mux1_State[i]){
      if(Mux1_State[i] == 1){
         usbMIDI.sendControlChange(Mux1_cc_values[i], 100, MIDI_CHANNEL);
       }else if(Mux1_State[i] == 0){
         usbMIDI.sendControlChange(Mux1_cc_values[i], 0, MIDI_CHANNEL);
         }
         }

     if(Mux2_Old_State[i] != Mux2_State[i]){
      if(Mux2_State[i] == 1){
         usbMIDI.sendControlChange(Mux2_cc_values[i], 100, MIDI_CHANNEL);
       }else if(Mux2_State[i] == 0){
         usbMIDI.sendControlChange(Mux2_cc_values[i], 0, MIDI_CHANNEL);
         }
         }

      if(Mux3_Old_State[i] != Mux3_State[i]){
      if(Mux3_State[i] == 1){
         usbMIDI.sendControlChange(Mux3_cc_values[i], 100, MIDI_CHANNEL);
       }else if(Mux3_State[i] == 0){
         usbMIDI.sendControlChange(Mux3_cc_values[i], 0, MIDI_CHANNEL);
         }
         }
    }
}
