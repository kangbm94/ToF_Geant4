#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
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
	int A[300],Z[300];
	int QMDnp=0;
	double QMDpx[300],QMDpy[300],QMDpz[300];
  private:
static	 PrimaryGeneratorAction* PrimaryGenerator_;
    BeamManager* BeManager;
    G4ParticleGun*   fParticleGun;
	 PrimaryGeneratorMessenger* fGunMessenger;
	 G4ParticleTable* particleTable;
	 G4IonTable* ionTable;
	G4String beamname_out; 
	bool BeamProfile=false;
	TFile* beam_file;
	TTree* beam_tree;
	int nev=0;
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
