#include "PrimaryGeneratorAction.hh"
#include "Target.hh"
#include "Randomize.hh"
#include <iostream>
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"

//PrimaryGeneratorAction* PrimaryGeneratorAction::PrimaryGenerator_=0;
PrimaryGeneratorAction::PrimaryGeneratorAction(BeamManager* beam)
	: G4VUserPrimaryGeneratorAction(), 
	fParticleGun(0)
{
	G4cout<<"Prg"<<G4endl;
	particleTable = G4ParticleTable::GetParticleTable();
	BeManager= beam;
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun();
	BeamProfile =(bool) BeManager->ProfileMode();
	if(BeamProfile){
		beam_file = (TFile*)BeManager->GetBeam();
		beam_tree = (TTree*)beam_file->Get("tree");
		beam_tree->SetBranchAddress("np",&QMDnp);
		beam_tree->SetBranchAddress("A",A);
		beam_tree->SetBranchAddress("Z",Z);
		beam_tree->SetBranchAddress("px",QMDpx);
		beam_tree->SetBranchAddress("py",QMDpy);
		beam_tree->SetBranchAddress("pz",QMDpz);
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
	delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	double bpx,bpy,bpz;
	int bA,bZ;
	auto particleTable = G4ParticleTable::GetParticleTable();
	auto ionTable = G4IonTable::GetIonTable();
	double ext_en = 0*keV;
	if(BeamProfile){
		beam_tree->GetEntry(nev);
		for(int i=0;i<QMDnp;i++){
			bpx=QMDpx[i];bpy=QMDpy[i];bpz=QMDpz[i];
			bA=A[i];bZ=Z[i];
		if(bZ==0){
//			G4cout<<"Warning: Neutron"<<G4endl;
			continue;
		}
		G4ParticleDefinition* particle = ionTable->GetIon(bZ,bA,ext_en);
		double charge = bZ*eplus;
		fParticleGun->SetParticleDefinition(particle);
			fParticleGun->SetParticleCharge(charge);
			fParticleGun->SetParticleMomentum(G4ThreeVector(bpx,bpy,bpz));
			fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,fTargetZ*mm));
			fParticleGun->GeneratePrimaryVertex(anEvent);
		}
		G4cout<<"QMD event "<<nev<<" end! np = "<< QMDnp<<G4endl;
	}
	else{
		G4ParticleDefinition* fPion = particleTable->FindParticle("pi+");
		auto particle = fPion;
		fParticleGun->SetParticleDefinition(particle);

		auto pp = (G4UniformRand())*GeV;
		auto mass = particle->GetPDGMass();
		auto ekin = std::sqrt(pp*pp+mass*mass)-mass;
		fParticleGun->SetParticleEnergy(ekin);

		auto phi = (G4UniformRand())*360*deg;
		auto theta = acos(2*(G4UniformRand()-0.5));
		fParticleGun->SetParticleMomentumDirection(
				G4ThreeVector(std::cos(phi)*std::sin(theta),std::sin(phi)*std::sin(theta),std::cos(theta)));

		fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,fTargetZ*mm));


		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
	nev++;
}

int PrimaryGeneratorAction::Getnbeam()
{
	nbeam=BeManager->GetBeamEntries();
	return nbeam;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

*/
