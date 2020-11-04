

#include "robocore.h"
#include "robomenus.h"
#include "robolliurex.h"


#include <lsf-1.0/system.hpp>
#include <lsf-1.0/filesystem.hpp>
#include <gtk/gtk.h>

#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <iomanip>

using namespace net::lliurex::robolliurex;
using namespace std;


/* 
	************* MainWindow ************
*/
MainWindow::MainWindow() : X11Window(1024,768,0)
{
	have_batt=false;
	batt=0.0f;
	
	srf_background = RoboCore::GetCore()->rsrc->GetSurface("blueprint.png");
	
	
}

void MainWindow::Flip()
{
	cairo_set_source_surface(cairo,srf_background,0,0);
	cairo_paint(cairo);
	
	cairo_text_extents_t te;
	cairo_font_extents_t fe;
	
	stringstream ss;
	ss<<"Version: "<<VERSION;
	
	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 11.0);
	cairo_text_extents (cairo, ss.str().c_str(), &te);
	cairo_font_extents (cairo, &fe);
	
	cairo_surface_t * target = cairo_get_target(cairo);
	float width = cairo_image_surface_get_width(target);
	float height = cairo_image_surface_get_height(target);
	
	
	
	cairo_move_to (cairo,5.0f,height-fe.height);
	cairo_set_source_rgb (cairo, 0.95, 0.95, 0.95);
	cairo_show_text (cairo, ss.str().c_str());	
	
	if(have_batt)
	{
		ss.str("");
		ss<<"Batt: "<<std::setprecision(2) << std::fixed<<batt<<" V";
				
		cairo_move_to (cairo,width-te.width-3.0f,fe.height+3.0f);
		cairo_set_source_rgb (cairo, 0.95, 0.95, 0.95);
		cairo_show_text (cairo, ss.str().c_str());
	}
		
	X11Window::Flip();
}


void MainWindow::SetBattery(float level)
{
	have_batt=true;
	batt=level;
}



RoboCore * RoboCore::singleton = nullptr;
string RoboCore::comm_name[]={"/dev/ttyS0","/dev/ttyS1","usb"};

RoboCore::RoboCore() : Application("net.lliurex.robolliurex")
{
	//set outselves as main application
	Application::Set(this);
	
	
	is_firmware_downloading=false;
	is_comm_testing=false;
	is_program_downloading=false;
	is_battery_requesting=false;
		
	
	
}



void RoboCore::Init()
{


	//load resources
	rsrc = new RsrcManager(RSRC_PATH); 

	/* guessing if usb tower is plugged */
	
	
	vector<string> modules;
	
	//ask lsf for current kernel modules
	modules=system::GetModuleList(); 
	
	usb_tower=false;
	
	//look for legousbtower
	for(int n=0;n<modules.size();n++) 
	{
		if(modules[n]=="legousbtower")
		{
			usb_tower=true;
		}
	}
	
	if(usb_tower)
	{
		clog<<"* Found Lego USB tower"<<endl;
		comm_port = RBC_PORT_USB;
		
		vector<string> towers = filesystem::List("/dev/usb/legousbtower*");
		
		if(towers.size()==0)
		{
			clog<<"* Warning, Lego driver is loaded but something failed!"<<endl;
		}
		else
		{
			string usbp="usb:"+towers[0];
			RoboCore::comm_name[comm_port]=usbp;
			clog<<"Using tower device: "<<towers[0]<<endl;
		}
		
	}
	else
	{
		clog<<"* Lego USB tower not found"<<endl;
		comm_port = RBC_PORT_COM1;
		clog<<"Using: "<<RoboCore::comm_name[comm_port]<<endl;
	}
	
	
	
	
	/* gui setup */
	
	gtk_init(0,nullptr); //gtk start up
	
	window = new MainWindow();
	AddWindow(window);
	
	
	//drag & drop setup
	vector<string>targets={"text/uri-list"};
	window->SetDndTargets(targets);
	
	window->SetTitle("Robolliurex");
	window->AddLayer(new MainScreen());
	window->AddLayer(new SetupScreen());
	window->AddLayer(new PilotMenu());
	window->AddLayer(new COMScreen());
	window->AddLayer(new FirmwareScreen());
	window->AddLayer(new TestScreen());
	window->AddLayer(new DropScreen());
	window->AddLayer(new Pilot1());
	window->AddLayer(new Pilot2());
	window->AddLayer(new Pilot3());
	window->AddLayer(new Pilot4());
}


