int trkfg,detfg,i,j,k,l,rfl,u1,u2,d1,d2,lost,absorb,Nrun,cntfg,mb,ufg,dfg=0;
void MirrorHit()
{
  double en,x,y,z;
  Long64_t time;
  int entries=0;
  float nce=0;
  float neff=0;
  TH1D* E = new TH1D("Energy","Energy",32,2,4.2);
  TH1D* T = new TH1D("Reflection","Reflection",20,0,20);
  TH2D* L = new TH2D("L","WallL",70,-350,350,120,-600,600);
  TH2D* R = new TH2D("R","WallR",70,-350,350,120,-600,600);
  TH2D* ML = new TH2D("ML","MirrorL",42,-210,210,120,-600,600);
  TH2D* MR = new TH2D("MR","MirrorR",42,-210,210,120,-600,600);
  TH2D* MSL = new TH2D("MSL","MirrorSlopeL",200,-1000,1000,120,-600,600);
  TH2D* MSR = new TH2D("MSR","MirrorSlopeR",200,-1000,1000,120,-600,600);
  //TH2D* MSL = new TH2D("MSL","MirrorSlopeL",163,-765,765,120,-600,600);
  // TH2D* MSR = new TH2D("MSR","MirrorSlopeR",163,-765,765,120,-600,600);
  TH2D* MU = new TH2D("ML","MirrorUp",220,-1100,1100,70,-350,350);
  TH2D* MD = new TH2D("MD","MirrorDown",220,-1100,1100,70,-350,350);
  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  TCanvas *c2 = new TCanvas("c2","c2",1200,600);
  TCanvas *c3 = new TCanvas("c3","c3",1200,600);
  TCanvas *c4 = new TCanvas("c4","c4",1200,600);
  TFile *file = new TFile("OutDiag.root");
  TTree *tree = (TTree *)file->Get("treerfl");
  tree->SetBranchAddress("eng",&en);
  tree->SetBranchAddress("rfl",&rfl);
  tree->SetBranchAddress("posx",&x);
  tree->SetBranchAddress("posy",&y);
  tree->SetBranchAddress("posz",&z);
  int nev = tree->GetEntries();
  cout<<nev<<endl;
  double xsl=0;
  double posx=350;
  double posz=430;
  int num=0;
  for(int i=0;i<nev;i++)
  {
    tree->GetEntry(i);
    if(rfl==10){
      num++;
      if(x==-1100)
      {
        L->Fill(z-350,y);
      }
      if(x==1100)
      {
        R->Fill(z-350,y);
      }
      if(z==685)
      {
        if(x>0)
        {
          MR->Fill(x-910,y);
        }
        else
        {
          ML->Fill(x+910,y);
        }
      }
      if(y==590)
      {
        MU->Fill(x,(z-350));
      }
      if(y==-590)
      {
        MD->Fill(x,(z-350));
      }
      if(x*x<1210000&&z<685&&y*y<348100)
      {
        if(x<0)
        {
          //        cout<<z<<" and "<<x<<" and "<<xsl<<endl;
          xsl=sqrt((z-posz)*(z-posz)+(x+posx)*(x+posx));
          if(z<posz)
          {
            MSL->Fill(xsl,y);
          }
          else
          {
            MSL->Fill(-xsl,y);
          }
        }
        else
        {
          xsl=sqrt((z-posz)*(z-posz)+(x-posx)*(x-posx));
          if(z>posz)
          {
            MSR->Fill(xsl,y);
          }
          else
          {
            MSR->Fill(-xsl,y);
          }
        }
      }
    }
  }
  cout<<xsl<<endl;
  c1->Divide(2,1);
  c2->Divide(2,1);
  c3->Divide(2,1);
  c4->Divide(2,1);
  c1->cd(1);
  MU->GetXaxis()->SetTitle("Xposition[mm]");
  MU->GetYaxis()->SetTitle("Yposition[mm]");
  MU->Draw("COLZ");
  c1->cd(2);
  MD->GetXaxis()->SetTitle("Xposition[mm]");
  MD->GetYaxis()->SetTitle("Yposition[mm]");
  MD->Draw("COLZ");
  c2->cd(1);
  L->GetXaxis()->SetTitle("Xposition[mm]");
  L->GetYaxis()->SetTitle("Yposition[mm]");
  L->Draw("COLZ");
  c2->cd(2);
  R->GetXaxis()->SetTitle("Xposition[mm]");
  R->GetYaxis()->SetTitle("Yposition[mm]");
  R->Draw("COLZ");
  c3->cd(1);
  ML->GetXaxis()->SetTitle("Xposition[mm]");
  ML->GetYaxis()->SetTitle("Yposition[mm]");
  ML->Draw("COLZ");
  c3->cd(2);
  MR->GetXaxis()->SetTitle("Xposition[mm]");
  MR->GetYaxis()->SetTitle("Yposition[mm]");
  MR->Draw("COLZ");
  c4->cd(1);
  MSL->GetXaxis()->SetTitle("Xposition[mm]");
  MSL->GetYaxis()->SetTitle("Yposition[mm]");
  MSL->Draw("COLZ");
  c4->cd(2);
  MSR->GetXaxis()->SetTitle("Xposition[mm]");
  MSR->GetYaxis()->SetTitle("Yposition[mm]");
  MSR->Draw("COLZ");
  cout<<"number is: "<<num<<endl;
}
