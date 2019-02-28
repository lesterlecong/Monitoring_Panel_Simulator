
float tempValue1[10];
float tempValue2[10];
float tempValue3[10];
bool isTemp1Reversed[10] = {false};
bool isTemp2Reversed[10] = {false};
bool isTemp3Reversed[10] = {false};

float randAccxValue[10];
float randAccyValue[10];
float randAcczValue[10];

int randRPM[10];
bool isRPMReversed[10] = {false};


int shock_led[10];

int battery_level[10];

char msg[200];

char * mac_address[10] = {"00:10:FA:6E:38:4A",
                          "8E:1E:9C:63:48:55",
                          "1C:C8:5A:B7:BC:9B",
                          "4B:20:8F:3F:73:54",
                          "8C:FD:7E:BC:8F:79",
                          "57:30:54:4E:A8:A3",
                          "90:53:6A:66:63:B4",
                          "57:DD:8B:B5:73:4F",
                          "AC:9C:D2:D8:DA:51",
                          "5C:9E:13:26:FE:5B"};
                          
void setup() {
  Serial.begin(9600);

}

void getNewTemperature(float &tempHolder, float stepSize, bool &isTempReversed) {
  if(!isTempReversed){
      tempHolder = tempHolder + stepSize;
      if(tempHolder >= 100.00) {
        tempHolder = 100.00;
        isTempReversed = true;
      }
  }
  else {
    tempHolder = tempHolder - stepSize;
    if(tempHolder <= 0.00) {
      tempHolder = 0.00;
      isTempReversed = false;
    }
  }
}

void getNewRPM(int &rpmHolder, int stepSize, bool &isReversed) {
  if(!isReversed){
      rpmHolder = rpmHolder + stepSize;
      if(rpmHolder >= 300) {
        rpmHolder = 300;
        isReversed = true;
      }
  }
  else {
    rpmHolder = rpmHolder - stepSize;
    if(rpmHolder <= 0) {
      rpmHolder = 0;
      isReversed = false;
    }
  }
}

/* t - temperature
 * a - accelerometer
 * r - rpm
 */
 uint8_t count = 0;
void loop() {
  
  
  getNewTemperature(tempValue1[count], 1.0, isTemp1Reversed[count]);
  getNewTemperature(tempValue2[count], 2.0, isTemp2Reversed[count]);
  getNewTemperature(tempValue3[count], 3.0, isTemp3Reversed[count]);
  
  randAccxValue[count] = random(0.0, 180.0);
  randAccyValue[count] = random(0.0, 180.0);
  randAcczValue[count] = random(0.0, 180.0);

  getNewRPM(randRPM[count], 1, isRPMReversed[count]);


  shock_led[count] = random(0, 2);

  battery_level[count] = random(0, 100);

  memset(msg, 0, 200);
  
  sprintf(msg, "p,%d,%s,%s,%s,%s,%s,%s,%d,%d,%s,%d,%s,%d\n", count,
                                                           String(tempValue1[count]).c_str(),
                                                           String(tempValue2[count]).c_str(),
                                                           String(tempValue3[count]).c_str(),
                                                           String(randAccxValue[count]).c_str(),
                                                           String(randAccyValue[count]).c_str(),
                                                           String(randAcczValue[count]).c_str(),
                                                           randRPM[count],
                                                           shock_led[count],
                                                           mac_address[count],
                                                           battery_level[count]);
                                                           

  Serial.write(msg);
                                   
  count = (count >= 9)? 0:(count + 1);
  //delay(100);

}
