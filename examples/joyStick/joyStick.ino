/**
 * joyStick.pde
 * RTno is RT-middleware and arduino.
 *
 * This program is just for JoyStick Shield sold by spackfun.com
 *
 * Pin Settings:
 *
 */
#define USE_MAINLOOP_EC
#include <RTno2.h>

/**
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_t &conf, exec_cxt_t &exec_cxt)
{
  conf._default.connection_type = ConnectionType::SERIAL1;
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ECType::MAINLOOP;
  exec_cxt.periodic.rate = 100;
}

/**
 * Declaration Division:
 *
 * DataPort and Data Buffer should be placed here.
 *
 * available data types are as follows:
 * TimedLong
 * TimedDouble
 * TimedFloat
 * TimedLongSeq
 * TimedDoubleSeq
 * TimedFloatSeq
 *
 * Please refer following comments. If you need to use some ports,
 * uncomment the line you want to declare.
 **/

TimedLongSeq stick;
OutPort<TimedLongSeq> stickOut("stick", stick);

TimedLongSeq button;
OutPort<TimedLongSeq> buttonOut("button", button);

int channelStickX = 0;
int channelStickY = 1;
int channelStickZ = 2;

int dummy;
//////////////////////////////////////////
// on_initialize
//
// This function is called in the initialization
// sequence when th processor is turned on.
// In on_initialize, usually DataPorts are added.
//
//////////////////////////////////////////
int onInitialize()
{
  /* Data Ports are added in this section.*/

  addOutPort(stickOut);
  addOutPort(buttonOut);

  pinMode(channelStickX, INPUT);
  pinMode(channelStickY, INPUT);
  pinMode(channelStickZ, INPUT);
  digitalWrite(channelStickZ, HIGH);

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  stick.data.length(3);
  button.data.length(4);

  return RTC_OK;
}

////////////////////////////////////////////
// on_activated
// This function is called when the RTnoRTC
// is activated. When the activation, the RTnoRTC
// sends message to call this function remotely.
// If this function is failed (return value
// is RTC_ERROR), RTno will enter ERROR condition.
////////////////////////////////////////////
int onActivated()
{
  // Write here initialization code.

  return RTC_OK;
}

/////////////////////////////////////////////
// on_deactivated
// This function is called when the RTnoRTC
// is deactivated.
/////////////////////////////////////////////
int onDeactivated()
{
  // Write here finalization code.

  return RTC_OK;
}

//////////////////////////////////////////////
// This function is repeatedly called when the
// RTno is in the ACTIVE condition.
// If this function is failed (return value is
// RTC_ERROR), RTno immediately enter into the
// ERROR condition.r
//////////////////////////////////////////////
int onExecute()
{
  /*
   * Output digital data in Voltage unit.
   */
  stick.data[0] = analogRead(channelStickX);
  stick.data[1] = analogRead(channelStickY);
  stick.data[2] = digitalRead(channelStickZ);
  stickOut.write();

  button.data[0] = digitalRead(3);
  button.data[1] = digitalRead(4);
  button.data[2] = digitalRead(5);
  button.data[3] = digitalRead(6);
  buttonOut.write();

  return RTC_OK;
}

//////////////////////////////////////
// on_error
// This function is repeatedly called when
// the RTno is in the ERROR condition.
// The ERROR condition can be recovered,
// when the RTno is reset.
///////////////////////////////////////
int onError()
{
  return RTC_OK;
}

////////////////////////////////////////
// This function is called when
// the RTno is reset. If on_reset is
// succeeded, the RTno will enter into
// the INACTIVE condition. If failed
// (return value is RTC_ERROR), RTno
// will stay in ERROR condition.ec
///////////////////////////////////////
int onReset()
{
  return RTC_OK;
}
