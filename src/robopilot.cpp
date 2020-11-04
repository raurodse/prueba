

#include "robopilot.h"
#include <lsf-1.0/filesystem.hpp>

#include <gtk/gtk.h>

#include <libintl.h>
#include <locale.h>
#include <sstream>

#define T(String) gettext(String)

using namespace std;
using namespace net::lliurex;
using namespace net::lliurex::robolliurex;


ToolBox::ToolBox(float x,float y):RoboMenu("Toolbox",x,y,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_HORITZONTAL) 
{
	//custom color
	color_fill[3]=0.90f;
	SetDepth( LGI_LAYER_DEPTH_TOP);
}

ToolBox::~ToolBox()
{
	
}

void ToolBox::Request(unsigned int target)
{
	ImageButton * img;
			
	for(int n=0;n<widgets.size();n++)
	{
		delete widgets[n];
	}
	widgets.clear();
	
	if(target & RBW_TARGET_STOP)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("stop.png"));
		img->tag=RBW_TARGET_STOP;
		Add(img);
	}
	
	if(target & RBW_TARGET_LIGHT)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("light.png"));
		img->tag=RBW_TARGET_LIGHT;
		Add(img);
	}
	
	if(target & RBW_TARGET_MOTOR_FORWARD)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("engine_forward.png"));
		img->tag=RBW_TARGET_MOTOR_FORWARD;
		Add(img);
	}
	
	if(target & RBW_TARGET_MOTOR_BACKWARD)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("engine_backward.png"));
		img->tag=RBW_TARGET_MOTOR_BACKWARD;
		Add(img);
	}
	
	if(target & RBW_TARGET_PRESS_RELEASE)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("press_sensor_release.png"));
		img->tag=RBW_TARGET_PRESS_RELEASE;
		Add(img);
	}
	
	if(target & RBW_TARGET_PRESS_ACTIVE)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("press_sensor_active.png"));
		img->tag=RBW_TARGET_PRESS_ACTIVE;
		Add(img);
	}
	
	if(target & RBW_TARGET_LIGHT_SENSOR)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("light_sensor.png"));
		img->tag=RBW_TARGET_LIGHT_SENSOR;
		Add(img);
	}
	
	if(target & RBW_TARGET_CLOCK)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("clock.png"));
		img->tag=RBW_TARGET_CLOCK;
		Add(img);
	}
	
	if(target & RBW_TARGET_CLOCK_1S)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("clock_1s.png"));
		img->tag=RBW_TARGET_CLOCK_1S;
		Add(img);
	}
	
	if(target & RBW_TARGET_CLOCK_2S)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("clock_2s.png"));
		img->tag=RBW_TARGET_CLOCK_2S;
		Add(img);
	}
	
	if(target & RBW_TARGET_CLOCK_4S)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("clock_4s.png"));
		img->tag=RBW_TARGET_CLOCK_4S;
		Add(img);
	}
	
	if(target & RBW_TARGET_CLOCK_6S)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("clock_6s.png"));
		img->tag=RBW_TARGET_CLOCK_6S;
		Add(img);
	}
	
	if(target & RBW_TARGET_CLOCK_8S)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("clock_8s.png"));
		img->tag=RBW_TARGET_CLOCK_8S;
		Add(img);
	}
	
	if(target & RBW_TARGET_CLOCK_10S)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("clock_10s.png"));
		img->tag=RBW_TARGET_CLOCK_10S;
		Add(img);
	}
	
	if(target & RBW_TARGET_LIGHT_WHITE)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("light_sensor_white.png"));
		img->tag=RBW_TARGET_LIGHT_WHITE;
		Add(img);
	}
	
	if(target & RBW_TARGET_LIGHT_BLACK)
	{
		img = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("light_sensor_black.png"));
		img->tag=RBW_TARGET_LIGHT_BLACK;
		Add(img);
	}
	Show();
}


void ToolBox::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget!=NULL)
	{
		Message * msg = new Message(RBW_MSG_TOOLBOX_RET);
		msg->data["target"]=new MessageDataInt(widget->tag);
			
		RoboCore::GetCore()->window->SendMessage(NULL,NULL,msg);
		
		Hide();
	}
}



PilotScreen::PilotScreen():RoboMenu("PilotScreen",0.5,0.5,RBW_POSITION_FACTOR,RBW_DISTRIBUTION_FACTOR)
{

}



PilotScreen::~PilotScreen()
{
	for(int n=0;n<slots.size();n++)
	{
		delete slots[n];
	}
}



void PilotScreen::Add(Widget * widget,float x,float y)
{
	RPoint p;
	p.x=x;
	p.y=y;
	RoboMenu::Add(widget);
	points[widget]=p;
}
		


