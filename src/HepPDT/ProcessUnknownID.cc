// ----------------------------------------------------------------------
//
// ProcessUnknownID.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------
#include "HepPDT/ProcessUnknownID.hh"
#include "HepPDT/ParticleDataTable.hh"

namespace HepPDT {

ParticleData * ProcessUnknownID::callProcessUnknownID
              ( ParticleID key, const ParticleDataTable & pdt ) 
{ 
    ParticleData * pd = 0;
    if( !alreadyHere ) {
       alreadyHere = true;
       pd = processUnknownID( key, pdt );
       alreadyHere = false;
    } 
    return pd;
}

}	// HepPDT
