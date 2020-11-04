
#ifndef _ROBOWIDGETS_
#define _ROBOWIDGETS_

#include <lgi-1.0/widget.hpp>
#include <lgi-1.0/layer.hpp>
#include <string>
#include <map>

#define RBW_POSITION_FIXED		0x0
#define RBW_POSITION_FACTOR	0x1

#define RBW_DISTRIBUTION_HORITZONTAL	0x0
#define RBW_DISTRIBUTION_VERTICAL		0x1
#define RBW_DISTRIBUTION_FACTOR			0x2


#define RBW_MSG_TOOLBOX_RET	0x01
#define RBW_MSG_SHOW_REQ		0x02
#define RBW_MSG_FIRM_STATUS	0x03
#define RBW_MSG_TEST_STATUS	0x04
#define RBW_MSG_RUN_STATUS	0x05
#define RBW_MSG_BATTERY_STATUS	0x06
#define RBW_MSG_DIALOG_LOAD	0x07
#define RBW_MSG_DIALOG_SAVE	0x08
#define RBW_MSG_DIALOG_LOAD_CANCEL	0x09
#define RBW_MSG_DIALOG_SAVE_CANCEL	0x0a
#define RBW_MSG_PILOT_LOAD	0x0b

using namespace net::lliurex::lgi;

void draw_round_square(cairo_t * cairo,float x,float y,float width,float height);

typedef struct
{
	float x;
	float y;
}RPoint;
	

class Button : public Widget
{
	
		
	public:
		bool enabled;
	
		std::string text;
		Button(std::string text);
		void Init(cairo_t * cairo);
		void Draw(cairo_t * cairo);
		void Enable(bool enable);
};

class ImageButton: public Widget
{
	private:
		cairo_surface_t * surface;
	
	public:
		ImageButton(cairo_surface_t * surface);
		void SetImage(cairo_surface_t * surface);
		void Draw(cairo_t * cairo);
		
};

class Image: public Widget
{
	private:
		cairo_surface_t * surface;
	public:
		Image(cairo_surface_t * surface);
		void SetImage(cairo_surface_t * surface);
		void Draw(cairo_t * cairo);
};

class Switch: public Widget
{
	private:
		int * value;
		int myvalue;
		std::string text;
	public:
		Switch(std::string text,int * value,int myvalue);
		void Init(cairo_t * cairo);
		void Draw(cairo_t * cairo);
		void OnMouseClick(MouseClickEvent * event);
};

class ProgressBar: public Widget
{
	private:
		float value;
		std::string text;
	
	public:
		ProgressBar(std::string text,float value);
		void Draw(cairo_t * cairo);
		void SetValue(float value);
		void SetText(std::string text);
	
};

class Label: public Widget
{
	private:
		std::string text;
	
	public:
		Label(std::string text);
		void Init(cairo_t * cairo);
		void Draw(cairo_t * cairo);
		void SetText(std::string text);
};

class RoboMenu: public Layer
{
	protected:
		int position_type;
		int distribution_type;
	
		std::string label;
		std::string name;
	
		float fx;
		float fy;
	
	
		float color_fill[4];
		float color_border[4];
		float color_text[4];
		
		std::map<Widget*,RPoint> points;
	
	public:
		RoboMenu(std::string label,float x,float y,int position_type,int distribution_type);
		void Draw(cairo_t * cairo);
	
		void OnMessage(Widget * widget, MessageEvent * event);
	
		virtual void Show();
		virtual void Show(std::string target);
		virtual void Hide();
		
};
#endif
