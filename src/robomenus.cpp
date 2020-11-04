
#include "robolliurex.h"
#include "robomenus.h"
#include "robocore.h"

#include <gtk/gtk.h>

#include <iostream>
#include <fstream>

using namespace std;
using namespace net::lliurex::lgi;
using namespace net::lliurex::robolliurex;

/*
	*************************** MainScreen ***********************************
*/


MainScreen::MainScreen(): RoboMenu(T("Start"),0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_VERTICAL)
{
	name ="main_screen";
	btn1 = new Button(T("Program"));
	btn2 = new Button(T("Set up"));
	btn3 = new Button(T("Exit"));
	
	btn1->Init(RoboCore::GetCore()->window->cairo);
	btn2->Init(RoboCore::GetCore()->window->cairo);
	btn3->Init(RoboCore::GetCore()->window->cairo);
	
	Add(btn1);
	Add(btn2);
	Add(btn3);
	
}

void MainScreen::OnDestroy(DestroyEvent * event)
{
	Application::Quit();
}


void MainScreen::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn1)
	{
		Show("pilot_menu");
		Hide();
	}
	
	if(widget==btn2)
	{
		Show("setup_screen");
		Hide();
	}
	
	if(widget==btn3)
	{
		Application::Quit();
	}
}

	
void MainScreen::OnResize(ResizeEvent * event)
{

}


/*
	*************************** SetupScreen ***********************************
*/

SetupScreen::SetupScreen() : RoboMenu(T("Setup"),0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_VERTICAL)
{
	name="setup_screen";
	btn1 = new Button(T("Select COM port"));
	btn2 = new Button(T("Download firmware"));
	btn3 = new Button(T("Test communications"));
	btn4 = new Button(T("<-- Back"));
	
	btn1->Init(RoboCore::GetCore()->window->cairo);
	btn2->Init(RoboCore::GetCore()->window->cairo);
	btn3->Init(RoboCore::GetCore()->window->cairo);
	btn4->Init(RoboCore::GetCore()->window->cairo);
	
	Add(btn1);
	Add(btn2);
	Add(btn3);
	Add(btn4);
	
	Hide();
		
}

void SetupScreen::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn4)
	{
		Show("main_screen");
		Hide();
	}
	
	if(widget==btn1)
	{
		Show("com_screen");
		Hide();
	}
	
	if(widget==btn2)
	{
		Show("firmware_screen");
		Hide();
	}
	
	if(widget==btn3)
	{
		Show("test_screen");
		Hide();
	}
}


/*
	*************************** PilotMenu ***********************************
*/

PilotMenu::PilotMenu(): RoboMenu(T("Pilots"),0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_VERTICAL)
{
	name="pilot_menu";
	btn1 = new Button(T("Pilot 1"));
	btn2 = new Button(T("Pilot 2"));
	btn3 = new Button(T("Pilot 3"));
	btn4 = new Button(T("Pilot 4"));
	
	btn5 = new Button(T("<-- Back"));
	
	btn1->Init(RoboCore::GetCore()->window->cairo);
	btn2->Init(RoboCore::GetCore()->window->cairo);
	btn3->Init(RoboCore::GetCore()->window->cairo);
	btn4->Init(RoboCore::GetCore()->window->cairo);
	btn5->Init(RoboCore::GetCore()->window->cairo);
	
	Add(btn1);
	Add(btn2);
	Add(btn3);
	Add(btn4);
	Add(btn5);
			
	Hide();
	
}

void PilotMenu::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn1)
	{
		Show("pilot_1");
		Hide();
	}
	
	if(widget==btn2)
	{
		Show("pilot_2");
		Hide();
	}
	
	if(widget==btn3)
	{
		Show("pilot_3");
		Hide();
	}
	
	if(widget==btn4)
	{
		Show("pilot_4");
		Hide();
	}
	
	if(widget==btn5)
	{
		Show("main_screen");
		Hide();
	}

}




/*
	*************************** COMScreen ***********************************
*/

