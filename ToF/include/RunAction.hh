/// \file /include/RunAction.hh
/// \brief Definition of the RunAction class
//
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1
#include "G4Timer.hh"
#include "globals.hh"
#include "G4UserRunAction.hh"
//#include "EventAction.hh"
#include "AnalysisManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4Timer;
class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(AnalysisManager* ana);
    virtual ~RunAction();
  void FillPerEvent(G4double, G4double, G4double, G4double);

  public:
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);
  private:
    G4Timer* fTimer;
    AnalysisManager* AnaManager;
//    EventAction* fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*RunAction_h*/
