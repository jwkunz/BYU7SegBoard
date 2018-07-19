#ifndef max7221Driver_c
#define max7221Driver_c

/*
  max7221Driver.h - Communicates with the MAX7721

  Created by Jakob Kunzler 07/04/2018
*/

#include "max7221Driver.h"

// ADDRESS CODES:
#define MX_ADDR_NO_OPT 0x0

#define MX_ADDR_INTENSITY 0x0A
#define MX_MAX_BRIGHT 15
#define MX_MIN_BRIGHT 1

#define MX_ADDR_SHUTDOWN 0x0C
#define MX_DATA_OFF 0x00
#define MX_DATA_ON 0x01

#define MX_ADDR_DISPTEST 0x0F
#define MX_DATA_DISPTEST_NORMAL 0x00
#define MX_DATA_DISPTEST_MODE 0x01

#define MX_ADDR_DECODE_MODE 0x09
#define MX_DATA_NO_DECODE 0x00
#define MX_DATA_CODEB_FLAG_DG0 0x01
#define MX_DATA_CODEB_FLAG_DG3_DG0 0x0F
#define MX_DATA_CODEB_FLAG_DG7_DG0 0xFF

#define MX_DATA_CODEB_CHAR_0 0x00
#define MX_DATA_CODEB_CHAR_1 0x01
#define MX_DATA_CODEB_CHAR_2 0x02
#define MX_DATA_CODEB_CHAR_3 0x03
#define MX_DATA_CODEB_CHAR_4 0x04
#define MX_DATA_CODEB_CHAR_5 0x05
#define MX_DATA_CODEB_CHAR_6 0x06
#define MX_DATA_CODEB_CHAR_7 0x07
#define MX_DATA_CODEB_CHAR_8 0x08
#define MX_DATA_CODEB_CHAR_9 0x09
#define MX_DATA_CODEB_CHAR_DASH 0x0A
#define MX_DATA_CODEB_CHAR_E 0x0B
#define MX_DATA_CODEB_CHAR_H 0x0C
#define MX_DATA_CODEB_CHAR_L 0x0D
#define MX_DATA_CODEB_CHAR_P 0x0E
#define MX_DATA_CODEB_CHAR_BLANK 0x0F

#define MX_ADDR_SCANLIM 0x0B

#define MX_MASK_DP 0x80

// Start Up
#define MX_STARTUP_LENGTH 8
const char MX_STARTUP[MX_STARTUP_LENGTH] = {'G','O','C','O','U','G','S','!'};

// Forms a data stream from an address and the data
uint16_t _MX_formCode(uint8_t address,uint8_t data)
{
  return (address<<8)|data;
}

