#include "Target.hh"
#include "MagneticField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "DetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Sphere.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>
#define pir 3.14159265358979323846
#include "G4Paraboloid.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Trap.hh"
#include "G4GenericTrap.hh"
#include "G4VSolid.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4NistManager.hh"
#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"
#include "G4AutoDelete.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4PVReplica.hh"
#include <stdio.h>
#include <cstdio>
#include "string.h"
#include "vector"
#include "MaterialList.hh"

#include "ToFSD.hh"
#include "TargetSD.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ThreadLocal MagneticField* DetectorConstruction::fMagneticField = 0;
G4ThreadLocal G4FieldManager* DetectorConstruction::fFieldMgr = 0;
	DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{

	//	mppc_z=Scintz;
	//Detector Position

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	bool checkOverlaps = true;
	// ------------- Materials -------------

	G4VisAttributes* world= new G4VisAttributes(G4Colour(0,0,0));
	G4VisAttributes* mppc_vis= new G4VisAttributes(G4Colour(200,0,200));
	G4VisAttributes* bs_vis= new G4VisAttributes(G4Colour(200,200,0));
	G4VisAttributes* Scint_vis= new G4VisAttributes(G4Colour(0,0,150));
	//  G4VisAttributes* shel= new G4VisAttributes(G4Colour(150,0,0));
	//	G4VisAttributes* dark= new G4VisAttributes(G4Colour(0,0,0));
  //Materials
	ConstructMaterials();
  auto air = G4Material::GetMaterial("G4_AIR");
  //auto argonGas = G4Material::GetMaterial("B5_Ar");
  auto argonGas = G4Material::GetMaterial("G4_Ar");
  auto scintillator = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  auto csI = G4Material::GetMaterial("G4_CESIUM_IODIDE");
  auto lead = G4Material::GetMaterial("G4_Pb");
	auto iron = G4Material::GetMaterial("G4_Fe");	 

	double BTOF_l = 1500*mm,BTOF_w=90*mm,BTOF_t=10*mm;
	double BTOF_guide_l=150*mm,BTOF_guide_w=45*mm;
	double BTOF_radius = 1415/2 * mm;
	double BTOF_z = 0;
	
	double FTOF_l = 500*mm,FTOF_w1 = 24*mm, FTOF_w2=90*mm,FTOF_t=5*mm;
	double FTOF_cut_l=450*mm,FTOF_cut_w2 = 83.4*mm;
	double FTOF_radius = 1364.9/2 * mm;//Outer radius
	double FTOF_z = BTOF_z+754.6*mm;//Center: BTOF_Center;
	double FTOF_gap = 7 * mm;

	double Pitch_angle=7.5*deg;
	auto PitchPlus = new G4RotationMatrix;
	auto PitchMinus = new G4RotationMatrix;

	double Solenoid_r1 = 800*mm,Solenoid_r2 = 900*mm,Solenoid_l = 3000*mm;	

	G4RotationMatrix* MirrorXZ
		= new G4RotationMatrix;
	MirrorXZ->rotateY(180*deg);
  

	//geometries---
	auto worldSolid 
    = new G4Box("worldBox",3.*m,3.*m,3.*m);
  auto worldLogical
    = new G4LogicalVolume(worldSolid,air,"worldLogical");
  auto worldPhysical
    = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,
                        false,0,checkOverlaps);
  


	//
	// ------------- Volumes --------------
	//
	auto TargetSolid
		= new G4Sphere("targetSolid",fTargetR/2*mm,fTargetR*mm,0,360*deg,0,180*deg);
	TargetLogical
		= new G4LogicalVolume(TargetSolid,air,"TargetLogical");

	auto LAMPSSolenoid
		= new G4Tubs("LAMPSSolenoid",Solenoid_r1, Solenoid_r2,Solenoid_l, 0,360*deg);
	auto LAMPSSolenoidLogical
		= new G4LogicalVolume(LAMPSSolenoid,iron, "LAMPSSolenoidLogical");
	auto LAMPSBFieldSolid
		= new G4Tubs("LAMPSBFieldSolid",0, Solenoid_r1,Solenoid_l, 0,360*deg);
	LAMPSBFieldLogical
		= new G4LogicalVolume(LAMPSBFieldSolid,air,"LAMPSBFieldLogical");
	auto TargetPhysical
		= new G4PVPlacement(0,G4ThreeVector(fTargetX*mm,fTargetY*mm,fTargetZ*mm),TargetLogical,"TargetLogical",LAMPSBFieldLogical,false,0,checkOverlaps);

  auto visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
	new G4PVPlacement(0,G4ThreeVector(),LAMPSBFieldLogical,"LAMPSBFieldLogical",worldLogical,false,0,checkOverlaps);
  visAttributes->SetVisibility(false);
  LAMPSBFieldLogical->SetVisAttributes(visAttributes);
  worldLogical->SetVisAttributes(visAttributes);



  // placement of Tube
  
  G4RotationMatrix* fieldRot = new G4RotationMatrix();
  fieldRot->rotateX(90.*deg);
	/*
  */
  // set step limit in tube with magnetic field  
//  G4UserLimits* userLimits = new G4UserLimits(1*m);


	// 
	auto BTOFBodySolid
		= new G4Box("BTOFBody",BTOF_w/2,BTOF_t/2,(BTOF_l-2*BTOF_guide_l)/2);
	auto BTOFGuideSolid
		= new G4Trd("BTOFGuide",BTOF_w/2,BTOF_guide_w/2,BTOF_t/2,BTOF_t/2,BTOF_guide_l/2);
	auto BTOFTempSolid 
		= new G4UnionSolid("BTOFTemp",BTOFBodySolid,BTOFGuideSolid,0,G4ThreeVector(0,0,(BTOF_l-2*BTOF_guide_l)/2+BTOF_guide_l/2));
	auto BTOFSolid
		= new G4UnionSolid("BTOFSolid",BTOFTempSolid,BTOFGuideSolid,MirrorXZ,G4ThreeVector(0,0,-(BTOF_l-2*BTOF_guide_l)/2-BTOF_guide_l/2));
	BTOFLogical
		= new G4LogicalVolume(BTOFSolid,scintillator,"BTOFLogical");