RoboCore::~RoboCore()
{
	delete rsrc;
}

RoboCore * RoboCore::GetCore()
{
	if(RoboCore::singleton==nullptr)
	{
		RoboCore::singleton=new RoboCore();
	}
	
	return RoboCore::singleton;
}

void RoboCore::Destroy()
{
	if(RoboCore::singleton!=nullptr)delete RoboCore::singleton;
}

void * auxDownloadFirmwareBlink(void * param)
{
	
	while(RoboCore::GetCore()->is_firmware_downloading)
	{
		Message * msg = new Message(RBW_MSG_FIRM_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_FIRM_STATUS_DOWNLOADING);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
		usleep(150000);
	}
}

void * auxDownloadFirmware(void * param)
{
	
	/* nqc -Susb -firmware firm328.lgo */
	Message * msg;
	FILE * fp;
	char buff[32];
	int status;
		
	string cmd = string("nqc -S") + RoboCore::comm_name[RoboCore::GetCore()->comm_port] + " -firmware " + FIRM_PATH;
	clog<<cmd<<endl;
	fp = popen( cmd.c_str(),"r" );
	
	if(fp==nullptr)
	{
		msg = new Message(RBW_MSG_FIRM_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_FIRM_STATUS_ERROR);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
		
		return nullptr;
	}
	
	status = pclose(fp);
	
	RoboCore::GetCore()->is_firmware_downloading=false;
	
	if(status==0)
	{
		msg = new Message(RBW_MSG_FIRM_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_FIRM_STATUS_COMPLETED);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
	}
	else
	{
		msg = new Message(RBW_MSG_FIRM_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_FIRM_STATUS_ERROR);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
	}
	
	return nullptr;
}

void RoboCore::DownloadFirmware()
{
	if(!is_firmware_downloading)
	{
		is_firmware_downloading=true;
		
		pthread_t aux_thread;
		pthread_create(&aux_thread,nullptr,auxDownloadFirmware,nullptr);
		
		pthread_t blink_thread;
		pthread_create(&blink_thread,nullptr,auxDownloadFirmwareBlink,nullptr);
	
	}
}

void * auxTestCommBlink(void * param)
{
	while(RoboCore::GetCore()->is_comm_testing==true)
	{
		Message * msg = new Message(RBW_MSG_TEST_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_TEST_STATUS_RUNNING);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
		usleep(150000);
	}
}

void * auxTestComm(void * param)
{
	
	Message * msg;
	FILE * fp;
	char buff[32];
	int status;
	
	
	string cmd = string("nqc -S") + RoboCore::comm_name[RoboCore::GetCore()->comm_port] + " -raw 10";
	clog<<cmd<<endl;
	fp = popen( cmd.c_str(),"r" );
	
	if(fp==nullptr)
	{
		RoboCore::GetCore()->is_comm_testing=false;
		msg = new Message(RBW_MSG_TEST_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_TEST_STATUS_ERROR);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
		
		return nullptr;
	}
	
	while(fgets(buff, sizeof(buff), fp)!=nullptr)
	{
		
	}
	
	status = pclose(fp);
	
	if(status==0)
	{
		RoboCore::GetCore()->is_comm_testing=false;
		msg = new Message(RBW_MSG_TEST_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_TEST_STATUS_OK);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
	}
	else
	{
		RoboCore::GetCore()->is_comm_testing=false;
		msg = new Message(RBW_MSG_TEST_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_TEST_STATUS_ERROR);
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
	}
	
	return nullptr;
}

void RoboCore::TestComm()
{
	if(!is_comm_testing)
	{
		is_comm_testing=true;
		pthread_t aux_thread;
		pthread_create(&aux_thread,nullptr,auxTestComm,nullptr);
		
		pthread_t blink_thread;
		pthread_create(&blink_thread,nullptr,auxTestCommBlink,nullptr);
	}
}

