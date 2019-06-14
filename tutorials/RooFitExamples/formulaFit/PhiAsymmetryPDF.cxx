/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "PhiAsymmetryPDF.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(PhiAsymmetryPDF); 

 PhiAsymmetryPDF::PhiAsymmetryPDF(const char *name, const char *title, 
                        RooAbsReal& _Phi,
                        RooAbsReal& _A,
                        RooAbsReal& _B) :
   HS::FIT::RooHSEventsPDF(name,title),
   Phi("Phi","Phi",this,_Phi),
   A("A","A",this,_A),
   B("B","B",this,_B)
 { 
   MakeSets();
   Phi.SetName(_Phi.GetName());
   A.SetName(_A.GetName());
   B.SetName(_B.GetName());
 } 


 PhiAsymmetryPDF::PhiAsymmetryPDF(const PhiAsymmetryPDF& other, const char* name) :  
   HS::FIT::RooHSEventsPDF(other,name),
   Phi("Phi",this,other.Phi),
   A("A",this,other.A),
   B("B",this,other.B)
 { 
   MakeSets();
   Phi.SetName(other.Phi.GetName());
   A.SetName(other.A.GetName());
   B.SetName(other.B.GetName());
   if(fEvTree) SetEvTree(fEvTree,fCut);//Needs fProxSet filled first
 } 
void PhiAsymmetryPDF::MakeSets(){
   fProxSet.push_back(&Phi);
   fParSet.push_back(&A);
   fParSet.push_back(&B);
   InitSets();
}



 Double_t PhiAsymmetryPDF::evaluateData() const 
 {
  
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   return 1.0 + (A*TMath::Cos(2*TMath::DegToRad()*Phi)+B*TMath::Sin(2*TMath::DegToRad()*Phi));
   // return 1.0 + (A*TMath::Cos(2/57.29578*Phi)+B*0);
 
 } 

Double_t PhiAsymmetryPDF::evaluateMC(const vector<Float_t> *vars,const  vector<Int_t> *cats) const {
// ENTER IDENTICAL EXPRESSION TO evaluate() IN TERMS OF MC VARIABLE ARGUMENTS HERE
//  Double_t mcPhi=(*vars)[fTreeEntry*fNvars+0];
  Double_t mcPhi=fvecReal[fTreeEntry*fNvars+0];
  return 1.0 + (A*TMath::Cos(2*TMath::DegToRad()*mcPhi)+B*TMath::Sin(2*TMath::DegToRad()*mcPhi)); 
	    
}


