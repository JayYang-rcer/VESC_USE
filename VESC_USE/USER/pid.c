#include "pid.h"
#include "main.h"
#include "math.h"


/**
  * @brief          pid struct data init
  * @param[out]     pid: PID struct data point
  * @param[in]      mode: PID_POSITION: normal pid
  *                 PID_DELTA: delta pid
  * @param[in]      PID: 0: kp, 1: ki, 2:kd
  * @param[in]      max_out: pid max out
  * @param[in]      max_iout: pid max iout
  * @retval         none
  */
	
PID_TypeDef    Drive_Motor_Pid[4];           //�ĸ����

/*������ʼ��-----------------------------*/
void Pid_Param_Init(
							PID_TypeDef * pid, 
							PID_ID    id,
							uint16_t  maxout,
							uint16_t  intergral_limit,
							float     deadband,
							uint16_t  period,
							int16_t   max_err,
							int16_t   target,
							float 	kp, 
							float 	ki, 
							float 	kd)
{
	pid->id = id;		
	
	pid->ControlPeriod = period;  //û�õ�
	pid->DeadBand = deadband;
	pid->IntegralLimit = intergral_limit;
	pid->MaxOutput = maxout;
	pid->Max_Err = max_err;
	pid->target = target;         //Ŀ��ֵ
	
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	
	pid->output = 0;
}

/*--------------------------------------------------------------

 ��;���Ĳ����趨

*/
void Pid_Reset(PID_TypeDef * pid, float kp, float ki, float kd)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
}

/*pid����-----------------------------------------------------------------------*/	
float Pid_Calculate(PID_TypeDef* pid, float measure)
{
	//  ���ݵĸ���
	pid->measure = measure;          //����ֵ���ڱ������²���ֵ
	pid->last_err  = pid->err;       //�ϴ������ڱ����������
	pid->last_output = pid->output;  //�ϴ�������ڱ����������
	
	pid->err = pid->target - pid->measure;  //���ֵ = Ŀ��ֵ - ����ֵ
	
	//�Ƿ��������
	if((fabsf(pid->err) > pid->DeadBand))   //����������
	{
			pid->pout = pid->kp * pid->err;      //p���ΪKp*���
			pid->iout += (pid->ki * pid->err);   //i���Ϊi+ki*���
			pid->dout =  pid->kd * (pid->err - pid->last_err);  //d���Ϊkd*�����-�ϴ���
			
			//�����Ƿ񳬳�����
			if(pid->iout > pid->IntegralLimit)
				   pid->iout = pid->IntegralLimit;       
			if(pid->iout < - pid->IntegralLimit)
				   pid->iout = - pid->IntegralLimit;
			
			//pid�����
			pid->output = pid->pout + pid->iout + pid->dout;   	

			//pid->output = pid->output*0.7f + pid->last_output*0.3f;  //�˲���
			if(pid->output>pid->MaxOutput)         
			{
				   pid->output = pid->MaxOutput;
			}
			if(pid->output < -(pid->MaxOutput))
			{
				   pid->output = -(pid->MaxOutput);
			}
	
	}
	return pid->output;
}




