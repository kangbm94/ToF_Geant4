/// \file /src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "SurfaceManager.hh"
#include "DetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
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

#include "MPPCSD.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
	DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
	fExpHall_x = 25*cm;
	fExpHall_y = 45*cm;
	fExpHall_z = 25*cm;

	Scintx=7*mm;
	Scinty=40*mm;
	Scintz= 2.5*mm;

	Glgh=50*mm;
	Gposy=Scinty+Glgh;
	GOutWth=35/2*mm;
	GOutHgh=4*mm;
//	air_th=0.01*mm;
	air_th=0*mm;
	mirror_th= 0.1*mm;      
	BS_th= 0.1*mm;      

	Double_t tmp=1*nm;
	Double_t tmp2=2*tmp;
	Double_t tmp3=3*tmp;



	mirror_lgh  = Scinty;
	mirror_wth1  = Scintx+2*air_th+2*mirror_th;
	mirror_wth2  = Scintz+2*air_th;
	mirror_posx = Scintx+mirror_th+2*air_th;
	mirror_posz = Scintz+mirror_th+2*air_th;


	BS_lgh  = mirror_lgh;
	BS_wth1  = mirror_wth1+2*BS_th;
	BS_wth2  = mirror_wth2+2*mirror_th;
	BS_posx=mirror_posx+mirror_th+BS_th;
	BS_posz=mirror_posz+mirror_th+BS_th;
	BS_posy=mirror_lgh+BS_th;



	//	mppc_z=Scintz;
	mppc_x=1.5*mm;
	mppc_z=1.5*mm;
	mppc_th=0.5*mm;
	for(int i=0;i<3;i++)
	{
		mppc_posx[i]=-4.2+4.2*i;
	}
	mppc_posz=0;

	resin_x=mppc_x;
	resin_z=mppc_z;
	window_x=mppc_x;
	window_z=mppc_z;
	window_th=0.15*mm;
	resin_th = 0.05*mm;
	resin_posy=Scinty+resin_th;
	window_posy=resin_posy+resin_th+window_th;

	mppc_posy=window_posy+mppc_th+window_th;	



	//Detector
	//Detector Position
	RotGuide->rotateX(90*deg);
	RotGuide2->rotateX(90*deg);
	RotGuide2->rotateY(180*deg);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{

	// ------------- Materials -------------
	G4double a, z, density, fractionmass;
	G4int nelements,natoms,ncomponents;



	//Aluminium
	//
	G4Element* Al = new G4Element("Aluminium","Al",z=13, a=26.98*g/mole);
	G4Material* Aluminium = new G4Material("Aluminium", density=2.70*g/cm3, nelements=1);
	Aluminium->AddElement(Al,1);
	// Air
	//
	G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
	G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
	G4Element* H  = new G4Element( "Hydrogen"  , "H"  ,  1.,   1.00794 *g/mole );
	G4Element* C  = new G4Element("Carbon"  ,"C" , z= 6., a=12.01*g/mole);
	G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
	air->AddElement(N, 70.*perCent);
	air->AddElement(O, 30.*perCent);

	//window
	G4Material* Epoxy = new G4Material("Epoxy",density=1.5*g/cm3,nelements=3);
	Epoxy->AddElement(O,36*perCent);
	Epoxy->AddElement(H,9*perCent);
	Epoxy->AddElement(C,55*perCent);


	G4Material* resin = new G4Material("resin",density=1.02*g/cm3,nelements=3);
	resin->AddElement(O,10*perCent);
	resin->AddElement(H,60*perCent);
	resin->AddElement(C,30*perCent);

	//water
	//
	G4Material* water = new G4Material("water",1*g/cm3,2);	
	water->AddElement(H,natoms=2);
	water->AddElement(O,natoms=1);



	//Scintillator
	//
	G4Material* EJ230 = new G4Material("EJ230",1.023*g/cm3,2);
	EJ230->AddElement(C,47.663*perCent);
	EJ230->AddElement(H,52.337*perCent);
	G4double ScinPhWv[]={
		287,300,313,325,338,
		350,363,375,388,400,
		413,425,438,450,463,
		475,488,500,
		513,525,538,550,563
	};
	const G4int nEnt = sizeof(ScinPhWv)/sizeof(G4double);
	G4double ScinPhEn[nEnt];
	G4double ScinRIdx[nEnt];
	G4double AlRIdx[nEnt];
	G4double ScinAbs[nEnt];
	G4double ScinFast[nEnt];
	G4double EpoxyRIdx[nEnt];

	G4double ScinFastPrt[nEnt]=//EJ232
	{
		0.00,0.00,0.0,0,0.05,
		0.25,0.7,0.9,0.7,0.55,
		0.4,0.3,0.15,0.07,0,
		0,0,0,
		0,0,0,0,0
	};

	/* 
		G4double ScinFastPrt[nEnt]=//EJ230
		{
		0.00,0.00,0.00,0.00,0.00,
		0.01,0.125,0.50,0.90,1.00,
		0.90,0.55,0.35,0.20,0.10,
		0.075,0.05,0.01,
		0,0,0,0,0
		};
		*/
	G4double ScinFastTot;
	for(int i=0;i<nEnt;i++)
	{	
//		AlRIdx[i]=1.2;
		ScinFastTot+=ScinFastPrt[i];
		ScinPhEn[i]=1239.84/ScinPhWv[i]*eV;
		ScinRIdx[i]=1.58;
		ScinAbs[i]=140*cm;//EJ230
		EpoxyRIdx[i]=1.55;
		//		ScinAbs[i]=155*cm;//EJ232, Measured
	}
	for(int i=0;i<nEnt;i++)
	{
		ScinFast[i]=ScinFastPrt[i]/ScinFastTot;
	}	
//	G4MaterialPropertiesTable* AlMPT = new G4MaterialPropertiesTable();
//	AlMPT->AddProperty("RINDEX",ScinPhEn, AlRIdx,nEnt);
//	Aluminium->SetMaterialPropertiesTable(AlMPT);

	G4MaterialPropertiesTable* EJ230MPT = new G4MaterialPropertiesTable();
	//	EJ230MPT->AddConstProperty("SCINTILLATIONYIELD",9700/MeV);//230
	EJ230MPT->AddConstProperty("SCINTILLATIONYIELD",8400/MeV);//232
	EJ230MPT->AddConstProperty("RESOLUTIONSCALE",0.1);
	EJ230MPT->AddConstProperty("FASTTIMECONSTANT",0.00001*ns);
	EJ230MPT->AddProperty("RINDEX",ScinPhEn, ScinRIdx,nEnt);
	EJ230MPT->AddProperty("ABSLENGTH",ScinPhEn,ScinAbs,nEnt);
	EJ230MPT->AddProperty("FASTCOMPONENT",ScinPhEn,ScinFast,nEnt);
	EJ230->SetMaterialPropertiesTable(EJ230MPT);

	G4MaterialPropertiesTable* EpoxyMPT = new G4MaterialPropertiesTable();
	EpoxyMPT->AddProperty("RINDEX",ScinPhEn, EpoxyRIdx,nEnt);
	Epoxy->SetMaterialPropertiesTable(EpoxyMPT);



	G4double RefractiveIndex_resin[nEnt];
	G4double Absorption_resin[nEnt];
	for(G4int i=0;i<nEnt;i++){
		RefractiveIndex_resin[i]=1.5;
		Absorption_resin[i] = 140.*cm;
	}   
	G4MaterialPropertiesTable* mpt_resin = new G4MaterialPropertiesTable();
	mpt_resin->AddProperty("RINDEX",ScinPhEn,RefractiveIndex_resin,nEnt);
	mpt_resin->AddProperty("ABSLENGTH",ScinPhEn,Absorption_resin,nEnt);
	resin->SetMaterialPropertiesTable(mpt_resin);

	//	EJ230->GetIonisation()->SetBirksConstant(0.123*mm/MeV);
	//Black sheet
	//
	density = 0.95*g/cm3;
	G4Material* Blacksheet
		= new G4Material("Blacksheet",density,2);
	Blacksheet->AddElement(C, 1);
	Blacksheet->AddElement(H, 2);
	// ------------ Generate & Add Material Properties Table ------------
	//
	//610 nm to 190nm to 180 nm.
	//ev = 1239.84/lambda[nm]
	G4double photonEnergy[] =
	{ 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
		2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
		2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
		2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
		2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
		3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
		3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
		3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV,
		4.275*eV, 4.428*eV, 4.592*eV, 4.769*eV,
		4.960*eV, 5.167*eV, 5.390*eV, 5.636*eV,
		5.904*eV, 6.199*eV, 6.525*eV, 6.888*eV
	};

	const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

	G4double pE[nEntries];
	for(int i=0;i<nEntries;i++)
	{
		pE[i]=photonEnergy[i]/eV;
	}

	// BS MPT
	G4double BSabsorption[nEntries];
	G4double BSRIdx[nEntries];
	for(int i=0;i<nEntries;i++)
	{
		BSabsorption[i]=1*nm;
		BSRIdx[i]=1.5;
	}
	G4MaterialPropertiesTable* BSMPT = new G4MaterialPropertiesTable();
	BSMPT->AddProperty("RINDEX",photonEnergy,BSRIdx,nEntries);
	BSMPT->AddProperty("ABSLENGTH",photonEnergy,BSabsorption,nEntries);
	Blacksheet->SetMaterialPropertiesTable(BSMPT);
	//
	// Air
	//

	G4double refractiveIndex2[nEntries] =
	{1};
	for(int i=0;i<nEntries;i++)
	{
		refractiveIndex2[i]=1;
	}
	G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
	myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex2, nEntries);

	//  G4cout << "Air G4MaterialPropertiesTable" << G4endl;
	//  myMPT2->DumpTable();

	air->SetMaterialPropertiesTable(myMPT2);

	//
	//glass
	//

	//
	//------------- color ---------------
	//

	G4VisAttributes* world= new G4VisAttributes(G4Colour(0,0,0));
	G4VisAttributes* mppc_vis= new G4VisAttributes(G4Colour(200,0,200));
	G4VisAttributes* bs_vis= new G4VisAttributes(G4Colour(200,200,0));
	G4VisAttributes* Scint_vis= new G4VisAttributes(G4Colour(0,0,150));
	//  G4VisAttributes* shel= new G4VisAttributes(G4Colour(150,0,0));
	//	G4VisAttributes* dark= new G4VisAttributes(G4Colour(0,0,0));


	//
	// ------------- Volumes --------------
	//

	//
	// The experimental Hall
	//
	G4Box* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);
	G4LogicalVolume* expHall_log
		= new G4LogicalVolume(expHall_box,air,"World",0,0,0);

	G4VPhysicalVolume* expHall_phys
		= new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);
	expHall_log   ->SetVisAttributes(world);

	//
	//Scintillator
	//
	G4VSolid* Scint = new G4Box("EJ230",Scintx,Scinty,Scintz);
	G4LogicalVolume* Scint_log = new G4LogicalVolume(Scint,EJ230,"Scintillator",0,0,0);
	Scint_log   ->SetVisAttributes(Scint_vis);



	G4VPhysicalVolume* Scint_phys=new G4PVPlacement(0,G4ThreeVector(0,0,0),Scint_log,"Scintillator",expHall_log,false,0);
	G4cout<<"Scintillator constructed"<<G4endl;

	//
	// mirrors
	//

	G4Box* mirror1     = new G4Box("mylar",mirror_wth1,mirror_lgh,mirror_th); 
	G4Box* mirror2     = new G4Box("mylar",mirror_th,mirror_lgh,mirror_wth2); 
	//	G4SubtractionSolid* GMylar=new G4SubtractionSolid("GuideMylar",Guide_Air,Air_Mylar);
	//	G4Box* mirror3     = new G4Box("mylar",mirror_wth1,mirror_th,mirror_wth2); 
	G4LogicalVolume* mirror1_log   = new G4LogicalVolume(mirror1,Aluminium,"mirror",0,0,0);
	G4LogicalVolume* mirror2_log   = new G4LogicalVolume(mirror2,Aluminium,"mirror",0,0,0);
	//	G4LogicalVolume* mirror3_log   = new G4LogicalVolume(mirror3,Aluminium,"mirror",0,0,0);

	G4VPhysicalVolume* Mirror_phys1=new G4PVPlacement(0,G4ThreeVector(0,0,mirror_posz),mirror1_log,"mirror",expHall_log,false,0);
	G4VPhysicalVolume* Mirror_phys2=new G4PVPlacement(0,G4ThreeVector(0,0,-mirror_posz),mirror1_log,"mirror",expHall_log,false,0);
	G4VPhysicalVolume* Mirror_phys3=new G4PVPlacement(0,G4ThreeVector(mirror_posx,0,0),mirror2_log,"mirror",expHall_log,false,0);
	G4VPhysicalVolume* Mirror_phys4=new G4PVPlacement(0,G4ThreeVector(-mirror_posx,0,0),mirror2_log,"mirror",expHall_log,false,0);
	//	new G4PVPlacement(0,G4ThreeVector(0,mirror_lgh,0),mirror3_log,"mirror",expHall_log,false,0);
	//	new G4PVPlacement(0,G4ThreeVector(0,-mirror_lgh,0),mirror3_log,"mirror",expHall_log,false,0);

	G4cout<<"Mylar constructed"<<G4endl;

	//
	//BS
	//
	G4Box* BS1     = new G4Box("blacksheet",BS_wth1,BS_lgh,BS_th); 
	G4Box* BS2     = new G4Box("blacksheet",BS_th,BS_lgh,BS_wth2); 
	//	G4Box* BS3     = new G4Box("blacksheet",BS_wth1,BS_th,BS_wth2); 
	//	G4SubtractionSolid* GBS=new G4SubtractionSolid("GuideBS",GuideB,Air_Mylar);
	G4LogicalVolume* BS1_log   = new G4LogicalVolume(BS1,Blacksheet,"BS",0,0,0);
	G4LogicalVolume* BS2_log   = new G4LogicalVolume(BS2,Blacksheet,"BS",0,0,0);
	//	G4LogicalVolume* BS3_log   = new G4LogicalVolume(BS3,Blacksheet,"BS",0,0,0);
	BS1_log   ->SetVisAttributes(bs_vis);
	BS2_log   ->SetVisAttributes(bs_vis);
	//	BS3_log   ->SetVisAttributes(bs_vis);
	//	GBS_log   ->SetVisAttributes(bs_vis);

	new G4PVPlacement(0,G4ThreeVector(0,0,BS_posz),BS1_log,"BS",expHall_log,false,0);
	new G4PVPlacement(0,G4ThreeVector(0,0,-BS_posz),BS1_log,"BS",expHall_log,false,0);
	new G4PVPlacement(0,G4ThreeVector(BS_posx,0,0),BS2_log,"BS",expHall_log,false,0);
	new G4PVPlacement(0,G4ThreeVector(-BS_posx,0,0),BS2_log,"BS",expHall_log,false,0);
	//	new G4PVPlacement(0,G4ThreeVector(0,BS_posy,0),BS3_log,"BS",expHall_log,false,0);
	//	new G4PVPlacement(0,G4ThreeVector(0,-BS_posy,0),BS3_log,"BS",expHall_log,false,0);/
	G4cout<<"BS constructed"<<G4endl;

	//
	//Window
	//


	G4Box* window = new G4Box("window",window_x,window_th,window_z);
	G4LogicalVolume* window_log= new G4LogicalVolume(window,Epoxy,"window",0,0,0);
	G4Box* Resin = new G4Box("resin",resin_x,resin_th,resin_z);
	G4LogicalVolume* resin_log= new G4LogicalVolume(Resin,resin,"resin",0,0,0);
	//	MPPC_log   ->SetVisAttributes(mppc_vis);
	//
	//MPPCs: name of PV should be mppc.
	//

	G4Box* MPPC = new G4Box("mppc",mppc_x,mppc_th,mppc_z);
	G4Box* VP = new G4Box("Virtual",Scintx,resin_th,Scintz);
	G4LogicalVolume* MPPC_log= new G4LogicalVolume(MPPC,Blacksheet,"mppc",0,0,0);
	G4LogicalVolume* VP_log= new G4LogicalVolume(VP,Blacksheet,"Virtual",0,0,0);
	MPPC_log   ->SetVisAttributes(mppc_vis);

	for(int i=0;i<3;i++)
	{
		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],resin_posy,-mppc_posz),resin_log,"resin",expHall_log,false,0);
		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],-resin_posy,-mppc_posz),resin_log,"resin",expHall_log,false,0);
		//		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],resin_posy,-mppc_posz),resin_log,"mppc",expHall_log,false,0);
		//		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],-resin_posy,-mppc_posz),resin_log,"mppc",expHall_log,false,0);
		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],window_posy,-mppc_posz),window_log,"window",expHall_log,false,0);
		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],-window_posy,-mppc_posz),window_log,"window",expHall_log,false,0);
		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],mppc_posy,-mppc_posz),MPPC_log,"mppc",expHall_log,false,i);
		new G4PVPlacement(0,G4ThreeVector(mppc_posx[i],-mppc_posy,-mppc_posz),MPPC_log,"mppc",expHall_log,false,i+8);
	}

	//
	//  Detection Region
	//
	//	new G4PVPlacement(0,G4ThreeVector(0,resin_posy,0),VP_log,"mirrorguide",expHall_log,false,0);
	//	new G4PVPlacement(0,G4ThreeVector(0,-resin_posy,0),VP_log,"mirrorguide",expHall_log,false,0);

	MPPCSD *mppcSD= new MPPCSD("/mppc");
	G4SDManager *SDMan = G4SDManager::GetSDMpointer();
	SDMan->AddNewDetector(mppcSD);
	MPPC_log->SetSensitiveDetector(mppcSD);

	//
	//  world Boundaries
	//


	// ------------- Surfaces --------------
	//

	G4OpticalSurface* OpMirrorSurface = new G4OpticalSurface("mirror",glisur,polished,dielectric_metal);
	G4double AlRfl[nEnt]={ 0};
   for(int i=0;i<nEnt;i++)
   {
      Double_t id=i;
      AlRfl[i]=0.975-0.03*id/11;
   }
	SurfaceManager* surf= new SurfaceManager();
	G4MaterialPropertiesTable* propertiesTable= new G4MaterialPropertiesTable();
