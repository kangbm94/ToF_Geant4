// $Id: SteppingAction.cc 71007 2013-06-09 16:14:59Z maire $
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "TH2D.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4VHit.hh"
#include "g4root.hh"
#include "RunAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//PrimaryGeneratorAction* PrimaryGenerator;
	SteppingAction::SteppingAction(AnalysisManager* ana)
:AnaManager(ana)
{
//	PrimaryGenerator=PrimaryGeneratorAction::GetPrimaryGenerator();
//	nbeam=PrimaryGenerator->Getnbeam();
	fScintillationCounter = 0;
	fCerenkovCounter      = 0;
	fEventNumber = -1;
//	std::cout<<"SteppingAction:: nbeam is: "<<nbeam<<std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ ; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
	G4Track* Track = step->GetTrack();
	double path = Track->GetTrackLength();
	if(path>10*CLHEP::m){
		Track->SetTrackStatus( fStopAndKill );
	}
	/*
	nev = G4RunManager::GetRunManager()->
		GetCurrentEvent()->GetEventID();
	G4int eventNumber = nev;
	G4StepPoint* prepoint = step->GetPreStepPoint();
	G4StepPoint* postpoint = step->GetPostStepPoint();
	G4VPhysicalVolume* prePV = prepoint->GetPhysicalVolume();
	G4VPhysicalVolume* postPV = postpoint->GetPhysicalVolume();
	G4String PostPVname;
	G4String PrePVname;
*/
/*	
	if(Track->GetTrackID()>5)
	{
	}
*/
	/*
	if(step->GetPostStepPoint()->GetPhysicalVolume() == NULL)
	{
		j=0;
		rfl=0;
		Aerfg=0;
		Hitcnt=0;
	}
	if(step->GetPostStepPoint()->GetPhysicalVolume() != NULL)
	{
		PostPVname = postPV->GetName();
	}
	if(step->GetPreStepPoint()->GetPhysicalVolume() != NULL)
	{ 
		PrePVname = prePV->GetName();
	}
	*/
	/*
		G4String TrackBeamName = Track->GetDynamicParticle()->
		GetParticleDefinition()->GetParticleName();
		*/
	/*
		if(TrackBeamName == "mu-")
		{
		G4cout<<"Beam Tracking..."<<G4endl;
		G4cout<<"PrePV is: "<<PrePVname<<G4endl;
		G4cout<<"PostPV is: "<<PostPVname<<G4endl;
		G4ThreeVector hitp=Track->GetPosition();
		eng=Track->GetKineticEnergy()/CLHEP::eV;
		xh     =hitp.x();
		yh     =hitp.y();
		zh     =-hitp.z();
		G4cout<<"Beam Position is: ("<<xh<<" , "<<yh<<" , "<<zh<<" )"<<G4endl;
		}
		*/
	/*
	if(      PostPVname == "mppc"      )
	{
		G4String TrackParticleName = Track->GetDynamicParticle()->
			GetParticleDefinition()->GetParticleName();

		if (TrackParticleName == "opticalphoton")
		{
//			Hitcnt++;
//			G4cout<<"Hit at time "<<ltime<<" ns"<<G4endl;
//			Track->SetTrackStatus( fStopAndKill );
//			G4cout<<"Track Killed at mppc"<<G4endl;
//			G4cout<<"Photon Hit at mppc"<<G4endl;
			rfl=0;
		}
	}
	if(      PostPVname == "mirror"      )
	{
		G4String TrackParticleName = Track->GetDynamicParticle()->
			GetParticleDefinition()->GetParticleName();

		if (TrackParticleName == "opticalphoton")
		{
			rfl++;
			//			rfl++;
			//			Track->SetTrackStatus( fStopAndKill );	
		}
	}
	*/
/*
	if( PrePVname=="Scintillator")
	{
		G4String TrackParticleName = Track->GetDynamicParticle()->
			GetParticleDefinition()->GetParticleName();
		if (TrackParticleName == "opticalphoton")
		{
			G4ThreeVector hitp=Track->GetPosition();
			eng=Track->GetKineticEnergy()/CLHEP::eV;
			rfl=Track->GetTrackID();
			xh     =hitp.x();
			yh     =hitp.y();
			zh     =-hitp.z();
			path	=Track->GetTrackLength();
			gtime   =Track-> GetGlobalTime();
			ltime   =Track-> GetLocalTime();
			AnaManager->FillScintParticle(nev,xh,yh,zh,eng,rfl,path,gtime,ltime);
		}
	}
	*/
	/*
	if( PostPVname == "kill")
	{
		rfl=0;
		Track->SetTrackStatus( fStopAndKill );
	}
	*/
	/*
		if(PostPVname == "window")
		{	
		j++;
		if(j>10)
		{
		Track->SetTrackStatus( fStopAndKill );
		j=0;
	//	rfl=0;
	}
	} */ 
	/*
	if (eventNumber != fEventNumber) {
		fEventNumber = eventNumber;
		fScintillationCounter = 0;
		fCerenkovCounter = 0;
	}

*/

	//	G4String ParticleName = Track->GetDynamicParticle()->
	//		GetParticleDefinition()->GetParticleName();

	//	if (ParticleName == "opticalphoton") return;

	/*
	const std::vector<const G4Track*>* secondaries =
		step->GetSecondaryInCurrentStep();

	if (secondaries->size()>0) {
		for(unsigned int i=0; i<secondaries->size(); ++i) {
			if (secondaries->at(i)->GetParentID()>0) {
				if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
						== G4OpticalPhoton::OpticalPhotonDefinition()){
					if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
							== "Scintillation")fScintillationCounter++;
					if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
							== "Cerenkov"){fCerenkovCounter++;
//					Track->SetTrackStatus( fStopAndKill );
					}
				}
			}
		}
	}
	*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
