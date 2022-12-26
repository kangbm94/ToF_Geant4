#ifndef Math_h
#define Math_h
double square(double a){ 
	return a*a;
}
int PM(int a){
	if(a%2==0){
		return 1;
	}
	else{
		return -1;
	}
}
double Min(double a, double b){
	if(a>b){
		return b;
	}
	else{
		return a;
	}
}
double Max(double a, double b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}
double Power(double x,int n){
		double value=1;
		for(int i=0;i<n;i++){
			value=value*x;
		}
		return value;
}
double Polynomial(double x, double* p,int n){
	double value=0;
	for(int i=0;i<n+1;i++){
		value+=p[i]*Power(x,i);
	}
	return value;
}
double SquareSum(double a, double b){
	return sqrt(a*a+b*b);
}
double Gaussian(double x, double mean, double sigma, double peak){
	double par=(x-mean)/sigma;
	double val = peak*exp(-par*par/2);
	return val;
}
double Step(double a){
	if(a>0){
		return 1;
	}
	else{
		return 0;
	}
}
//
double QuadRoot(double a,double b,double c, int conf){
	if(conf<0){
		return  (-b -sqrt(b*b-4*a*c))/(2*a);
	}
	else{
		return (-b +sqrt(b*b-4*a*c))/(2*a);
	}
}
double T1(double a,double b, double c, double d){
	double p0=1/(3*a);
	double p1=2*b*b*b-9*a*b*c+27*a*a*d;
	double p2 = b*b-3*a*c;
	double val= -b*p0-p0*(
			pow((p1+sqrt(p1*p1-4*p2*p2*p2))/2,1./3)
		 +pow((p1-sqrt(p1*p1-4*p2*p2*p2))/2,1./3)
			);
		return val;
}


double Qr1(double a, double b, double c, double d, double e){
	return 4;
}





//Randoms
double GenUniformRandom(double range){
	double rnd=gRandom->Rndm();
	return range*rnd;
}
double GenUniformRandom(){
	return GenUniformRandom(1);
}
double chebyshev(double x, int n){
	double val;
	switch(n){
		case 0:
			val=1;
			break;
		case 1: 
			val=x;
			break;
		case 2: 
			val= 2*x*x-1;
			break;
		case 3:
			val= 4*x*x*x-3*x;
			break;
		case 4: 
			val= 8*x*x*x*x-8*x*x+1;
			break;
		case 5: 
			val= 16*x*x*x*x*x-20*x*x*x+5*x;
			break;
		case 6: 
			val= 32*x*x*x*x*x*x-48*x*x*x*x+18*x*x-1;
			break;
	}
	return val;
}
#endif