//	new G4PVPlacement(0,G4ThreeVector(0,0,8*m),BTOFLogical,"BTOFPhysical",worldLogical,false,0,checkOverlaps);
//	PitchPlus->rotateZ(2*Pitch_angle);	
	for(int i=0;i<48;i++){
		auto Pitch = new G4RotationMatrix;
		Pitch->rotateZ(-(i+4)*Pitch_angle);
		if(i==41||i==42||i==46||i==47) continue;
		new G4PVPlacement(Pitch,G4ThreeVector(BTOF_radius*sin((i+4)*Pitch_angle) ,-BTOF_radius*cos((i+4)*Pitch_angle),0),BTOFLogical, "BTOFSegment"+std::to_string(i),LAMPSBFieldLogical,false, 0,checkOverlaps);
	}

	


	auto FTOFSolid
		= new G4Trd("FTOFGuide",FTOF_w1/2,FTOF_w2/2,FTOF_t/2,FTOF_t/2,FTOF_l/2);
	FTOFLogical
		= new G4LogicalVolume(FTOFSolid,scintillator,"FTOFLogical");
	auto FTOFCutSolid
		= new G4Trd("FTOFGuide",FTOF_w1/2,FTOF_cut_w2/2,FTOF_t/2,FTOF_t/2,FTOF_cut_l/2);
	FTOFCutLogical
		= new G4LogicalVolume(FTOFCutSolid,scintillator,"FTOFCutLogical");
	

	for(int i=0;i<48;i++){
		auto Pitch = new G4RotationMatrix;
		Pitch->rotateX(-90*deg);
		Pitch->rotateY(-(i+4)*Pitch_angle);
		if(i<41){
			if(i%2==0){
		new G4PVPlacement(Pitch,G4ThreeVector((FTOF_radius-FTOF_l/2)*sin((i+4)*Pitch_angle) ,-(FTOF_radius-FTOF_l/2)*cos((i+4)*Pitch_angle),FTOF_z+FTOF_gap/2),FTOFLogical, "FTOFSegment"+std::to_string(i),LAMPSBFieldLogical,false, 0,checkOverlaps);
			}
			else{
		new G4PVPlacement(Pitch,G4ThreeVector((FTOF_radius-FTOF_l/2)*sin((i+4)*Pitch_angle) ,-(FTOF_radius-FTOF_l/2)*cos((i+4)*Pitch_angle),FTOF_z-FTOF_gap/2),FTOFLogical, "FTOFSegment"+std::to_string(i),LAMPSBFieldLogical,false, 0,checkOverlaps);
			}
		}
		else{
			if(i%2==0){
			new G4PVPlacement(Pitch,G4ThreeVector((FTOF_radius-FTOF_l/2-25*mm)*sin((i+4)*Pitch_angle) ,-(FTOF_radius-FTOF_l/2-25*mm)*cos((i+4)*Pitch_angle),FTOF_z+FTOF_gap/2),FTOFCutLogical, "FTOFSegment"+std::to_string(i),LAMPSBFieldLogical,false, 0,checkOverlaps);
			}
			else{
			new G4PVPlacement(Pitch,G4ThreeVector((FTOF_radius-FTOF_l/2-25*mm)*sin((i+4)*Pitch_angle) ,-(FTOF_radius-FTOF_l/2-25*mm)*cos((i+4)*Pitch_angle),FTOF_z-FTOF_gap/2),FTOFCutLogical, "FTOFSegment"+std::to_string(i),LAMPSBFieldLogical,false, 0,checkOverlaps);
			}
		}
	}


	//always return the physical World
  return worldPhysical;
}
void DetectorConstruction::ConstructMaterials()
{
  auto nistManager = G4NistManager::Instance();

  // Air 
  nistManager->FindOrBuildMaterial("G4_AIR");
  
  // With a density different from the one defined in NIST
  nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  
 
	//Iron
//  nistManager->FindOrBuildMaterial("G4_Fe");
  // Vacuum "Galactic"
  // nistManager->FindOrBuildMaterial("G4_Galactic");

  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void DetectorConstruction::ConstructSDandField()
{
  // sensitive detectors -----------------------------------------------------
	auto sdManager = G4SDManager::GetSDMpointer();
  G4String SDname;
	
	TargetSD* TargetDet = new TargetSD(SDname = "/Target");
	sdManager->AddNewDetector(TargetDet);
	TargetLogical->SetSensitiveDetector(TargetDet);	
 
	ToFSD* ToFDet = new ToFSD(SDname = "/ToF");
	sdManager->AddNewDetector(ToFDet);
	BTOFLogical->SetSensitiveDetector(ToFDet);	
	FTOFLogical->SetSensitiveDetector(ToFDet);	
	FTOFCutLogical->SetSensitiveDetector(ToFDet);	
	

  // magnetic field ----------------------------------------------------------
  fMagneticField = new MagneticField();
  fFieldMgr = new G4FieldManager();
  fFieldMgr->SetDetectorField(fMagneticField);
  fFieldMgr->CreateChordFinder(fMagneticField);
  G4bool forceToAllDaughters = true;
  LAMPSBFieldLogical->SetFieldManager(fFieldMgr, forceToAllDaughters);
}    
