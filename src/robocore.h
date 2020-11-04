

#ifndef _ROBOCORE_
#define _ROBOCORE_

#include <cairo.h>
#include <lgi-1.0/application.hpp>
#include <lgi-1.0/x11window.hpp>
#include <lgi-1.0/layer.hpp>

#include "robowidgets.h"
#include "rsrcmanager.h"

#ifdef LOCAL
	#define FIRM_PATH "../rsrc/FIRM0328.lgo"
#else
	#define FIRM_PATH "/lib/firmware/rcx/FIRM0328.lgo"
#endif

#define RBC_PORT_COM1	0x00
#define RBC_PORT_COM2	0x01
#define RBC_PORT_USB	0x02

#define RBC_RUN_STATUS_DOWNLOADING		0x01
#define RBC_RUN_STATUS_COMPLETED		0x02
#define RBC_RUN_STATUS_NQC_ERROR		0x03
#define RBC_RUN_STATUS_COMM_ERROR		0x04

#define RBC_TEST_STATUS_RUNNING			0x01
#define RBC_TEST_STATUS_OK			0x02
#define RBC_TEST_STATUS_ERROR			0x03

#define RBC_FIRM_STATUS_DOWNLOADING		0x01
#define RBC_FIRM_STATUS_COMPLETED		0x02
#define RBC_FIRM_STATUS_ERROR			0x03

namespace net
{
	namespace lliurex
	{
		namespace robolliurex
		{
		
			class MainWindow : public lgi::X11Window
			{
			
				private:
					bool have_batt;
					float batt;
					cairo_surface_t * srf_background;
			
				public:
				
				MainWindow();
				
				/*!
				 overrided flip method, so we can perform custom drawing operations
				*/
				void Flip();
				
				/*!
				 Sets battery level 
				*/
				void SetBattery(float level);
				
			};
		
			class RoboCore : public lgi::Application
			{
				private:
					static RoboCore * singleton;
					RoboCore();
					~RoboCore();
					
					
					
				
				public:
					static std::string comm_name[];
					int comm_port;
					bool usb_tower;
				
					bool is_firmware_downloading;
					bool is_comm_testing;
					bool is_program_downloading;
					bool is_battery_requesting;
				
				
				
					std::string program_path;
					std::string firmware_path;
				
					MainWindow * window;
					RsrcManager * rsrc;
					
					/*!
						Initialization
					*/
					void Init();
					
					
					/*!
						static singleton
					*/
					static RoboCore * GetCore();
					
					/*!
						static singleton destructor
					*/
					static void Destroy();
				
					/*!
						Performs an asynchronous firmware download
					*/
					void DownloadFirmware();
					
					/*!
						Performs an asynchronous Comm test
					*/
					void TestComm();
					
					/*!
						Performs an asynchronous program download
					*/
					void DownloadProgram(std::string path);
					
					/*!
						Performs an asynchronous battery read
					*/
					void GetBattery();
					
					
					/*!
						Overrided custom event dispatching
					*/
					int CustomEventsDispatch();
					
					/*!
						Overrided message hook
					*/
					void OnMessage(BaseWindow * window,Layer * layer, Widget * widget,MessageEvent * event);
			};
		}
	}
}

#endif
