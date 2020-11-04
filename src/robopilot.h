
#ifndef _ROBOPILOT_
#define _ROBOPILOT_

#include <string>
#include <vector>
#include <map>

#include "robocore.h"
#include "robowidgets.h"
#include "rsrcmanager.h"
#include "roboslot.h"

#define RBW_DIALOG_LOAD	0x01
#define RBW_DIALOG_SAVE	0x02

namespace net
{
	namespace lliurex
	{
		namespace robolliurex
		{
			
			class ToolBox: public RoboMenu
			{
				public:
					ToolBox(float x,float y);
					~ToolBox();
				
					void Request(unsigned int target);
					void OnMouseClick(Widget * widget,MouseClickEvent * event);
			};
			
						
			class PilotScreen: public RoboMenu
			{
				public:
						
					std::vector<RoboSlot *> slots;
					RoboSlot * selected_slot;
					
					ToolBox * toolbox;
				
					
					PilotScreen();
					virtual ~PilotScreen();
					
					
					void Add(Widget * widget,float x,float y);
					void Draw(cairo_t * cairo);
					
					
					
			};
			
			class Pilot1: public PilotScreen
			{
				public:
					Label* lbl_title;
					Button* btn_back;
					Button* btn_run;
				
					Pilot1();
					
					void Build();
				
					void OnMouseClick(Widget * widget,MouseClickEvent * event);
					void Hide();
					void OnMessage(Widget * widget, MessageEvent * event);
			};
			
			class Pilot2: public PilotScreen
			{
				public:
					Label* lbl_title;
					Button* btn_back;
					Button* btn_run;
				
					Pilot2();
					
					void Build();
				
					void OnMouseClick(Widget * widget,MouseClickEvent * event);
					void Hide();
					void OnMessage(Widget * widget, MessageEvent * event);
			};
			
			class Pilot3: public PilotScreen
			{
				public:
					
					Label* lbl_title;
					Button* btn_back;
					Button* btn_run;
					ImageButton * btn_run_mode;
					Button * btn_load;
					Button * btn_save;
				
					bool run_single;
				
					Pilot3();
					
					void Build();
				
					void OnMouseClick(Widget * widget,MouseClickEvent * event);
					void Hide();
					void OnMessage(Widget * widget, MessageEvent * event);
				
			};
			
			class Pilot4: public PilotScreen
			{
				public:
					
					Label* lbl_title;
					Button* btn_back;
					Button* btn_run;
					ImageButton * btn_run_mode;
					Button * btn_load;
					Button * btn_save;
					Button * btn_add;
					Button * btn_remove;
					Button * btn_right;
					Button * btn_left;
					Label * lbl_step;
				
					int steps;
					int current_step;
					bool run_single;
				
					Pilot4();
					
					void Build();
				
					void OnMouseClick(Widget * widget,MouseClickEvent * event);
					void Hide();
					void OnMessage(Widget * widget, MessageEvent * event);
					void Draw(cairo_t * cairo);
					void UpdateButtons();
					
					
			};
			
			
		}
	}
}

#endif
