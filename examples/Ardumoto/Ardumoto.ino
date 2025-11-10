/**
 * RTnoVehicle.pde
 * RTno is RT-middleware and arduino.
 *
 *
 *
 *
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
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

static const int pinMotorADir = 12;
static const int pinMotorAPWM = 3;
static const int pinMotorBDir = 13;
static const int pinMotorBPWM = 11;

TimedLongSeq in0;
InPort<TimedLongSeq> in0In("vel", in0);

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
  /* Data Ports are added in this section. */
  addInPort(in0In);

  // Some initialization (like port direction setting)
  pinMode(pinMotorADir, OUTPUT);
  pinMode(pinMotorBDir, OUTPUT);
  pinMode(pinMotorAPWM, OUTPUT);
  pinMode(pinMotorBPWM, OUTPUT);

  digitalWrite(pinMotorADir, LOW);
  digitalWrite(pinMotorBDir, LOW);
  analogWrite(pinMotorAPWM, 0);
  analogWrite(pinMotorBPWM, 0);
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
  digitalWrite(pinMotorADir, LOW);
  digitalWrite(pinMotorBDir, LOW);
  analogWrite(pinMotorAPWM, 0);
  analogWrite(pinMotorBPWM, 0);

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
  digitalWrite(pinMotorADir, LOW);
  digitalWrite(pinMotorBDir, LOW);
  analogWrite(pinMotorAPWM, 0);
  analogWrite(pinMotorBPWM, 0);

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
  /* Read Input Port */
  if (in0In.isNew())
  {
    in0In.read();
    long vel_a = in0.data[0];
    long vel_b = in0.data[1];
    if (vel_a < 0)
    {
      digitalWrite(pinMotorADir, HIGH);
      vel_a = -vel_a;
    }
    else
    {
      digitalWrite(pinMotorADir, LOW);
    }
    if (vel_b < 0)
    {
      digitalWrite(pinMotorBDir, HIGH);
      vel_b = -vel_b;
    }
    else
    {
      digitalWrite(pinMotorBDir, LOW);
    }
    if (vel_a > 255)
      vel_a = 255;
    if (vel_b > 255)
      vel_b = 255;
    analogWrite(pinMotorAPWM, vel_a);
    analogWrite(pinMotorBPWM, vel_b);
  }
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
