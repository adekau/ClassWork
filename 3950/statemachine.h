#ifndef STATEMACHINE_H
#define STATEMACHINE_H
typedef enum{
  ST_ANY,
  ST_IDLE,
  ST_INIT,
  ST_LED_ON,
  ST_LED_OFF,
  ST_FLASHING
} state_t;

typedef enum{
  EV_ANY,
  EV_BUTTON_PUSHED,
  EV_TIME_OUT,
  EV_NONE
} event_t;

typedef struct {
  state_t state;
  event_t event;
  void (*func)(void);
} stateTrans_t;

#endif
