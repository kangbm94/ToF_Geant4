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
#include "G4FieldManager.hh"


using std::vector;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class DetectorMessenger;
class G4GlobalMagFieldMessenger;
class MagneticField;


class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();
		virtual ~DetectorConstruction();
		void ConstructMaterials();
		void ConstructSDandField();

	public:
		virtual G4VPhysicalVolume* Construct();
		void MakeScintWLG(G4VPhysicalVolume * v);
		//    virtual void ConstructSDandField();
		/*    void SetTargetMaterial (G4String );
				void SetChamberMaterial(G4String );
				void SetMaxStep (G4double );*/
	private:

		G4double mppc_x;
		G4double mppc_z;
		G4double mppc_th;
		G4double mppc_posx[8];
		G4double mppc_posy;
		G4double mppc_posz;
    static G4ThreadLocal MagneticField* fMagneticField;
    static G4ThreadLocal G4FieldManager* fFieldMgr;

		//		G4UserLimits* fStepLimit;      
		G4LogicalVolume* BTOFLogical;
		G4LogicalVolume* FTOFLogical;
		G4LogicalVolume* FTOFCutLogical;
		G4LogicalVolume* LAMPSBFieldLogical;
		G4LogicalVolume* TargetLogical;

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