COMScreen::COMScreen(): RoboMenu(T("COM Selection"),0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_VERTICAL)
{
	value = RoboCore::GetCore()->comm_port;
	name="com_screen";
	sw1 = new Switch(T("COM 1"),&value,0);
	sw2 = new Switch(T("COM 2"),&value,1);
	sw3 = new Switch(T("USB"),&value,2);
	btn1 = new Button(T("<-- Back"));
	
	btn1->Init(RoboCore::GetCore()->window->cairo);
	sw1->Init(RoboCore::GetCore()->window->cairo);
	sw2->Init(RoboCore::GetCore()->window->cairo);
	sw3->Init(RoboCore::GetCore()->window->cairo);
	
	Add(sw1);
	Add(sw2);
	Add(sw3);
	Add(btn1);
	
			
	Hide();
	
}
		
	
	
void COMScreen::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn1)
	{
		RoboCore::GetCore()->comm_port=value;
		Show("setup_screen");
		Hide();
	}

}


/*
	*************************** FirmwareScreen ***********************************
*/

FirmwareScreen::FirmwareScreen(): RoboMenu(T("Download firmware"),0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_VERTICAL)
{
	name="firmware_screen";
	lbl1 = new Label(T("Place the brick in front of the tower, turn it on and press Download to begin the firmware update"));
	btn1 = new Button(T("Download"));
	btn2 = new Button(T("<-- Back"));
	img1 = new Image(RoboCore::GetCore()->rsrc->GetSurface("firm00.png"));
	
	frame=0;
	
	lbl1->Init(RoboCore::GetCore()->window->cairo);
	btn1->Init(RoboCore::GetCore()->window->cairo);
	btn2->Init(RoboCore::GetCore()->window->cairo);
	
	Add(lbl1);
	Add(btn1);
	Add(img1);
	Add(btn2);
	
	Hide();
	
}


void FirmwareScreen::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn1)
	{
		btn1->Enable(false);
		RoboCore::GetCore()->DownloadFirmware();
					
	}
	
	if(widget==btn2)
	{
		
		Show("setup_screen");
		Hide();
	}

}
	
void FirmwareScreen::OnMessage(Widget * widget, MessageEvent * event)
{
	if(event->msg->id==RBW_MSG_FIRM_STATUS)
	{
		int status = ((MessageDataInt *)event->msg->data["status"])->value;
		
		if(status==RBC_FIRM_STATUS_DOWNLOADING)
		{
			frame++;
			frame=frame%10;
			
			stringstream ss;
			
			ss<<"firm0"<<frame<<".png";
			
			img1->SetImage(RoboCore::GetCore()->rsrc->GetSurface(ss.str()));
		}
		
		if(status==RBC_FIRM_STATUS_COMPLETED)
		{
			img1->SetImage(RoboCore::GetCore()->rsrc->GetSurface("firm_ok.png"));
			btn1->Enable(true);
		}
		
		if(status==RBC_FIRM_STATUS_ERROR)
		{
			img1->SetImage(RoboCore::GetCore()->rsrc->GetSurface("firm_error.png"));
			btn1->Enable(true);
		}
	}
	
	RoboMenu::OnMessage(widget,event);
}



/*
	*************************** TestScreen ***********************************
*/

TestScreen::TestScreen(): RoboMenu(T("Test communications"),0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_VERTICAL)
{
	
	name="test_screen";
	frame=0;
	
	lbl1 = new Label(T("Place the brick in front of the tower, turn it on and press Start to test the communications"));
	btn1 = new Button(T("Start"));
	btn2 = new Button(T("<-- Back"));
	img1 = new Image(RoboCore::GetCore()->rsrc->GetSurface("firm00.png"));
	
	btn1->Init(RoboCore::GetCore()->window->cairo);
	lbl1->Init(RoboCore::GetCore()->window->cairo);
	btn2->Init(RoboCore::GetCore()->window->cairo);
	
	Add(lbl1);
	Add(btn1);
	Add(img1);
	Add(btn2);
			
	Hide();
	
}
		
	
	
void TestScreen::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn1)
	{
		RoboCore::GetCore()->TestComm();
		btn1->Enable(false);
	}
	
	if(widget==btn2)
	{
		Show("setup_screen");
		Hide();
	}

}
	