void * auxDownloadProgram(void * param)
{
	Message * msg = new Message(RBW_MSG_RUN_STATUS);
	msg->data["status"]=new MessageDataInt(RBC_RUN_STATUS_DOWNLOADING); 
	RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
	
	FILE * fp;
	char buff[32];
	int status=0;
	
	
	string cmd = string("nqc -S") + RoboCore::comm_name[RoboCore::GetCore()->comm_port] + " -TRCX2 -d " + RoboCore::GetCore()->program_path;
	
	fp = popen( cmd.c_str(),"r" );
	
	if(fp==nullptr)
	{
		msg = new Message(RBW_MSG_RUN_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_RUN_STATUS_NQC_ERROR); 
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
		
		RoboCore::GetCore()->is_program_downloading=false;
		return nullptr;
	}
	
	while(fgets(buff, sizeof(buff), fp)!=nullptr)
	{
		clog << buff;
	}
	
	status=pclose(fp);
	
	if(status!=0)
	{
		msg = new Message(RBW_MSG_RUN_STATUS);
		msg->data["status"]=new MessageDataInt(RBC_RUN_STATUS_COMM_ERROR); 
		RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
		
		RoboCore::GetCore()->is_program_downloading=false;
		return nullptr;
	}
	
	msg = new Message(RBW_MSG_RUN_STATUS);
	msg->data["status"]=new MessageDataInt(RBC_RUN_STATUS_COMPLETED); 
	RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);
	

	RoboCore::GetCore()->is_program_downloading=false;
	
	RoboCore::GetCore()->GetBattery();
	
	return nullptr;
}

void RoboCore::DownloadProgram(string path)
{
	if(!is_program_downloading)
	{
		is_program_downloading=true;
		pthread_t aux_thread;
		program_path=path;
		pthread_create(&aux_thread,nullptr,auxDownloadProgram,nullptr);
	}
}


void * auxGetBattery(void * param)
{
	
	FILE * fp;
	char buff[32];
	int status=0;
		
	
	string cmd = string("nqc -S") + RoboCore::comm_name[RoboCore::GetCore()->comm_port] + " -raw 30";
		
	fp = popen( cmd.c_str(),"r" );
	
	if(fp==nullptr)
	{
		return nullptr;
	}
	
	while(fgets(buff, sizeof(buff), fp)!=nullptr)
	{
		clog << buff;
	}
	
	status=pclose(fp);
	
	if(status!=0)
	{
		return nullptr;
	}
	
	stringstream ss;
	
	int low,high;
	float batt;
	
	ss.str(buff);
	ss>>hex>>low>>high;
	
	batt=((high<<8) + low)/1000.0f;
	
	clog<<"Batt: "<<batt<<endl;
	
	Message * msg = new Message(RBW_MSG_BATTERY_STATUS);
	msg->data["value"]=new MessageDataFloat(batt); 
	RoboCore::GetCore()->window->SendMessage(nullptr,nullptr,msg);

	RoboCore::GetCore()->is_battery_requesting=false;
	
	return nullptr;
}

void RoboCore::GetBattery()
{
	if(!is_battery_requesting)
	{
		is_battery_requesting=true;
		pthread_t aux_thread;
		pthread_create(&aux_thread,nullptr,auxGetBattery,nullptr);
				
	}
}


int RoboCore::CustomEventsDispatch()
{
	int events = 0;
	
	while(gtk_events_pending())
	{
		events++;
		gtk_main_iteration();
	}
	
	return events;
	
}

void RoboCore::OnMessage(BaseWindow * window,Layer * layer, Widget * widget,MessageEvent * event)
{

	Message * msg = event->msg;
	
	//catch battery status messages
	if(msg->id==RBW_MSG_BATTERY_STATUS)
	{
		float value;
		
		value = (static_cast<MessageDataFloat *>(msg->data["value"]))->value;
		
		this->window->SetBattery(value);
	}
}
