#include <stdio.h>
#include <math.h>

//����PID�Ľṹ��
struct _pid{
	int pv;//������
	int sp;//�趨ֵ
	float integral;//����ֵ -- ƫ���ۼ�ֵ
	float pgain;
	float igain;
	float dgain;
	int deadband;//����
	int last_error;
};

struct _pid warm, * pid;

int process_point, set_point, dead_band;
float p_gain, i_gain, d_gain, integral_val, new_integ;

void pid_init(struct _pid* warm, int process_point, int set_point)
{
	struct _pid* pid;
	pid = warm;
	pid->pv = process_point;
	pid->sp = set_point;

}
//�趨PID����-----P��I��D������
void pid_tune(struct _pid* pid, float p_gain, float i_gain, float d_gain, int dead_band)
{
	pid->pgain = p_gain;
	pid->igain = i_gain;
	pid->dgain = d_gain;
	pid->deadband = dead_band;
	pid->integral = integral_val;
	pid->last_error = 0;
}
//�趨�����ʼֵ
void pid_setinting(struct _pid* pid, float new_integ)
{
	pid->integral = new_integ;//����ֵ
	pid->last_error = 0;
}

void pid_bumpless(struct _pid* pid)//�������
{
	pid->last_error = (pid->sp) - (pid->pv);
}

float pid_calc(struct _pid* pid)//pid����
{
	int err;
	float pterm, dterm, result, ferror;

	err = (pid->sp) - (pid->pv);//���

	if (abs(err) > pid->deadband)//����ж�����
	{
		ferror = (float)err;
		pterm = pid->pgain * ferror;
		if (pterm > 100 || pterm < -100)
		{
			pid->integral = 0.0f;
		}
		else
		{
			if (pid->integral > 100.0)
			{
				pid->integral = 100.0f;
			}
		}
		dterm = ((float)(err-pid->last_error))*pid->dgain;
		result = pterm + pid->integral + dterm;

	}
	else
	{
		result = pid->integral;
	}
	pid->last_error = err;
	return result;
}

int main(void)
{
	float display_value=0.0f;
	int count = 0;
	pid = &warm;

	process_point = 30;
	set_point = 40;
	p_gain = (float)(5.2);
	i_gain = (float)(0.77);
	d_gain = (float)(0.18);
	dead_band = 2;

	integral_val = (float)(0.01);
	printf("The values of Process point,Set point,P gain,I gain,D gain \n");
	printf("%6d %6d %4f %4f %4f\n", process_point, set_point, p_gain, i_gain, d_gain);
	printf("Enter the value of Process point\n");
	while (count <= 20)
	{
		scanf_s("%d",&process_point);
		pid_init(&warm,process_point,set_point);
		pid_tune(&warm,p_gain,i_gain,d_gain, dead_band);
		pid_setinting(&warm,0.0);
		pid_bumpless(&warm);
		printf("%f\n", process_point);
		//printf("\n%f%f%f%f", warm, process_point, set_point, p_gain);
		count++;
	}
}