void PilotScreen::Draw(cairo_t * cairo)
{
	//predrawing operations
	float s_width,s_height;
	float w,h;
	
	cairo_surface_t * srf;
	
	
	srf = cairo_get_target(cairo);
	s_width=cairo_image_surface_get_width(srf);
	s_height=cairo_image_surface_get_height(srf);
	
	
	cairo_set_line_width(cairo,4.0f);
	cairo_set_source_rgb(cairo, 0.96, 0.62, 0.11);
	cairo_move_to(cairo,s_width*0.05f,s_height*0.5f);
	cairo_line_to(cairo,s_width*0.95f,s_height*0.5f);
	cairo_stroke(cairo);
	
	srf = RoboCore::GetCore()->rsrc->GetSurface("semaphore_green.png");
	w = cairo_image_surface_get_width(srf);
	h = cairo_image_surface_get_height(srf);
	cairo_set_source_surface(cairo,srf,(s_width*0.05f)-(w/2.0f),(s_height*0.5f)-(h/2.0f));
	cairo_paint(cairo);
	
	srf = RoboCore::GetCore()->rsrc->GetSurface("semaphore_red.png");
	w = cairo_image_surface_get_width(srf);
	h = cairo_image_surface_get_height(srf);
	cairo_set_source_surface(cairo,srf,(s_width*0.95f)-(w/2.0f),(s_height*0.5f)-(h/2.0f));
	cairo_paint(cairo);
	
	RoboMenu::Draw(cairo);
}

		



Pilot1::Pilot1()
{
	label="Pilot 1";
	name="pilot_1";
	
	RoboSlot * slot;
	slot = new RoboSlot(0.4f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_EASY,ROBOSLOT_OUTPUT_A,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD);
	slots.push_back(slot);
	slot = new RoboSlot(0.6f,ROBOSLOT_TYPE_INPUT,ROBOSLOT_MODE_EASY,ROBOSLOT_INPUT_C ,RBW_TARGET_CLOCK_1S | RBW_TARGET_CLOCK_2S | RBW_TARGET_CLOCK_4S | RBW_TARGET_CLOCK_6S | RBW_TARGET_CLOCK_8S | RBW_TARGET_CLOCK_10S);
	slots.push_back(slot);
	
	lbl_title = new Label(label);
	lbl_title->Init(RoboCore::GetCore()->window->cairo);			
	btn_back = new Button(T("<-- Back"));
	btn_back->Init(RoboCore::GetCore()->window->cairo);
	btn_run = new Button(T("Run >"));
	btn_run->Init(RoboCore::GetCore()->window->cairo);
		
	selected_slot=NULL;
	
	Build();
	
	toolbox = new ToolBox(0.5f,0.2f);
	RoboCore::GetCore()->window->AddLayer(toolbox);
	
	Hide();
	
	
}

void Pilot1::Build()
{
	widgets.clear();
	points.clear();
	
	Add(lbl_title,0.5f,0.05f);
	Add(btn_back,0.4f,0.90f);
	Add(btn_run,0.6f,0.90f);
	
	for(int n=0;n<slots.size();n++)
	{
		slots[n]->Build(RoboCore::GetCore()->window->cairo);
	}
	
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			Add(slots[n]->widgets[m],slots[n]->x,(slots[n]->widgets[m]->tag & 0x00FF)/100.0f);
		}
	}
	
}

void Pilot1::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn_back)
	{
		Show("pilot_menu");
		Hide();
	}
		
		
	if(widget==btn_run)
	{
		CodeBuilder * cb = new CodeBuilder(&slots);
		cb->Save("/tmp/pilot1.nqc");
		
		RoboCore::GetCore()->DownloadProgram("/tmp/pilot1.nqc");
		btn_run->Enable(false);
	}
	
	selected_slot=NULL;
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			if(widget==slots[n]->widgets[m])
			{
				selected_slot=slots[n];
				break;
			}
		}
	}
	
	if(selected_slot!=NULL)
	{
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_BUTTON)
		{
			toolbox->Request(selected_slot->target_mask);
		}
	}
	
}

void Pilot1::Hide()
{
	toolbox->Hide();
	RoboMenu::Hide();
}

void Pilot1::OnMessage(Widget * widget,MessageEvent * event)
{
	if(event->msg->id==RBW_MSG_TOOLBOX_RET)
	{
		unsigned int target = ((MessageDataInt *)event->msg->data["target"])->value;
		if(selected_slot!=NULL)
		{
			selected_slot->target=target;
			Build();
		}
	}
	
	if(event->msg->id==RBW_MSG_RUN_STATUS)
	{
		unsigned int status = ((MessageDataInt *)event->msg->data["status"])->value;
		
		if(status==RBC_RUN_STATUS_DOWNLOADING)
			btn_run->Enable(false);
		else
			btn_run->Enable(true);
	}
	
	RoboMenu::OnMessage(widget,event);
}


