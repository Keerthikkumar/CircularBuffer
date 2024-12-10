/*
 ============================================================================
 Name        : Circular_Buffer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 50



typedef struct {
  float Mag[3];  /* Magnetometer sensor output [uT] */
  int TimeStamp; /* Timestamp [ms] */
} MMC_Input_t;

typedef struct _Ring_Buffer_
{
  MMC_Input_t MMC_data[MAX_BUFFER_SIZE];
  int Head;
  int Last;
  int Intex_Buf_Size;
  struct Ring_Buffer *node;

}Ring_Buffer;

int Write_Buffer(Ring_Buffer *RB_data,MMC_Input_t MMC_Value)
{
	int Ret = 1;
	RB_data->MMC_data[RB_data->Head] = MMC_Value;

	RB_data->Head = ((RB_data->Head + 1)%MAX_BUFFER_SIZE);
	if(RB_data->Intex_Buf_Size < MAX_BUFFER_SIZE)
	{
		RB_data->Intex_Buf_Size++;
	}
	else
	{
		RB_data->Last = ((RB_data->Last + 1)%MAX_BUFFER_SIZE);
	}

	printf("Write BUffer Data : [ %f %f %f ]\n",MMC_Value.Mag[0],MMC_Value.Mag[1],MMC_Value.Mag[2]);
//	MMC_Input_t data_in[MAX_BUFFER_SIZE];

//	if((index+1 % MAX_BUFFER_SIZE) == 0) return Ret = 1;
	return Ret = 0;
}

int Read_Buffer(Ring_Buffer *RB_READ_data,int Data_Index)
{
	int Ret = 1;

	printf("Read BUffer Data : [ %f %f %f ]\n",RB_READ_data->MMC_data[Data_Index].Mag[0],
												RB_READ_data->MMC_data[Data_Index].Mag[1],
												RB_READ_data->MMC_data[Data_Index].Mag[2]);

	return Ret = 0;
}


int main(void) {
	Ring_Buffer MMC_RB_Data;

	MMC_RB_Data.Head = 0;
	MMC_RB_Data.Last = 0;
	MMC_RB_Data.Intex_Buf_Size = 0;


	int NoOfSamples = 0;

	MMC_Input_t data_in[] =
	{
		{-90.300003,3.600000,46.799999,0},
		{-84.300003,9.600000,44.500000,20},
		{-74.199997,13.000000,35.099998,40},
		{-63.700001,19.299999,30.100000,60},
		{-56.400002,20.700001,30.600000,80},
		{-52.299999,21.900000,30.100000,100},
		{-53.500000,18.700001,21.700001,120},
		{-53.099998,11.200000,10.500000,140},
		{-52.000000,0.300000,3.900000,160},
		{-49.299999,-8.100000,2.500000,180},
		{-46.200001,-12.600000,1.200000,200},
		{-45.599998,-9.000000,0.700000,220},
		{-53.400002,-0.100000,4.000000,240},
		{-64.800003,6.300000,14.500000,260},
		{-72.900002,8.400000,24.900000,280},
		{-78.699997,5.500000,39.099998,300},
		{-78.400002,-0.300000,50.799999,320},
		{-75.900002,-8.500000,59.500000,340},
		{-69.900002,-16.799999,68.500000,360},
		{-58.900002,-25.200001,72.000000,380},
		{-49.500000,-36.000000,69.000000,400},
		{-40.599998,-42.099998,64.199997,420},
		{-33.299999,-44.799999,59.400002,440},
		{-28.299999,-44.099998,55.799999,460},
		{-20.100000,-40.299999,54.000000,480},
		{-15.900000,-36.400002,51.000000,500},
		{-10.800000,-29.200001,51.000000,520},
		{-8.200000,-18.700001,52.799999,540},
		{-7.600000,-8.200000,52.500000,560},
		{-10.200000,1.000000,48.400002,580},
		{-15.600000,9.900000,41.799999,600},
		{-21.299999,14.800000,33.099998,620},
		{-28.200001,15.400000,22.500000,640},
		{-36.599998,13.000000,13.900000,660},
		{-43.599998,8.200000,7.300000,680},
		{-49.299999,-0.400000,2.500000,700},
		{-52.500000,-11.200000,1.500000,720},
		{-52.200001,-19.000000,1.200000,740},
		{-51.000000,-26.700001,2.400000,760},
		{-47.700001,-30.900000,4.000000,780},
		{-41.500000,-31.200001,3.000000,800},
		{-38.700001,-29.200001,3.700000,820},
		{-41.700001,-23.200001,2.100000,840},
		{-48.000000,-18.100000,1.300000,860},
		{-58.500000,-12.600000,3.100000,880},
		{-65.500000,-7.200000,8.200000,900},
		{-73.199997,-3.600000,14.500000,920},
		{-78.599998,-1.900000,25.200001,940},
		{-80.400002,0.100000,36.400002,960},
		{-81.000000,-3.900000,46.500000,980}

	};

	NoOfSamples = sizeof(data_in) / sizeof(MMC_Input_t);

	printf("No of Sample Size : %d\n",NoOfSamples);
	printf("Buffer Size : %ld MMC Buffer Size : %ld\n",sizeof(Ring_Buffer),sizeof(data_in));


	int Data_Index = 0;
	int Read_Flag = 0;
	while(1)
	{
		Write_Buffer(&MMC_RB_Data,data_in[Data_Index]);
		Data_Index++;
		Read_Flag++;
		if(Read_Flag > MAX_BUFFER_SIZE)
		{
			if(Data_Index > MAX_BUFFER_SIZE)
				Data_Index = 0;
			Read_Buffer(&MMC_RB_Data,Data_Index);
		}

		sleep(1);
	}
	return EXIT_SUCCESS;
}
