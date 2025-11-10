/**
 * digitalInOut.ino
 * RTno is RT-middleware and arduino.
 *
 * This is a simple example for RTno begineer.
 * This program just use general I/O pin.
 *
 * I/O pin settings:
 * Pin [ 8,  9, 10, 11, 12, 13] ... Output Pins.
 * Pin [ 2,  3,  4,  5,  6,  7] ... Input Pins.
 *
 * I/O port settings:
 * Port "in0"
 *  -type       : TimedLongSeq
 *  -data length: 6
 *  -description: each data element corresponds to the output pin level.
 *                If data is 0, corresponding output pin will LOW (0 Volt)
 *                If data is non-zero, pin will HIGH (Vcc level).
 *                The 6th element corresponds to the 13th pin (LED pin),
 *                so you can confirm this program's behavior without any
 *                modification to the arduino board.
 *
 * Port "out0"
 *  -type       : TimedLongSeq
 *  -data length: 6
 *  -description: each data element corresponds to the input pin level.
 *                If data is 0, corresponding output pin will LOW (0 Volt)
 *                If data is non-zero, pin will HIGH (Vcc level).
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
  exec_cxt.periodic.rate = 10; // [Hz]
}

/**
 * Declaration Division:
 *
 * DataPort and Data Buffer should be placed here.
 *
 * Currently, following 6 types are available.
 * TimedLong:
 * TimedDouble:
 * TimedFloat:
 * TimedLongSeq:
 * TimedDoubleSeq:
 * TimedFloatSeq:
 *
 * Please refer following comments. If you need to use some ports,
 * uncomment the line you want to declare.
 **/
TimedLongSeq in0;
InPort<TimedLongSeq> in0In("in0", in0);

TimedLongSeq out0;
OutPort<TimedLongSeq> out0Out("out0", out0);

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
  /* Data Ports are added in this section.
   */
  addInPort(in0In);
  addOutPort(out0Out);

  // Some initialization (like port direction setting)
  for (int i = 0; i < 6; i++)
  {
    pinMode(2 + i, INPUT);
  }
  for (int i = 0; i < 6; i++)
  {
    pinMode(8 + i, OUTPUT);
  }

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
   * Input digital data
   */

  if (in0In.isNew())
  {
    in0In.read();
    for (int i = 0; i < in0.data.length() && i < 6; i++)
    {
      digitalWrite(8 + i, in0.data[i]);
    }
  }

  /*
   * Output digital data in Voltage unit.
   */
  out0.data.length(6);
  for (int i = 0; i < 6; i++)
  {
    out0.data[i] = digitalRead(2 + i);
  }
  out0Out.write();

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
