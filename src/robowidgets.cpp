
#include <iostream>
#include <string>
#include <pango/pangocairo.h>

#include "robowidgets.h"
#include "robocore.h"

using namespace std;
using namespace net::lliurex::robolliurex;

/**
 * draw a rounded corner square
 **/ 
void draw_round_square(cairo_t * cairo,float x,float y,float width,float height)
{
	float w=3.0f;
	float v=5.0f;
	float rwidth = width - (w*2.0f) - (v*2.0f);
	float rheight = height - (w*2.0f) - (v*2.0f);
	
	if(width<6.0)return;
	
	//top
	cairo_move_to(cairo,x,y+w+v);
	cairo_curve_to(cairo,x,y+w,x+w,y,x+w+v,y);
	cairo_line_to(cairo,x+w+v+rwidth,y);
	cairo_curve_to(cairo,x+w+v+rwidth+v,y,x+width,y+w,x+width,y+w+v);
	
	//right side
	cairo_line_to(cairo,x+width,y+w+v+rheight);
	
	//bottom
	cairo_curve_to(cairo,x+width,y+w+v+rheight+v,x+w+v+rwidth+w,y+height,x+w+v+rwidth,y+height);
	cairo_line_to(cairo,x+w+v,y+height);
	cairo_curve_to(cairo,x+w,y+height,x,y+w+v+rheight+v,x,y+w+v+rheight);
	
	//left side
	cairo_line_to(cairo,x,y+w+v);
		
}



Button::Button(string text)
{
		
	//provisional size
	this->width=5;
	this->height=5;
	this->x=0.0f;
	this->y=0.0f;
	
	this->name="robolliurex::Button";
	this->text=string(text);
	
	this->mouse_over=false;
	this->mouse_press=false;
	this->focus=false;
	this->enabled=true;

}

void Button::Init(cairo_t * cairo)
{
	cairo_text_extents_t te;
	cairo_font_extents_t fe;
	
	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 16.0);
	cairo_text_extents (cairo, text.c_str(), &te);
	cairo_font_extents (cairo, &fe);
	
	width=te.width;
	height=(fe.height);
	width+=20.0f; // 10+10 margins 
	height+=(height*0.8f);
}