//	propertiesTable->AddProperty("REFLECTIVITY",ScinPhEn,AlRfl,nEnt);
	G4MaterialPropertiesTable* propertiesTable2= new G4MaterialPropertiesTable();
	G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();
	G4double reflectivity2[2]={0.94,0.94};
	G4double ephoton[2] = {2.034*eV, 7*eV};
	G4OpticalSurface* Mirrorscint = new G4OpticalSurface("Mirrorscint");
//	OpMirrorSurface->SetMaterialPropertiesTable(propertiesTable);
	G4OpticalSurface* OpDiffusiveSurface = new G4OpticalSurface("diffuse");
   surf->SetSurface(Mirrorscint,propertiesTable,ScinPhEn,AlRfl,nEnt);

	new G4LogicalSkinSurface("mirror",mirror1_log,Mirrorscint);
	new G4LogicalSkinSurface("mirror",mirror2_log,Mirrorscint);
	//	new G4LogicalSkinSurface("mirror",GMylar_log,OpMirrorSurface);
	//	new G4LogicalSkinSurface("mirror",mirror3_log,OpMirrorSurface);
/*
	new G4LogicalBorderSurface("ScintWrap", Scint_phys,Mirror_phys1,Mirrorscint);
	new G4LogicalBorderSurface("ScintWrap", Scint_phys,Mirror_phys2,Mirrorscint);
	new G4LogicalBorderSurface("ScintWrap", Scint_phys,Mirror_phys3,Mirrorscint);
	new G4LogicalBorderSurface("ScintWrap", Scint_phys,Mirror_phys4,Mirrorscint);
*/
//	Mirrorscint->SetType(dielectric_LUT);
//	Mirrorscint->SetModel(LUT);
	//	Mirrorscint->SetFinish(polishedlumirrorair);
