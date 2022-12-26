void Insert(Double_t tmp[3],Double_t a,Double_t b,Double_t c)
{
	tmp[0]=a;
	tmp[1]=b;
	tmp[2]=c;
}
void Subtract(Double_t tmp[3],Double_t a[3], Double_t b[3])
{
	for(int i=0;i<3;i++)
	{
		tmp[i]=a[i]-b[i];
	}
}
Double_t Product(Double_t a[3],Double_t b[3])
{
	Double_t val=0;
	for(int i=0;i<3;i++)
	{
		val+=a[i]*b[i];
	}
	return val;
}
void Normalize(Double_t a[3])
{
	Double_t norm = sqrt(Product(a,a));
	if(norm==0)
	{
		norm=1;
	}
	for(int i=0;i<3;i++)
	{
		a[i]=a[i]/norm;
	}
}
Double_t Abs(Double_t a)
{
	if(a>0)
	{
		return a;
	}
	else
	{
		return -a;
	}
}
void Print(Double_t a[3])
{
	for(int i=0;i<3;i++)
	{
		cout<<a[i]<<endl;
	}
}
void Angle()
{
	TString name= "LGtest.root";
	Double_t posx,posy,posz;
	Double_t px,py,pz;
	TFile* file = new TFile(name,"READ");
	TTree* tree= (TTree*)file->Get("treeg");
	tree->SetBranchAddress("posxg",&posx);
	tree->SetBranchAddress("posyg",&posy);
	tree->SetBranchAddress("poszg",&posz);
	tree->SetBranchAddress("pxg",&px);
	tree->SetBranchAddress("pyg",&py);
	tree->SetBranchAddress("pzg",&pz);
	Int_t ent=tree->GetEntries();
	Double_t n1[3],n2[3],n3[3],n4[3];	
	Insert(n1,0,-6,-100);
	Insert(n2,100,-17.5,0);
	Insert(n3,0,0,-1);
	Insert(n4,-100,-17.5,0);
	Normalize(n1);
	Normalize(n2);
	Normalize(n3);
	Normalize(n4);
	Double_t v1[3],v2[3];	
	Insert(v1,-35,400,5);
	Insert(v2,35,400,-5);
	Int_t flg=0;
	Double_t pos[3];
	Double_t mom[3];
	Double_t pv1[3];
	Double_t pv2[3];
	Int_t plane=0;
	Double_t cos=0;
	TH1I* PLANE = new TH1I("Hit Plane","Hit Plane",5,0,5);
	TH1D* COS = new TH1D("Incident Cosine","Incident Cosine",100,0,1);
//	ent=10;
	for(int i=0;i<ent;i++)
	{
		tree->GetEntry(i);
		posy=Abs(posy);
		Insert(pos,posx,posy,posz);
		Insert(mom,px,py,pz);
		Subtract(pv1,v1,pos);
		Subtract(pv2,v2,pos);
		Normalize(mom);
		Normalize(pv1);
		Normalize(pv2);
		//		cout<<"pv1 is: "<<endl;
		//	Print(pv1);
		//		cout<<"pv2 is: "<<endl;
		//	Print(pv2);
		//		cout<<"Plane 1: "<<Abs(Product(n1,pv1))<<endl;

		//		cout<<"Plane 3: "<<Abs(Product(n3,pv2))<<endl;
		//		cout<<Product(n1,pv1)<<endl;
		if(Abs(Product(n1,pv1))<1e-10)
		{
			plane=1;
			cos=Product(n1,mom);
		}
		else if(Abs(Product(n2,pv1))<0.005)
		{
			plane=2;
			cos=Product(n2,mom);
			//		cout<<"Plane 2: "<<Abs(Product(n2,pv1))<<endl;
		}
		else if(Abs(Product(n3,pv2))<1e-10)
		{
			plane=3;
			cos=Product(n3,mom);
		}
		else if(Abs(Product(n4,pv2))<0.005)
		{
			plane=4;
			cos=Product(n4,mom);
			//		cout<<"Plane 4: "<<Abs(Product(n4,pv2))<<endl;
		}
		else
		{
			cout<<"Fail"<<endl;
			cout<<"Plane 1: "<<Abs(Product(n1,pv1))<<endl;
			cout<<"Plane 2: "<<Abs(Product(n2,pv1))<<endl;
			cout<<"Plane 3: "<<Abs(Product(n3,pv2))<<endl;
			cout<<"Plane 4: "<<Abs(Product(n4,pv2))<<endl;
			cout<<"Position: ( "<<posx<<" , "<<posy<<" , "<<posz<<" )"<<endl;
			flg++;
		}
		
//		PLANE->Fill(plane);
		COS->Fill(Abs(cos));
		//	plane=4;
	}
//	PLANE->Draw();
	COS->Draw();
	cout<<"Failed: "<<flg<<endl;
}
