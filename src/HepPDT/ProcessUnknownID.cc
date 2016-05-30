// ----------------------------------------------------------------------
//
// ProcessUnknownID.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------
#include "HepPDT/ProcessUnknownID.hh"
#include "HepPDT/ParticleDataTable.hh"

namespace HepPDT {

thread_local bool ProcessUnknownID::alreadyHere = false;

class sentry {
public:
  sentry(bool& b) : b_(b) { b_ = true; }
  ~sentry() { b_ = false; }
private:
  bool& b_;
};

ParticleData * ProcessUnknownID::callProcessUnknownID
              ( ParticleID key, const ParticleDataTable & pdt ) 
{ 
    ParticleData * pd = 0;
    if( !alreadyHere ) {
       sentry s(alreadyHere);
       pd = processUnknownID( key, pdt );
    } 
    return pd;
}

}	// HepPDT
