int trkfg,detfg,i,j,k,l,rfl,u1,u2,d1,d2,lost,absorb,Nrun,cntfg,mb,ufg,dfg=0;
void rootanal()
{
  double en,x,y,z;
  Long64_t time;
  int entries=0;
  float nce=0;
  float neff=0;
  TH1D* E = new TH1D("Energy","Energy",32,2,4.2);
  TH1D* T = new TH1D("Reflection","Reflection",20,0,20);
  TH2D* U = new TH2D("U","DetU",100,-50,50,90,-5,95);
  TH2D* D = new TH2D("D","DetD",100,-50,50,90,-5,95);
  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  TCanvas *c2 = new TCanvas("c2","c2",1200,600);
  TCanvas *c3 = new TCanvas("c3","c3",1200,600);
  TFile *file = new TFile("Out.root");
  TTree *tree = (TTree *)file->Get("tree");
  tree->SetBranchAddress("eng",&en);
  tree->SetBranchAddress("rfl",&rfl);
  tree->SetBranchAddress("posxu",&x);
  tree->SetBranchAddress("posyu",&y);
  tree->SetBranchAddress("poszu",&z);
  int nev = tree->GetEntries();
  for(int i=0;i<nev;i++)
  {
    tree->GetEntry(i);
    if(y>0)
    {
      U->Fill(x,sqrt((z-50)*(z-50)+(y-115)*(y-115)));
    }
    else
    {
      D->Fill(x,sqrt((z-50)*(z-50)+(y+115)*(y+115)));
    }
    E->Fill(en);
    T->Fill(rfl);
  }
  c1->Divide(2,1);
  c1->cd(1);
  E->GetXaxis()->SetTitle("Energy of Photon[eV]");
  E->GetYaxis()->SetTitle("detection[#]");
  E->Draw();
  c1->cd(2);
  T->GetXaxis()->SetTitle("Reflection[#]");
  T->GetYaxis()->SetTitle("detection[#]");
  T->Draw();
  c2->cd();
  U->GetXaxis()->SetTitle("Xposition[mm]");
  U->GetYaxis()->SetTitle("Yposition[mm]");
  U->Draw("COLZ");
  c3->cd();
  D->GetXaxis()->SetTitle("Xposition[mm]");
  D->GetYaxis()->SetTitle("Yposition[mm]");
  D->Draw("COLZ");
}
