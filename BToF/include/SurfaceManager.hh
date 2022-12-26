#ifndef SurfaceManager_hh
#define SurfaceManager_hh 1
#include "G4OpticalSurface.hh"
#include "G4MaterialPropertiesTable.hh"
class SurfaceManager
{
	public:
		SurfaceManager();
		~SurfaceManager();
		void SetSurface(G4OpticalSurface* Surf,G4MaterialPropertiesTable* Mpt, G4double* Photon, G4double* Rfl, G4int ent);
};
#endif
