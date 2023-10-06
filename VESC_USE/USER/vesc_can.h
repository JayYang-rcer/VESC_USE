#ifndef __VESC_CAN_H
#define __VESC_CAN_H
#include "main.h"

#ifndef wtrcfg_VESC_COMMAND_DUTY_MAX
#define wtrcfg_VESC_COMMAND_DUTY_MAX 100
#endif 
#ifndef wtrcfg_VESC_COMMAND_CURRENT_MAX
#define wtrcfg_VESC_COMMAND_CURRENT_MAX 10
#endif 
#ifndef wtrcfg_VESC_COMMAND_POS_MAX
#define wtrcfg_VESC_COMMAND_POS_MAX 360
#endif 
#ifndef wtrcfg_VESC_COMMAND_ERPM_MAX
#define wtrcfg_VESC_COMMAND_ERPM_MAX 20000
#endif 
#ifndef wtrcfg_VESC_UART_TIMEOUT 
#define wtrcfg_VESC_UART_TIMEOUT 0xff
#endif



typedef enum {
	CAN_PACKET_SET_DUTY = 0,
	CAN_PACKET_SET_CURRENT,
	CAN_PACKET_SET_CURRENT_BRAKE,
	CAN_PACKET_SET_RPM,
	CAN_PACKET_SET_POS,
	CAN_PACKET_FILL_RX_BUFFER,
	CAN_PACKET_FILL_RX_BUFFER_LONG,
	CAN_PACKET_PROCESS_RX_BUFFER,
	CAN_PACKET_PROCESS_SHORT_BUFFER,
	CAN_PACKET_STATUS,
	CAN_PACKET_SET_CURRENT_REL,
	CAN_PACKET_SET_CURRENT_BRAKE_REL,
	CAN_PACKET_SET_CURRENT_HANDBRAKE,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
	CAN_PACKET_STATUS_2,
	CAN_PACKET_STATUS_3,
	CAN_PACKET_STATUS_4,
	CAN_PACKET_PING,
	CAN_PACKET_PONG,
	CAN_PACKET_DETECT_APPLY_ALL_FOC,
	CAN_PACKET_DETECT_APPLY_ALL_FOC_RES,
	CAN_PACKET_CONF_CURRENT_LIMITS,
	CAN_PACKET_CONF_STORE_CURRENT_LIMITS,
	CAN_PACKET_CONF_CURRENT_LIMITS_IN,
	CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN,
	CAN_PACKET_CONF_FOC_ERPMS,
	CAN_PACKET_CONF_STORE_FOC_ERPMS,
	CAN_PACKET_STATUS_5
}
CAN_PACKET_ID;


//限幅函数
void assert_param_pos(float *pos);
void assert_param_rpm(float *rpm);
void assert_param_current(float *current);
void assert_param_duty(float *duty);




//buffer函数
int16_t buffer_get_int16(const uint8_t *buffer, int32_t *index);
uint16_t buffer_get_uint16(const uint8_t *buffer, int32_t *index);
int32_t buffer_get_int32(const uint8_t *buffer, int32_t *index);
uint32_t buffer_get_uint32(const uint8_t *buffer, int32_t *index);
float buffer_get_float16(const uint8_t *buffer, float scale, int32_t *index);
float buffer_get_float32(const uint8_t *buffer, float scale, int32_t *index);

void buffer_append_int32(uint8_t *buffer, int32_t number, int32_t *index);
void buffer_append_float32(uint8_t *buffer, float number, float scale, int32_t *index);





void comm_can_transmit_eid(uint32_t id, uint8_t *data, uint8_t len);	   //拓展帧发送函数
void comm_can_transmit_sid(uint32_t id, uint8_t *data, uint8_t len);		   //标准帧发送函数
void comm_can_set_duty(uint8_t controller_id, float duty);					   //设置对应ID占空比
void comm_can_set_current(uint8_t controller_id, float current);			   //设置对应ID电流环
void comm_can_set_current_brake(uint8_t controller_id, float current);		   //设置对应ID刹车电流
void comm_can_set_rpm(uint8_t controller_id, float rpm);					   //设置对应ID转速环
void comm_can_set_pos(uint8_t controller_id, float pos);					   //设置对应ID位置环
void comm_can_set_current_rel(uint8_t controller_id, float current_rel);	   //设置电流限幅
void comm_can_set_current_brake_rel(uint8_t controller_id, float current_rel); //设置刹车电流限幅
void comm_can_set_handbrake(uint8_t controller_id, float current);			   //设置刹车电流
void comm_can_set_handbrake_rel(uint8_t controller_id, float current_rel);	   //设置刹车电流限幅
#endif


