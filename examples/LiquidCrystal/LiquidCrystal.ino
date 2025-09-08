/**
 * LiquidCrystal.ino
 * RTno is RT-middleware and arduino.
 * 
 * This example uses LiquidCrystal library.
 * http://arduino.cc/en/Reference/LiquidCrystalConstructor
 *
 * This program is tested by LCD shield by Prototyping Lab.
 * http://prototypinglab.com
 *
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */
#include <RTno.h>
#include <LiquidCrystal.h>

/**
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_str& conf, exec_cxt_str& exec_cxt) {
  conf._default.connection_type = ConnectionTypeSerial1;
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ProxySynchronousExecutionContext;
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


  TimedLong in0;
  InPort<TimedLong> in0In;


  // Initialize the library with the numbers of the interface pins.
  LiquidCrystal lcd;

  int dummy;
  public:
  RTC(): dummy(0)
  , lcd(12, 11, 5, 4, 3, 2)
  , in0In("in0", in0)
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
    addInPort(in0In);
  
    lcd.begin(16, 2);
    
    lcd.setCursor(0, 0);
    lcd.print("RTC_INACTIVE  ");
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
    lcd.setCursor(0, 0);
    lcd.print("RTC_ACTIVE   ");
    
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
    lcd.setCursor(0, 0);
    lcd.print("RTC_INACTIVE   ");

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
    /**
     * Usage of InPort with premitive type.
     */
    if(in0In.isNew()) {
      in0In.read();
      long data = in0.data;
      lcd.setCursor(0, 1);
      lcd.print("data=           ");
      lcd.setCursor(6,1);
      lcd.print(data, DEC);
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
  RTno_setup(onInitialize, onActivated, onDeactivated, onExecute, onError, onReset);
}

//////////////////////////////////////////
// DO NOT MODIFY THESE FUNCTIONS
//////////////////////////////////////////
void loop() {
  RTno_loop();
}