// Returns a seven segment data code for a given char
uint8_t _MX_decodeChar(char d)
{
#define MX_CHAR_0 0x7E
#define MX_CHAR_1 0x30
#define MX_CHAR_2 0x6D
#define MX_CHAR_3 0x79
#define MX_CHAR_4 0x33
#define MX_CHAR_5 0x5B
#define MX_CHAR_6 0x5F 
#define MX_CHAR_7 0x70
#define MX_CHAR_8 0x7F
#define MX_CHAR_9 0x73
#define MX_CHAR_DASH 0x01
#define MX_CHAR_A 0x77
#define MX_CHAR_B 0x7F
#define MX_CHAR_C 0x4E
#define MX_CHAR_D 0x7E
#define MX_CHAR_E 0x4F
#define MX_CHAR_F 0x47
#define MX_CHAR_G 0x5F
#define MX_CHAR_H 0x37
#define MX_CHAR_I 0x06
#define MX_CHAR_J 0x3C
#define MX_CHAR_K 0x37
#define MX_CHAR_L 0x0E
#define MX_CHAR_M 0x54
#define MX_CHAR_N 0x76
#define MX_CHAR_O 0x7E
#define MX_CHAR_P 0x67
#define MX_CHAR_Q 0xFE
#define MX_CHAR_R 0x66
#define MX_CHAR_S 0x5B
#define MX_CHAR_T 0x07
#define MX_CHAR_U 0x3E
#define MX_CHAR_V 0X1C
#define MX_CHAR_W 0x2A
#define MX_CHAR_X 0x37
#define MX_CHAR_Y 0x3B
#define MX_CHAR_Z 0x6D
#define MX_CHAR_BLANK 0x00
#define MX_CHAR_EXCLAMATION_POINT 0xA0


  
  switch(d){
    case '0':
    return MX_CHAR_0;
    break;

    case '1':
    return MX_CHAR_1;
    break;

    case '2':
    return MX_CHAR_2;
    break;
    
    case '3':
    return MX_CHAR_3;
    break;

    case '4':
    return MX_CHAR_4; 
    break;

    case '5':
    return MX_CHAR_5;
    break;

    case '6':
    return MX_CHAR_6;
    break;

    case '7':
    return MX_CHAR_7;
    break;

    case '8':
    return MX_CHAR_8;
    break;

    case '9':
    return MX_CHAR_9;
    break;

    case '-':
    return MX_CHAR_DASH;
    break;

    case 'A':
    return MX_CHAR_A;
    break;
    
    case 'B':
    return MX_CHAR_B;
    break;

    case 'C':
    return MX_CHAR_C;
    break;

    case 'D':
    return MX_CHAR_D;
    break;

    case 'E':
    return MX_CHAR_E;
    break;

    case 'F':
    return MX_CHAR_F;
    break;

    case 'G':
    return MX_CHAR_G;
    break;

    case 'H':
    return MX_CHAR_H;
    break;

    case 'I':
    return MX_CHAR_I;
    break;

    case 'J':
    return MX_CHAR_J;
    break;

    case 'K':
    return MX_CHAR_K;
    break;

    case 'L':
    return MX_CHAR_L;
    break;

    case 'M':
    return MX_CHAR_M;
    break;

    case 'N':
    return MX_CHAR_N;
    break;

    case 'O':
    return MX_CHAR_O;
    break;

    case 'P':
    return MX_CHAR_P;
    break;

    case 'Q':
    return MX_CHAR_Q;
    break;

    case 'R':
    return MX_CHAR_R;
    break;
    
    case 'S':
    return MX_CHAR_S;
    break;

    case 'T':
    return MX_CHAR_T;
    break;
    
    case 'U':
    return MX_CHAR_U;
    break;
    
    case 'V':
    return MX_CHAR_V;
    break;

    case 'W':
    return MX_CHAR_W;
    break;

    case 'X':
    return MX_CHAR_X;
    break;
    
    case 'Y':
    return MX_CHAR_Y;
    break;
    
    case 'Z':
    return MX_CHAR_Z;
    break;

    case '!':
    return MX_CHAR_EXCLAMATION_POINT;
    break;
    
    default:
    return 0x00;
    break;
  }
    
}

// Adds the decimal place to a character code
uint16_t _MX_add_Decimal(uint16_t code)
{
  return (MX_MASK_DP|code);
}


/*
 Gets the bits in data between pos_start and pos_end and places at end.
 To get 1 bit, set pos_start = pos_end.
 */
uint8_t _MX_getBits(uint16_t data,uint8_t pos_end,int8_t pos_start)
{
  // Amount to shift left
  uint8_t left = MX_DATA_LEN-1-pos_end;
  // Amount to shift right
  uint8_t right = MX_DATA_LEN-1-(pos_end-pos_start);
  // shift to exclude unwanted data
  data = data<<left;
  data = data>>right;
  
  
  return data; 
}


/*
  Sends an array uint8_t length of MX_DATA_LEN
  Each element is a 'bit' = to 1 or 0.
  D0 is the first element of the array
  Give the data in [D0,D1,...] format.
 */
