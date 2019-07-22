/*
Date :- 21 - July - 2019
Sketch By:- Ahmed Nouira "ahmnouira@gmail.com"

//step 1 add the U8glib.h your librarys. this libray can be downloaded from:
//https://github.com/olikraus/u8glib
// [ put connection this on REDME.md table ] 
// this for arduino UNO but you can easly updated to mega board

*/

// connect following wires for ST7920 contoller based LCD 
/*  LCD   -->    Arduino Uno
 *  D0    :7 --> 8
 *  D1    :8 --> 9
 *  D2    :9 --> 10 
 *  D3    :10 --> 11
 *  D4    :11 --> 4 
 *  D5    :12 --> 5 
 *  D6    :13 --> 6
 *  D7    :14 --> 7
 *  En    :6 --> 18 (A4) enable serial clock  
 *  di/RS :4 --> 17 (A3) slave select 
 *  rw    :5 --> 16 (A2) serial data 
 *  VSS   :2 --> GND
 *  VDD:  :1 --> 5v
 *  BLA   :19 --> 5v (backlight anode)
 *  BLK   :20 --> GND (backlight cathode)
 *  V0    :3 --> POT (10K) for contrast 
 *  VOUT  :18 --> POT pin + GND
 *  PSB   :15 --> 5v or (GND !) serial mode select
 *  PST   :17 --> 5v
 *  NC    :16 --> not connected
 */ 

// connect following wires for KS0108 contoller based LCD
/*  LCD     -->    Arduino Uno
 *  Vss     :1 --> GND 
 *  Vcc     :2 --> 5v
 *  V0      :3 --> POT(10K) for contrast
 *  di/RS   :4 --> 17 (A3)
 *  R\W     :5 --> 16 (A2)
 *  EN      :6 --> 18 (A4)
 *  DB0     :7 --> 8
 *  DB1     :8 --> 9
 *  DB2     :9 --> 10
 *  DB3     :10 --> 11
 *  DB4     :11 --> 4
 *  DB5     :12 --> 5
 *  DB6     :13 --> 6
 *  DB7     :14 --> 7
 *  CS1     :15 --> 2
 *  CS2     :16 --> 3
 *  RST     :17 --> VCC
 *  Vout    :18 -->  POT pin + GND or POT (10K)
 *  LEDA    :19 --> 5v
 *  LEDK    :20 --> GND
 *  
 *  
 */

// connect following wires for T6963 contoller based LCD

/*  LCD     -->    Arduino Uno
 *  FGND    :1 --> GND ( Frame ground ) 
 *  Vss     :2 --> GND
 *  Vdd     :3 --> 5v Logic supply
 *  Wee/Vo  :4 --> 10 POT ( WIPER), Negative supply for LCD 
 *  WR      :5 --> 17 (A2) Data write
 *  RD      :6 --> 16 (A3) Data read
 *  CE/CS   :7 --> 18 (A4) chip enable   
 *  C/D     :8 --> 15 (A1) HIGH; command, LOW: data
 *  A       :9 --> 5v Backlight anode
 *  RESET   :10 --> Vcc Controller reset, or connect it 
 *  D0      :11 --> 8
 *  D1      :12 --> 9
 *  D2      :13 --> 10
 *  D3      :14 --> 11
 *  D4      :15 --> 4
 *  D5      :16 --> 5
 *  D6      :17 --> 6
 *  D7      :18 --> 7
 *  FS      :19 --> GND ,Font select HIGH: 6*8, LOW 8*8
 *  K       :20 --> GND ,Backlight cathode
 *  
 *  
 */

/*_________________________________________________________________
   T6963c LCD PIN   |    LCD PIN NAME  |     MEGA 2560            |
  ________________________________________________________________|
          1         |          FG      |       GND                |
          2         |         GND      |       GN                 |
          3         |         VDD      |       +5V                |
          4         |          VO      |  10K POT WIPER – LEG 2   |
          5         |          WR      |        17                |
          6         |          RD      |        18                |
          7         |       CE/CS      |        14                |
          8         |         C/D      |        15                |
          9         |         RST      |        16                |
         10         |         DB0      |         8                |
         11         |         DB1      |         9                |
         12         |         DB2      |        10                |
         13         |         DB3      |        11                |
         14         |         DB4      |         4                |
         15         |         DB5      |         5                |
         16         |         DB6      |         6                |
         17         |         DB7      |         7                |
         18         |          FS      |       GND                |
         19         |         VEE      |    10K POT–LEG1          |
         20         |       LED A      |    +3.3V – 5V            |
  ________________________________________________________________|
*/



#include "U8glib.h"

// connect pot at A0 for testing 
#define myPot  A0
int sample[128];

// for ST920 based LCD 
//U8GLIB_ST7920_128X64_4X(d0, d1, d2, d3, d4, d5, d6, d7, en, di, rw)
U8GLIB_ST7920_128X64_4X  u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);

// for KS0108 based LCD (d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw)
//U8GLIB_KS0108_128 u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 2, 3, 17, 16 )

// for T6963 128X64 driver U8GLIB_T6963_128X128(d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd [, reset])
// a0 == C/D
//U8GLIB_T6963_128X128 u8g(8, 9, 10, 11, 4, 5, 6, 7,18, 15, 17,16)
void setup() {
  // put your setup code here, to run once:
  // asign default color Value
  if ( u8g.getMode() == U8G_MODE_R3G3B2) 
    u8g.setColorIndex(255); // RGB = White
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT) 
    u8g.setColorIndex(3);
  else if (u8g.getMode() == U8G_MODE_BW)
    u8g.setColorIndex(1); 
  
}

void u8g_prepare() {  // set the font settings
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void DrawFrameMarkers() {  // draw some points in the screen
  u8g.drawFrame(0, 0, 128,64); 
  u8g.drawPixel(25, 16); 
  u8g.drawPixel(50, 16);
  u8g.drawPixel(100,16) ;
  u8g.drawPixel(25, 32) ;
  u8g.drawPixel(50, 32) ;
  u8g.drawPixel(100,32);
  u8g.drawPixel(25,48);
  u8g.drawPixel(50,48) ;
  u8g.drawPixel(100,48) ; 
}

void read_sample(void) {
  for (int xpos = 0;  xpos <100; xpos++ ) {
     sample[xpos] = analogRead(myPot);
  }
}

void draw(void) {
  char _buffer[5]; // buffer to convert sample[xpos] to charArry 
  u8g_prepare();
  DrawFrameMarkers();
 u8g.drawStr(100, 8, "current value: ");
  for (int xpos = 1; xpos < 99; xpos++) {
    //sample/10.2 4 because 1 024 becomes 100 = 5 volts
    u8g.drawLine(xpos, sample[xpos]/10.24, xpos+1, sample[xpos+1]/10.24);
    u8g.drawStr(100,18, itoa(sample[xpos], _buffer, 10)); // itoa
  }
 
}
void loop() {
  // put your main code here, to run repeatedly:
  // collect data
  read_sample();
  // show collected data 
  u8g.firstPage();
  do {
    draw();
  }while(u8g.nextPage());
  // rebuild the picture after some delay
  delay(100);
}
