
#ifndef _ROBOMENUS_
#define _ROBOMENUS_

#include "robocore.h"
#include "robowidgets.h"
#include "rsrcmanager.h"
#include "roboslot.h"
#include "robopilot.h"

namespace net
{
	namespace lliurex
	{
		namespace robolliurex
		{
			class MainScreen: public RoboMenu
			{
			
				protected:
			
	
				Button * btn1;
				Button * btn2;
				Button * btn3;
				
				public:
				
				MainScreen();
				void OnDestroy(DestroyEvent * event);
				void OnMouseClick(Widget * widget,MouseClickEvent * event);
				void OnResize(ResizeEvent * event);
			};
			
			
			
			class SetupScreen: public RoboMenu
			{
				protected:
				
				Button * btn1;
				Button * btn2;
				Button * btn3;
				Button * btn4;
					
				public:
				
				SetupScreen();
				void OnMouseClick(Widget * widget,MouseClickEvent * event);
			};
			
			
			
			class PilotMenu: public RoboMenu
			{
				protected:
				
				Button * btn1;
				Button * btn2;
				Button * btn3;
				Button * btn4;
				Button * btn5;
				
				public:
				
				PilotMenu();
				void OnMouseClick(Widget * widget,MouseClickEvent * event);
			};
			
			
			
			class COMScreen: public RoboMenu
			{
				protected:
				
				int value;
	
				Switch *sw1;
				Switch *sw2;
				Switch *sw3;

				Button * btn1;
				
				public:
				
				COMScreen();
				void OnMouseClick(Widget * widget,MouseClickEvent * event);
			};
			
			
			
			class FirmwareScreen: public RoboMenu
			{
				protected:
				
				Label * lbl1;
				Button * btn1;
				Button * btn2;
				Image * img1;
				int frame;
				
				public:
				
				FirmwareScreen();
				void OnMouseClick(Widget * widget,MouseClickEvent * event);
				void OnMessage(Widget * widget, MessageEvent * event);
			};
			
			
			
			class TestScreen: public RoboMenu
			{
				protected:

				Label * lbl1;
				Image * img1;
				Button * btn1;
				Button * btn2;
				int frame;
				
				public:
				
				TestScreen();
				
				void OnMouseClick(Widget * widget,MouseClickEvent * event);
				void OnMessage(Widget * widget, MessageEvent * event);
			};
			
			
			class DropScreen: public RoboMenu
			{
				private:
				
				char * filename;
				int pilot_type;

				protected:

				Label * lbl1;

				Button * btn1;
				Button * btn2;
				
				public:
				
				DropScreen();
				void OnMouseClick(Widget * widget,MouseClickEvent * event);
				void OnMessage(Widget * widget, MessageEvent * event);
				void OnDndEnter(DndEnterEvent * event);
				void OnDndDrop(DndDropEvent * event);
				
			};
		}
	}
}


#endif
