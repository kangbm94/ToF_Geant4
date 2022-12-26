#include "TargetSD.hh"
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

TargetSD::TargetSD(G4String name): G4VSensitiveDetector(name){
	collectionName.insert("TargetCollection");
}
TargetSD::~TargetSD(){}
void TargetSD::Initialize(G4HCofThisEvent* hitsCE)
{
	static G4int hitsCID = -1;
	TargetCollection = new TargetHitsCollection(SensitiveDetectorName,collectionName[0]);
	if(hitsCID<0)
	{
		hitsCID=GetCollectionID(0);
	}
	hitsCE->AddHitsCollection(hitsCID,TargetCollection);
}
G4bool TargetSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
//	G4cout<<"Processing Hits.."<<G4endl;
	G4Track* aTrack=aStep->GetTrack();
	const G4VTouchable *thePostTouchable = aStep->GetPostStepPoint()->GetTouchable();
	G4VPhysicalVolume* thePostPV=thePostTouchable->GetVolume();
	G4String hitName = thePostPV->GetName();

	G4int trackNo=aTrack->GetTrackID();
	G4ThreeVector hitpos=aStep->GetPostStepPoint()->GetPosition();
	G4ThreeVector hitmom=aStep->GetPostStepPoint()->GetMomentum();
	G4int partID= aTrack->GetDefinition()->GetPDGEncoding();
	G4int nev= G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	TargetHit* aHit = new TargetHit();
	aHit->SetMom(hitmom);
	aHit->SetPos(hitpos);
	aHit->SetTrackNo(trackNo);
	aHit->SetPartID(partID);
	aHit->SetEvtNo(nev);
	TargetCollection->insert(aHit);
	return true;
}
void TargetSD::EndOfEvent(G4HCofThisEvent*){}
void TargetSD::clear(){
	G4int nHits=TargetCollection->entries();
	for(G4int i=0;i<nHits;i++)
	{
		delete(*TargetCollection)[i];
	}
}
