/* DU-INO Basic CV Randomizer with Display Graphics but without Controls.
 *  AUDIO AND OLED.
 *  
 *  by Rino Petrozziello 
 *  www.rinopetrozziello.com
 * 
 * This is a very basic example of how to
 * build a simple CV randomizer 
 * which uses GT1,GT2,GT3,GT4 as trigger inputs and 
 * CO1,CO2,CO3,CO4 as CV outputs.
 * 
 * In this example there's not code for the control part.
 * 
 * Below the configuration to apply on the backside of the module.
 * 
 * SWITCH CONFIGURATION
 * ------------------------
 * SG2 [^][^] SG1
 * SG4 [^][^] SG3
 * SC2 [_][_] SC1
 * SC4 [_][_] SC3
 */

#include <du-ino_function.h>
#include <du-ino_widgets.h>

int mod1 = 0;
int mod2 = 0;
int mod3 = 0;
int mod4 = 0;

class DU_RINO_Function : public DUINO_Function
{
  public:
  /* Change ->(0b00001111)<- according to the switch configuration */
  DU_RINO_Function() : DUINO_Function(0b00001111) { }

  virtual void function_setup()
  {
    /* Initialize Display contents */
    containerOut = new DUINO_WidgetContainer<4>(DUINO_Widget::DoubleClick);
    container1 = new DUINO_DisplayWidget(0,0,63,30,DUINO_Widget::Full);
    containerOut->attach_child(container1,0);
    container2 = new DUINO_DisplayWidget(63,0,63,30,DUINO_Widget::Full);
    containerOut->attach_child(container2,1);
    container3 = new DUINO_DisplayWidget(0,30,63,30,DUINO_Widget::Full);
    containerOut->attach_child(container3,2);
    container4 = new DUINO_DisplayWidget(63,30,63,30,DUINO_Widget::Full);
    containerOut->attach_child(container4,3);

    /* This will be shown at StartUp */
    Display.fill_rect(container1->x(),container1->y(),63,30, DUINO_SH1106::Black);
    Display.draw_text(container1->x()+2, container1->y()+1, "GT1", DUINO_SH1106::White);
    Display.draw_text(container1->x()+2, container1->y()+16, "0.0", DUINO_SH1106::White);
    Display.draw_text(container1->x()+30, container1->y()+16, "cv", DUINO_SH1106::White);

    Display.fill_rect(container2->x(),container2->y(),63,30, DUINO_SH1106::Black);
    Display.draw_text(container2->x()+2, container2->y()+1, "GT2", DUINO_SH1106::White);
    Display.draw_text(container2->x()+2, container2->y()+16, "0.0", DUINO_SH1106::White);
    Display.draw_text(container2->x()+30, container2->y()+16, "cv", DUINO_SH1106::White);
    
    Display.fill_rect(container3->x(),container3->y(),63,30, DUINO_SH1106::Black);
    Display.draw_text(container3->x()+2, container3->y()+1, "GT3", DUINO_SH1106::White);
    Display.draw_text(container3->x()+2, container3->y()+16, "0.0", DUINO_SH1106::White);
    Display.draw_text(container3->x()+30, container3->y()+16, "cv", DUINO_SH1106::White);

    Display.fill_rect(container4->x(),container4->y(),63,30, DUINO_SH1106::Black);
    Display.draw_text(container4->x()+2, container4->y()+1, "GT4", DUINO_SH1106::White);
    Display.draw_text(container4->x()+2, container4->y()+16, "0.0", DUINO_SH1106::White);
    Display.draw_text(container4->x()+30, container4->y()+16, "cv", DUINO_SH1106::White);

    widget_setup(containerOut);
    Display.display();
  }

  virtual void function_loop()
  {
    container1->display();
    container2->display();
    container3->display();
    container4->display();
    gateControl();
  }