void Button::Draw(cairo_t * cairo)
{
	cairo_text_extents_t te;
	cairo_font_extents_t fe;
	
	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 16.0);
	cairo_text_extents (cairo, text.c_str(), &te);
	cairo_font_extents (cairo, &fe);
	
	width=te.width;
	height=(fe.height);
	width+=20.0f; // 10+10 margins 
	height+=(height*0.8f);
	
	if(enabled)
	{
		if(focus)
		{
			cairo_set_source_rgb(cairo, 0.35, 0.73, 1.0);
			cairo_set_line_width (cairo, 2.0);
			draw_round_square(cairo,x-2,y-2,width+4,height+4);
			cairo_stroke(cairo);
		}
	
		if(mouse_press)
			cairo_set_source_rgb(cairo, 0.96, 0.62, 0.11);
		else
		{
			if(mouse_over)
				cairo_set_source_rgb(cairo, 0.30, 0.68, 1.0);
			else
				cairo_set_source_rgb(cairo, 0.20, 0.48, 0.8);
				
		}
	}
	else
	{
		if(mouse_press)
			cairo_set_source_rgb(cairo, 0.40, 0.40, 0.40);
		else
		{
			if(mouse_over)
				cairo_set_source_rgb(cairo, 0.30, 0.30, 0.30);
			else
				cairo_set_source_rgb(cairo, 0.20, 0.20, 0.20);
				
		}
	}
	
	draw_round_square(cairo,x,y,width,height);
	cairo_fill(cairo);
	
	cairo_set_source_rgb(cairo, 0.2, 0.2, 0.2);
	cairo_set_line_width (cairo, 2.0);
	draw_round_square(cairo,x,y,width,height);
	cairo_stroke(cairo);
	
	cairo_pattern_t *pat;

	pat = cairo_pattern_create_linear (x, y,x , y+height);
	if(mouse_press)
	{
		cairo_pattern_add_color_stop_rgb(pat, 0,0.0f,0.0f,0.0f);
		cairo_pattern_add_color_stop_rgb(pat, 1,0.0f,0.0f,0.0f);
		//cairo_pattern_add_color_stop_rgb(pat, 1,1.0,1.0,1.0f);
	}
	else
	{
		cairo_pattern_add_color_stop_rgb(pat, 0,1.0,1.0,1.0f);
		cairo_pattern_add_color_stop_rgb(pat, 1,0.0f,0.0f,0.0f);
	}
	
	cairo_set_source (cairo, pat);
	cairo_set_line_width (cairo, 1.0);
	draw_round_square(cairo,x+1,y+1,width-2,height-2);
	cairo_stroke(cairo);
	cairo_pattern_destroy (pat);
			
	cairo_set_source_rgb (cairo, 0.05, 0.05, 0.05);
	
	if(mouse_press)
		cairo_move_to (cairo, x+((width-te.width)/2.0)+1,y+(height)-((height-fe.height)/2.0)-fe.descent+2);
	else
		cairo_move_to (cairo, x+((width-te.width)/2.0)+1,y+(height)-((height-fe.height)/2.0)-fe.descent+1);
	
	cairo_show_text (cairo, text.c_str());
	
	cairo_set_source_rgb (cairo, 0.95, 0.95, 0.95);
	
	if(mouse_press)
		cairo_move_to (cairo, x+((width-te.width)/2.0),y+(height)-((height-fe.height)/2.0)-fe.descent+1);
	else
		cairo_move_to (cairo, x+((width-te.width)/2.0),y+(height)-((height-fe.height)/2.0)-fe.descent);
	
	cairo_show_text (cairo, text.c_str());
	
}

void Button::Enable(bool enable)
{
	this->enabled=enable;
}

ImageButton::ImageButton(cairo_surface_t * surface)
{
	this->x=0.0f;
	this->y=0.0f;
	
	this->name="robolliurex::ImageButton";
		
	this->mouse_over=false;
	this->mouse_press=false;
	this->focus=false;
	
	this->surface=surface;
	
	this->width=cairo_image_surface_get_width(surface)+10.0f;
	this->height=cairo_image_surface_get_height(surface)+10.0f;
}

void ImageButton::SetImage(cairo_surface_t * surface)
{
	this->surface=surface;
}

void ImageButton::Draw(cairo_t * cairo)
{
	
	if(focus)
	{
		cairo_set_source_rgb(cairo, 0.35, 0.73, 1.0);
		cairo_set_line_width (cairo, 2.0);
		draw_round_square(cairo,x-2,y-2,width+4,height+4);
		cairo_stroke(cairo);
	}
	
	if(mouse_press)
		cairo_set_source_rgb(cairo, 0.96, 0.62, 0.11);
	else
	{
		if(mouse_over)
			cairo_set_source_rgb(cairo, 0.30, 0.68, 1.0);
		else
			cairo_set_source_rgb(cairo, 0.20, 0.48, 0.8);
	}
	
	
	
	draw_round_square(cairo,x,y,width,height);
	cairo_fill(cairo);
	
	cairo_set_source_rgb(cairo, 0.2, 0.2, 0.2);
	cairo_set_line_width (cairo, 2.0);
	draw_round_square(cairo,x,y,width,height);
	cairo_stroke(cairo);
	
	cairo_pattern_t *pat;

	pat = cairo_pattern_create_linear (x, y,x , y+height);
	if(mouse_press)
	{
		cairo_pattern_add_color_stop_rgb(pat, 0,0.0f,0.0f,0.0f);
		cairo_pattern_add_color_stop_rgb(pat, 1,0.0f,0.0f,0.0f);
		//cairo_pattern_add_color_stop_rgb(pat, 1,1.0,1.0,1.0f);
	}
	else
	{
		cairo_pattern_add_color_stop_rgb(pat, 0,1.0,1.0,1.0f);
		cairo_pattern_add_color_stop_rgb(pat, 1,0.0f,0.0f,0.0f);
	}
	
	cairo_set_source (cairo, pat);
	cairo_set_line_width (cairo, 1.0);
	draw_round_square(cairo,x+1,y+1,width-2,height-2);
	cairo_stroke(cairo);
	cairo_pattern_destroy (pat);
	
	if(mouse_press)	
		cairo_set_source_surface(cairo,surface,x+6.0f,y+6.0f);
	else
		cairo_set_source_surface(cairo,surface,x+5.0f,y+5.0f);
	
	cairo_paint(cairo);
	
}


