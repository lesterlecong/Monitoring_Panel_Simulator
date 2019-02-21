
float tempValue1;
float tempValue2;
float tempValue3;
bool isTemp1Reversed = false;
bool isTemp2Reversed = false;
bool isTemp3Reversed = false;

float randAccxValue;
float randAccyValue;
float randAcczValue;

int randRPM;
bool isRPMReversed = false;

int led1;
int led2;
int led3;
int led4;

char msg[50];

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
void loop() {
  
  
  getNewTemperature(tempValue1, 1.0, isTemp1Reversed);
  getNewTemperature(tempValue2, 2.0, isTemp2Reversed);
  getNewTemperature(tempValue3, 3.0, isTemp3Reversed);
  
  randAccxValue = random(0.0, 180.0);
  randAccyValue = random(0.0, 180.0);
  randAcczValue = random(0.0, 180.0);

  getNewRPM(randRPM, 1, isRPMReversed);

  led1 = random(0, 2);
  led2 = random(0, 2);
  led3 = random(0, 2);
  led4 = random(0, 2);

  
  sprintf(msg, "t,0,%s\n", String(tempValue1).c_str());
  Serial.write(msg);
  sprintf(msg, "t,1,%s\n", String(tempValue2).c_str());
  Serial.write(msg);
  sprintf(msg, "t,2,%s\n", String(tempValue3).c_str());
  Serial.write(msg);
  
  sprintf(msg, "a,0,%s\n", String(randAccxValue).c_str());
  Serial.write(msg);
  sprintf(msg, "a,1,%s\n", String(randAccyValue).c_str());
  Serial.write(msg);
  sprintf(msg, "a,2,%s\n", String(randAcczValue).c_str());
  Serial.write(msg);
                                       
  sprintf(msg, "r,0,%d\n",randRPM);
  Serial.write(msg);               

  sprintf(msg, "l,0,%d\n",led1);
  Serial.write(msg);
  sprintf(msg, "l,1,%d\n",led2);
  Serial.write(msg);
  sprintf(msg, "l,2,%d\n",led3);
  Serial.write(msg);
  sprintf(msg, "l,3,%d\n",led4);
  Serial.write(msg);
                                   
  
  //delay(100);

}