  void gateControl()
  {
    /* GATE1 CONFIG */
    const bool gate1 = gt_read(GT1);
    if(!mod1 && gate1 > 0){
      /* GATE1 HIGH 
       * send random CV to CO1
      */
      mod1 = 1;
      int ax = random(1000);
      float bx = ax/100;
      cv_out(CO1,bx);
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      /* show contents on the oled display */
      Display.fill_rect(container1->x(),container1->y(),63,30, container1->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container1->x()+2, container1->y()+1, "GT1", container1->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container1->x()+2, container1->y()+16, bxx, container1->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container1->x()+30, container1->y()+16, "cv", container1->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
    } else if(mod1 && gate1 == 0){
      /* GATE1 LOW */
      int ax = random(1000);
      float bx = ax/100;
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      Display.fill_rect(container1->x(),container1->y(),63,30, container1->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container1->x()+2, container1->y()+1, "GT1", container1->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container1->x()+2, container1->y()+16, bxx, container1->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container1->x()+30, container1->y()+16, "cv", container1->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      mod1 = 0;
    }
    
    /* GATE2 CONFIG */
    const bool gate2 = gt_read(GT2);
    if(!mod2 && gate2 > 0){
      /* GATE2 HIGH 
       * send random CV to CO2
       */
      mod2 = 1;
      int ax = random(1000);
      float bx = ax/100;
      cv_out(CO2,bx);
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      Display.fill_rect(container2->x(),container2->y(),63,30, container2->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container2->x()+2, container2->y()+1, "GT2", container2->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container2->x()+2, container2->y()+16, bxx, container2->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container2->x()+30, container2->y()+16, "cv", container2->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
    } else if(mod2 && gate2 == 0){
      /* GATE2 LOW */
      int ax = random(1000);
      float bx = ax/100;
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      Display.fill_rect(container2->x(),container2->y(),63,30, container2->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container2->x()+2, container2->y()+1, "GT2", container2->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container2->x()+2, container2->y()+16, bxx, container2->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container2->x()+30, container2->y()+16, "cv", container2->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      mod2 = 0;
    }

    /* GATE3 CONFIG */
    const bool gate3 = gt_read(GT3);
    if(!mod3 && gate3 > 0){
      /* GATE3 HIGH 
       * send random CV to CO3
       */
      mod3 = 1;
      int ax = random(1000);
      float bx = ax/100;
      cv_out(CO3,bx);
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      Display.fill_rect(container3->x(),container3->y(),63,30, container3->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container3->x()+2, container3->y()+1, "GT3", container3->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container3->x()+2, container3->y()+16, bxx, container3->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container3->x()+30, container3->y()+16, "cv", container3->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
    } else if(mod3 && gate3 == 0){
      /* GATE3 LOW */
      int ax = random(1000);
      float bx = ax/100;
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      Display.fill_rect(container3->x(),container3->y(),63,30, container3->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container3->x()+2, container3->y()+1, "GT3", container3->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container3->x()+2, container3->y()+16, bxx, container3->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container3->x()+30, container3->y()+16, "cv", container3->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      mod3 = 0;
    }

    /* GATE4 CONFIG */
    const bool gate4 = gt_read(GT4);
    if(!mod4 && gate4 > 0){
      /* GATE4 HIGH 
       * send random CV to CO4
       */
      mod4 = 1;
      int ax = random(1000);
      float bx = ax/100;
      cv_out(CO4,bx);
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      Display.fill_rect(container4->x(),container4->y(),63,30, container4->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container4->x()+2, container4->y()+1, "GT4", container4->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container4->x()+2, container4->y()+16, bxx, container4->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container4->x()+30, container4->y()+16, "cv", container4->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
    } else if(mod4 && gate4 == 0){
      /* GATE4 LOW */
      int ax = random(1000);
      float bx = ax/100;
      char bxx[5];
      /* convert float to const char* */
      dtostrf(bx,3,2,bxx);
      Display.fill_rect(container4->x(),container4->y(),63,30, container4->inverted() ? DUINO_SH1106::White : DUINO_SH1106::Black);
      Display.draw_text(container4->x()+2, container4->y()+1, "GT4", container4->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container4->x()+2, container4->y()+16, bxx, container4->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      Display.draw_text(container4->x()+30, container4->y()+16, "cv", container4->inverted() ? DUINO_SH1106::Black : DUINO_SH1106::White);
      mod4 = 0;
    }
  }

  DUINO_WidgetContainer<4> * containerOut;
  DUINO_DisplayWidget * container1;
  DUINO_DisplayWidget * container2;
  DUINO_DisplayWidget * container3;
  DUINO_DisplayWidget * container4;
};

DU_RINO_Function * function;

void setup()
{
  function = new DU_RINO_Function();
  function->begin();
}

void loop()
{
  function->function_loop();
}
