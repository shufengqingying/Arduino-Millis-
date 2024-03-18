#ifndef SF_delay_H
#define SF_delay_H
#include <Arduino.h>

class SF_Delay {
private:

  struct Millis_Data {

    void (*P_callback)();  //定义回调函数指针
    bool fuction;          //用于选择毫秒计时或者微秒
    uint32_t set_time;     //创建延时变量
    uint32_t data_time;    //创建Millis的记录变量
    bool state;            //记录状态变量
                           // 构造函数
    Millis_Data()
      : P_callback(NULL) {}  // 初始化 P_callback 为 NULL
  };

  Millis_Data Data_1[49]{};  //创建50个延时节点结构体,可以根据内存空间和程序功能修改数量,

  int number_max;  //记录延时体数量

public:
  //序列号、延时时间、模式（默认毫秒延时）
  void begin(int number, uint32_t delay_time, void (*P_call_back)(), bool set_fuction);  //延时体编号,延时时间,毫秒/微秒选择
  int Search(int munber);                                                                //查询延时体状态,达到延时时间后返回true
  void run();                                                                            //运行检测函数
};

extern SF_Delay SFdelay;  //声明类后,可以在外部调用


#endif