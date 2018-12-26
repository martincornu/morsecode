#define THRESHOLD 200
#define MESSAGE_LENGTH 7
#define PIN_OUTPUT 13
#define PIN_LED_GREEN 12
#define PIN_LED_RED 11
#define MORSE_SOLUTION "--..-.-"

char morse_result[MESSAGE_LENGTH+1] = {0};  //User's result
uint8_t indice = 0;            //Indice to insert char in more_result
uint16_t val = 0;              // A Variable to Store the Light Value from the LDR
uint16_t ctrHigh = 0;          // Count time of active light
uint16_t ctrLow = 0;           // Count time of no light
uint16_t dotLenMin = 1000;     // Length of a dot between 1000 and 6000
uint16_t dashLen = 8500;       // Length of  a dash between 6000 and + inf
uint16_t spaceLen = 50000;     // Length min of "low state" before comp results

bool door_open;

void setup()
{
  Serial.begin(9600);// Start a Serial Connection
  door_open = false;
  digitalWrite(PIN_OUTPUT, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED, LOW);
  Serial.println("Let's go !");
}

void loop()
{
  if (door_open == false)         //If door not open
  {
    val = analogRead(4);          //Read LDR value
    if (val >= THRESHOLD)         //If light
    {
      ctrHigh++;                  //Then count time of active light
      ctrLow = 0;
      digitalWrite(PIN_LED_GREEN, LOW);
      digitalWrite(PIN_LED_RED, LOW);
    }
    else                          //If no light
    {
      ctrLow++;                   //Count time of no light

//      "if" used to mesure the time of "button pressed by the user"       
//      if (ctrHigh >= dotLenMin){
//        Serial.print("ctrHigh = "); Serial.println(ctrHigh);
//      }

      if ((ctrHigh >= dotLenMin) && (ctrHigh < dashLen)) {      //Check if "time of active light" match a dot
        Serial.print(".");
        morse_result[indice]='.';                                  //If yes, add the dot to the "result" string
        indice++;
        Serial.print(" Morse result: ");
        Serial.println(morse_result);
      } else if (ctrHigh >= dashLen) {                          //Check if "time of active light" match a dash
        Serial.print("-");
        morse_result[indice]='-';                               //If yes, add the dash to the "result" string
        indice++;
        Serial.print(" Morse result: ");
        Serial.println(morse_result);
      } 
      else                                                      //After the "matching" tests, we will compare
                                                                //our "result" string with the "solution" string
      {
          if(ctrLow == spaceLen)                                //If no signals since spaceLen time (~4sec)
          {
              if(strcmp(morse_result, MORSE_SOLUTION) == 0)     //Check if our result match the solution
              {
                digitalWrite(PIN_OUTPUT, LOW);
                digitalWrite(LED_BUILTIN, LOW);                 //If yes, deactivate electro magnet and set the bool door_open to true
                digitalWrite(PIN_LED_GREEN, HIGH);
                digitalWrite(PIN_LED_RED, LOW);
                door_open = true;
                Serial.println("Good result !! OPEN THE DOOR");
              }
              else                                              //If not
              {
                digitalWrite(PIN_LED_RED, HIGH);
                digitalWrite(PIN_LED_GREEN, LOW);
              }
              indice=0;                                         //Both cases, reset variables
              raz(morse_result);
              Serial.println("Remise à zero");
          }
      }
    ctrHigh = 0;
    }
  }
}

void raz(char * morse) {
  for (int i=0; i<MESSAGE_LENGTH-1; i++) {
    morse[i]='\0';  
  }
}

