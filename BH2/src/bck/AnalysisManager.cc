#include "AnalysisManager.hh"
#include "G4SDManager.hh"
#include "MPPCHit.hh"
#include "G4UnitsTable.hh"
#include <sstream>
#include "TNtuple.h"
#include "TTree.h"
#include "TBranch.h"
#include "math.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "G4ThreeVector.hh"
AnalysisManager::AnalysisManager()
{
	fillcnt=0;
}
AnalysisManager::~AnalysisManager()
{
}

void AnalysisManager::CreateFile(G4String filename)
{
	G4String dirname = "./Out/";
	G4String name=dirname+filename+".root";
	file = new TFile(name,"RECREATE");
	tree = new TTree("tree","tree");
	tree->Branch("nev",&nev,"nev/I");
	tree->Branch("seg",&seg,"seg/I");
	tree->Branch("eng",&eng,"eng/D");
	tree->Branch("pid",&pid,"pid/I");
	tree->Branch("posx",&x,"x/D");
	tree->Branch("posy",&y,"y/D");
	tree->Branch("posz",&z,"z/D");
	tree->Branch("posx",&px,"px/D");
	tree->Branch("posy",&py,"py/D");
	tree->Branch("posz",&pz,"pz/D");
	tree->Branch("path",&path,"path/D");
	tree->Branch("gtime",&gtime,"gtime/D");
	tree->Branch("ltime",&ltime,"ltime/D");
	std::cout<<"file created with name "<<filename<<" in directory "<<dirname<<std::endl;
}
void AnalysisManager::CloseFile()
{
	file->Close();
}
void AnalysisManager::BeginOfRun()
{
	G4cout<<"[AnaMan]: Begin of Run"<<G4endl;
}
void AnalysisManager::EndOfRun()
{
	G4cout<<"[AnaMan]: End of Run"<<G4endl;
	file->Write();
	std::cout<<"file written"<<std::endl;
//	file->Close();
}

void AnalysisManager::BeginOfEvent(const G4Event* anEvent)
{
	G4cout<<"[AnaMan]: Begin of Event"<<G4endl;
}

void AnalysisManager::EndOfEvent(const G4Event* anEvent)
{
	G4cout<<"[AnaMan]: End of Event"<<G4endl;
	G4HCofThisEvent* HCTE = anEvent->GetHCofThisEvent();
	if(!HCTE)
	{
		G4cout<<"[AnaMan]: No HC in this evnet "<<G4endl;
		return;
	}
	G4SDManager *SDMan = G4SDManager::GetSDMpointer();
	G4int nhmppc=0;
	MPPCHitsCollection *MPPCHC=0;
	G4int colIdMPPC= SDMan->GetCollectionID("MPPCCollection");
	if(colIdMPPC>=0)
	{
		MPPCHC=dynamic_cast<MPPCHitsCollection*>(HCTE->GetHC(colIdMPPC));
	}
	if(MPPCHC){
		nhmppc=MPPCHC->entries();
		G4cout<<"nhmppc is :  "<<nhmppc<<G4endl;
	}
	for(int i=0;i<nhmppc;i++)
	{
		MPPCHit *aHit=(*MPPCHC)[i];
		seg=aHit->GetSegmentID();
		pid=aHit->GetPartID();
		G4ThreeVector Pos=aHit->GetPos();
		G4ThreeVector Mom=aHit->GetMom();
		x=Pos.x();
		y=Pos.y();
		z=Pos.z();
		px=Mom.x()/1e6;
		py=Mom.y()/1e6;
		pz=Mom.z()/1e6;
		ntr=aHit->GetTrackNo();
		gtime=aHit->GetGlobalTime();
		ltime=aHit->GetLocalTime();
		path=aHit->GetPath();
		eng=aHit->GetEng();
		pid=aHit->GetPartID();
		nev=aHit->GetEvtNo();
		tree->Fill();
	}
}
