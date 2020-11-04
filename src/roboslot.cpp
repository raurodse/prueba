
#include "robocore.h"
#include "rsrcmanager.h"
#include "roboslot.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;
using namespace net::lliurex::robolliurex;

int StringToInt(string value)
{
	stringstream is(value);
	int i;
	is>>i;
	
	return i;
}

float StringToFloat(string value)
{
	stringstream is(value);
	float f;
	is>>f;
	
	return f;
}

RoboSlot::RoboSlot(float x,int type,int mode,int slot,unsigned int target_mask)
{
	this->type=type;
	this->mode=mode;
	this->slot=slot;
	this->target_mask=target_mask;
	this->target=RBW_TARGET_NONE;
	this->x=x;
	
	labels[ROBOSLOT_OUTPUT_A]="A";
	labels[ROBOSLOT_OUTPUT_B]="B";
	labels[ROBOSLOT_OUTPUT_C]="C";
	labels[ROBOSLOT_INPUT_1]="1";
	labels[ROBOSLOT_INPUT_2]="2";
	labels[ROBOSLOT_INPUT_3]="3";
	labels[ROBOSLOT_INPUT_C]="CPU";
	powers[ROBOSLOT_POWER_1]="1";
	powers[ROBOSLOT_POWER_2]="2";
	powers[ROBOSLOT_POWER_3]="3";
	powers[ROBOSLOT_POWER_4]="4";
	powers[ROBOSLOT_POWER_5]="5";
	
	power=ROBOSLOT_POWER_1;
	
	clock_value=1.0f;
	light_value=50;
	
	clock_mode=ROBOSLOT_CLOCK_MODE_EQUAL;
	light_mode=ROBOSLOT_LIGHT_MODE_GT;
	
}

void RoboSlot::CycleSlot()
{
	if(slot==ROBOSLOT_INPUT_C)return;
		
	slot++;
	if(slot==ROBOSLOT_INPUT_C)slot=ROBOSLOT_INPUT_1;
	btn_slot->text=labels[slot];
	btn_slot->Init(RoboCore::GetCore()->window->cairo);
}

void RoboSlot::CyclePower()
{
	power++;
	if(power>ROBOSLOT_POWER_5)power=ROBOSLOT_POWER_1;
	btn_power->text=powers[power];
	btn_power->Init(RoboCore::GetCore()->window->cairo);
	
}

void RoboSlot::IncreaseClock()
{
	stringstream code_stream;
	
	clock_value+=0.10;
	code_stream<<clock_value;
	lbl_clock->SetText(code_stream.str());
	lbl_clock->Init(RoboCore::GetCore()->window->cairo);
}

void RoboSlot::DecreaseClock()
{
	stringstream code_stream;
	
	clock_value-=0.10;
		
	if(clock_value<=0.0)clock_value=0.0;
	
	code_stream<<clock_value;
	lbl_clock->SetText(code_stream.str());
	lbl_clock->Init(RoboCore::GetCore()->window->cairo);
}

void RoboSlot::IncreaseLight()
{
	light_value+=1;
	
	if(light_value>100)light_value=100;
	
	stringstream code_stream;
	
	code_stream<<light_value;
	lbl_light->SetText(code_stream.str());
	lbl_light->Init(RoboCore::GetCore()->window->cairo);
}

void RoboSlot::DecreaseLight()
{
	light_value-=1;
	
	if(light_value<0)light_value=0;
	
	stringstream code_stream;
	
	code_stream<<light_value;
	lbl_light->SetText(code_stream.str());
	lbl_light->Init(RoboCore::GetCore()->window->cairo);
}

void RoboSlot::CycleClockMode()
{
	clock_mode++;
	clock_mode=clock_mode%2;
	
	if(clock_mode==ROBOSLOT_CLOCK_MODE_EQUAL)
		img_clock->SetImage(RoboCore::GetCore()->rsrc->GetSurface("equal.png"));
	else
		img_clock->SetImage(RoboCore::GetCore()->rsrc->GetSurface("dice.png"));
}

void RoboSlot::CycleLightMode()
{
	light_mode++;
	light_mode=light_mode%2;
	
	if(light_mode==ROBOSLOT_LIGHT_MODE_LT)
		img_light->SetImage(RoboCore::GetCore()->rsrc->GetSurface("less_than.png"));
	else
		img_light->SetImage(RoboCore::GetCore()->rsrc->GetSurface("great_than.png"));
}


