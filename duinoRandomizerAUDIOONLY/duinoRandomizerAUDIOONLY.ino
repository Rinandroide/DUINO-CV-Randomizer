/* DU-INO Basic CV Randomizer without Display and Controls. 
 *  AUDIO PART ONLY
 *  
 *  by Rino Petrozziello 
 *  www.rinopetrozziello.com
 * 
 * This is a very basic example of how to
 * build a simple CV randomizer 
 * which uses GT1,GT2,GT3,GT4 as trigger inputs and 
 * CO1,CO2,CO3,CO4 as CV outputs.
 * 
 * In this example there's not code for the graphical part 
 * but ONLY for the AUDIO. Watch the next example to know how 
 * to implement a simple graphics on oled display. 
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
  }

  virtual void function_loop()
  {
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
    } else if(mod1 && gate1 == 0){
      /* GATE1 LOW */
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
    } else if(mod2 && gate2 == 0){
      /* GATE2 LOW */
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
    } else if(mod3 && gate3 == 0){
      /* GATE3 LOW */
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
    } else if(mod4 && gate4 == 0){
      /* GATE4 LOW */
      mod4 = 0;
    }
  }
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
