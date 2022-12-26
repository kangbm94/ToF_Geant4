#include "TargetHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"
#include <iomanip>

TargetHit::TargetHit()
	: segID_(0),gtime_(-100),ltime_(-100),trackNo_(0)
{}
G4Allocator<TargetHit> TargetHitAllocator;
void TargetHit::Draw(){
	G4VVisManager *pVisManager= G4VVisManager::GetConcreteInstance();
	if(pVisManager){
		G4Circle circle(pos_);
		circle.SetScreenSize(3.0);
		circle.SetFillStyle(G4Circle::filled);
		G4Colour colour(125,0,125);
		G4VisAttributes attribs(colour);
		circle.SetVisAttributes(attribs);
		pVisManager->Draw(circle);
	}
}
void TargetHit::Print(){}

