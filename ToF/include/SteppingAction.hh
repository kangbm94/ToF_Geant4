
// $Id: SteppingAction.hh 69469 2013-05-05 21:42:35Z ihrivnac $
//
/// \file SteppingAction.hh
/// \brief Definition of the SteppingAction class

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "AnalysisManager.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"
/// Stepping action class
/// 

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(AnalysisManager *ana);
    virtual ~SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);
    AnalysisManager* AnaManager;    
  private:
    G4int fScintillationCounter;
    G4int fCerenkovCounter;
    G4int fEventNumber;
/*
		int nbeam;    
G4int j=0;
    G4int rfl=0;
	G4int Aerfg=0;
	G4int Hitcnt=0;
    G4ThreeVector fPos;
    G4ThreeVector fMom;
    G4double eng=0;
    G4double xh=0;
    G4double yh=0;
    G4double zh=0;
    G4double path=0;
    G4double gtime=0;
    G4double ltime=0;
	 G4int nev=0;
    G4int pid=0;
    G4int nevtmp=0;
    G4double px=0;
    G4double py=0;
    G4double pz=0;
    G4double polx=0;
    G4double poly=0;
    G4double polz=0;
*/
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