Pilot2::Pilot2()
{
	label="Pilot 2";
	name="pilot_2";
	
	RoboSlot * slot;
	slot = new RoboSlot(0.21f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_A,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.29f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_C,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.75f,ROBOSLOT_TYPE_INPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_INPUT_1 ,RBW_TARGET_CLOCK_1S | RBW_TARGET_CLOCK_2S | RBW_TARGET_CLOCK_4S | RBW_TARGET_CLOCK_6S | RBW_TARGET_CLOCK_8S | RBW_TARGET_CLOCK_10S | RBW_TARGET_PRESS_ACTIVE | RBW_TARGET_PRESS_RELEASE);
	slots.push_back(slot);
	
	lbl_title = new Label(label);
	lbl_title->Init(RoboCore::GetCore()->window->cairo);			
	btn_back = new Button(T("<-- Back"));
	btn_back->Init(RoboCore::GetCore()->window->cairo);
	btn_run = new Button(T("Run >"));
	btn_run->Init(RoboCore::GetCore()->window->cairo);
		
	selected_slot=NULL;
	
	Build();
	
	toolbox = new ToolBox(0.5f,0.2f);
	RoboCore::GetCore()->window->AddLayer(toolbox);
	
	Hide();
	
	
}

void Pilot2::Build()
{
	widgets.clear();
	points.clear();
	
	Add(lbl_title,0.5f,0.05f);
	Add(btn_back,0.4f,0.90f);
	Add(btn_run,0.6f,0.90f);
	
	for(int n=0;n<slots.size();n++)
	{
		slots[n]->Build(RoboCore::GetCore()->window->cairo);
	}
	
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			Add(slots[n]->widgets[m],slots[n]->x,(slots[n]->widgets[m]->tag & 0x00FF)/100.0f);
		}
	}
	
}

void Pilot2::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn_back)
	{
		Show("pilot_menu");
		Hide();
	}
		
		
	if(widget==btn_run)
	{
		CodeBuilder * cb = new CodeBuilder(&slots);
		cb->Save("/tmp/pilot2.nqc");
		
		RoboCore::GetCore()->DownloadProgram("/tmp/pilot2.nqc");
		btn_run->Enable(false);
	}
	
	selected_slot=NULL;
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			if(widget==slots[n]->widgets[m])
			{
				selected_slot=slots[n];
				break;
			}
		}
	}
	
	if(selected_slot!=NULL)
	{
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_BUTTON)
		{
			toolbox->Request(selected_slot->target_mask);
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_SLOT_BUTTON)
		{
			selected_slot->CycleSlot();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_POWER_BUTTON)
		{
			selected_slot->CyclePower();
		}
		
	}
	
}

void Pilot2::Hide()
{
	toolbox->Hide();
	RoboMenu::Hide();
}

void Pilot2::OnMessage(Widget * widget,MessageEvent * event)
{
	if(event->msg->id==RBW_MSG_TOOLBOX_RET)
	{
		unsigned int target = ((MessageDataInt *)event->msg->data["target"])->value;
		if(selected_slot!=NULL)
		{
			selected_slot->target=target;
			Build();
		}
	}
	
	if(event->msg->id==RBW_MSG_RUN_STATUS)
	{
		unsigned int status = ((MessageDataInt *)event->msg->data["status"])->value;
		
		if(status==RBC_RUN_STATUS_DOWNLOADING)
			btn_run->Enable(false);
		else
			btn_run->Enable(true);
	}
	
	RoboMenu::OnMessage(widget,event);
}