Image::Image(cairo_surface_t * surface)
{
	this->x=0.0f;
	this->y=0.0f;
	
	this->name="robolliurex::Image";
		
	this->mouse_over=false;
	this->mouse_press=false;
	this->focus=false;
	
	this->surface=surface;
	
	this->width=cairo_image_surface_get_width(surface)+10.0f;
	this->height=cairo_image_surface_get_height(surface)+10.0f;
}


void Image::SetImage(cairo_surface_t * surface )
{
	this->surface=surface;
	
	this->width=cairo_image_surface_get_width(surface)+10.0f;
	this->height=cairo_image_surface_get_height(surface)+10.0f;
}

void Image::Draw(cairo_t * cairo)
{
		
	cairo_set_source_rgb(cairo, 0.4, 0.4, 0.4);
	
	draw_round_square(cairo,x,y,width,height);
	cairo_fill(cairo);
	
	cairo_set_source_rgb(cairo, 0.2, 0.2, 0.2);
	cairo_set_line_width (cairo, 2.0);
	draw_round_square(cairo,x,y,width,height);
	cairo_stroke(cairo);
	
	cairo_set_source_surface(cairo,surface,x,y);
	cairo_paint(cairo);
	
}

Switch::Switch(string text,int * value,int myvalue)
{
	//provisional size
	this->width=5;
	this->height=5;
	this->x=0.0f;
	this->y=0.0f;
	
	this->name="robolliurex::Switch";
	this->text=string(text);
	
	this->mouse_over=false;
	this->mouse_press=false;
	this->focus=false;
	
	this->myvalue=myvalue;
	this->value=value;
}

void Switch::Init(cairo_t * cairo)
{
	cairo_text_extents_t te;
	cairo_font_extents_t fe;
	
	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 16.0);
	cairo_text_extents (cairo, text.c_str(), &te);
	cairo_font_extents (cairo, &fe);
	
	width=te.width;
	height=(fe.height);
	width+=20.0f; // 10+10 margins 
	height+=(height*0.8f);
	
}

void Switch::Draw(cairo_t * cairo)
{
	cairo_text_extents_t te;
	cairo_font_extents_t fe;
	
	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 16.0);
	cairo_text_extents (cairo, text.c_str(), &te);
	cairo_font_extents (cairo, &fe);
	
	width=te.width;
	height=(fe.height);
	width+=20.0f; // 10+10 margins 
	height+=(height*0.8f);
	
	if(*value==myvalue)
	{
		cairo_set_source_rgb(cairo, 0.88, 0.50, 0.07);
		//cairo_set_source_rgb(cairo, 0.96, 0.62, 0.11);
	}
	else
	{
		cairo_set_source_rgb(cairo, 0.4, 0.4, 0.4);
	}
	
	
	
	draw_round_square(cairo,x,y,width,height);
	cairo_fill(cairo);
	
	cairo_set_source_rgb(cairo, 0.2, 0.2, 0.2);
	cairo_set_line_width (cairo, 2.0);
	draw_round_square(cairo,x,y,width,height);
	cairo_stroke(cairo);
	
	
	cairo_set_source_rgb (cairo, 0.05, 0.05, 0.05);
	cairo_move_to (cairo, x+((width-te.width)/2.0)+1,y+(height)-((height-fe.height)/2.0)-fe.descent+1);
	cairo_show_text (cairo, text.c_str());
	
	cairo_set_source_rgb (cairo, 0.95, 0.95, 0.95);
	
	cairo_move_to (cairo, x+((width-te.width)/2.0),y+(height)-((height-fe.height)/2.0)-fe.descent);
	cairo_show_text (cairo, text.c_str());
}

