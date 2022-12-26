#include "MPPCSD.hh"
#include "MPPCHit.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4TrajectoryContainer.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

MPPCSD::MPPCSD(G4String name): G4VSensitiveDetector(name){
	collectionName.insert("MPPCCollection");
}
MPPCSD::~MPPCSD(){}
void MPPCSD::Initialize(G4HCofThisEvent* hitsCE)
{
	static G4int hitsCID = -1;
	MPPCCollection = new MPPCHitsCollection(SensitiveDetectorName,collectionName[0]);
	if(hitsCID<0)
	{
		hitsCID=GetCollectionID(0);
	}
	hitsCE->AddHitsCollection(hitsCID,MPPCCollection);
}
G4bool MPPCSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
//	G4cout<<"Processing Hits.."<<G4endl;
	G4Track* aTrack=aStep->GetTrack();
	G4double path = aTrack->GetTrackLength();
	G4int nHits=MPPCCollection->entries();
	const G4VTouchable *thePostTouchable = aStep->GetPostStepPoint()->GetTouchable();
	G4VPhysicalVolume* thePostPV=thePostTouchable->GetVolume();
//	const G4VTouchable *thePreTouchable = aStep->GetPreStepPoint()->GetTouchable();
//	G4VPhysicalVolume* thePrePV=theTouchable->GetVolume();
	G4String hitName = thePostPV->GetName();
	G4int hitSegment= thePostPV->GetCopyNo();

	G4int trackNo=aTrack->GetTrackID();
	G4ThreeVector hitpos=aStep->GetPostStepPoint()->GetPosition();
	G4ThreeVector hitmom=aStep->GetPostStepPoint()->GetMomentum();
	G4double velocity=aTrack->GetVelocity();
	G4double gtime = aTrack->GetGlobalTime();
	G4double ltime = aTrack->GetLocalTime();
	G4double Eng=aTrack->GetKineticEnergy()/CLHEP::eV;
	G4int partID= aTrack->GetDefinition()->GetPDGEncoding();
	G4int nev= G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	MPPCHit* aHit = new MPPCHit();
	aHit->SetSegmentID(hitSegment);
	aHit->SetPass();
	aHit->SetEng(Eng);
	aHit->SetPos(hitpos);
	aHit->SetMom(hitmom);
	aHit->SetTrackNo(trackNo);
	aHit->SetGlobalTime(gtime);
	aHit->SetLocalTime(ltime);
	aHit->SetVelocity(velocity);
	aHit->SetPath(path);
	aHit->SetPartID(partID);
	aHit->SetEvtNo(nev);
	if(hitName=="mppc")
	{
		MPPCCollection->insert(aHit);
//		G4cout<<"Inserging Hit..."<<G4endl;
	}
	return true;
}
void MPPCSD::EndOfEvent(G4HCofThisEvent*){}
void MPPCSD::clear(){
	G4int nHits=MPPCCollection->entries();
	for(G4int i=0;i<nHits;i++)
	{
		delete(*MPPCCollection)[i];
	}
}