Pilot3::Pilot3()
{
	label="Pilot 3";
	name="pilot_3";
	
	RoboSlot * slot;
	slot = new RoboSlot(0.12f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_A,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.20f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_B,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.28f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_C,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	
	slot = new RoboSlot(0.36f,ROBOSLOT_TYPE_INPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_INPUT_1 ,RBW_TARGET_CLOCK_1S | RBW_TARGET_CLOCK_2S | RBW_TARGET_CLOCK_4S | RBW_TARGET_CLOCK_6S | RBW_TARGET_CLOCK_8S | RBW_TARGET_CLOCK_10S | RBW_TARGET_PRESS_ACTIVE | RBW_TARGET_PRESS_RELEASE | RBW_TARGET_LIGHT_WHITE | RBW_TARGET_LIGHT_BLACK);
	slots.push_back(slot);
	
	slot = new RoboSlot(0.64f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_A,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.72f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_B,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.80f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_C,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	
	slot = new RoboSlot(0.88f,ROBOSLOT_TYPE_INPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_INPUT_1 ,RBW_TARGET_CLOCK_1S | RBW_TARGET_CLOCK_2S | RBW_TARGET_CLOCK_4S | RBW_TARGET_CLOCK_6S | RBW_TARGET_CLOCK_8S | RBW_TARGET_CLOCK_10S | RBW_TARGET_PRESS_ACTIVE | RBW_TARGET_PRESS_RELEASE | RBW_TARGET_LIGHT_WHITE | RBW_TARGET_LIGHT_BLACK);
	slots.push_back(slot);
	
	lbl_title = new Label(label);
	lbl_title->Init(RoboCore::GetCore()->window->cairo);			
	btn_back = new Button(T("<-- Back"));
	btn_back->Init(RoboCore::GetCore()->window->cairo);
	btn_run = new Button(T("Run >"));
	btn_run->Init(RoboCore::GetCore()->window->cairo);
		
	btn_run_mode = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
		
	btn_load = new Button(T("Load"));
	btn_load->Init(RoboCore::GetCore()->window->cairo);
	btn_save = new Button(T("Save"));
	btn_save->Init(RoboCore::GetCore()->window->cairo);
		
	selected_slot=NULL;
	run_single=true;
	
	Build();
	
	toolbox = new ToolBox(0.5f,0.2f);
	RoboCore::GetCore()->window->AddLayer(toolbox);
	
	
	Hide();
	
	
}

void Pilot3::Build()
{
	widgets.clear();
	points.clear();
	
	Add(lbl_title,0.5f,0.05f);
	
	Add(btn_back,0.2f,0.90f);
	Add(btn_run,0.8f,0.90f);
	Add(btn_run_mode,0.7f,0.90f);
	Add(btn_load,0.4f,0.90f);
	Add(btn_save,0.5f,0.90f);
	
	for(int n=0;n<slots.size();n++)
	{
		slots[n]->Build(RoboCore::GetCore()->window->cairo);
	}
	
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			Add(slots[n]->widgets[m],slots[n]->x,(slots[n]->widgets[m]->tag & 0x00FF)/100.0f);
		}
	}
	
}

void PilotLoad(GtkDialog * dialog,gint r_id,gpointer data)
{
	PilotScreen * pilot = (PilotScreen *)data;
	
	if(r_id==GTK_RESPONSE_ACCEPT)
	{
		char * filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		clog<<"Loading "<<filename<<endl;
		string path(filename);		
		g_free(filename);
		
		Message * msg = new Message(RBW_MSG_DIALOG_LOAD);
		msg->data["path"]=new MessageDataString(path);
		RoboCore::GetCore()->window->SendMessage(pilot,NULL,msg);
		
	}
	else
	{
		Message * msg = new Message(RBW_MSG_DIALOG_LOAD_CANCEL);
		RoboCore::GetCore()->window->SendMessage(pilot,NULL,msg);
	}
	
	gtk_widget_destroy(GTK_WIDGET(dialog));
	
	
}