void _MX_SendData(uint16_t data)
{
  //Serial.println("Starting Sending Data...");
  digitalWrite(PIN_DATA_CLK,LOW);
  digitalWrite(PIN_CS,LOW);
  for (uint8_t m = 0; m < MX_DATA_LEN; m++)
  {
    uint8_t p = MX_DATA_LEN-1-m;
    uint8_t b = _MX_getBits(data,p,p);
    //Serial.print(b);
    digitalWrite(PIN_DATA_IN,b);
    digitalWrite(PIN_DATA_CLK,HIGH);
    digitalWrite(PIN_DATA_CLK,LOW);
  }
  digitalWrite(PIN_CS,HIGH);
  //Serial.println("\nData Sent");
}



// Turns on = true, off = false 
void MX_powerSwitch(bool state)
{
  if(state)
    _MX_SendData(_MX_formCode(MX_ADDR_SHUTDOWN,MX_DATA_ON));
  else
    _MX_SendData(_MX_formCode(MX_ADDR_SHUTDOWN,MX_DATA_OFF));
}

// Sets brightness between 0 and 15
void MX_setBrightness(uint8_t brightness)
{
  uint8_t level = _MX_getBits(brightness,3,0);
  _MX_SendData(_MX_formCode(MX_ADDR_INTENSITY,level));
}

// The number of segments to enable (0-7)
void MX_setNoSegments(uint8_t numSegs)
{
  _MX_SendData(_MX_formCode(MX_ADDR_SCANLIM,numSegs));  
}

// The number of segments to enable (0-7)
void MX_noDecode()
{
  _MX_SendData(_MX_formCode(MX_ADDR_DECODE_MODE,MX_DATA_NO_DECODE));  
}

// Toggle display test
void MX_dispTest(bool on)
{
  if(on)
  _MX_SendData(_MX_formCode(MX_ADDR_DISPTEST,MX_DATA_DISPTEST_MODE));
  else
  _MX_SendData(_MX_formCode(MX_ADDR_DISPTEST,MX_DATA_DISPTEST_NORMAL));    
}

// Displays the chars in the string on the screen. Handles decimal point
void MX_disp_string(const char* text,uint8_t textLength)
{
  uint8_t digitCtr = 0;
  for (uint8_t charCtr = 0; charCtr < textLength; charCtr++)
  {
    // Get Value
    char character = text[charCtr];
    // Get Code
    uint16_t code = _MX_decodeChar(text[charCtr]);
    // Peak ahead for decimal point
    if (charCtr+1 < textLength)
    {
      // Handle Decimal Point
      if (text[charCtr+1]=='.')
      {
        // Add decimal
        code = _MX_add_Decimal(code);
        // Skip to next
        charCtr++;
      }
    }    
    // Send
    _MX_SendData(_MX_formCode(digitCtr+1,code));
    digitCtr++;
  }
  while (digitCtr<8)
  {
    _MX_SendData(_MX_formCode(digitCtr+1,_MX_decodeChar(' ')));
    digitCtr++;
  }
}

void MX_writeBLANK()
{
  char blank[8] = {' ',' ',' ',' ',' ',' ',' ',' ',};
  MX_disp_string(blank,8);
}

// Init Settings
void MX_init()
{
  Serial.println("Initing MX...");

  // INIT PINS
  pinMode(PIN_DATA_IN,OUTPUT);
  pinMode(PIN_DATA_CLK,OUTPUT);
  pinMode(PIN_CS,OUTPUT);

  // INIT DEVICE

  Serial.println("NO DECODE");
  MX_noDecode();

  Serial.println("NO SEGS");
  MX_setNoSegments(MX_NO_SEGS-1);

  Serial.println("BRIGHTNESS");
  MX_setBrightness(MX_MIN_BRIGHT);

  Serial.println("START STRING");
  MX_disp_string(MX_STARTUP,MX_STARTUP_LENGTH);

  Serial.println("DISP TEST OFF");
  MX_dispTest(false);

  Serial.println("INIT POWER");
  MX_powerSwitch(true);
  

  
  Serial.println("MX inited");
}

#endif
