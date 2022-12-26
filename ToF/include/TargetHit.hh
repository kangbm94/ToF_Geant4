#ifndef TargetHit_h
#define TargetHit_h
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class TargetHit : public G4VHit
{
	public:
		TargetHit();
		~TargetHit(){};
	private:
		TargetHit(const TargetHit&);
		const TargetHit& operator=(const TargetHit&);
	public:
		G4int operator==(const TargetHit&) const;
		inline void *operator new(size_t);
		inline void operator delete(void *aHit);
		virtual void Draw();
		virtual void Print();
	private:
		G4int pass_;
		G4int partID_;
		G4int segID_;
		G4double gtime_;
		G4double ltime_;
		G4double velocity_;
		G4double path_;
		G4double eng_;
		G4ThreeVector pos_;
		G4ThreeVector mom_;
		G4int trackNo_;
		G4int nev_;
	public:
		void SetPass(void){pass_=1;}
		void SetSegmentID( G4int id){segID_=id;}
		void SetGlobalTime(G4double time){gtime_=time;}
		void SetLocalTime(G4double time){ltime_=time;}
		void SetVelocity(G4double vel){ velocity_=vel;}
		void SetPath(G4double path){path_=path;}
		void SetEng(G4double eng){eng_=eng;}
		void SetPos(const G4ThreeVector& pos) {pos_=pos;}
		void SetMom(const G4ThreeVector& mom) {mom_=mom;}
		void SetTrackNo(G4int trackNo){trackNo_=trackNo;}
		void SetEvtNo(G4int nev){nev_=nev;}
		void SetPartID(G4int partID){partID_=partID;}

		G4int GetPass(void){return pass_;}
		G4int GetSegmentID(void ){return segID_;}
		G4int GetTrackNo(void){return trackNo_;}
		G4int GetEvtNo(void){return nev_;}
		G4double GetGlobalTime(void){return gtime_;}
		G4double GetLocalTime(void){return ltime_;}
		G4double GetVelocity(void){ return velocity_;}
		G4ThreeVector GetPos(void) {return pos_;}
		G4ThreeVector GetMom(void) {return mom_;}
		G4double GetPath(void){return path_;}
		G4double GetEng(void){return eng_;}
		G4double GetPartID(void){return partID_;}
		
};

typedef G4THitsCollection<TargetHit> TargetHitsCollection;
extern G4Allocator<TargetHit> TargetHitAllocator;
inline void * TargetHit::operator new(size_t)
{
	return static_cast<void*> (TargetHitAllocator.MallocSingle());
}

inline void TargetHit::operator delete(void* aHit)
{
	TargetHitAllocator.FreeSingle(static_cast<TargetHit*>(aHit));
}
#endif