void PilotSave(GtkDialog * dialog,gint r_id,gpointer data)
{
	PilotScreen * pilot = (PilotScreen *)data;
	
	if(r_id==GTK_RESPONSE_ACCEPT)
	{
		char * filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		string path(filename);
		g_free(filename);
		
		string base_path=filesystem::DirName(path);
		string base_name=filesystem::BaseName(path);
		
		if(base_name.length()<4)
		{
			base_name=base_name+".rbl";
		}
		else
		{
			string extension=base_name.substr(base_name.length()-4,string::npos);
			clog<<"extension: "<<extension<<endl;
			if(extension!=".rbl")
			{
				base_name=base_name+".rbl";
			}
		}
		
		string final_path=base_path+"/"+base_name;
		clog<<"Saving "<<final_path<<endl;
		
		Message * msg = new Message(RBW_MSG_DIALOG_SAVE);
		msg->data["path"]=new MessageDataString(final_path);
		RoboCore::GetCore()->window->SendMessage(pilot,NULL,msg);	
	}
	else
	{
		Message * msg = new Message(RBW_MSG_DIALOG_SAVE_CANCEL);
		RoboCore::GetCore()->window->SendMessage(pilot,NULL,msg);
	}
	gtk_widget_destroy(GTK_WIDGET(dialog));
		
}


					
void Pilot3::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn_back)
	{
		Show("pilot_menu");
		Hide();
	}
	
	if(widget==btn_load)
	{
		Hide();
				
		GtkWidget *dialog;
		char  * filename;
		
		dialog = gtk_file_chooser_dialog_new (T("Load"),NULL,GTK_FILE_CHOOSER_ACTION_OPEN,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-open", GTK_RESPONSE_ACCEPT,NULL);
		g_signal_connect(GTK_DIALOG(dialog),"response",G_CALLBACK(PilotLoad),this);
		
		GtkFileFilter *filter;

		filter = gtk_file_filter_new();
		gtk_file_filter_set_name(filter,"Robolliurex");
		gtk_file_filter_add_pattern(filter,"*.rbl");
		gtk_file_chooser_add_filter( GTK_FILE_CHOOSER(dialog),filter);
		
		gtk_widget_show_all(dialog);
		
		
		//Show();	
	}
	
	if(widget==btn_save)
	{
		Hide();
		GtkWidget *dialog;
		char * filename;
		
		dialog = gtk_file_chooser_dialog_new (T("Save"),NULL,GTK_FILE_CHOOSER_ACTION_SAVE,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-save", GTK_RESPONSE_ACCEPT,NULL);
		g_signal_connect(GTK_DIALOG(dialog),"response",G_CALLBACK(PilotSave),this);
		GtkFileFilter *filter;

		filter = gtk_file_filter_new();
		gtk_file_filter_set_name(filter,"Robolliurex");
		gtk_file_filter_add_pattern(filter,"*.rbl");
		gtk_file_chooser_add_filter( GTK_FILE_CHOOSER(dialog),filter);
		gtk_widget_show_all(dialog);
	}
		
	if(widget==btn_run)
	{
		CodeBuilder * cb = new CodeBuilder(&slots,run_single);
		cb->Save("/tmp/pilot3.nqc");
		
		RoboCore::GetCore()->DownloadProgram("/tmp/pilot3.nqc");
		btn_run->Enable(false);
	}
	
	if(widget==btn_run_mode)
	{
		run_single=!run_single;
		
		clog<<"run_single: "<<run_single<<endl;
		
		if(run_single)
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
		else
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_repeat.png"));
	}
	
	selected_slot=NULL;
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			if(widget==slots[n]->widgets[m])
			{
				selected_slot=slots[n];
				break;
			}
		}
	}
	
	if(selected_slot!=NULL)
	{
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_BUTTON)
		{
			toolbox->Request(selected_slot->target_mask);
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_SLOT_BUTTON)
		{
			selected_slot->CycleSlot();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_POWER_BUTTON)
		{
			selected_slot->CyclePower();
		}
		
	}
	
}

void Pilot3::Hide()
{
	toolbox->Hide();
	RoboMenu::Hide();
}

void Pilot3::OnMessage(Widget * widget,MessageEvent * event)
{
	if(event->msg->id==RBW_MSG_TOOLBOX_RET)
	{
		unsigned int target = ((MessageDataInt *)event->msg->data["target"])->value;
		if(selected_slot!=NULL)
		{
			selected_slot->target=target;
			Build();
		}
	}
	
	if(event->msg->id==RBW_MSG_RUN_STATUS)
	{
		unsigned int status = ((MessageDataInt *)event->msg->data["status"])->value;
		
		if(status==RBC_RUN_STATUS_DOWNLOADING)
			btn_run->Enable(false);
		else
			btn_run->Enable(true);
	}
	
	if(event->msg->id==RBW_MSG_PILOT_LOAD)
	{
		string path = static_cast<MessageDataString *>(event->msg->data["path"])->value;
		int pilot =static_cast<MessageDataInt *>(event->msg->data["pilot"])->value;
		
		if(pilot==3)
		{
			clog<<"Pilot3 Loading "<<path<<endl;
			vector<int> header;
			RoboSlot::Load(path,&slots,&header);
			
			run_single=header[2];
			
			if(run_single)
				btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
			else
				btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_repeat.png"));
			
			
			Build();
			
			Show();
		}
	}
	
	
	if(event->msg->id==RBW_MSG_DIALOG_LOAD)
	{
		string path = ((MessageDataString *)event->msg->data["path"])->value;
		clog<<"Pilot3 Loading "<<path<<endl;
		vector<int> header;
		RoboSlot::Load(path,&slots,&header);
		
		run_single=header[2];
		
		if(run_single)
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
		else
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_repeat.png"));
		
		
		Build();
		
					
		Show();
	}
	
	if(event->msg->id==RBW_MSG_DIALOG_LOAD_CANCEL)
	{
		Show();
	}
	
	if(event->msg->id==RBW_MSG_DIALOG_SAVE)
	{
		string path = ((MessageDataString *)event->msg->data["path"])->value;
				
		vector<int> header;
		header.push_back(1);//robolliurex version 1
		header.push_back(3);//pilot 3
		header.push_back(run_single);
		RoboSlot::Save(path,&slots,&header);
		
		Show();
		
	}
	
	if(event->msg->id==RBW_MSG_DIALOG_SAVE_CANCEL)
	{
		Show();
	}
	
	RoboMenu::OnMessage(widget,event);
}


