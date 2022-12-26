#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H 1
#include "TNtuple.h"
#include "TTree.h"
#include "TBranch.h"
#include "math.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
class TFile;
class TTree;
class TH1F;
class TH2F;
class AnalysisManager
{
  public: AnalysisManager();
          virtual ~AnalysisManager();
          void CreateFile(G4String name);
          void CreateFile(G4String name,int njob,int nthread);
          void CloseFile();
          void BeginOfRun();
          void EndOfRun();
          void BeginOfEvent(const G4Event* anEvent);
          void EndOfEvent(const G4Event* anEvent);

  private:
          TFile *file;
          TTree *tree;
			 G4int nev;
			 G4int eng;
			 G4int ntr;
			 G4int pid;
			 G4int seg;
			 G4int rfl;
			 G4double x;
			 G4double y;
			 G4double z;
			 G4double px;
			 G4double py;
			 G4double pz;
			 G4double path;
			 G4double gtime;
			 G4double ltime;
			 
			 G4int fillcnt=0;
          G4int writecnt=0;
          G4double tmpx=0;
          G4double tmpy=0;
          G4double tmpz=0;
          G4double tmpen=0;
};
#endif
