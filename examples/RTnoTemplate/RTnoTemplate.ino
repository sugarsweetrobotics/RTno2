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
//#include <Timer1ExecutionContext.h>

/** 
 * Include UART.h header
 *  to use ConnectionTypeSerial1, 2, 3
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

  // TimedLong in0;
  // InPort<TimedLong> in0In;

  // TimedDouble in1;
  // InPort<TimedDouble> in1In;

  // TimedLongSeq in2;
  // InPort<TimedLongSeq> in2In;


  // TimedLong out0;
  // OutPort<TimedLong> out0Out;

  // TimedFloat out1;
  // OutPort<TimedFloat> out1Out;

  // TimedDouble out2;
  // OutPort<TimedDouble> out2Out;

  // TimedLongSeq out3;
  // OutPort<TimedLongSeq> out3Out;

  int dummy;
  public:
  RTC(): dummy(0)
  // , in0In("in0", in0)
  // , in1In("in1", in1)
  // , in2In("in2", in2)
  // , out0Out("out0", out0)
  // , out1Out("out1", out1)
  // , out2Out("out2", out2)
  // , out3Out("out3", out3)
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
    /* Data Ports are added in this section.*/
    /*    
    addInPort(in0In);
    addInPort(in1In);
    addInPort(in2In);
    addOutPort(out0Out);
    addOutPort(out1Out);
    addOutPort(out2Out);
    addOutPort(out3Out);
    */
    
    // Some initialization (like port direction setting)
    // int LED = 13;
    // pinMode(LED, OUTPUT);
    // digitalWrite(LED, HIGH);
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
  int onExecute() {
    // const int LED = 13;
    // if (in0In.isNew()) {
    //   int data = in0In.read();
    //   if (in0.data == 2) {
    //     digitalWrite(LED, LOW);
    //   } else if (in0.data == 3) {
    //     digitalWrite(LED, HIGH);
    //   }
    // }

    // if (in1In.isNew()) {
    //   in1In.read();
    //   if (in1.data > 3.0) {
    //     digitalWrite(LED, HIGH);
    //   } else if (in1.data < -1.0) {
    //     digitalWrite(LED, LOW);
    //   }
    // }

    // if (in2In.isNew()) {
    //   in2In.read();
    //   if (in2.data.length() == 3) {
    //     digitalWrite(LED, HIGH);
    //   } else {
    //     digitalWrite(LED, LOW);
    //   }
    // }

    // out0.data = 1234;
    // out0Out.write();


    // out1.data = 54.321;
    // out1Out.write();

    // out2.data = 54.321;
    // out2Out.write();


    // out3.data.length(3);
    // out3.data[0] = 4;
    // out3.data[1] = 5;
    // out3.data[2] = 6;
    // out3Out.write();

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

