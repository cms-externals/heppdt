// ----------------------------------------------------------------------
//
// HeavyIonUnknownID.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------
#include "HepPDT/HeavyIonUnknownID.hh"
#include "HepPDT/ParticleDataTable.hh"

namespace HepPDT {

ParticleData * HeavyIonUnknownID::processUnknownID
              ( ParticleID key, const ParticleDataTable & pdt ) 
{ 
    ParticleData * pd = 0;
    if( key.isNucleus() ) {
     
        // have to create a TempParticleData with all properties first
        TempParticleData tpd(key);
	// calculate approximate mass
	// WARNING: any calls to particle() from here MUST reference 
	//          a ParticleData which is already in the table
	// This convention is enforced.
	const ParticleData * proton = pdt.particle(2212);
	if( proton ) {
	    double protonMass = proton->mass();
	    tpd.tempMass = Measurement(key.A()*protonMass, 0.);
	    pd = new ParticleData(tpd);
	}
    }
    return pd;
}

}	// HepPDT