Pilot4::Pilot4()
{
	label="Pilot 4";
	name="pilot_4";
	
	steps=1;
	current_step=1;
	
	RoboSlot * slot;
	slot = new RoboSlot(0.17f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_A,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.25f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_B,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	slot = new RoboSlot(0.33f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_C,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
	slots.push_back(slot);
	
	slot = new RoboSlot(0.75f,ROBOSLOT_TYPE_INPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_INPUT_1 ,RBW_TARGET_CLOCK | RBW_TARGET_LIGHT_SENSOR | RBW_TARGET_PRESS_ACTIVE | RBW_TARGET_PRESS_RELEASE);
	slots.push_back(slot);
		
	
	lbl_title = new Label(label);
	lbl_title->Init(RoboCore::GetCore()->window->cairo);			
	btn_back = new Button(T("<-- Back"));
	btn_back->Init(RoboCore::GetCore()->window->cairo);
	btn_run = new Button(T("Run >"));
	btn_run->Init(RoboCore::GetCore()->window->cairo);
	
	btn_run_mode = new ImageButton(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
	
	btn_load = new Button(T("Load"));
	btn_load->Init(RoboCore::GetCore()->window->cairo);
	btn_save = new Button(T("Save"));
	btn_save->Init(RoboCore::GetCore()->window->cairo);
	
	btn_add = new Button(T("Add"));
	btn_add->Init(RoboCore::GetCore()->window->cairo);
	
	btn_remove = new Button(T("Remove"));
	btn_remove->Init(RoboCore::GetCore()->window->cairo);
	
	btn_right = new Button(T("Right"));
	btn_right->Init(RoboCore::GetCore()->window->cairo);
	
	btn_left = new Button(T("Left"));
	btn_left->Init(RoboCore::GetCore()->window->cairo);
	
	lbl_step = new Label(T("Step n out of m"));
	lbl_step->Init(RoboCore::GetCore()->window->cairo);			
	
		
	selected_slot=NULL;
	run_single=true;
	
	UpdateButtons();
		
	
	Build();
	
	toolbox = new ToolBox(0.5f,0.2f);
	RoboCore::GetCore()->window->AddLayer(toolbox);
	
	Hide();
	
	
}

void Pilot4::Build()
{
	widgets.clear();
	points.clear();
	
	Add(lbl_title,0.5f,0.05f);
	
	Add(btn_back,0.18f,0.90f);
	Add(btn_run,0.8f,0.90f);
	Add(btn_run_mode,0.6f,0.90f);
	Add(btn_load,0.3f,0.90f);
	Add(btn_save,0.4f,0.90f);
	
	Add(btn_right,0.7f,0.20f);
	Add(btn_left,0.3f,0.20f);
	Add(btn_add,0.8f,0.20f);
	Add(btn_remove,0.18f,0.20f);
	
	Add(lbl_step,0.5f,0.20f);
	
	stringstream ss;
	
	ss<<T("Step ")<<current_step<<T(" out of ")<<steps;
	lbl_step->SetText(ss.str());
	
	for(int n=0;n<slots.size();n++)
	{
		slots[n]->Build(RoboCore::GetCore()->window->cairo);
	}
	
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			Add(slots[n]->widgets[m],slots[n]->x-(current_step-1),(slots[n]->widgets[m]->tag & 0x00FF)/100.0f);
		}
	}
	
}

void Pilot4::UpdateButtons()
{
	if(current_step==steps)
		{
			btn_add->Enable(true);
			btn_remove->Enable(true);
			btn_right->Enable(false);
			btn_left->Enable(true);
		}
		else
		{
			btn_add->Enable(false);
			btn_remove->Enable(false);
			btn_right->Enable(true);
		}
		
	if(current_step==1)
	{
		btn_remove->Enable(false);
		btn_left->Enable(false);
	}
}

void Pilot4::OnMouseClick(Widget * widget,MouseClickEvent * event)
{
	if(widget==btn_back)
	{
		Show("pilot_menu");
		Hide();
	}
	
	if(widget==btn_load)
	{
		Hide();
		
		GtkWidget *dialog;
		char  * filename;
		
		dialog = gtk_file_chooser_dialog_new (T("Load"),NULL,GTK_FILE_CHOOSER_ACTION_OPEN,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-open", GTK_RESPONSE_ACCEPT,NULL);
		g_signal_connect(GTK_DIALOG(dialog),"response",G_CALLBACK(PilotLoad),this);
		
		GtkFileFilter *filter;

		filter = gtk_file_filter_new();
		gtk_file_filter_set_name(filter,"Robolliurex");
		gtk_file_filter_add_pattern(filter,"*.rbl");
		gtk_file_chooser_add_filter( GTK_FILE_CHOOSER(dialog),filter);
		
		gtk_widget_show_all(dialog);
	}
	
	if(widget==btn_save)
	{
		Hide();
		GtkWidget *dialog;
		char * filename;
		
		dialog = gtk_file_chooser_dialog_new (T("Save"),NULL,GTK_FILE_CHOOSER_ACTION_SAVE,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-save", GTK_RESPONSE_ACCEPT,NULL);
		g_signal_connect(GTK_DIALOG(dialog),"response",G_CALLBACK(PilotSave),this);
		GtkFileFilter *filter;

		filter = gtk_file_filter_new();
		gtk_file_filter_set_name(filter,"Robolliurex");
		gtk_file_filter_add_pattern(filter,"*.rbl");
		gtk_file_chooser_add_filter( GTK_FILE_CHOOSER(dialog),filter);
		gtk_widget_show_all(dialog);
	}	
		
	if(widget==btn_run)
	{
		CodeBuilder * cb = new CodeBuilder(&slots,run_single);
		cb->Save("/tmp/pilot4.nqc");
		
		RoboCore::GetCore()->DownloadProgram("/tmp/pilot4.nqc");
		btn_run->Enable(false);
		
		delete cb;
	}
	
	if(widget==btn_run_mode)
	{
		run_single=!run_single;
			
		if(run_single)
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
		else
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_repeat.png"));
	}
	
	if(widget==btn_right && btn_right->enabled)
	{
	
		if(current_step < steps)current_step++;
		
		
		UpdateButtons();
		Build();
	}
	
	if(widget==btn_left && btn_left->enabled)
	{
		if(current_step > 1)current_step--;
		
		
		
		UpdateButtons();
		Build();
	}
	
	if(widget==btn_add && btn_add->enabled)
	{
		
		RoboSlot * slot;
		
		slot = new RoboSlot(steps+0.20f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_A,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
		slots.push_back(slot);
		slot = new RoboSlot(steps+0.32f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_B,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
		slots.push_back(slot);
		slot = new RoboSlot(steps+0.44f,ROBOSLOT_TYPE_OUTPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_OUTPUT_C,RBW_TARGET_LIGHT | RBW_TARGET_MOTOR_FORWARD | RBW_TARGET_MOTOR_BACKWARD | RBW_TARGET_STOP);
		slots.push_back(slot);
		
		slot = new RoboSlot(steps+0.7f,ROBOSLOT_TYPE_INPUT,ROBOSLOT_MODE_NORMAL,ROBOSLOT_INPUT_1 ,RBW_TARGET_CLOCK | RBW_TARGET_LIGHT_SENSOR | RBW_TARGET_PRESS_ACTIVE | RBW_TARGET_PRESS_RELEASE);
		slots.push_back(slot);
		
		steps++;
		UpdateButtons();
		Build();
	}
	
	if(widget==btn_remove && btn_remove->enabled)
	{
		if(steps>1)
		{
			RoboSlot * slot;
			
			for(int n=0;n<4;n++)
			{
				slot = slots.back();
				slots.pop_back();
				delete slot;
			}
						
			steps--;
			current_step--;
			UpdateButtons();
			Build();
		}
	}
	
	selected_slot=NULL;
	for(int n=0;n<slots.size();n++)
	{
		for(int m=0;m<slots[n]->widgets.size();m++)
		{
			if(widget==slots[n]->widgets[m])
			{
				selected_slot=slots[n];
				break;
			}
		}
	}
	
	if(selected_slot!=NULL)
	{
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_BUTTON)
		{
			toolbox->Request(selected_slot->target_mask);
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_SLOT_BUTTON)
		{
			selected_slot->CycleSlot();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_POWER_BUTTON)
		{
			selected_slot->CyclePower();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_CLOCK_INCREASE)
		{
			selected_slot->IncreaseClock();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_CLOCK_DECREASE)
		{
			selected_slot->DecreaseClock();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_LIGHT_INCREASE)
		{
			selected_slot->IncreaseLight();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_LIGHT_DECREASE)
		{
			selected_slot->DecreaseLight();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_LIGHT_MODE)
		{
			selected_slot->CycleLightMode();
		}
		
		if( (widget->tag>>8)==ROBOSLOT_WIDGET_CLOCK_MODE)
		{
			selected_slot->CycleClockMode();
		}
		
	}
	
}

void Pilot4::Hide()
{
	toolbox->Hide();
	RoboMenu::Hide();
}

void Pilot4::OnMessage(Widget * widget,MessageEvent * event)
{
	if(event->msg->id==RBW_MSG_TOOLBOX_RET)
	{
		unsigned int target = ((MessageDataInt *)event->msg->data["target"])->value;
		if(selected_slot!=NULL)
		{
			selected_slot->target=target;
			Build();
		}
	}
	
	if(event->msg->id==RBW_MSG_RUN_STATUS)
	{
		unsigned int status = ((MessageDataInt *)event->msg->data["status"])->value;
		
		if(status==RBC_RUN_STATUS_DOWNLOADING)
			btn_run->Enable(false);
		else
			btn_run->Enable(true);
	}
	
	if(event->msg->id==RBW_MSG_PILOT_LOAD)
	{
		string path = static_cast<MessageDataString *>(event->msg->data["path"])->value;
		int pilot =static_cast<MessageDataInt *>(event->msg->data["pilot"])->value;
		
		if(pilot==4)
		{
			clog<<"Pilot4 Loading "<<path<<endl;
			vector<int> header;
			RoboSlot::Load(path,&slots,&header);
			
			run_single=header[2];
			
			if(run_single)
				btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
			else
				btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_repeat.png"));
			
			
			Build();
			
			Show();
		}
	}
	
	
	if(event->msg->id==RBW_MSG_DIALOG_LOAD)
	{
		
				
		string path = ((MessageDataString *)event->msg->data["path"])->value;
		clog<<"Pilot4 Loading "<<path<<endl;
		
		vector<int> header;
		RoboSlot::Load(path,&slots,&header);
		
		
		run_single = header[2];
		
		steps = header[3];
		current_step=1;
		
		if(run_single)
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_single.png"));
		else
			btn_run_mode->SetImage(RoboCore::GetCore()->rsrc->GetSurface("run_repeat.png"));
		
		Build();
		
			
		UpdateButtons();	
		Show();
		
		
	}
	
	if(event->msg->id==RBW_MSG_DIALOG_LOAD_CANCEL)
	{
		Show();
	}
	
	if(event->msg->id==RBW_MSG_DIALOG_SAVE)
	{
		
		string path = ((MessageDataString *)event->msg->data["path"])->value;
		
		
		vector<int> header;
		header.push_back(1);
		header.push_back(4);
		header.push_back(run_single);
		header.push_back(steps);
		RoboSlot::Save(path,&slots,&header);
		
		Show();
		
	}
	
	if(event->msg->id==RBW_MSG_DIALOG_SAVE_CANCEL)
	{
		Show();
	}
	
	RoboMenu::OnMessage(widget,event);
}




void Pilot4::Draw(cairo_t * cairo)
{
	//predrawing operations
	float s_width,s_height;
	float w,h;
	
	cairo_surface_t * srf;
	
	
	srf = cairo_get_target(cairo);
	s_width=cairo_image_surface_get_width(srf);
	s_height=cairo_image_surface_get_height(srf);
	
	
	cairo_set_line_width(cairo,4.0f);
	cairo_set_source_rgb(cairo, 0.96, 0.62, 0.11);
	cairo_move_to(cairo,s_width*0.05f,s_height*0.5f);
	cairo_line_to(cairo,s_width*0.95f,s_height*0.5f);
	cairo_stroke(cairo);
	
	srf = RoboCore::GetCore()->rsrc->GetSurface("semaphore_green.png");
	w = cairo_image_surface_get_width(srf);
	h = cairo_image_surface_get_height(srf);
	cairo_set_source_surface(cairo,srf,-(s_width*(current_step-1))+(s_width*0.05f)-(w/2.0f),(s_height*0.5f)-(h/2.0f));
	cairo_paint(cairo);
	
	srf = RoboCore::GetCore()->rsrc->GetSurface("semaphore_red.png");
	w = cairo_image_surface_get_width(srf);
	h = cairo_image_surface_get_height(srf);
	cairo_set_source_surface(cairo,srf,(s_width*(steps-1))-(s_width*(current_step-1))+(s_width*0.95f)-(w/2.0f),(s_height*0.5f)-(h/2.0f));
	cairo_paint(cairo);
	
	RoboMenu::Draw(cairo);
}
