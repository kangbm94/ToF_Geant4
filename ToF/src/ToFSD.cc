#include "ToFSD.hh"
#include "ToFHit.hh"
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

ToFSD::ToFSD(G4String name): G4VSensitiveDetector(name){
	collectionName.insert("ToFCollection");
}
ToFSD::~ToFSD(){}
void ToFSD::Initialize(G4HCofThisEvent* hitsCE)
{
	static G4int hitsCID = -1;
	ToFCollection = new ToFHitsCollection(SensitiveDetectorName,collectionName[0]);
	if(hitsCID<0)
	{
		hitsCID=GetCollectionID(0);
	}
	hitsCE->AddHitsCollection(hitsCID,ToFCollection);
}
G4bool ToFSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
//	G4cout<<"Processing Hits.."<<G4endl;
	G4Track* aTrack=aStep->GetTrack();
	G4double path = aTrack->GetTrackLength();
	G4int nHits=ToFCollection->entries();
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
	ToFHit* aHit = new ToFHit();
	aHit->SetSegmentID(hitSegment);
//	aHit->SetPass();
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
		ToFCollection->insert(aHit);
//		G4cout<<"Inserging Hit..."<<G4endl;
	return true;
}
void ToFSD::EndOfEvent(G4HCofThisEvent*){}
void ToFSD::clear(){
	G4int nHits=ToFCollection->entries();
	for(G4int i=0;i<nHits;i++)
	{
		delete(*ToFCollection)[i];
	}
}
