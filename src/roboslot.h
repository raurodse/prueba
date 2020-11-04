
#ifndef _ROBOSLOT_
#define _ROBOSLOT_

#include "robowidgets.h"

#include <lgi-1.0/widget.hpp>
#include <lgi-1.0/layer.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


#define ROBOSLOT_TYPE_INPUT	0x01
#define ROBOSLOT_TYPE_OUTPUT	0x02
#define ROBOSLOT_TYPE_CPU		0x03

#define ROBOSLOT_OUTPUT_A		0x01
#define ROBOSLOT_OUTPUT_B		0x02
#define ROBOSLOT_OUTPUT_C		0x03

#define ROBOSLOT_INPUT_1		0x4
#define ROBOSLOT_INPUT_2		0x5
#define ROBOSLOT_INPUT_3		0x6
#define ROBOSLOT_INPUT_C		0x7

#define ROBOSLOT_MODE_EASY	0x01
#define ROBOSLOT_MODE_NORMAL	0x02

#define ROBOSLOT_WIDGET_NONE			0x00
#define ROBOSLOT_WIDGET_BUTTON		0x01
#define ROBOSLOT_WIDGET_SLOT_BUTTON	0x02
#define ROBOSLOT_WIDGET_POWER_BUTTON	0x03
#define ROBOSLOT_WIDGET_LIGHT_INCREASE	0x04
#define ROBOSLOT_WIDGET_LIGHT_DECREASE	0x05
#define ROBOSLOT_WIDGET_LIGHT_MODE		0x06
#define ROBOSLOT_WIDGET_CLOCK_INCREASE	0x07
#define ROBOSLOT_WIDGET_CLOCK_DECREASE	0x08
#define ROBOSLOT_WIDGET_CLOCK_MODE	0x09

#define ROBOSLOT_POWER_1		0x01
#define ROBOSLOT_POWER_2		0x02
#define ROBOSLOT_POWER_3		0x03
#define ROBOSLOT_POWER_4		0x04
#define ROBOSLOT_POWER_5		0x05

#define ROBOSLOT_LIGHT_MODE_GT		0x00
#define ROBOSLOT_LIGHT_MODE_LT		0x01

#define ROBOSLOT_CLOCK_MODE_EQUAL		0x00
#define ROBOSLOT_CLOCK_MODE_DICE		0x01


namespace net
{
	namespace lliurex
	{
		namespace robolliurex
		{
			class RoboSlot
			{
				public:
					std::vector<Widget *> widgets;
					std::map<int,std::string> labels;
					std::map<int,std::string> powers;
					int type;
					int mode;
					int slot;
					unsigned int target_mask;
					int target;
					float x;
					int power;
				
					double clock_value;
					int light_value;
				
					int clock_mode;
					int light_mode;
				
					Label * lbl_clock;
					Label * lbl_light;
					Button * btn_power;
					Button * btn_slot;
					
					ImageButton * img_clock;
					ImageButton * img_light;
				
				
					RoboSlot(float x,int type,int mode,int slot,unsigned int target_mask);
					void Build(cairo_t * cairo);
				
					void CycleSlot();
					void CyclePower();
				
					void IncreaseClock();
					void DecreaseClock();
					
					void IncreaseLight();
					void DecreaseLight();
					
					void CycleClockMode();
					void CycleLightMode();
					
					static void Save(std::string path,std::vector<RoboSlot *> * slots, std::vector<int> * header);
					static void Load(std::string path,std::vector<RoboSlot *> * slots, std::vector<int> * header);
					
					
			};
			
			class CodeBuilder
			{
				public:
					std::stringstream code_stream;
					CodeBuilder(std::vector<RoboSlot *> * slots,bool run_single=true);
					void Save(std::string path);
			};
		}
	}
}

#endif