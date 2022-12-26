#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "BeamManager.hh"
class G4ParticleGun;
class G4Event;
class PrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(BeamManager* beam);
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);
static	 PrimaryGeneratorAction* GetPrimaryGenerator(){return PrimaryGenerator_;}
	int Getnbeam();
  private:
static	 PrimaryGeneratorAction* PrimaryGenerator_;
    BeamManager* BeManager;
    G4ParticleGun*   fParticleGun;
	 PrimaryGeneratorMessenger* fGunMessenger;
	 G4ParticleTable* particleTable;
	G4String beamname_out; 
	int nbeam;
	int pid_pr;
	int np=0;
	double p_pr;
	double px_pr;
	double py_pr;
	double pz_pr;
	double polx_pr;
	double poly_pr;
	double polz_pr;
	double x_pr;
	double y_pr;
	double z_pr;
	double t_pr;
	
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*PrimaryGeneratorAction_h*/
