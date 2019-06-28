/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "PhiAsymmetryPDFVar.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(PhiAsymmetryPDFVar); 

 PhiAsymmetryPDFVar::PhiAsymmetryPDFVar(const char *name, const char *title, 
                        RooAbsReal& _Phi,
                        RooAbsReal& _A,
			RooAbsReal& _B,
		        RooAbsReal& _COS2,
		        RooAbsReal& _SIN2) :  HS::FIT::RooHSEventsPDF(name,title),
   Phi("Phi","Phi",this,_Phi),
   A("A","A",this,_A),
   B("B","B",this,_B),
   COS2("COS2","COS2",this,_COS2),
   SIN2("SIN2","SIN2",this,_SIN2)
 { 
   MakeSets();
   Phi.SetName(_Phi.GetName());
   A.SetName(_A.GetName());
   B.SetName(_B.GetName());
   COS2.SetName(_COS2.GetName());
   SIN2.SetName(_SIN2.GetName());
   cout<<"CREATE FORMULAVARS "<<endl;
   //fCos=new RooFormulaVar("cos2Phi","cos(2*TMath::DegToRad()*Phi)",RooArgList(Phi.arg() ));
   //fSin=new RooFormulaVar("sin2Phi","sin(2*TMath::DegToRad()*Phi)",RooArgList(Phi.arg()));
   cout<<"DONE CREATE FORMULAVARS "<<endl;
   fArgsL.add(_A);
   fArgsL.add(_COS2);
   fArgsL.add(_B);
   fArgsL.add(_SIN2);

  // Double_t NComponents=fArgsL.getSize();
  // for(Int_t i=0;i<NComponents;i++){
  //   fArgsV.push_back(RooRealProxy(fArgsL[i].GetName(),fArgsL[i].GetName(),this,(RooAbsReal&)fArgsL[i]));
  // } 
 }

 PhiAsymmetryPDFVar::PhiAsymmetryPDFVar(const PhiAsymmetryPDFVar& other, const char* name) :  
   HS::FIT::RooHSEventsPDF(other,name),
   Phi("Phi",this,other.Phi),
   A("A",this,other.A),
   B("B",this,other.B),
   COS2("COS2",this,other.COS2),
   SIN2("SIN2",this,other.SIN2),
   fArgsL("argsl",this,other.fArgsL)
 { 
   MakeSets();
   Phi.SetName(other.Phi.GetName());
   A.SetName(other.A.GetName());
   B.SetName(other.B.GetName());
   if(fEvTree) SetEvTree(fEvTree,fCut);//Needs fProxSet filled first
  cout<<"COPYING FORMULAVARS "<<endl;
  //fCos=nullptr;
  //fSin=other.fSin;
  // fCos=new RooFormulaVar("cos2Phi","cos(2*TMath::DegToRad()*Phi)",RooArgList(Phi.arg() ));
  //fSin=new RooFormulaVar("sin2Phi","sin(2*TMath::DegToRad()*Phi)",RooArgList(Phi.arg()));
  cout<<"DONE COPYING FORMULAVARS "<<endl;
  fArgs.push_back(&A);
  fArgs.push_back(&COS2);
  fArgs.push_back(&B);
  fArgs.push_back(&SIN2);
  
  Double_t NComponents=fArgsL.getSize();
  for(Int_t i=0;i<NComponents;i++){
    fArgsV.push_back(new RooRealProxy(fArgsL[i].GetName(),fArgsL[i].GetName(),this,(RooAbsReal&)fArgsL[i]));
  } 
 } 
void PhiAsymmetryPDFVar::MakeSets(){
   fProxSet.push_back(&Phi);
   fParSet.push_back(&A);
   fParSet.push_back(&B);
   fParSet.push_back(&COS2);
   fParSet.push_back(&SIN2);
   InitSets();
}



 Double_t PhiAsymmetryPDFVar::evaluate() const 
 {
   //cout<<COS2<<" "<<SIN2<<" "<<Phi<<endl;
    // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   //return 1.0 + A*COS2+B*SIN2;
   //return 1 + *fArgs[0]*(*fArgs[1]) + *fArgs[2]*(*fArgs[3]);
   Double_t val=1;
   // Double_t NComponents=fArgs.size();
   // for(Int_t i=0;i<NComponents;i+=2){
   //   val+=*fArgs[i]*(*fArgs[i+1]);
   // }

   // Double_t NComponents=fArgsL.getSize();
   // for(Int_t i=0;i<NComponents;i+=2){
   //   val+=(static_cast<RooAbsReal&>(fArgsL[i])).getVal()*(static_cast<RooAbsReal&>(fArgsL[i+1])).getVal();
   // }

  Double_t NComponents=fArgsV.size();
   for(Int_t i=0;i<NComponents;i+=2){
     val+=(*fArgsV[i])*(*fArgsV[i+1]);
   }

   
   return val;
 } 

Double_t PhiAsymmetryPDFVar::evaluateMC(const vector<Float_t> *vars,const  vector<Int_t> *cats) const {
// ENTER IDENTICAL EXPRESSION TO evaluate() IN TERMS OF MC VARIABLE ARGUMENTS HERE
  Double_t mcPhi=(*vars)[fTreeEntry*fNvars+0];
  return 1.0 + (A*TMath::Cos(2*TMath::DegToRad()*mcPhi)+B*TMath::Sin(2*TMath::DegToRad()*mcPhi)); 
	    
}

