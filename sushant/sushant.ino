#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

void draw(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("This is final year");
  u8g.setPrintPos(0, 25);
  u8g.print("Project");
  
}

void draw2(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("Presented by");
  u8g.setPrintPos(0, 25);
  u8g.print("Group");
  u8g.setPrintPos(0, 40);
  u8g.setFont(u8g_font_profont10);
  u8g.print("PEC 3.5");
}

void setup(void) {
}

void loop(void) {
    delay(7000);
  u8g.firstPage();

  do {
    draw();
  } while (u8g.nextPage() );
  delay(7000);
  u8g.firstPage();
  do {
    draw2();
  } while (u8g.nextPage());
  delay(10000);
}
