#include <stdio.h>
#include <stdlib.h>
#include "statemachine.h"

state_t initHandler(void);
state_t buttonPushedHandler(void);

static stateTrans_t stateTrans[] = {
  // State	, Event			, Function
  {ST_INIT	, EV_ANY		, initHandler },
  {ST_IDLE	, EV_BUTTON_PUSHED	, buttonPushedHandler }
};

int main(void) {
  // main func
  return 0; 
}

state_t initHandler(void) {
  // init handler method
  return ST_IDLE;
}

state_t buttonPushedHandler(void) {
  // button pushed handler
  return ST_IDLE;
}
