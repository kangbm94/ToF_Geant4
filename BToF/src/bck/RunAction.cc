// Make this appear first!
#include "G4Timer.hh"
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(AnalysisManager* ana)
 : AnaManager(ana)
{  
  fTimer = new G4Timer;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
 delete fTimer;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4cout << "Run start." << G4endl;
  fTimer->Start();
  AnaManager->BeginOfRun();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{

  G4cout << "Run end." << G4endl;
  fTimer->Stop();
  AnaManager->EndOfRun();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
