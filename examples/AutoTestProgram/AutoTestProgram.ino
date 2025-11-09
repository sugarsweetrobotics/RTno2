/**
 * RTnoTemplate.ino
 * RTno is RT-middleware and arduino.
 *
 * Using RTno, arduino device can communicate any RT-components
 *  through the RTno-proxy component which is launched in PC.
 * Connect arduino with USB, and program with RTno library.
 * You do not have to define any protocols to establish communication
 *  between arduino and PC.
 *
 * Using RTno, you must not modify the function "setup" and "loop".
 * Those functions are automatically defined in this file.
 * You, developers, must define following functions:
 *  int RTC::onInitialize(void);
 *  int RTC::onActivated(void);
 *  int RTC::onDeactivated(void);
 *  int RTC::onExecute(void);
 *  int RTC::onError(void);
 *  int RTC::onReset(void);
 * These functions are spontaneously called by the RTno-proxy
 *  RT-component which is launched in the PC.
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */

/**
 * Include Timer1ExecutionContext.h header
 *  to use Timer1ExecutionContext
 * See Timer1EC example to know in more detail
 */
// #include <Timer1ExecutionContext.h>

/**
 * Include UART.h header
 *  to use ConnectionTypeSerial1, 2, 3
 */
#include <RTno2.h>

// #define TEST_SEQUENCE
#define TEST_SIMPLE_BYTE_DATA
#define TEST_SIMPLE_MULTIBYTE_DATA

/**
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_t &conf, exec_cxt_t &exec_cxt)
{
  conf._default.connection_type = ConnectionType::SERIAL1;
  // conf._default.connection_type = ConnectionTypeSerial2; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeSerial3; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeEtherTcp; // This configuration is avaiable with Ethernet Shield.
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ECType::PROXY_SYNCHRONOUS;

  // Configurations Below are configuration parameter for EtherTcp connection.
  // conf._default.port = 23;
  // conf._default.mac_address = MacAddr(0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED);
  // conf._default.ip_address = IPAddr(192,168,42,100);
  // conf._default.subnet_mask = IPAddr(255,255,255,0);
  // conf._default.default_gateway = IPAddr(192,168,42,254);

  // exec_cxt.periodic.type = Timer1ExecutionContext; // onExecute is called by Timer1. Period must be specified by 'rate' option.
  // *caution: TimerOne can not be used with PWM 9, 10.
  // exec_cxt.periodic.rate = 1000; // [Hz] This option is indispensable when type is Timer*ExecutionContext.
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
/* InPorts */

#if defined TEST_SIMPLE_BYTE_DATA
TimedBoolean bool_in;
InPort<TimedBoolean> bool_inIn("bool_in", bool_in);
TimedChar char_in;
InPort<TimedChar> char_inIn("char_in", char_in);
TimedOctet octet_in;
InPort<TimedOctet> octet_inIn("octet_in", octet_in);
#endif

#if defined TEST_SIMPLE_MULTIBYTE_DATA
TimedLong long_in;
InPort<TimedLong> long_inIn("long_in", long_in);
TimedFloat float_in;
InPort<TimedFloat> float_inIn("float_in", float_in);
TimedDouble double_in;
InPort<TimedDouble> double_inIn("double_in", double_in);
#endif

#if defined TEST_SEQUENCE
TimedBooleanSeq bool_seq_in;
InPort<TimedBooleanSeq> bool_seq_inIn("bool_seq_in", bool_seq_in);
TimedCharSeq char_seq_in;
InPort<TimedCharSeq> char_seq_inIn("char_seq_in", char_seq_in);
TimedOctetSeq octet_seq_in;
InPort<TimedOctetSeq> octet_seq_inIn("octet_seq_in", octet_seq_in);

TimedLongSeq long_seq_in;
InPort<TimedLongSeq> long_seq_inIn("long_seq_in", long_seq_in);
TimedFloatSeq float_seq_in;
InPort<TimedFloatSeq> float_seq_inIn("float_seq_in", float_seq_in);
TimedDoubleSeq double_seq_in;
InPort<TimedDoubleSeq> double_seq_inIn("double_seq_in", double_seq_in);
#endif

/* OutPorts */

#if defined TEST_SIMPLE_BYTE_DATA
TimedBoolean bool_out;
OutPort<TimedBoolean> bool_outOut("bool_out", bool_out);
TimedChar char_out;
OutPort<TimedChar> char_outOut("char_out", char_out);
TimedOctet octet_out;
OutPort<TimedOctet> octet_outOut("octet_out", octet_out);
#endif

