const double LightSpeed = 299792458;// m/s

const int nbuf = 300;
int np,bnp;
int pid[nbuf],bpid[nbuf],trk[nbuf],ntrk[nbuf];
double px[nbuf],py[nbuf],pz[nbuf],x[nbuf],y[nbuf],z[nbuf],bpx[nbuf],bpy[nbuf],bpz[nbuf],bx[nbuf],by[nbuf],bz[nbuf];
double path[nbuf],time_[nbuf];

int AtomicNumber(int pid){
	int val = pid-1e9;
	val = val%10000;
	return val/10;
}
int ChargeNumber(int pid){
	if(pid<10000){
		return 1;
	}
	int val = pid-1e9;
	return val/10000;
}
int ZNumber(int pid){
	int val = pid%10000;
	return val/10;
}
TFile* org = new TFile("../../QMD.root","read");
void Analyze(){
	cout<<"Analyze(filename)"<<endl;
	cout<<"AnalyzeByZ(filename)"<<endl;
}
double beta(double path, double time){
	return path/time/LightSpeed * 1e6;	
}
double norm(double a,double b, double c){
	double val = a*a+b*b+c*c;
	return sqrt(val);
}
void Analyze(TString filename){
	TFile* file = new TFile(filename,"read");
	TTree* tree = (TTree*)file->Get("tree");
	tree->SetBranchAddress("QMDnp",&np);
	tree->SetBranchAddress("QMDpid",pid);
	tree->SetBranchAddress("QMDpx",px);
	tree->SetBranchAddress("QMDpy",py);
	tree->SetBranchAddress("QMDpz",pz);
	tree->SetBranchAddress("QMDx",x);
	tree->SetBranchAddress("QMDy",y);
	tree->SetBranchAddress("QMDz",z);
	tree->SetBranchAddress("QMDpath",path);
	tree->SetBranchAddress("QMDtime",time_);


	gRandom->SetSeed();

	TCanvas* c1 = new TCanvas("c1","c1",1200,800);
//	c1->Divide(2,2);
	TH2D* hist1 = new TH2D("beta vs Momentum", "beta vs Momentum",1000,0,3e3,1000,0,1);
	TH2D* hist2 = new TH2D("beta vs Momentum_150ps", "beta vs Momentum_150ps",2000,0,6e3,1000,0,1);
	TH2D* hist3 = new TH2D("beta vs Momentum_200ps", "beta vs Momentum_200ps",2000,0,6e3,1000,0,1);
	TH2D* hist4 = new TH2D("beta vs Momentum_300ps", "beta vs Momentum_300ps",2000,0,6e3,1000,0,1);
	int ent = tree->GetEntries();
	for(int i=0;i<ent;i++){
		tree->GetEntry(i);
		for(int j=0;j<np;j++){
			double pid_ = pid[j];
			int chg = ChargeNumber(pid_);
			double px_=px[j];	
			double py_=py[j];	
			double pz_=pz[j];	
			double t=time_[j];
			double path_=path[j];	
			double mom = norm(px_,py_,pz_)/chg;
			//			double mom = norm(px_,py_,pz_);
			double bet = beta(path_,t);
			double t1 = t+gRandom->Gaus(0,0.15);
			double t2 = t+gRandom->Gaus(0,0.2);
			double t3 = t+gRandom->Gaus(0,0.3);
			hist1->Fill(mom,beta(path_,t));
			mom=gRandom->Gaus(mom,0.03*mom);
			if(pid_!=2202){
				hist2->Fill(mom,beta(path_,t1));
				hist3->Fill(mom,beta(path_,t2));
				hist4->Fill(mom,beta(path_,t3));
			}
		}
	}
	c1->cd(1);
	hist1->GetXaxis()->SetTitle("Momentum/Z[MeV]");
	hist1->GetYaxis()->SetTitle("beta");
	hist1->Draw("col");
	c1->cd(2);
	hist2->GetXaxis()->SetTitle("Momentum/Z[MeV]");
	hist2->GetYaxis()->SetTitle("beta");
	hist2->Draw("col");
	c1->cd(3);
	hist3->GetXaxis()->SetTitle("Momentum/Z[MeV]");
	hist3->GetYaxis()->SetTitle("beta");
	hist3->Draw("col");
	c1->cd(4);
	hist4->GetXaxis()->SetTitle("Momentum/Z[MeV]");
	hist4->GetYaxis()->SetTitle("beta");
	hist4->Draw("col");
	int Eent = hist1->GetEffectiveEntries();
	cout<<Eent<<endl;

	c1->SaveAs("BetaVsMomZ.pdf");
}
void AnalyzeByZ(TString filename){
	TFile* file = new TFile(filename,"read");
	TTree* tree = (TTree*)file->Get("tree");
	tree->SetBranchAddress("QMDnp",&np);
	tree->SetBranchAddress("QMDpid",pid);
	tree->SetBranchAddress("QMDpx",px);
	tree->SetBranchAddress("QMDpy",py);
	tree->SetBranchAddress("QMDpz",pz);
	tree->SetBranchAddress("QMDx",x);
	tree->SetBranchAddress("QMDy",y);
	tree->SetBranchAddress("QMDz",z);
	tree->SetBranchAddress("QMDpath",path);
	tree->SetBranchAddress("QMDtime",time_);

	gStyle->SetOptStat(0000);
	gRandom->SetSeed();

	const int nz = 10;
	TCanvas* c[nz];
	TH2D* hist[nz*4];
	TString ht[4];
	TString ht_base = "Beta vs Momentum/Z";
		for(int i=0;i<nz;i++){
			c[i]= new TCanvas(Form("c%d",i),Form("c%d",i),1200,800);
//			c[i]->Divide(2,2);
			ht[0]= ht_base+Form("_Z=%d",i+1);
			ht[1]= ht_base+Form("_150ps")+Form("_Z=%d",i+1);
			ht[2]= ht_base+Form("_200ps")+Form("_Z=%d",i+1);
			ht[3]= ht_base+Form("_300ps")+Form("_Z=%d",i+1);
			hist[i*4]= new TH2D(ht[0], ht[0],1000,0,3e3,1000,0,1);
			hist[i*4+1]= new TH2D(ht[1], ht[1],1000,0,3e3,1000,0,1);
			hist[i*4+2]= new TH2D(ht[2], ht[2],1000,0,3e3,1000,0,1);
			hist[i*4+3]= new TH2D(ht[3], ht[3],1000,0,3e3,1000,0,1);
		}
		cout<<"Hist ini"<<endl;
	int ent = tree->GetEntries();
	for(int i=0;i<ent;i++){

		tree->GetEntry(i);
		for(int j=0;j<np;j++){
			double pid_ = pid[j];
			int chg = ChargeNumber(pid_);
			double px_=px[j];	
			double py_=py[j];	
			double pz_=pz[j];	
			double t=time_[j];
			double path_=path[j];	
			double mom = norm(px_,py_,pz_)/chg;
			double bet = beta(path_,t);
			double t1 = t+gRandom->Gaus(0,0.15);
			double t2 = t+gRandom->Gaus(0,0.2);
			double t3 = t+gRandom->Gaus(0,0.3);
			if(chg<nz+1){
//				mom=gRandom->Gaus(mom,0.03*mom);
				path_=gRandom->Gaus(path_,0.03*path_);
				hist[4*chg-4]->Fill(mom,beta(path_,t));
				hist[4*chg-3]->Fill(mom,beta(path_,t1));
				hist[4*chg-2]->Fill(mom,beta(path_,t2));
				hist[4*chg-1]->Fill(mom,beta(path_,t3));
			
				/*
				hist[4*chg-4]->Fill(mom,t);
				mom=gRandom->Gaus(mom,0.03*mom);
				hist[4*chg-3]->Fill(mom,t1);
				hist[4*chg-2]->Fill(mom,t2);
				hist[4*chg-1]->Fill(mom,t3);
			*/
			}
		}
	}
	for(int i=0;i<nz;i++){
		c[i]->cd(1);
		gPad->SetLogz();
		hist[4*i]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[4*i]->GetYaxis()->SetTitle("beta");
		hist[4*i]->Draw("col");
		c[i]->cd(2);
		gPad->SetLogz();
		hist[4*i+1]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[4*i+1]->GetYaxis()->SetTitle("beta");
		hist[4*i+1]->Draw("col");
		c[i]->cd(3);
		gPad->SetLogz();
		hist[4*i+2]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[4*i+2]->GetYaxis()->SetTitle("beta");
		hist[4*i+2]->Draw("col");
		c[i]->cd(4);
		gPad->SetLogz();
		hist[4*i+3]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[4*i+3]->GetYaxis()->SetTitle("beta");
		hist[4*i+3]->Draw("col");
	}
}
void MakeGraph(TString filename){
	TFile* file = new TFile(filename,"read");
	TTree* tree = (TTree*)file->Get("tree");
	tree->SetBranchAddress("QMDnp",&np);
	tree->SetBranchAddress("QMDpid",pid);
	tree->SetBranchAddress("QMDpx",px);
	tree->SetBranchAddress("QMDpy",py);
	tree->SetBranchAddress("QMDpz",pz);
	tree->SetBranchAddress("QMDx",x);
	tree->SetBranchAddress("QMDy",y);
	tree->SetBranchAddress("QMDz",z);
	tree->SetBranchAddress("QMDpath",path);
	tree->SetBranchAddress("QMDtime",time_);

	gStyle->SetOptStat(0000);
	gRandom->SetSeed();

	const int nz = 1;
	TCanvas* c[nz];
	TH2D* hist[nz*6];
	TString ht[6];
	TString ht_base = "Beta vs Momentum/Z";
		for(int i=0;i<nz;i++){
			c[i]= new TCanvas(Form("c%d",i),Form("c%d",i),1200,800);
//			c[i]->Divide(2,1);
			ht[0]= ht_base;//+Form("_Z=%d or 2",1);
			ht[1]= ht_base+Form("_Z=%d",2);
			ht[2]= ht_base+Form("_Z=%d",2);
			ht[3]= ht_base+Form("_180ps");//+Form("_Z=%d or 2",1);
			ht[4]= ht_base+Form("_180ps");//+Form("_Z=%d",2);
			ht[5]= ht_base+Form("_180ps")+Form("_Z=%d",3);
			hist[i*6]= new TH2D(ht[0], ht[0],1000,0,3e3,1000,0,1);
			hist[i*6+1]= new TH2D(ht[1], ht[1],1000,0,3e3,1000,0,1);
			hist[i*6+2]= new TH2D(ht[2], ht[2],1000,0,3e3,1000,0,1);
			hist[i*6+3]= new TH2D(ht[3], ht[3],1000,0,3e3,1000,0,1);
			hist[i*6+4]= new TH2D(ht[4], ht[4],1000,0,3e3,1000,0,1);
			hist[i*6+5]= new TH2D(ht[5], ht[5],1000,0,3e3,1000,0,1);
		}
		cout<<"Hist ini"<<endl;
	int ent = tree->GetEntries();
	for(int i=0;i<ent;i++){

		tree->GetEntry(i);
		for(int j=0;j<np;j++){
			double pid_ = pid[j];
			int chg = ChargeNumber(pid_);
			int zn = ZNumber(pid_);
			double px_=px[j];	
			double py_=py[j];	
			double pz_=pz[j];	
			double t=time_[j];
			double path_=path[j];	
			double mom = norm(px_,py_,pz_)/chg;
			mom=gRandom->Gaus(mom,0.03*mom);
			double bet = beta(path_,t);
			double t1 = t+gRandom->Gaus(0,0.15);
			double t2 = t+gRandom->Gaus(0,0.25);
			double t3 = t+gRandom->Gaus(0,0.3);
			if(1){
				path_=gRandom->Gaus(path_,0.005*path_);
				hist[0]->Fill(mom,beta(path_,t));
				hist[3]->Fill(mom,beta(path_,t2));
			}
			if(chg==1){
				path_=gRandom->Gaus(path_,0.005*path_);
				hist[1]->Fill(mom,beta(path_,t));
				hist[4]->Fill(mom,beta(path_,t2));
			}
			if(chg==2&&zn==5){
				path_=gRandom->Gaus(path_,0.005*path_);
				hist[2]->Fill(mom,beta(path_,t));
				hist[5]->Fill(mom,beta(path_,t2));
			}
		}
	}
	for(int i=0;i<nz;i++){
		c[i]->cd(1);
		gPad->SetLogz();
		hist[6*i]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[6*i]->GetYaxis()->SetTitle("beta");
		hist[6*i]->GetXaxis()->SetTitleSize(0.05);
		hist[6*i]->GetYaxis()->SetTitleSize(0.05);
//		hist[6*i]->Draw("col");
		c[i]->cd(3);
		gPad->SetLogz();
		hist[6*i+1]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[6*i+1]->GetYaxis()->SetTitle("beta");
		hist[6*i+1]->GetXaxis()->SetTitleSize(0.05);
		hist[6*i+1]->GetYaxis()->SetTitleSize(0.05);
//		hist[6*i+1]->Draw("colz");
		c[i]->cd(4);
		gPad->SetLogz();
		hist[6*i+2]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[6*i+2]->GetYaxis()->SetTitle("beta");
		hist[6*i+2]->GetXaxis()->SetTitleSize(0.05);
		hist[6*i+2]->GetYaxis()->SetTitleSize(0.05);
//		hist[6*i+2]->Draw("colz");
		c[i]->cd(2);
		gPad->SetLogz();
		hist[6*i+3]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[6*i+3]->GetYaxis()->SetTitle("beta");
		hist[6*i+3]->GetXaxis()->SetTitleSize(0.05);
		hist[6*i+3]->GetYaxis()->SetTitleSize(0.05);
		hist[6*i+3]->Draw("col");
		c[i]->cd(5);
		gPad->SetLogz();
		hist[6*i+4]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[6*i+4]->GetYaxis()->SetTitle("beta");
		hist[6*i+4]->GetXaxis()->SetTitleSize(0.05);
		hist[6*i+4]->GetYaxis()->SetTitleSize(0.05);
//		hist[6*i+4]->Draw("col");
		c[i]->cd(6);
		gPad->SetLogz();
		hist[6*i+5]->GetXaxis()->SetTitle("Momentum/Z[MeV]");
		hist[6*i+5]->GetYaxis()->SetTitle("beta");
		hist[6*i+5]->GetXaxis()->SetTitleSize(0.05);
		hist[6*i+5]->GetYaxis()->SetTitleSize(0.05);
//		hist[6*i+5]->Draw("col");
	}
	TCanvas* c2 = new TCanvas("c2","c2",1200,600);
	
	auto* h2 = (TH1D*)hist[2]->ProjectionY("beta distribution at P = 2 GeV, Z=3",190,210);
	h2->SetTitle("P/Z=1 GeV/c, Z=2");
	h2->GetYaxis()->SetTitle("Entries/[0.001]");
	c2->cd();
	h2->Draw();
	
}
