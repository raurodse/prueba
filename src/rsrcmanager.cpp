

#include "rsrcmanager.h"
#include <lsf-1.0/filesystem.hpp>
#include <dirent.h>
#include <vector>

using namespace net::lliurex::robolliurex;
using namespace std;

/*!
  Resource Manager loads a directory with png files, and keeps them as cairo surfaces for later querys 
  \param path directory containing png to load
 */ 
RsrcManager::RsrcManager(string path)
{
	
	vector<string> files;
	
	files=filesystem::List(path+"/*.png");
	
	clog<<"* Loading resources:...";
	for(string file : files)
	{
		string name = filesystem::BaseName(file);
		
		surfaces[name]=cairo_image_surface_create_from_png(file.c_str());
	}
	clog<<"ok"<<endl;
	
	
}

RsrcManager::~RsrcManager()
{
	clog<<"* Unloading resources:...";
	for(pair<string,cairo_surface_t *>iter : surfaces)
	{
		cairo_surface_destroy(iter.second);
	}
	clog<<"ok"<<endl;
}

/*!
	Query for a surface
	\param name surface name, which is given by the file basename ('example.png')
 */ 
cairo_surface_t * RsrcManager::GetSurface(string name)
{
	return surfaces[name];
}
