#include "AnalysisManager.hh"
#include "G4SDManager.hh"
#include "ToFHit.hh"
#include "TargetHit.hh"
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
void AnalysisManager::Initialize(){
	nev=-9999;eng=-9999;ntr=-9999;pid=-9999;seg=-9999;rfl=-9999;
	ipx=-9999;ipy=-9999;ipz=-9999;ix=-9999;iy=-9999;iz=-9999;px=-9999;py=-9999;pz=-9999;x=-9999;y=-9999;z=-9999;
	path=-9999;gtime=-9999;
}

void AnalysisManager::ClearQMD(){
	QMDnp=0;
	QMDBnp=0;
	for(int i=0;i<buf_size;i++){
		QMDpx[i]=0;
		QMDpy[i]=0;
		QMDpz[i]=0;
		QMDx[i]=0;
		QMDy[i]=0;
		QMDz[i]=0;
		QMDtr[i]=0;
		QMDpath[i]=0;
		QMDtime[i]=0;
		QMDBpx[i]=0;
		QMDBpy[i]=0;
		QMDBpz[i]=0;
		QMDBx[i]=0;
		QMDBy[i]=0;
		QMDBz[i]=0;
		QMDBtr[i]=0;
	}

}
void AnalysisManager::SetFile(TFile* files){
	file=files;
	tree = new TTree("tree","tree");
	tree->Branch("nev",&nev,"nev/I");
	tree->Branch("pid",&pid,"pid/I");
	tree->Branch("ipx",&ipx,"ipx/D");
	tree->Branch("ipy",&ipy,"ipy/D");
	tree->Branch("ipz",&ipz,"ipz/D");
	tree->Branch("ix",&ix,"ix/D");
	tree->Branch("iy",&iy,"iy/D");
	tree->Branch("iz",&iz,"iz/D");
	tree->Branch("px",&px,"px/D");
	tree->Branch("py",&py,"py/D");
	tree->Branch("pz",&pz,"pz/D");
	tree->Branch("x",&x,"x/D");
	tree->Branch("y",&y,"y/D");
	tree->Branch("z",&z,"z/D");
	tree->Branch("gtime",&gtime,"gtime/D");
//	std::cout<<"file created with name "<<filename<<" in directory "<<dirname<<std::endl;
}
void AnalysisManager::CreateFile(G4String filename)
{
	G4String dirname = "./Out/";
	G4String name=dirname+filename;
	file = new TFile(name,"write");
	tree = new TTree("tree","tree");
	tree->Branch("nev",&nev,"nev/I");
	tree->Branch("pid",&pid,"pid/I");
	tree->Branch("ipx",&ipx,"px/D");
	tree->Branch("ipy",&ipy,"py/D");
	tree->Branch("ipz",&ipz,"pz/D");
	tree->Branch("px",&px,"px/D");
	tree->Branch("py",&py,"py/D");
	tree->Branch("pz",&pz,"pz/D");
	tree->Branch("x",&x,"x/D");
	tree->Branch("y",&y,"y/D");
	tree->Branch("z",&z,"z/D");
	tree->Branch("gtime",&gtime,"gtime/D");
	std::cout<<"file created with name "<<filename<<" in directory "<<dirname<<std::endl;
}


