#ifndef ToFSD_h
#define ToFSD_h
#include "ToFHit.hh"
#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class ToFSD : public G4VSensitiveDetector
{
	public:
		ToFSD(G4String name);
		~ToFSD();
		void Initialize(G4HCofThisEvent*);
		G4bool ProcessHits(G4Step* aStep,G4TouchableHistory*);
		void EndOfEvent(G4HCofThisEvent*);
		void clear();
		G4int dummy_trid;
		G4double tof;
	private:
		ToFHitsCollection* ToFCollection;
};


#endif
