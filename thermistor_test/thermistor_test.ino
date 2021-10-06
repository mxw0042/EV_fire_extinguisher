//Thermometer with thermistor

/*thermistor parameters:
 * RT0: 10 000 Ω
 * B: 3977 K +- 0.75%
 * T0:  25 C
 * +- 5%
 */

//These values are in the datasheet
#define RT0 10000   // Ω
#define B 3977      // K
#define THRESHOLD 25
      
//--------------------------------------


#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ

//Variables
float RT, VR, ln, TX, T0, VRT;
int myLEDs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 22, 24, 26, 28};
int myPins[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};

void setup() {
  Serial.begin(9600);
  for (int i=0; i<(sizeof(myLEDs)/sizeof(int)); i++){
    pinMode(myLEDs[i], OUTPUT); 
  }
  T0 = 25 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin
}

void loop() {
  for (int i=0; i<(sizeof(myPins)/sizeof(int)); i++){
      readTemp(myPins[i], myLEDs[i]);
    
//      Serial.print("Temperature ");
//      Serial.print(i);
//      Serial.print(" :");
//      Serial.print("\t");
//      Serial.print(TX);
//      Serial.print("C\t\t");
//      Serial.print(TX + 273.15);        //Conversion to Kelvin
//      Serial.print("K\t\t");
//      Serial.print((TX * 1.8) + 32);    //Conversion to Fahrenheit
//      Serial.println("F");
      
  }
  Serial.println();
}

void readTemp(int pin, int LED){
  VRT = analogRead(pin);              //Acquisition analog value of VRT
  VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT
  
  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor
    
  TX = TX - 273.15;                 //Conversion to Celsius
    
  if (TX>THRESHOLD){
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }

  Serial.print("\t");
  Serial.print(TX);
  Serial.print("C\t");
  delay(50);
}
