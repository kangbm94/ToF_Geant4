TF1* fLandau = new TF1("fLandau","landau",0,4000);

double SlewFn(double* x, double* p){
	double val = p[0]/sqrt(x[0]-p[1])+p[2];
	return val;
}
TF1* fSlew = new TF1("fSlew","SlewFn",0,4,3);


void Timing(){
	TFile* file = new TFile("Cosmic00.root","read");
	TTree* tree = (TTree*)file->Get("tree");
	int qdc[16];
	int tdc[16];
	tree->SetBranchAddress("qdc",qdc);
	tree->SetBranchAddress("tdc",tdc);
	int ref_ch=1;
	int det_ch[2]={2,3};
	int trg_ch[4]={8,9,12,13};
	int ch[6]={det_ch[0],det_ch[1],trg_ch[0],trg_ch[1],trg_ch[2],trg_ch[3]};
	TString name[6]={"BTOFU","BTOFD","TRG1L","TRG1R","TRG2L","TRG2R"};
	int ent = tree->GetEntries();
	TH1I* QDCHist[6];
	TCanvas* c1 = new TCanvas("c1","c1",1200,800);
	c1->Divide(3,2);
	int ped = 130;
	double mpv[6];
	for(int i=0;i<6;i++){
		TString ht = name[i]+"_QDCHist"; 
		QDCHist[i]=new TH1I(ht,ht,4000,0,4000);
		c1->cd(i+1);
		tree->Draw(Form("qdc[%d]>>",ch[i])+ht,Form("tdc[%d]!=-9999",ch[i]),"0");
		QDCHist[i]->Fit(fLandau,"q0");
		mpv[i]=fLandau->GetParameter(1)-ped;
		cout<<mpv[i]<<endl;
	}
	
	TH1I* TDCPeakHist[6];
	int tpeak[6];

	for(int i=0;i<6;i++){
		TString ht = name[i]+"_TDCPeakHist"; 
		TDCPeakHist[i]=new TH1I(ht,ht,200,-1000,1000);
		c1->cd(i+1);
		tree->Draw(Form("tdc[%d]-tdc[%d]>>",ch[i],ref_ch)+ht,Form("tdc[%d]!=-9999",ch[i]),"0");
		tpeak[i]=-1000+10*(TDCPeakHist[i]->GetMaximumBin());
		cout<<tpeak[i]<<endl;
	}
	double lsb= 0.025;
	TH2D* SlewHist[6];
	double p0[6],p1[6],p2[6];
	for(int i=0;i<6;i++){
		c1->cd(i+1);
		TString ht = name[i]+"_Slew"; 
		SlewHist[i]=new TH2D(ht,ht,100,0,5,100,-5,5);
		tree->Draw(  Form("%f*(tdc[%d]-tdc[%d]-%d):(qdc[%d]-%d)/%f>>",lsb,ch[i],ref_ch,tpeak[i],ch[i],ped,mpv[i])+ht,Form("tdc[%d]!=-9999",ch[i]),"col");	
		fSlew->SetRange(0.2,4);
		SlewHist[i]->Fit("fSlew","R");	
		p0[i]=fSlew->GetParameter(0);	
		p1[i]=fSlew->GetParameter(1);	
		p2[i]=fSlew->GetParameter(2);	
	}
	TCanvas* c2 = new TCanvas("c2","c2",1200,800);
	c2->Divide(3,2);

	TH1D* TimeHist[6];
	for(int i=0;i<6;i++){
		c2->cd(i+1);
		TString ht = name[i]+"_Time"; 
		TimeHist[i]=new TH1D(ht,ht,100,-5,5);
		tree->Draw(  Form("%f*(tdc[%d]-tdc[%d]-%d) -%f/sqrt((qdc[%d]-%d)/%f-%f)-%f>>",lsb,ch[i],ref_ch,tpeak[i],p0[i],ch[i],ped,mpv[i],p1[i],p2[i])+ht,Form("tdc[%d]!=-9999",ch[i]),"col");	
		TimeHist[i]->Fit("gaus","R");	
	}
	cout<<"hi"<<endl;
	TFile* fn = new TFile("Cosmic_PHC.root","recreate");
	TTree* tree_PHC = new TTree("tree","tree");
	double timing[6],charge[6];
	tree_PHC->Branch("t",timing,"t[6]/D");
	tree_PHC->Branch("de",charge,"de[6]/D");
	for(int i=0;i<ent;i++){
		tree->GetEntry(i);
		for(int j=0;j<6;j++){
			charge[j]=(qdc[ch[j]]-ped)/mpv[j];
			cout<<j<<" : "<<charge[j]<<endl;
//			charge[j]=(qdc[ch[j]]-ped);
			timing[j]=lsb*(tdc[ch[j]]-tdc[ref_ch]-tpeak[j])-p0[j]/sqrt(charge[j]-p1[j])-p2[j];
		}
		tree_PHC->Fill();
	}
	fn->Write();
}