void RoboSlot::Build(cairo_t * cairo)
{
	bool power_button=false;
	
	for(int n=0;n<widgets.size();n++)
	{
		delete widgets[n];
	}
	widgets.clear();
	
		
	
	Label * lbl;
	
	ImageButton * btn;
	cairo_surface_t * surface;
	
	switch(target)
	{
		case RBW_TARGET_NONE:
			surface = RoboCore::GetCore()->rsrc->GetSurface("none.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_STOP:
			surface = RoboCore::GetCore()->rsrc->GetSurface("stop.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_MOTOR_FORWARD:
			surface = RoboCore::GetCore()->rsrc->GetSurface("engine_forward.png");
			btn = new ImageButton(surface);
			power_button=true;
		break;
		
		case RBW_TARGET_MOTOR_BACKWARD:
			surface = RoboCore::GetCore()->rsrc->GetSurface("engine_backward.png");
			btn = new ImageButton(surface);
			power_button=true;
		break;
		
		case RBW_TARGET_LIGHT:
			surface = RoboCore::GetCore()->rsrc->GetSurface("light.png");
			btn = new ImageButton(surface);
			power_button=true;
		break;
		
		case RBW_TARGET_CLOCK:
			slot=ROBOSLOT_INPUT_C;
			surface = RoboCore::GetCore()->rsrc->GetSurface("clock.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_CLOCK_1S:
			slot=ROBOSLOT_INPUT_C;
			surface = RoboCore::GetCore()->rsrc->GetSurface("clock_1s.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_CLOCK_2S:
			slot=ROBOSLOT_INPUT_C;
			surface = RoboCore::GetCore()->rsrc->GetSurface("clock_2s.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_CLOCK_4S:
			slot=ROBOSLOT_INPUT_C;
			surface = RoboCore::GetCore()->rsrc->GetSurface("clock_4s.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_CLOCK_6S:
			slot=ROBOSLOT_INPUT_C;
			surface = RoboCore::GetCore()->rsrc->GetSurface("clock_6s.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_CLOCK_8S:
			slot=ROBOSLOT_INPUT_C;
			surface = RoboCore::GetCore()->rsrc->GetSurface("clock_8s.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_CLOCK_10S:
			slot=ROBOSLOT_INPUT_C;
			surface = RoboCore::GetCore()->rsrc->GetSurface("clock_10s.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_PRESS_ACTIVE:
			slot=(slot==ROBOSLOT_INPUT_C) ? ROBOSLOT_INPUT_1 : slot;
			surface = RoboCore::GetCore()->rsrc->GetSurface("press_sensor_active.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_PRESS_RELEASE:
			slot=(slot==ROBOSLOT_INPUT_C) ? ROBOSLOT_INPUT_1 : slot;
			surface = RoboCore::GetCore()->rsrc->GetSurface("press_sensor_release.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_LIGHT_WHITE:
			slot=(slot==ROBOSLOT_INPUT_C) ? ROBOSLOT_INPUT_1 : slot;
			surface = RoboCore::GetCore()->rsrc->GetSurface("light_sensor_white.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_LIGHT_BLACK:
			slot=(slot==ROBOSLOT_INPUT_C) ? ROBOSLOT_INPUT_1 : slot;
			surface = RoboCore::GetCore()->rsrc->GetSurface("light_sensor_black.png");
			btn = new ImageButton(surface);
		break;
		
		case RBW_TARGET_LIGHT_SENSOR:
			slot=(slot==ROBOSLOT_INPUT_C) ? ROBOSLOT_INPUT_1 : slot;
			surface = RoboCore::GetCore()->rsrc->GetSurface("light_sensor.png");
			btn = new ImageButton(surface);
		break;
		
		default:
			break;
			
	}
	
	if(mode==ROBOSLOT_MODE_NORMAL && type==ROBOSLOT_TYPE_INPUT)
	{
		Button * sltbtn=new Button(labels[slot]);
		sltbtn->tag=ROBOSLOT_WIDGET_SLOT_BUTTON<<8 | 40;
		sltbtn->Init(cairo);
		btn_slot=sltbtn;
		btn->tag=ROBOSLOT_WIDGET_BUTTON<<8 | 50;
		
		widgets.push_back(sltbtn);
		widgets.push_back(btn);

	}
	else
	{
		lbl=new Label(labels[slot]);
		lbl->tag=ROBOSLOT_WIDGET_NONE<<8 | 40;
		lbl->Init(cairo);
		btn->tag=ROBOSLOT_WIDGET_BUTTON<<8 | 50;
		
		widgets.push_back(lbl);
		widgets.push_back(btn);
	}
	
	if(power_button && mode==ROBOSLOT_MODE_NORMAL)
	{
		Button * pwrbtn = new Button(powers[power]);
		pwrbtn->tag=ROBOSLOT_WIDGET_POWER_BUTTON<<8 | 60;
		pwrbtn->Init(cairo);
		btn_power=pwrbtn;
		widgets.push_back(pwrbtn);
	}
	
	if(target==RBW_TARGET_LIGHT_SENSOR)
	{
		ImageButton * img;
		stringstream code_stream;
		
		img = new ImageButton( RoboCore::GetCore()->rsrc->GetSurface("plus.png"));
		img->tag=ROBOSLOT_WIDGET_LIGHT_INCREASE<<8 | 60;
		widgets.push_back(img);
		code_stream<<light_value;
		lbl = new Label(code_stream.str());
		lbl->tag=ROBOSLOT_WIDGET_NONE<<8 | 65;
		lbl->Init(cairo);
		lbl_light=lbl;
		widgets.push_back(lbl);
		img = new ImageButton( RoboCore::GetCore()->rsrc->GetSurface("minus.png"));
		img->tag=ROBOSLOT_WIDGET_LIGHT_DECREASE<<8 | 70;
		widgets.push_back(img);
		
		if(clock_mode==ROBOSLOT_LIGHT_MODE_LT)
			surface=RoboCore::GetCore()->rsrc->GetSurface("less_than.png");
		else
			surface=RoboCore::GetCore()->rsrc->GetSurface("great_than.png");
		
		img = new ImageButton(surface);
		img->tag=ROBOSLOT_WIDGET_LIGHT_MODE<<8 | 78;
		img_light=img;
		widgets.push_back(img);
	}
	
	if(target==RBW_TARGET_CLOCK)
	{
		ImageButton * img;
		stringstream code_stream;
		
		img = new ImageButton( RoboCore::GetCore()->rsrc->GetSurface("plus.png"));
		img->tag=ROBOSLOT_WIDGET_CLOCK_INCREASE<<8 | 60;
		widgets.push_back(img);
		code_stream<<clock_value;
		lbl = new Label(code_stream.str());
		lbl->tag=ROBOSLOT_WIDGET_NONE<<8 | 65;
		lbl->Init(cairo);
		lbl_clock=lbl;
		widgets.push_back(lbl);
		img = new ImageButton( RoboCore::GetCore()->rsrc->GetSurface("minus.png"));
		img->tag=ROBOSLOT_WIDGET_CLOCK_DECREASE<<8 | 70;
		widgets.push_back(img);
		
		
		if(clock_mode==ROBOSLOT_CLOCK_MODE_EQUAL)
			surface=RoboCore::GetCore()->rsrc->GetSurface("equal.png");
		else
			surface=RoboCore::GetCore()->rsrc->GetSurface("dice.png");
		
		img = new ImageButton( surface);
		
		img->tag=ROBOSLOT_WIDGET_CLOCK_MODE<<8 | 78;
		img_clock=img;
		widgets.push_back(img);
	}
}


void RoboSlot::Save(string path,vector<RoboSlot *> * slots, vector<int> * header)
{
		
	fstream fs;
	
	fs.open (path.c_str(), std::fstream::out);
	
	/* header write */
	for(int n=0;n<header->size()-1;n++)
	{
		fs<<header->at(n)<<":";
	}
	fs<<header->at(header->size()-1)<<endl;
	
	/* slots */
	for(int n=0;n<slots->size();n++)
	{
		
		fs<<slots->at(n)->x<<":"<<slots->at(n)->type<<":"<<slots->at(n)->mode<<":"<<slots->at(n)->slot<<":"<<slots->at(n)->target_mask<<":"<<slots->at(n)->target<<":"<<slots->at(n)->power<<":"<<slots->at(n)->clock_value<<":"<<slots->at(n)->light_value<<":"<<slots->at(n)->clock_mode<<":"<<slots->at(n)->light_mode<<endl;
	}
	
	fs.close();
	
}

void RoboSlot::Load(string path,vector<RoboSlot *> * slots,vector<int> * header)
{
	fstream fs;
		
	fs.open (path.c_str(), std::fstream::in);
	
	slots->clear();
	bool headers=true;
	
	while(!fs.eof())
	{
		float x;
		int type;
		int mode;
		int slot;
		unsigned int target_mask;
		unsigned int target;
		int power;
		int clock_value;
		int light_value;
		int clock_mode;
		int light_mode;
		
		char buf[128];
		
		
		fs.getline(buf,128,'\n');
		
		vector<string> elems;
		stringstream ss(buf);
		string item;
		
		
		while (std::getline(ss, item,':'))
		{
			elems.push_back(item);
		}
		
		if(headers)
		{
			for(int n=0;n<elems.size();n++)
			{
				int nh = StringToInt(elems[n]);
				header->push_back(nh);
			}
			headers=false;
		}
		else
		{
			if(elems.size()==11)
			{
							
				x=StringToFloat(elems[0]);
							
				type=StringToInt(elems[1]);
				mode=StringToInt(elems[2]);
				slot=StringToInt(elems[3]);
				target_mask=(unsigned int)StringToInt(elems[4]);
				target=(unsigned int)StringToInt(elems[5]);
				power=StringToInt(elems[6]);
				clock_value=StringToInt(elems[7]);
				light_value=StringToInt(elems[8]);
				clock_mode=StringToInt(elems[9]);
				light_mode=StringToInt(elems[10]);
				
				RoboSlot * rs = new RoboSlot(x,type,mode,slot,target_mask);
				rs->target=target;
				rs->power=power;
				rs->clock_value=clock_value;
				rs->light_value=light_value;
				rs->clock_mode=clock_mode;
				rs->light_mode=light_mode;
				
				slots->push_back(rs);
				
			}
		}
			
		
	}
	
	
	fs.close();
}

CodeBuilder::CodeBuilder(vector<RoboSlot *> * slots,bool run_single)
{
	vector<RoboSlot *>::iterator it;
	RoboSlot * slot;
	
	/* clear */
	code_stream.str("");
	
	code_stream<<"/* RoboLliurex generated code */\n";
	code_stream<<"\n";
	code_stream<<"task main (){\n";
	code_stream<<"int tmp_sensor;\n";
	
	
	if(!run_single)
	{
		code_stream<<"while(1){\n";
	}
	
	for(it=slots->begin();it!=slots->end();it++)
	{
		slot=*it;
		 
		if(slot->type==ROBOSLOT_TYPE_OUTPUT)
		{
			string out_port;
			switch(slot->slot)
			{
				case ROBOSLOT_OUTPUT_A:
					out_port="OUT_A";
				break;
				
				case ROBOSLOT_OUTPUT_B:
					out_port="OUT_B";
				break;
				
				case ROBOSLOT_OUTPUT_C:
					out_port="OUT_C";
				break;
			}
			switch(slot->target)
			{
				
				case RBW_TARGET_STOP:
					code_stream<<"SetOutput("<<out_port<<",OUT_OFF);\n";
				break;
				
				case RBW_TARGET_MOTOR_FORWARD:
					code_stream<<"SetOutput("<<out_port<<",OUT_ON);\n";
					code_stream<<"SetPower("<<out_port<<","<<slot->power<<");\n";
					code_stream<<"SetDirection("<<out_port<<",OUT_FWD);\n";
				break;
				
				case RBW_TARGET_MOTOR_BACKWARD:
					code_stream<<"SetOutput("<<out_port<<",OUT_ON);\n";
					code_stream<<"SetPower("<<out_port<<","<<slot->power<<");\n";
					code_stream<<"SetDirection("<<out_port<<",OUT_REV);\n";
				break;
				
				case RBW_TARGET_LIGHT:
					code_stream<<"SetOutput("<<out_port<<",OUT_ON);\n";
					code_stream<<"SetPower("<<out_port<<","<<slot->power<<");\n";
					code_stream<<"SetDirection("<<out_port<<",OUT_FWD);\n";
				break;
			}
		}
		
		if(slot->type==ROBOSLOT_TYPE_INPUT)
		{
			string in_port;
			
			switch(slot->slot)
			{
				case ROBOSLOT_INPUT_1:
					in_port="SENSOR_1";
				break;
				
				case ROBOSLOT_INPUT_2:
					in_port="SENSOR_2";
				break;
				
				case ROBOSLOT_INPUT_3:
					in_port="SENSOR_3";
				break;
			}
			
			switch(slot->target)
			{
				case RBW_TARGET_PRESS_ACTIVE:
					code_stream<<"SetSensorType("<<in_port<<",SENSOR_TYPE_TOUCH);\n";
					code_stream<<"SetSensorMode("<<in_port<<",SENSOR_MODE_BOOL);\n";
					
					code_stream<<"while(!"<<in_port<<"){\n";
					code_stream<<"}\n";
					
					
				break;
				
				case RBW_TARGET_PRESS_RELEASE:
					code_stream<<"SetSensorType("<<in_port<<",SENSOR_TYPE_TOUCH);\n";
					code_stream<<"SetSensorMode("<<in_port<<",SENSOR_MODE_BOOL);\n";
					
					code_stream<<"while("<<in_port<<"){\n";
					code_stream<<"}\n";
					
					
				break;
								
				
				case RBW_TARGET_LIGHT_SENSOR:
					//code_stream<<"SetSensor("<<in_port<<",SENSOR_LIGHT);\n";
					code_stream<<"SetSensorType("<<in_port<<",SENSOR_TYPE_LIGHT);\n";
					code_stream<<"SetSensorMode("<<in_port<<",SENSOR_MODE_PERCENT);\n";
					
					if(slot->light_mode==ROBOSLOT_LIGHT_MODE_GT)
						code_stream<<"while(!("<<in_port<<">"<<slot->light_value-5<<")){\n";
					
					if(slot->light_mode==ROBOSLOT_LIGHT_MODE_LT)
						code_stream<<"while(!("<<in_port<<"<"<<slot->light_value+5<<")){\n";
					
					code_stream<<"}\n";
				break;
					
				case RBW_TARGET_LIGHT_WHITE:
					code_stream<<"SetSensor("<<in_port<<",SENSOR_LIGHT);\n";
					code_stream<<"tmp_sensor="<<in_port<<";\n";
					code_stream<<"while("<<in_port<<"<tmp_sensor+5){\n";
					code_stream<<"}\n";
				break;
				
				case RBW_TARGET_LIGHT_BLACK:
					code_stream<<"SetSensor("<<in_port<<",SENSOR_LIGHT);\n";
					code_stream<<"tmp_sensor="<<in_port<<";\n";
					code_stream<<"while("<<in_port<<">tmp_sensor-5){\n";
					code_stream<<"}\n";
				break;
				
				case RBW_TARGET_CLOCK:
					if(slot->clock_mode==ROBOSLOT_CLOCK_MODE_EQUAL)
					{
						code_stream<<"Wait("<<(int)(slot->clock_value*100.0f)<<");\n";
					}
					
					if(slot->clock_mode==ROBOSLOT_CLOCK_MODE_DICE)
					{
						code_stream<<"Wait(Random(1000));\n";
					}
				break;
				
				case RBW_TARGET_CLOCK_1S:
					code_stream<<"Wait(100);\n";
				break;
				
				case RBW_TARGET_CLOCK_2S:
					code_stream<<"Wait(200);\n";
				break;
				
				case RBW_TARGET_CLOCK_4S:
					code_stream<<"Wait(400);\n";
				break;
				
				case RBW_TARGET_CLOCK_6S:
					code_stream<<"Wait(600);\n";
				break;
				
				case RBW_TARGET_CLOCK_8S:
					code_stream<<"Wait(800);\n";
				break;
				
				case RBW_TARGET_CLOCK_10S:
					code_stream<<"Wait(1000);\n";
				break;
			}
		}
		
			
	}
	
	if(!run_single)
	{
		code_stream<<"}\n";
	}
	
	code_stream<<"Off(OUT_A);\n";
	code_stream<<"Off(OUT_B);\n";
	code_stream<<"Off(OUT_C);\n";
	code_stream<<"}";
	
	clog<<code_stream.str();
}

void CodeBuilder::Save(string path)
{
	fstream fout;
	
	fout.open(path.c_str(),fstream::out);
	fout<<code_stream.str();
	fout.close();
}
