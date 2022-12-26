
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::
  PhysicsListMessenger(PhysicsList* pPhys) 
  : G4UImessenger(),
    fPhysicsList(pPhys)
{
fDir = new G4UIdirectory("/LACSim/");
  fDir->SetGuidance("UI commands of this example");

  fPhysDir = new G4UIdirectory("/LACSim/phys/");
  fPhysDir->SetGuidance("PhysicsList control");
 
  fVerboseCmd = new G4UIcmdWithAnInteger("/LACSim/phys/verbose",this);
  fVerboseCmd->SetGuidance("set verbose for physics processes");
  fVerboseCmd->SetParameterName("verbose",false);
  fVerboseCmd->SetDefaultValue(0);
  fVerboseCmd->SetRange("verbose>=0");
  fVerboseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  fCerenkovCmd =
           new G4UIcmdWithAnInteger("/LACSim/phys/cerenkovMaxPhotons",this);
  fCerenkovCmd->SetGuidance("set max nb of photons per step");
  fCerenkovCmd->SetParameterName("MaxNumber",false);
  fCerenkovCmd->SetRange("MaxNumber>=0");
  fCerenkovCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete fVerboseCmd;
  delete fCerenkovCmd;
  delete fPhysDir;
  delete fDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue)
{
  if( command == fVerboseCmd )
   {fPhysicsList->SetVerbose(fVerboseCmd->GetNewIntValue(newValue));}

  if( command == fCerenkovCmd )
   {fPhysicsList->
              SetNbOfPhotonsCerenkov(fCerenkovCmd->GetNewIntValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
