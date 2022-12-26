//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "tls.hh"
#include <cmath>
#include <vector>
#include "G4TwoVector.hh"

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

using std::vector;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class DetectorMessenger;
class G4GlobalMagFieldMessenger;


class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();
		virtual ~DetectorConstruction();



	public:
		virtual G4VPhysicalVolume* Construct();
		void MakeScintWLG(G4VPhysicalVolume * v);
		//    virtual void ConstructSDandField();
		/*    void SetTargetMaterial (G4String );
				void SetChamberMaterial(G4String );
				void SetMaxStep (G4double );*/
	private:
		G4double fExpHall_x;
		G4double fExpHall_y;
		G4double fExpHall_z;

		G4double Scintx;
		G4double Scinty;
		G4double Scintz;

		G4double window_x;
		G4double window_z;
		G4double window_th;
		G4double window_posy;

		G4double mppc_x;
		G4double mppc_z;
		G4double mppc_th;
		G4double mppc_posx[8];
		G4double mppc_posy;
		G4double mppc_posz;

		G4double air_th;
		G4double resin_th;
		G4double resin_x;
		G4double resin_z;
		G4double resin_posy;

		G4double mirror_lgh;
		G4double mirror_wth1;
		G4double mirror_wth2;
		G4double mirror_th;
		G4double mirror_posx;
		G4double mirror_posy;
		G4double mirror_posz;



		G4double BS_lgh;
		G4double BS_wth1;
		G4double BS_wth2;
		G4double BS_th;
		G4double BS_posx;
		G4double BS_posy;
		G4double BS_posz;

		G4double Glgh;
		G4double Gposy;
		vector<G4TwoVector> GVtx;
		vector<G4TwoVector> GAirVtx1;
		vector<G4TwoVector> GAirVtx2;
		vector<G4TwoVector> GAirVtx3;
		vector<G4TwoVector> GAirVtx4;
		vector<G4TwoVector> GMylarVtx1;
		vector<G4TwoVector> GMylarVtx2;
		vector<G4TwoVector> GMylarVtx3;
		vector<G4TwoVector> GMylarVtx4;
		vector<G4TwoVector> GBSVtx1;
		vector<G4TwoVector> GBSVtx2;
		vector<G4TwoVector> GBSVtx3;
		vector<G4TwoVector> GBSVtx4;
		G4double GOutWth;
		G4double GOutHgh;

		G4double GuideVtx[4];
		G4double GuideEndVtx[4];
		G4double GuideMVtx[4];
		G4double GuideEndMVtx[4];
		G4double GuideBVtx[4];
		G4double GuideEndBVtx[4];
		
		G4RotationMatrix* RotGuide= new G4RotationMatrix();
		G4RotationMatrix* RotGuide1= new G4RotationMatrix();
		G4RotationMatrix* RotGuide2= new G4RotationMatrix();
		//		G4UserLimits* fStepLimit;      


		// methods
		/*    void DefineMaterials();
				G4VPhysicalVolume* DefineVolumes();

		// data members
		G4int fNbOfChambers;

		G4LogicalVolume*   fLogicTarget;     // pointer to the logical Target
		G4LogicalVolume**  fLogicChamber;    // pointer to the logical Chamber

		G4Material*        fTargetMaterial;  // pointer to the target  material
		G4Material*        fChamberMaterial; // pointer to the chamber material

		G4UserLimits* fStepLimit;            // pointer to user step limits

		DetectorMessenger*  fMessenger;   // messenger
		*/
		//  G4bool fCheckOverlaps;
		//  G4LogicalVolume* Detreg_log;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*DetectorConstruction_h*/