TimedLong long_out;
OutPort<TimedLong> long_outOut("long_out", long_out);
TimedFloat float_out;
OutPort<TimedFloat> float_outOut("float_out", float_out);
TimedDouble double_out;
OutPort<TimedDouble> double_outOut("double_out", double_out);

#if defined TEST_SEQUENCE
TimedBooleanSeq bool_seq_out;
OutPort<TimedBooleanSeq> bool_seq_outOut("bool_seq_out", bool_seq_out);
TimedCharSeq char_seq_out;
OutPort<TimedCharSeq> char_seq_outOut("char_seq_out", char_seq_out);
TimedOctetSeq octet_seq_out;
OutPort<TimedOctetSeq> octet_seq_outOut("octet_seq_out", octet_seq_out);

TimedLongSeq long_seq_out;
OutPort<TimedLongSeq> long_seq_outOut("long_seq_out", long_seq_out);
TimedFloatSeq float_seq_out;
OutPort<TimedFloatSeq> float_seq_outOut("float_seq_out", float_seq_out);
TimedDoubleSeq double_seq_out;
OutPort<TimedDoubleSeq> double_seq_outOut("double_seq_out", double_seq_out);
#endif
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
#if defined TEST_SIMPLE_BYTE_DATA
  addInPort(bool_inIn);
  addOutPort(bool_outOut);
  addInPort(char_inIn);
  addOutPort(char_outOut);
  addInPort(octet_inIn);
  addOutPort(octet_outOut);
#endif

#if defined TEST_SIMPLE_MULTIBYTE_DATA
  addInPort(long_inIn);
  addOutPort(long_outOut);
  addInPort(float_inIn);
  addOutPort(float_outOut);
  addInPort(double_inIn);
  addOutPort(double_outOut);
#endif

#if defined TEST_SEQUENCE
  addInPort(bool_seq_inIn);
  addOutPort(bool_seq_outOut);
  addInPort(char_seq_inIn);
  addOutPort(char_seq_outOut);
  addInPort(octet_seq_inIn);
  addOutPort(octet_seq_outOut);

  addInPort(long_seq_inIn);
  addOutPort(long_seq_outOut);
  addInPort(float_seq_inIn);
  addOutPort(float_seq_outOut);
  addInPort(double_seq_inIn);
  addOutPort(double_seq_outOut);
#endif
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

#if defined TEST_SIMPLE_BYTE_DATA
  bool_in.data = false;
  bool_out.data = false;
  char_in.data = 'a';
  char_out.data = 'a';
  octet_in.data = 1;
  octet_out.data = 1;
#endif

#if defined TEST_SIMPLE_MULTIBYTE_DATA
  long_in.data = 1;
  long_out.data = 1;
  float_in.data = 1.0f;
  float_out.data = 1.0f;
  double_in.data = 1.0;
  double_out.data = 1.0;
#endif

#if defined TEST_SEQUENCE
  bool_seq_in.data.length(1);
  bool_seq_in.data[0] = false;
  bool_seq_out.data.length(1);
  bool_seq_out.data[0] = false;
  char_seq_in.data.length(1);
  char_seq_in.data[0] = 'a';
  char_seq_out.data.length(1);
  char_seq_out.data[0] = 'a';
  octet_seq_in.data.length(1);
  octet_seq_in.data[0] = 1;
  octet_seq_out.data.length(1);
  octet_seq_out.data[0] = 1;

  long_seq_in.data.length(1);
  long_seq_in.data[0] = 1;
  long_seq_out.data.length(1);
  long_seq_out.data[0] = 1;
  float_seq_in.data.length(1);
  float_seq_in.data[0] = 1.0f;
  float_seq_out.data.length(1);
  float_seq_out.data[0] = 1.0f;
  double_seq_in.data.length(1);
  double_seq_in.data[0] = 1.0;
  double_seq_out.data.length(1);
  double_seq_out.data[0] = 1.0;
#endif
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

#if defined TEST_SIMPLE_BYTE_DATA
  bool_in.data = false;
  bool_out.data = false;
  char_in.data = 'a';
  char_out.data = 'a';
  octet_in.data = 1;
  octet_out.data = 1;
#endif

