#ifndef MPPCSD_h
#define MPPCSD_h
#include "MPPCHit.hh"
#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class MPPCSD : public G4VSensitiveDetector
{
	public:
		MPPCSD(G4String name);
		~MPPCSD();
		void Initialize(G4HCofThisEvent*);
		G4bool ProcessHits(G4Step* aStep,G4TouchableHistory*);
		void EndOfEvent(G4HCofThisEvent*);
		void clear();
		G4int dummy_trid;
		G4double tof;
	private:
		MPPCHitsCollection* MPPCCollection;
};


#endif
