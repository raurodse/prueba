
#ifndef _RSRCMANAGER_
#define _RSRCMANAGER_

#include <iostream>
#include <map>
#include <cairo.h>

#ifdef LOCAL
	#define RSRC_PATH "../svg/"
#else
	#define RSRC_PATH "/usr/share/pixmaps/robolliurex/"
#endif

#define RBW_TARGET_NONE			0x00
#define RBW_TARGET_STOP			0x01
#define RBW_TARGET_MOTOR_FORWARD	0x02
#define RBW_TARGET_MOTOR_BACKWARD	0x04
#define RBW_TARGET_LIGHT		0x08
#define RBW_TARGET_PRESS_RELEASE	0x10
#define RBW_TARGET_PRESS_ACTIVE		0x20
#define RBW_TARGET_LIGHT_SENSOR		0x40
#define RBW_TARGET_CLOCK		0x80
#define RBW_TARGET_CLOCK_1S		0x100
#define RBW_TARGET_CLOCK_2S		0x200
#define RBW_TARGET_CLOCK_4S		0x400
#define RBW_TARGET_CLOCK_6S		0x800
#define RBW_TARGET_CLOCK_8S		0x1000
#define RBW_TARGET_CLOCK_10S		0x2000
#define RBW_TARGET_LIGHT_WHITE		0x4000
#define RBW_TARGET_LIGHT_BLACK		0x8000

namespace net
{
	namespace lliurex
	{
		namespace robolliurex
		{
			
			class RsrcManager
			{
				private:
					std::string basepath;
					std::map<std::string,cairo_surface_t *>surfaces;
				
				public:
					
					RsrcManager(std::string path);
					~RsrcManager();
					
					cairo_surface_t * GetSurface(std::string name);
			};
		}
	}
}
#endif