//	Mirrorscint->SetFinish(polishedvm2000air);
	//	Mirrorscint->SetFinish(etchedvm2000air);
//	Mirrorscint->SetMaterialPropertiesTable(propertiesTable);




	G4double specularlobe[2] = {0.75, 0.75};
	G4double specularspike[2] = {0, 0};
	G4double backscatter[2] = {0, 0};

	propertiesTable2->AddProperty("REFLECTIVITY",ephoton,reflectivity2,2);
	propertiesTable2->AddProperty("SPECULARLOBECONSTANT",ephoton,specularlobe,2);
	propertiesTable2->AddProperty("SPECULARSPIKECONSTANT",ephoton,specularspike,2);
	propertiesTable2->AddProperty("BACKSCATTERCONSTANT",ephoton,backscatter,2);

	OpDiffusiveSurface ->SetType(dielectric_dielectric);
	OpDiffusiveSurface ->SetModel(unified);
	OpDiffusiveSurface ->SetSigmaAlpha(0.5);
	OpDiffusiveSurface ->SetMaterialPropertiesTable(propertiesTable2);
	/*	G4OpticalSurface* OpAerogelSurface = new G4OpticalSurface("AerogelSurface");
		OpAerogelSurface->SetType(dielectric_dielectric);
		OpAerogelSurface->SetFinish(polished);
		OpAerogelSurface->SetModel(unified);
		G4double PP[2] = { 1.4E-9*GeV,7E-9*GeV};
		*/
	G4OpticalSurface* OpBSSurface = new G4OpticalSurface("BS");
	OpBSSurface->SetType(dielectric_dielectric);
	OpBSSurface->SetModel(unified);
	OpBSSurface->SetFinish(groundfrontpainted);
	OpBSSurface->SetSigmaAlpha(0.1);
	G4double SPECULARLOBECONSTANz[2] =
	{ 0.3, 0.3 };
	G4double SPECULARSPIKECONSTANz[2] =
	{ 0.2, 0.2 };
	G4double BACKSCATTERCONSTANz[2] =
	{ 0.2, 0.2 };

	G4double REFLECTIVITY_blacksheet[2] =
	{ 0.055,0.045};
	myST1->AddProperty("SPECULARLOBECONSTANT", ephoton, SPECULARLOBECONSTANz, 2);
	myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, SPECULARSPIKECONSTANz, 2);
	myST1->AddProperty("BACKSCATTERCONSTANT", ephoton, BACKSCATTERCONSTANz, 2);
	myST1->AddProperty("REFLECTIVITY", ephoton, REFLECTIVITY_blacksheet, 2);
	OpBSSurface->SetMaterialPropertiesTable(myST1);
	new G4LogicalSkinSurface("BS",BS1_log,OpBSSurface);
	new G4LogicalSkinSurface("BS",BS2_log,OpBSSurface);
	//	new G4LogicalSkinSurface("BS",BS3_log,OpBSSurface);
	//	new G4LogicalSkinSurface("BS",GBS_log,OpBSSurface);
	//OpticalRadiatorSurface 

	//  myST1->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    num);
	//  myST1->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   num);
	//  myST1->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     num);
	//	OpAerogelSurface->SetMaterialPropertiesTable(myST2);


	//always return the physical World
	return expHall_phys;
}
