/**
* This program is used to work with TI - MSP430 MCU and related devices. 
*/

/**
* Defining Pins on MSP430 board where 3 axis Accelerometer is added.
*/
#define acc_x P1_3
#define acc_y P1_4
#define acc_z P1_5

/**
* Defining Ping where digitised signal from EMG sensor will be added.
*/

#define EMG P1_0

/**
* Defining number of samples required to calculate Moving average of signal from EMG sensor.
*/

#define SAMPLES 25

/**
* Defining LCD input to MCU pins.
*/

int lcd[6] = {11,12,13,14,15,18};

int accx,accy,accz,emg;

/**
* This section will run once and will be used to initialise type of PINs i.e. Input or Output mode along with
* setting the BAUD rate used for communicating with peripheral devices like LCD etc.
*/

void setup()
{
Serial.begin(115200);
pinMode(acc_x,INPUT);
pinMode(acc_y,INPUT);
pinMode(acc_z,INPUT);
pinMode(EMG,INPUT);
for(int i=0;i<6;i++)
  pinMode(lcd[i],OUTPUT);
}

/**
* This section is used to match conditioned sensor signals with a look up table fetched in an iteration.
*/
void loop()
{
    accx = analogRead(acc_x);
    accy = analogRead(acc_y);
    accz = analogRead(acc_z);
    char ch;
    if(z>=310 && z<=330 && x<300)//set1
    ch = '1';
  else if(x>=330 && x<=345 && y>400)//set2
    ch = '2';
  else if(z>=380 && z<=400 && x<300)//set3
    ch = '3';
  else if(y>=340 && y<=350 && z<300)//set4
    ch = '4';
  else if(x>=355 && x<=365 && y>400)//set5
    ch = '5';
  else if(x>=320 &&x<=340 && y<300)//set6
    ch = '6';
  else if(y>=350 &&y<=365 && x<300)//set7
    ch = '7';
    switch(ch)
    {
      case '1':
	       emg = moving_avg();
               set1(emg);
               lcd.setCursor(0,1);
               //lcd.print("Stop");
              break;
      case '2':emg = moving_avg();
               set2(emg);
               lcd.setCursor(0,1);
               //lcd.print("Yes");
              break;
      case '3':emg = moving_avg();
               set3(emg);
                lcd.setCursor(0,1);
               //lcd.print("Read");
              break;
      case '4':emg = moving_avg();
               set4(emg);
                lcd.setCursor(0,1);
               //lcd.print("Write");
              break;
      case'5':emg = moving_avg();
               set5(emg);
              lcd.setCursor(0,1);
               //lcd.print("Me");
              break;
      case '6':emg = moving_avg();
               set6(emg);
              lcd.setCursor(0,1);
              // lcd.print("No");
              break;
      case '7':emg = moving_avg();
               set7(emg);
                lcd.setCursor(0,1);
               //lcd.print("Drink");
              break;
      default: Serial.println("ELECTRONICS VOICE");
                //lcd.setCursor(0,0);
               //lcd.print("Electronic Voice");
  }
delay(10);
}

/**
* This section calculates moving average of EMG sensor.
*/
int moving_avg()
{
  for(int i = 0; i < SAMPLES; i++)
  {
  reading[i] = analogRead(EMG) ;//* multiplier;
  delay(2);
  }
  for(int i = 0; i < SAMPLES; i++)
  {
    finalReading += reading[i];
  }
  finalReading = finalReading/SAMPLES;
  return finalReading;
}