void TestScreen::OnMessage(Widget * widget, MessageEvent * event)
{
	if(event->msg->id==RBW_MSG_TEST_STATUS)
	{
		int status = ((MessageDataInt *)event->msg->data["status"])->value;
		
		if(status==RBC_TEST_STATUS_RUNNING)
		{
			frame++;
			frame=frame%10;
			
			stringstream ss;
			
			ss<<"firm0"<<frame<<".png";
			
			img1->SetImage(RoboCore::GetCore()->rsrc->GetSurface(ss.str()));
		}
		
		if(status==RBC_TEST_STATUS_OK)
		{
			img1->SetImage(RoboCore::GetCore()->rsrc->GetSurface("firm_ok.png"));
			btn1->Enable(true);
			RoboCore::GetCore()->GetBattery();
		}
		
		if(status==RBC_TEST_STATUS_ERROR)
		{
			img1->SetImage(RoboCore::GetCore()->rsrc->GetSurface("firm_error.png"));
			btn1->Enable(true);
		}
	}
	
	RoboMenu::OnMessage(widget,event);
}

/*
	*************************** DropScreen ***********************************
*/

DropScreen::DropScreen(): RoboMenu("Drop",0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_VERTICAL)
{
	
	name="drop_screen";
	
	lbl1 = new Label(T("Drop a valid Robolliurex file"));

	btn1 = new Button(T("Load"));
	btn2 = new Button(T("Cancel"));
	
	btn1->Enable(false);
	
	
	btn1->Init(RoboCore::GetCore()->window->cairo);
	lbl1->Init(RoboCore::GetCore()->window->cairo);
	btn2->Init(RoboCore::GetCore()->window->cairo);
	
	Add(lbl1);
	Add(btn1);
	Add(btn2);
			
	Hide();
	
}

void DropScreen::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn1)
	{
					
		clog<<"Trying to Load "<<filename<<" pilot "<<pilot_type<<endl;
		
		Message * msg = new Message(RBW_MSG_PILOT_LOAD);
		msg->data["path"]=new MessageDataString(filename);
		msg->data["pilot"]=new MessageDataInt(pilot_type);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
		
		Hide();
		
	}
	
	if(widget==btn2)
	{
		Show("main_screen");
		Hide();
	}

}

	
void DropScreen::OnMessage(Widget * widget, MessageEvent * event)
{
	
	RoboMenu::OnMessage(widget,event);
}

	
void DropScreen::OnDndEnter(DndEnterEvent * event)
{
	
	lbl1->SetText(T("Drop a valid Robolliurex file"));
	lbl1->Init(RoboCore::GetCore()->window->cairo);
	btn1->Enable(false);
	
	Show("drop_screen");
}
	
	
void DropScreen::OnDndDrop(DndDropEvent * event)
{
	
				
	string uri="";
	
	for(int n=0;n<event->size;n++)
	{
		char c = (char)event->data[n];
		
		if(c=='\r' || c=='\n')
			break;
		else
			uri=uri+c;
	}
	
		
		
	clog<<"uri:["<<uri<<"]"<<endl;
	
	filename=g_filename_from_uri(uri.c_str(),nullptr,nullptr);
	
					
	
	if(filename!=nullptr)
	{
		
		clog<<"filename:["<<filename<<"]"<<endl;
		/* trying to guess whenever is a valid file */
		fstream fs;
		fs.open (filename, std::fstream::in);
		
		char header[8];
		fs.read(header,5);
		
		fs.close();
		
		bool is_valid=false;
		
		if(header[0]=='1')/* robolliurex version 1 */
			if(header[1]==':')
				if(header[2]=='3' || header[2]=='4') /* pilot 3 or 4 */
				{
					
					is_valid=true;
				}
		
		
		if(is_valid)
		{
			pilot_type=header[2]-'0';
			
			lbl1->SetText(T("It seems a valid Robolliurex file"));
			lbl1->Init(RoboCore::GetCore()->window->cairo);
			
		}
		else
		{
			lbl1->SetText(T("Unknown file format"));
			lbl1->Init(RoboCore::GetCore()->window->cairo);
		}
		
		btn1->Enable(is_valid);		
		
	}
	else
	{
		clog<<"Failed to parse uri"<<endl;
		btn1->Enable(false);
	}
			
} 

