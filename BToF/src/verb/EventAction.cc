// $Id: EventAction.cc 100946 2016-11-03 11:28:08Z gcosmo $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Trajectory.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

	EventAction::EventAction()
: G4UserEventAction(),
	fAbsoEdepHCID(-1),
	fGapEdepHCID(-1),
	fAbsoTrackLengthHCID(-1),
	fGapTrackLengthHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>* 
EventAction::GetHitsCollection(G4int hcID,
		const G4Event* event) const
{
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*void EventAction::PrintEventStatistics(
  G4double absoEdep, G4double absoTrackLength,
  G4double gapEdep, G4double gapTrackLength) const
  {
// Print event statistics
//
G4cout
<< "   Absorber: total energy: " 
<< std::setw(7) << G4BestUnit(absoEdep, "Energy")
<< "       total track length: " 
<< std::setw(7) << G4BestUnit(absoTrackLength, "Length")
<< G4endl
<< "        Gap: total energy: " 
<< std::setw(7) << G4BestUnit(gapEdep, "Energy")
<< "       total track length: " 
<< std::setw(7) << G4BestUnit(gapTrackLength, "Length")
<< G4endl;
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
/*	
	if (G4VVisManager::GetConcreteInstance()) {
		G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer(); G4int n_trajectories = 0;
		if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
		n_trajectories=5;
		for (G4int i=0; i < n_trajectories; i++)
			
		{ G4Trajectory* trj=(G4Trajectory*)((*(evt->GetTrajectoryContainer()))[i]);
//			if (drawFlag == "all") trj->DrawTrajectory(50);
//			else if ((drawFlag == "charged")&&(trj->GetCharge() != 0.))
				trj->DrawTrajectory();
//			else if ((drawFlag == "neutral")&&(trj->GetCharge() == 0.))
//				                        trj->DrawTrajectory(50);
		
		} 
	}
*/		


}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
