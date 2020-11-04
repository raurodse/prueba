
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>

#include <cairo.h>
#include <lgi-1.0/x11window.hpp>
#include <lgi-1.0/layer.hpp>
#include <lsf-1.0/utils.hpp>

#include <gtk/gtk.h>
 
#include "robocore.h"
#include "robowidgets.h"
#include "rsrcmanager.h"
#include "roboslot.h"
#include "robopilot.h"





using namespace std;
using namespace net::lliurex::lgi;
using namespace net::lliurex::robolliurex;



int main(int argc,char * argv[])
{
	/* locale setup */
	setlocale(LC_ALL,"");
	bindtextdomain("robolliurex","/usr/share/locale");
	textdomain("robolliurex");
	
	RoboCore * core = RoboCore::GetCore();
	core->Init();
	core->Run(LGI_DISPATCH_EVENTS_WAIT);
	
	RoboCore::Destroy();
}