void Switch::OnMouseClick(MouseClickEvent * event)
{
	*value=myvalue;
}

ProgressBar::ProgressBar(string text,float value)
{
	//provisional size
	this->width=200;
	this->height=30;
	this->x=0.0f;
	this->y=0.0f;
	
	this->name="robolliurex::ProgressBar";
	this->text=string(text);
	
	this->mouse_over=false;
	this->mouse_press=false;
	this->focus=false;
	
	this->value=value;
}

void ProgressBar::Draw(cairo_t * cairo)
{
	/* clamp value */
	if(value<0.0f)value=0.0f;
	if(value>1.0f)value=1.0f;
	
	cairo_text_extents_t te;
	cairo_font_extents_t fe;
	
	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 16.0);
	cairo_text_extents (cairo, text.c_str(), &te);
	cairo_font_extents (cairo, &fe);
	
	
	
	cairo_set_source_rgb(cairo, 0.4, 0.4, 0.4);
	draw_round_square(cairo,x,y,width,height);
	cairo_fill(cairo);
	
	cairo_set_source_rgb(cairo, 0.20, 0.48, 0.8);
	draw_round_square(cairo,x,y,value*width,height);
	cairo_fill(cairo);
	
	cairo_set_source_rgb(cairo, 0.30, 0.68, 1.0);
	cairo_set_line_width (cairo, 2.0);
	draw_round_square(cairo,x+2.0f,y+2.0f,value*(width-4.0f),height-4.0f);
	cairo_stroke(cairo);
	
	cairo_set_source_rgb(cairo, 0.2, 0.2, 0.2);
	cairo_set_line_width (cairo, 2.0);
	draw_round_square(cairo,x,y,width,height);
	cairo_stroke(cairo);
	
	cairo_set_source_rgb (cairo, 0.95, 0.95, 0.95);
	
	cairo_move_to (cairo, x+((width-te.width)/2.0),y+(height)-((height-fe.height)/2.0)-fe.descent);
	cairo_show_text (cairo, text.c_str());
	
	
}

void ProgressBar::SetValue(float value)
{
	this->value=value;
}

void ProgressBar::SetText(string text)
{
	this->text=text;
}

Label::Label(string text)
{
	//provisional size
	this->width=200;
	this->height=30;
	this->x=0.0f;
	this->y=0.0f;
	
	this->name="robolliurex::Label";
	this->text=string(text);
	
	this->mouse_over=false;
	this->mouse_press=false;
	this->focus=false;
	
	this->text=text;
}

void Label::SetText(string text)
{
	this->text=text;
}

void Label::Init(cairo_t * cairo)
{
	/* there is place for improvment here */
	PangoLayout * layout = pango_cairo_create_layout(cairo);
	PangoFontDescription * font;
	
	font = pango_font_description_from_string("Ubuntu 12");
	pango_layout_set_width(layout,256*PANGO_SCALE);
	pango_layout_set_height(layout,512*PANGO_SCALE);
	pango_layout_set_font_description(layout, font);
	pango_layout_set_text(layout, text.c_str(), -1);
	
	pango_cairo_update_layout(cairo,layout);
	
	int tw,th;
	pango_layout_get_pixel_size(layout,&tw,&th);
	
	width = 20.0f + tw;
	height = th + (0.3f*th);
	
	pango_font_description_free(font);
	g_object_unref(layout);
	
}

