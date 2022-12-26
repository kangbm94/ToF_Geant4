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
					void CreateQMDFile(G4String name);
					void CreateQMDFile(TFile* files);
					void SetFile(TFile* files);
					void CreateFile(G4String name,int njob,int nthread);
					void CloseFile();
					void BeginOfRun();
					void EndOfRun();
					void BeginOfEvent(const G4Event* anEvent);
					void EndOfEvent(const G4Event* anEvent);
					void Initialize();
					void ClearQMD();
	private:
					TFile *file;
					TTree *tree;
					G4int nev;
					G4int eng;
					G4int ntr;
					G4int pid;
					G4int seg;
					G4int rfl;
					G4double ix;
					G4double iy;
					G4double iz;
					G4double ipx;
					G4double ipy;
					G4double ipz;
					G4double x;
					G4double y;
					G4double z;
					G4double px;
					G4double py;
					G4double pz;
					G4double path;
					G4double gtime;
					G4double ltime;
				
					const static G4int buf_size=300;
					G4int QMDnp = 0;
					G4int QMDpid[buf_size];
					G4double QMDpx[buf_size];
					G4double QMDpy[buf_size];
					G4double QMDpz[buf_size];
					G4double QMDx[buf_size];
					G4double QMDy[buf_size];
					G4double QMDz[buf_size];
					G4double QMDpath[buf_size];
					G4double QMDtime[buf_size];
					G4double QMDtr[buf_size];

					G4int QMDBnp = 0;
					G4int QMDBpid[buf_size];
					G4double QMDBpx[buf_size];
					G4double QMDBpy[buf_size];
					G4double QMDBpz[buf_size];
					G4double QMDBx[buf_size];
					G4double QMDBy[buf_size];
					G4double QMDBz[buf_size];
					G4double QMDBtr[buf_size];



					G4int fillcnt=0;
					G4int writecnt=0;
					G4double tmpx=0;
					G4double tmpy=0;
					G4double tmpz=0;
					G4double tmpen=0;
};
#endif