#if defined TEST_SIMPLE_MULTIBYTE_DATA
  long_in.data = 1;
  long_out.data = 1;
  float_in.data = 1.0f;
  float_out.data = 1.0f;
  double_in.data = 1.0;
  double_out.data = 1.0;
#endif

#if defined TEST_SEQUENCE
  bool_seq_in.data.length(1);
  bool_seq_in.data[0] = false;
  bool_seq_out.data.length(1);
  bool_seq_out.data[0] = false;
  char_seq_in.data.length(1);
  char_seq_in.data[0] = 'a';
  char_seq_out.data.length(1);
  char_seq_out.data[0] = 'a';
  octet_seq_in.data.length(1);
  octet_seq_in.data[0] = 1;
  octet_seq_out.data.length(1);
  octet_seq_out.data[0] = 1;

  long_seq_in.data.length(1);
  long_seq_in.data[0] = 1;
  long_seq_out.data.length(1);
  long_seq_out.data[0] = 1;
  float_seq_in.data.length(1);
  float_seq_in.data[0] = 1.0f;
  float_seq_out.data.length(1);
  float_seq_out.data[0] = 1.0f;
  double_seq_in.data.length(1);
  double_seq_in.data[0] = 1.0;
  double_seq_out.data.length(1);
  double_seq_out.data[0] = 1.0;
#endif
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

#if defined TEST_SIMPLE_BYTE_DATA
  if (bool_inIn.isNew())
  {
    bool_inIn.read();
  }
  bool_out.data = bool_in.data;
  bool_outOut.write();

  if (char_inIn.isNew())
  {
    char_inIn.read();
  }
  char_out.data = char_in.data;
  char_outOut.write();

  if (octet_inIn.isNew())
  {
    octet_inIn.read();
  }
  octet_out.data = octet_in.data;
  octet_outOut.write();
#endif

#if defined TEST_SIMPLE_MULTIBYTE_DATA
  if (long_inIn.isNew())
  {
    long_inIn.read();
  }
  long_out.data = long_in.data;
  long_outOut.write();

  if (float_inIn.isNew())
  {
    float_inIn.read();
  }
  float_out.data = float_in.data;
  float_outOut.write();

  if (double_inIn.isNew())
  {
    double_inIn.read();
  }
  double_out.data = double_in.data;
  double_outOut.write();
#endif

#if defined TEST_SEQUENCE
  if (bool_seq_inIn.isNew())
  {
    bool_seq_inIn.read();
  }
  bool_seq_out.data.length(bool_seq_in.data.length());
  for (int i = 0; i < bool_seq_in.data.length(); i++)
  {
    bool_seq_out.data[i] = bool_seq_in.data[i];
  }
  bool_seq_outOut.write();

  if (char_seq_inIn.isNew())
  {
    char_seq_inIn.read();
  }
  char_seq_out.data.length(char_seq_in.data.length());
  for (int i = 0; i < char_seq_in.data.length(); i++)
  {
    char_seq_out.data[i] = char_seq_in.data[i];
  }
  char_seq_outOut.write();

  if (octet_seq_inIn.isNew())
  {
    octet_seq_inIn.read();
  }
  octet_seq_out.data.length(octet_seq_in.data.length());
  for (int i = 0; i < octet_seq_in.data.length(); i++)
  {
    octet_seq_out.data[i] = octet_seq_in.data[i];
  }
  octet_seq_outOut.write();

  if (long_seq_inIn.isNew())
  {
    long_seq_inIn.read();
  }
  long_seq_out.data.length(long_seq_in.data.length());
  for (int i = 0; i < long_seq_in.data.length(); i++)
  {
    long_seq_out.data[i] = long_seq_in.data[i];
  }
  long_seq_outOut.write();

  if (float_seq_inIn.isNew())
  {
    float_seq_inIn.read();
  }
  float_seq_out.data.length(float_seq_in.data.length());
  for (int i = 0; i < float_seq_in.data.length(); i++)
  {
    float_seq_out.data[i] = float_seq_in.data[i];
  }
  float_seq_outOut.write();

  if (double_seq_inIn.isNew())
  {
    double_seq_inIn.read();
  }
  double_seq_out.data.length(double_seq_in.data.length());
  for (int i = 0; i < double_seq_in.data.length(); i++)
  {
    double_seq_out.data[i] = double_seq_in.data[i];
  }
  double_seq_outOut.write();
#endif
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