void Label::Draw(cairo_t * cairo)
{
	
	
	PangoLayout * layout = pango_cairo_create_layout(cairo);
	PangoFontDescription * font;
	
	font = pango_font_description_from_string("Ubuntu 12");
	pango_layout_set_width(layout,256*PANGO_SCALE);
	pango_layout_set_height(layout,512*PANGO_SCALE);
	pango_layout_set_font_description(layout, font);
	pango_layout_set_text(layout, text.c_str(), -1);
	
	pango_cairo_update_layout(cairo,layout);
	
	int tw,th;
	pango_layout_get_pixel_size(layout,&tw,&th);
	
	width = 20.0f + tw;
	height = th + (0.3f*th);
	
	
	cairo_set_source_rgb(cairo, 0.4, 0.4, 0.4);
		
	draw_round_square(cairo,x,y,width,height);
	cairo_fill(cairo);
	
	cairo_set_source_rgb(cairo, 0.2, 0.2, 0.2);
	cairo_set_line_width (cairo, 2.0);
	draw_round_square(cairo,x,y,width,height);
	cairo_stroke(cairo);
	
	cairo_set_source_rgb (cairo, 0.05, 0.05, 0.05);
	cairo_move_to (cairo,1+x+((width/2.0)-(tw/2.0)),1+y+((height/2.0)-(th/2.0)));
	pango_cairo_show_layout(cairo,layout);
	
	cairo_set_source_rgb (cairo, 0.95, 0.95, 0.95);
	cairo_move_to (cairo,x+((width/2.0)-(tw/2.0)),y+((height/2.0)-(th/2.0)));
	pango_cairo_show_layout(cairo,layout);
	
	pango_font_description_free(font);
	g_object_unref(layout);
	
	
}


RoboMenu::RoboMenu(string label,float x,float y,int position_type, int distribution_type):Layer("robolliurex::RoboMenu")
{
	this->label=label;
	this->fx=x;
	this->fy=y;
	this->position_type=position_type;
	this->distribution_type=distribution_type;
	
		
	//rgba
	color_fill[0]=0.33f; 
	color_fill[1]=0.34f;
	color_fill[2]=0.30f;
	color_fill[3]=0.40f;
			
	color_border[0]=0.53f;
	color_border[1]=0.84f;
	color_border[2]=1.0f;
	color_border[3]=0.9f;
		
	
	color_text[0]=0.85f;
	color_text[1]=0.85f;
	color_text[2]=0.85f;
	color_text[3]=1.0f;
	
	SetDepth( LGI_LAYER_DEPTH_TOP + 1);
}

