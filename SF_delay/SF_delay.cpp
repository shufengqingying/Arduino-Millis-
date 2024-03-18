#include "SF_delay.h"

SF_Delay SFdelay;  //声明类的名字,在这里可以修改函数在外部调用时的名称

void SF_Delay::begin(int number, uint32_t delay_time, void (*P_call_back)(), bool set_fuction) {
  if (number_max < number) {
    number_max = number;  //记录最新延时体的编号,用于循环检查
  }
  // Serial.print("当前序号:");
  // Serial.println(number);
  Data_1[number - 1].P_callback = P_call_back;  //c传递回调函数的指针
  Data_1[number - 1].set_time = delay_time;
  Data_1[number - 1].fuction = set_fuction;
}

void SF_Delay::run() {  //绑定回调函数
  for (int i = 0; i < number_max; i++) {
    uint32_t NOWtime = (Data_1[i].fuction != false ? micros() : millis());  //选择记录的模式
    if (NOWtime - Data_1[i].data_time >= Data_1[i].set_time) {
      Data_1[i].state = 0;  //先将状态值设置为0
      if (Data_1[i].P_callback != NULL) {
        Data_1[i].P_callback();  // 再调用函数指针指向的函数
      }
      Data_1[i].data_time = NOWtime;  //刷新时间
    } else {
      Data_1[i].state = 1;  //状态值设置为1
    }
  }
}

int SF_Delay::Search(int number) {
  return Data_1[number - 1].state;
  // Serial.print("当前延时时间:");
  // Serial.println(number);
}
