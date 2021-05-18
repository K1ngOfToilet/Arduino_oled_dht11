#include <Arduino.h>
#include <U8g2lib.h>
#include <dht11.h>
dht11 DHT11;
#define DHT11Pin 3
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// End of constructor list

//初始化
void setup(void) 
{
  pinMode(DHT11Pin,INPUT);
  u8g2.begin();
  u8g2.enableUTF8Print(); 
}

//时间初始化
uint8_t m = 55;
uint8_t n = 23;
uint8_t k = 23;
uint8_t nian = 21;
uint8_t yue = 05;
uint8_t ri = 17;

//菜单显示
void loop(void)
{
  //时钟
  char m_str[3];
  strcpy(m_str, u8x8_u8toa(m, 2));
  char n_str[3];
  strcpy(n_str, u8x8_u8toa(n, 2));
  char k_str[3];
  strcpy(k_str, u8x8_u8toa(k, 2));
  //日期
  char nian_str[3];
  strcpy(nian_str, u8x8_u8toa(nian, 2));
  char yue_str[3];
  strcpy(yue_str, u8x8_u8toa(yue, 2));
  char ri_str[3];
  strcpy(ri_str, u8x8_u8toa(ri, 2));

  u8g2.firstPage();
  do {  

     int chk = DHT11.read(DHT11Pin);
     Serial.print("Humidity (%): ");
     Serial.println((float)DHT11.humidity, 2);
     Serial.print("Temperature (oC): ");
     Serial.println((float)DHT11.temperature, 2);
  
     u8g2.drawUTF8(0, 12, "T: ");
     u8g2.drawUTF8(60, 12, "H: ");
     u8g2.setCursor(16, 12);  
     u8g2.print((float)DHT11.temperature, 2);
     u8g2.setCursor(78, 12);  
     u8g2.print((float)DHT11.humidity, 2);  

    u8g2.drawLine(0,20,128,20);
    u8g2.drawLine(80,20,80,64);
    u8g2.drawLine(0,63,128,63);

    u8g2.drawUTF8(82,35,"By");
    u8g2.drawUTF8(82,50,"K_O_T");
    
    u8g2.setFont(u8g2_font_unifont_t_symbols);//字体设置 

    u8g2.drawStr(0,35,"20");
    u8g2.drawStr(16,35,nian_str);
    u8g2.drawStr(30,35,"/");
    u8g2.drawStr(38,35,yue_str);
    u8g2.drawStr(55,35,"/");
    u8g2.drawStr(62,35,ri_str);

    u8g2.drawStr(0,59,k_str);
    u8g2.drawStr(22,59,":");
    u8g2.drawStr(32,59,n_str);
    u8g2.drawStr(50,59,":");
    u8g2.drawStr(60,59,m_str);
  } while ( u8g2.nextPage() );
  delay(1000);
  m++;
  if ( m == 60 )
  {
    m = 0;
    n++;
    if (n == 24)
    { 
    n = 0;
    k++;
    if (k == 24)
    {
    k = 0; 
    ri++;
    if(ri == 31)
    {
      ri = 0;
      yue++;
      if(yue == 12)
      {
        yue = 0;
        nian++;  
      }
    }
    }
    }
    
  }
  
  
}
