#include "SurfaceManager.hh"
SurfaceManager::SurfaceManager()
{
}
SurfaceManager::~SurfaceManager()
{
}

void SurfaceManager:: SetSurface(G4OpticalSurface* Surf,G4MaterialPropertiesTable* Mpt, G4double* Photon, G4double* Rfl, G4int ent)
{
//	Surf = new G4OpticalSurface("mirror");

	//glisur

	/*
	Surf->SetType(dielectric_metal);
	Surf->SetFinish(polished);
//	Surf->SetFinish(ground);
	Surf->SetModel(glisur);
*/
	//LUT
	Surf->SetType(dielectric_LUT);
	Surf->SetModel(LUT);
	Surf->SetFinish(polishedteflonair);
	Mpt->AddProperty("REFLECTIVITY",Photon,Rfl,ent);
	for(int i=0;i<ent;i++)
	{
		G4cout<<"[SurfMan]:: Rfl "<<i<<" is : "<<Rfl[i]<<G4endl;
	}
	Surf->SetMaterialPropertiesTable(Mpt);
//	Surf->SetType(dielectric_LUTDAVIS);
//	Surf->SetModel(DAVIS);
	G4cout<<"Surface Set:"<<G4endl;
}