void AnalysisManager::CreateQMDFile(G4String filename)
{
	G4String dirname = "./Out/";
	G4String name=dirname+filename;
	file = new TFile(name,"recreate");
	tree = new TTree("tree","tree");
	tree->Branch("QMDnp",&QMDnp,"QMDnp/I");
	tree->Branch("QMDpid",QMDpid,"QMDpid[QMDnp]/I");
	tree->Branch("QMDtr",QMDtr,"QMDtr[QMDnp]/I");
	tree->Branch("QMDpx",QMDpx,"QMDpx[QMDnp]/D");
	tree->Branch("QMDpy",QMDpy,"QMDpy[QMDnp]/D");
	tree->Branch("QMDpz",QMDpz,"QMDpz[QMDnp]/D");
	tree->Branch("QMDx",QMDx,"QMDx[QMDnp]/D");
	tree->Branch("QMDy",QMDy,"QMDy[QMDnp]/D");
	tree->Branch("QMDz",QMDz,"QMDz[QMDnp]/D");
	tree->Branch("QMDpath",QMDpath,"QMDpath[QMDnp]/D");
	tree->Branch("QMDtime",QMDtime,"QMDtime[QMDnp]/D");
	
	tree->Branch("QMDBnp",&QMDBnp,"QMDBnp/I");
	tree->Branch("QMDBpid",QMDBpid,"QMDBpid[QMDnp]/I");
	tree->Branch("QMDBtr",QMDBtr,"QMDBtr[QMDBnp]/I");
	tree->Branch("QMDBpx",QMDBpx,"QMDBpx[QMDBnp]/D");
	tree->Branch("QMDBpy",QMDBpy,"QMDBpy[QMDBnp]/D");
	tree->Branch("QMDBpz",QMDBpz,"QMDBpz[QMDBnp]/D");
	tree->Branch("QMDBx",QMDBx,"QMDBx[QMDBnp]/D");
	tree->Branch("QMDBy",QMDBy,"QMDBy[QMDBnp]/D");
	tree->Branch("QMDBz",QMDBz,"QMDBz[QMDBnp]/D");
	
	std::cout<<"file created with name "<<filename<<" in directory "<<dirname<<std::endl;
}
void AnalysisManager::CreateQMDFile(TFile* files)
{
	file = files;
	tree = new TTree("tree","tree");
	tree->Branch("QMDnp",&QMDnp,"QMDnp/I");
	tree->Branch("QMDpid",QMDpid,"QMDpid[QMDnp]/I");
	tree->Branch("QMDtr",QMDtr,"QMDtr[QMDnp]/I");
	tree->Branch("QMDpx",QMDpx,"QMDpx[QMDnp]/D");
	tree->Branch("QMDpy",QMDpy,"QMDpy[QMDnp]/D");
	tree->Branch("QMDpz",QMDpz,"QMDpz[QMDnp]/D");
	tree->Branch("QMDx",QMDx,"QMDx[QMDnp]/D");
	tree->Branch("QMDy",QMDy,"QMDy[QMDnp]/D");
	tree->Branch("QMDz",QMDz,"QMDz[QMDnp]/D");
	tree->Branch("QMDpath",QMDpath,"QMDpath[QMDnp]/D");
	tree->Branch("QMDtime",QMDtime,"QMDtime[QMDnp]/D");
	
	tree->Branch("QMDBnp",&QMDBnp,"QMDBnp/I");
	tree->Branch("QMDBpid",QMDBpid,"QMDBpid[QMDnp]/I");
	tree->Branch("QMDBtr",QMDBtr,"QMDBtr[QMDBnp]/I");
	tree->Branch("QMDBpx",QMDBpx,"QMDBpx[QMDBnp]/D");
	tree->Branch("QMDBpy",QMDBpy,"QMDBpy[QMDBnp]/D");
	tree->Branch("QMDBpz",QMDBpz,"QMDBpz[QMDBnp]/D");
	tree->Branch("QMDBx",QMDBx,"QMDBx[QMDBnp]/D");
	tree->Branch("QMDBy",QMDBy,"QMDBy[QMDBnp]/D");
	tree->Branch("QMDBz",QMDBz,"QMDBz[QMDBnp]/D");
	
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
//	G4cout<<"[AnaMan]: Begin of Event"<<G4endl;
	Initialize();
}

void AnalysisManager::EndOfEvent(const G4Event* anEvent)
{
	ClearQMD();
	G4HCofThisEvent* HCTE = anEvent->GetHCofThisEvent();
	if(!HCTE)
	{
		G4cout<<"[AnaMan]: No HC in this evnet "<<G4endl;
		return;
	}
	G4SDManager *SDMan = G4SDManager::GetSDMpointer();
	G4int nhmppc=0;
	TargetHitsCollection *TargetHC=0;
	ToFHitsCollection *ToFHC=0;
	G4int colIdTarget= SDMan->GetCollectionID("TargetCollection");
	G4int colIdToF= SDMan->GetCollectionID("ToFCollection");
	if(colIdTarget>=0)
	{
		TargetHC=dynamic_cast<TargetHitsCollection*>(HCTE->GetHC(colIdTarget));
	}
	if(colIdToF>=0)
	{
		ToFHC=dynamic_cast<ToFHitsCollection*>(HCTE->GetHC(colIdToF));
	}
	int TargetNH=TargetHC->entries();
	int ToFNH=ToFHC->entries();
	TargetHit *TargetHit;
	ToFHit *ToFHit;
	QMDBnp = TargetNH;
	for(int i = 0;i<TargetNH;++i){
		TargetHit=(*TargetHC)[i];
		seg=TargetHit->GetSegmentID();
		pid=TargetHit->GetPartID();
		G4ThreeVector Pos=TargetHit->GetPos();
		G4ThreeVector Mom=TargetHit->GetMom();
		QMDBpx[i]=Mom.x();
		QMDBpy[i]=Mom.y();
		QMDBpz[i]=Mom.z();
		QMDBx[i]=Pos.x();
		QMDBy[i]=Pos.y();
		QMDBz[i]=Pos.z();
		ntr=TargetHit->GetTrackNo();
		eng=TargetHit->GetEng();
		nev=TargetHit->GetEvtNo();
		QMDBpid[i]=TargetHit->GetPartID();
		QMDBtr[i]=ntr;
	}
	QMDnp = ToFNH;
	for(int i = 0;i<ToFNH;++i){
		ToFHit=(*ToFHC)[i];
		seg=ToFHit->GetSegmentID();
		pid=ToFHit->GetPartID();
		G4ThreeVector Pos=ToFHit->GetPos();
		G4ThreeVector Mom=ToFHit->GetMom();
		QMDpx[i]=Mom.x();
		QMDpy[i]=Mom.y();
		QMDpz[i]=Mom.z();
		QMDx[i]=Pos.x();
		QMDy[i]=Pos.y();
		QMDz[i]=Pos.z();
		ntr=ToFHit->GetTrackNo();
		QMDtime[i]=ToFHit->GetGlobalTime();
		QMDpath[i]=ToFHit->GetPath();
		eng=ToFHit->GetEng();
		QMDpid[i]=ToFHit->GetPartID();
		nev=ToFHit->GetEvtNo();
		QMDtr[i]=ntr;
	}
	tree->Fill();
}