void RoboMenu::Draw(cairo_t * cairo)
{
	float a=5.0f;
	float b=10.0f;
	float c=20.0f;
	
	float maxw=0.0f;
	float my=b+c;
	
	float maxh=0.0f;
	float mx=b;
	
	float s_width,s_height;
	cairo_surface_t * srf;
	
	cairo_text_extents_t te;
	
	srf = cairo_get_target(cairo);
	s_width=cairo_image_surface_get_width(srf);
	s_height=cairo_image_surface_get_height(srf);
	
	if(distribution_type==RBW_DISTRIBUTION_VERTICAL)
	{
		for(int n=0;n<widgets.size();n++)
		{
			if(widgets[n]->width>maxw)maxw=widgets[n]->width;
			widgets[n]->y=my;
			my = my + widgets[n]->height+b;
		}
	}
	maxw=maxw+50.0f;
	
	if(distribution_type==RBW_DISTRIBUTION_HORITZONTAL)
	{
		for(int n=0;n<widgets.size();n++)
		{
			if(widgets[n]->height>maxh)maxh=widgets[n]->height;
			widgets[n]->x=mx;
			mx = mx + widgets[n]->width+b;
		}
		
		maxh+=c;
	}
	
	if(distribution_type==RBW_DISTRIBUTION_FACTOR)
	{
		for(int n=0;n<widgets.size();n++)
		{
			widgets[n]->x=(s_width*points[widgets[n]].x) - (widgets[n]->width/2.0f);
			widgets[n]->y=s_height*points[widgets[n]].y - (widgets[n]->height/2.0f);
		}
	}

	
	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 16.0);
	
	cairo_text_extents (cairo, label.c_str(), &te);
	
	if(te.width>maxw)maxw=te.width;
		
	switch(position_type)
	{
		case RBW_POSITION_FIXED:
			/* nothing to do */
		break;
		
		case RBW_POSITION_FACTOR:
			if(distribution_type==RBW_DISTRIBUTION_VERTICAL)
			{
				x=(fx*s_width) - ((maxw+b)/2.0f);
				y=(fy*s_height) - ((my+a)/2.0f);
			}
			
			if(distribution_type==RBW_DISTRIBUTION_HORITZONTAL)
			{
				x=(fx*s_width) - ((mx)/2.0f);
				y=(fy*s_height) - ((maxh+a)/2.0f);
			}
		break;
	}
	
	if(distribution_type!=RBW_DISTRIBUTION_FACTOR)
	{
		cairo_set_source_rgba(cairo, color_fill[0],color_fill[1],color_fill[2],color_fill[3]);
		if(distribution_type==RBW_DISTRIBUTION_VERTICAL)
			draw_round_square(cairo,x,y,maxw+b,my+a);
		
		if(distribution_type==RBW_DISTRIBUTION_HORITZONTAL)
			draw_round_square(cairo,x,y,mx+a,maxh+c);
		
		cairo_fill(cairo);
		
		
		cairo_set_source_rgba(cairo,color_border[0],color_border[1],color_border[2],color_border[3]);
		cairo_set_line_width (cairo, 2.0);
		
		if(distribution_type==RBW_DISTRIBUTION_VERTICAL)
			draw_round_square(cairo,x,y,maxw+b,my+a);
		
		if(distribution_type==RBW_DISTRIBUTION_HORITZONTAL)
			draw_round_square(cairo,x,y,mx+a,maxh+c);
		
		cairo_stroke(cairo);
				
		
		
		cairo_set_source_rgba(cairo, color_text[0],color_text[1],color_text[2],color_text[3]);
		cairo_move_to (cairo, x+a,y+c);
		cairo_show_text (cairo, label.c_str());
	}
	
	for(int n=0;n<widgets.size();n++)
	{
		if(distribution_type==RBW_DISTRIBUTION_VERTICAL)
		{
			widgets[n]->x=a+(maxw/2.0f)-(widgets[n]->width/2.0f);
		}
		
		if(distribution_type==RBW_DISTRIBUTION_HORITZONTAL)
		{
			widgets[n]->y=c+(maxh/2.0f)-(widgets[n]->height/2.0f);
		}
		
		cairo_save(cairo);
			cairo_translate(cairo,x,y);	
			widgets[n]->Draw(cairo);
		cairo_restore(cairo);	
	}
}

void RoboMenu::OnMessage(Widget * widget, MessageEvent * event)
{
	if(event->msg->id==RBW_MSG_SHOW_REQ)
	{
		string name_req = ((MessageDataString *)event->msg->data["name"])->value;
		
		if(name_req==name)
		{
			Show();
		}
		else Hide();
	}
}

void RoboMenu::Show()
{
	visible=true;
}

void RoboMenu::Show(string target)
{
	Message *msg = new Message(RBW_MSG_SHOW_REQ);
	msg->data["name"]=new MessageDataString(target);
	msg->data["source"]=new MessageDataString(name);
	
	RoboCore::GetCore()->window->SendMessage(NULL,NULL,msg);
	
}

void RoboMenu::Hide()
{
	visible=false;
}
