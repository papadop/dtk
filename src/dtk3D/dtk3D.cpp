/* dtk3D.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 09:23:28 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 11:42:27 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Change Log:
 * 
 */

#include "dtk3D.h"
#include "dtk3DItemMesh.h"

namespace dtk3D
{
    namespace mesh {
	namespace _private {
	    dtk3DItemMeshPluginFactory factory;
	    dtk3DItemMeshPluginManager manager;
	}
	
	dtk3DItemMeshPluginFactory& pluginFactory(void) {
	    return _private::factory;
	}
	
	dtk3DItemMeshPluginManager& pluginManager(void) {
	    return _private::manager;
	}
    }
}