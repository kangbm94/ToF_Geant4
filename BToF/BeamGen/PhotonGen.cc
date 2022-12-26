#include "fvec.hh"
#define pi  3.14159265358979323846
Double_t norm(Double_t u,Double_t v)
{
	return 1/sqrt(1+u*u+v*v);
}

void PhotonGen()
{
	gRandom->SetSeed();
	Int_t pid;
	Int_t pid_;

	TString nameb= "PhotonTest.root";
	Double_t posx,posy,posz;
	Double_t px_,py_,pz_;
	Double_t polx,poly,polz;
	Double_t ltime;
	TFile* fileb = new TFile(nameb,"READ");
	TTree* treeb= (TTree*)fileb->Get("treeg");
	treeb->SetBranchAddress("posxg",&posx);
	treeb->SetBranchAddress("posyg",&posy);
	treeb->SetBranchAddress("poszg",&posz);
	treeb->SetBranchAddress("pxg",&px_);
	treeb->SetBranchAddress("pyg",&py_);
	treeb->SetBranchAddress("pzg",&pz_);
	treeb->SetBranchAddress("pid",&pid_);
	treeb->SetBranchAddress("polxg",&polx);
	treeb->SetBranchAddress("polyg",&poly);
	treeb->SetBranchAddress("polzg",&polz);
	treeb->SetBranchAddress("ltimeg",&ltime);

	Int_t ent=treeb->GetEntries();

	//	Int_t nbeam=100;
	Double_t p,px,py,pz,x,y,z,tof;
	Double_t polx_,poly_,polz_;
	TString name="GenPhoton2";
	TString dir="../build/Beam/";
	TFile* file = new TFile(dir+name+".root","RECREATE","Output");
	TTree* tree = new TTree("tree","tree");
	tree->Branch("pid",&pid,"pid/I");
	tree->Branch("p",&p,"p/D");
	tree->Branch("px",&px,"px/D");
	tree->Branch("py",&py,"py/D");
	tree->Branch("pz",&pz,"pz/D");
	tree->Branch("x",&x,"x/D");
	tree->Branch("y",&y,"y/D");
	tree->Branch("z",&z,"z/D");
	tree->Branch("polx",&polx_,"polx/D");
	tree->Branch("poly",&poly_,"poly/D");
	tree->Branch("polz",&polz_,"polz/D");
	tree->Branch("tof",&tof,"tof/D");
	for(int i=0;i<ent;i++)
	{
		treeb->GetEntry(i);
		pid=0;
		x=posx;
		y=posy;
		z=posz;
		px=px_/1000;
		py=py_/1000;
		pz=pz_/1000;
		polx_=polx;
		poly_=poly;
		polz_=polz;
		tof=ltime;
		tree->Fill();
	}
	gDirectory->Delete("tree;1");
	file->Write();
	cout<<"file "<<name+".root"<<" written at "<<dir<<endl;
}
