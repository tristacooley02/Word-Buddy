// Functions for Battery Monitoring

int batterySensor = 34; // Battery Sensor is located to GPIO 34
float bHigh = 905.0;      // UPDATE THIS CODE -- Analog Value read at 5.0 volts
float bLow = 450.0;       // UPDATE THIS CODE -- Analog Value read at 3.0 volts
float vHigh = 5.0;      // Test volts at 5.0 volts
float vLow = 3.0;       // Test volts at 3.0 volts
float chrgMax = 4.2;  // Fully Charged Battery
float chrgMin = 3.2;  // Fully Depleted Battery
int lastChrg = 100;   // Keep Track of Last Charge
int chargeTolerance = 10;

// initBattery() declares the battery sensor as an input
void initBattery(){

 pinMode(batterySensor,INPUT);
  
}

// voltsBattery reads the battery sensor and returns the voltage of the battery
// This is accomplished reading the battery sensor and mapping its value (using the special mapFloat function) 
// that range from bHigh to bLow, to the new scale of vHigh to vLow. This mapped value is returned as a floating number
float voltsBattery(){
  
  float currentNow = analogRead(batterySensor);
  float currentVolt = mapFloat(currentVolt, bLow, bHigh, vLow, vHigh);
  return currentVolt;

  
}

// percentBattery reads the battery sensor and returns the % remaining in the battery
// This is accomplished calling the voltsBattery function and mapping its value (using the special mapFloat function) 
// that range from chargeMin to chargeMax, to the new scale of 0.0 to 100.0 (representing % charge). 
// This mapped value is returned as a floating number
float percentBattery(){

  float currentVolt = voltsBattery();
  float currentChrg = mapFloat(currentVolt, chrgMin, chrgMax, 0.0, 100.0);
  return currentChrg;

}


// updateBattery gets the current percent of charge remaining. It then compares that value to the last known % charge
// of the battery. If they have changed, it updates the last known charge as well as updates the bleKeyboard library
// using the bleKeyboard.setBatteryLevel(curCharge) function
void updateBattery(){
  
  float currentChrg = percentBattery();
    if(abs(currentChrg - lastChrg) > chargeTolerance){
      lastChrg = currentChrg;
      bleKeyboard.setBatteryLevel(currentChrg);
  }
    Serial.println(lastChrg);
  
}

// The normal Arduino float( ) function only works with integers. 
// This special function works with floating numbers for more precision
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
