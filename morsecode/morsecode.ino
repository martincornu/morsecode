#define THRESHOLD 200
#define MESSAGE_LENGTH 7

const char MorseTree[] = {'\0','E', 'T', 'I', 'A', 'N', 'M', 'S',
                          'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H',
                          'V', 'F', 'U', 'L', 'A', 'P', 'J', 'B',
                          'X', 'C', 'Y', 'Z', 'Q', '\0','\0','5',
                          '4', '\0','3', '\0','\0','\0','2', '\0',
                          '\0','+', '\0','\0','\0','\0','1', '6',
                          '=', '/', '\0','\0','\0','(', '\0','7',
                          '\0','\0','\0','8', '\0','9', '0', '\0',
                          '\0','\0','\0','\0','\0','\0','\0','\0',
                          '\0','\0','\0','?', '_', '\0','\0','\0',
                          '\0','"', '\0','\0','.', '\0','\0','\0',
                          '\0','@', '\0','\0','\0','\0','\0','\0',
                          '-', '\0','\0','\0','\0','\0','\0','\0',
                          '\0',';', '!', '\0',')', '\0','\0','\0',
                          '\0','\0',',', '\0','\0','\0','\0',':',
                          '\0','\0','\0','\0','\0','\0','\0'
                         };

char morse_result[MESSAGE_LENGTH+1] = {0};
int cpt = 0;

int val = 0; // A Variable to Store the Light Value from the LDR
int ctrHigh = 0;
int ctrLow = 0;
int codePtr = 0;
int dotLen = 3000;
int dashLen = 6000;
int spaceLen = 10000;

void setup()
{
  Serial.begin(9600);// Start a Serial Connection
}

void loop()
{
  val = analogRead(4);
  if (val >= THRESHOLD)
  {
    ctrHigh++;
    ctrLow = 0;
    //digitalWrite(13, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  } else {
    ctrLow++;
    if ((ctrHigh >= dotLen) && (ctrHigh < dashLen)) {
      Serial.print(".");
      codePtr = (2*codePtr) + 1;
      morse_result[cpt]='.';
      cpt++;
      Serial.print(" Morse result: ");
      Serial.println(morse_result);
    } else if (ctrHigh >= dashLen) {
      Serial.print("-");
      codePtr = (2*codePtr) + 2;
      morse_result[cpt]='-';
      cpt++;
      Serial.print(" Morse result: ");
      Serial.println(morse_result);
    } else {
        if(ctrLow == spaceLen){
          Serial.print(MorseTree[codePtr]);
          codePtr = 0;
          if(strcmp(morse_result, "--..-.-") == 0) {
            digitalWrite(13, HIGH);
            Serial.println("Good result !! OPEN THE DOOR");
            cpt=0;
            raz(morse_result);
            Serial.println("Remise à zero");
         }
        if (cpt >= MESSAGE_LENGTH) {
          digitalWrite(12, HIGH);
          cpt=0;
          raz(morse_result);
          Serial.println("Remise à zero");
        }
      }
    }
  ctrHigh = 0;
  //digitalWrite(13, LOW);
  }
}

void raz(char * morse) {
  for (int i=0; i<MESSAGE_LENGTH-1; i++) {
    morse[i]='\0';  
  }
}

