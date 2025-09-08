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
#include <RTno.h>



/**
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_str& conf, exec_cxt_str& exec_cxt) {
  conf._default.connection_type = ConnectionTypeSerial1;
  // conf._default.connection_type = ConnectionTypeSerial2; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeSerial3; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeEtherTcp; // This configuration is avaiable with Ethernet Shield.
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ProxySynchronousExecutionContext;
  
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
class RTC : public DataFlowComponentBase {

  TimedLongSeq in0;
  InPort<TimedLongSeq> in0In("vel", in0);

  /*
  * Definition of I/O pin
  */

  static const int pinMotorADir = 12;
  static const int pinMotorAPWM = 3;
  static const int pinMotorBDir = 13;
  static const int pinMotorBPWM = 11;


  int dummy;
  public:
  RTC(): dummy(0)
   , in0In("in0", in0)
  {}

  //////////////////////////////////////////
  // on_initialize
  //
  // This function is called in the initialization
  // sequence when th processor is turned on.
  // In on_initialize, usually DataPorts are added.
  //
  //////////////////////////////////////////
  int onInitialize() {
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
  int onActivated() {
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
  int onExecute() {
    /* Read Input Port */
    if(in0In.isNew()) {
      in0In.read();
      long vel_a = in0.data[0];
      long vel_b = in0.data[1];
      if(vel_a < 0) {
        digitalWrite(pinMotorADir, HIGH);
        vel_a = -vel_a;
      }else {
        digitalWrite(pinMotorADir, LOW);
      }
      if(vel_b < 0) {
        digitalWrite(pinMotorBDir, HIGH);
        vel_b = -vel_b;
      } else {
        digitalWrite(pinMotorBDir, LOW);
      }
      if(vel_a > 255) vel_a = 255;
      if(vel_b > 255) vel_b = 255;
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

};

//////////////////////////////////////////
// DO NOT MODIFY THESE FUNCTIONS
//////////////////////////////////////////
void setup() {
  RTno_setup(new RTC());
}

//////////////////////////////////////////
// DO NOT MODIFY THESE FUNCTIONS
//////////////////////////////////////////
void loop() {
  RTno_loop();
}
