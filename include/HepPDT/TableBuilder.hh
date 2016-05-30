// ----------------------------------------------------------------------
//
// TableBuilder.hh
// Author: Marc Paterno, Walter Brown, Lynn Garren
//
// ----------------------------------------------------------------------
// User code:
//    ParticleDataTable pdt;
//    {
//       TableBuilder      tb(pdt);
//       addPythiaParticles( istream1, tb );
//       addPythiaParticles( istream2, tb );
//       tb.addParticle( myTempParticleData );
//       // ...
//    }  // triggers tb's destruction, filling pdt!
// ----------------------------------------------------------------------
#ifndef TableBuilder_HH
#define TableBuilder_HH


#include <iostream>
#include <string>
#include <map>

#include "HepPDT/ParticleDataTable.hh"
#include "HepPDT/TempParticleData.hh"
#include "HepPDT/DefTable.hh"
#include "HepPDT/stringtodouble.hh"

namespace HepPDT {

//! The TableBuilder class is used to construct a ParticleDataTable.

///
/// \class TableBuilder
/// \author Marc Paterno, Walter Brown, Lynn Garren
///
/// Define this class and use the add methods to define a ParticleDataTable.
/// The destructor fills ParticleDataTable from the information in TableBuilder.
/// See the examples for user code.
///
class TableBuilder  {
  typedef  std::map<ParticleID,TempParticleData>   TempMap;
  typedef  std::map<std::string,ParticleID>        TempIDMap;
  typedef  std::map<std::string,TempAliasData>     TempAliasMap;

public:
  /// create TableBuilder from a ParticleDataTable
  explicit TableBuilder( ParticleDataTable & table,
                          std::ostream & str = std::cerr )
  : pdt(table), os(str)   { reverseEngineer(); }
  /// call the ParticleDataTable conversion method upon destruction
  ~TableBuilder()  { pdt.convertTemporaryMap( tempPDT, os ); }

  /// create a TempParticleData from a ParticleID
  inline TempParticleData &  getParticleData( ParticleID pid );
  /// create a TempParticleData from a particle name
  inline TempParticleData &  getParticleData( std::string const & name );
  /// create an antiparicle TempParticleData from a ParticleID
  inline TempParticleData &  getAntiParticle( ParticleID pid, 
                                              const std::string & aname );

  // --- mutators
  //
  /// add a TempParticleData to the map
  inline void addParticle( TempParticleData const & pd );
  /// remove a TempParticleData from the map
         void removeParticle(ParticleID pid )  { tempPDT.erase(pid); }
  
  /// add alias information to the alias map
  inline void addAlias( TempAliasData const & ad );

  // --- booleans
  //
  /// check to see if this particle is already defined
  inline bool hasParticleData( std::string const & name );
  /// check to see if this alias is already defined
  inline bool hasAlias( std::string const & alias );
  /// check to see if this particle name is already defined
         bool hasDefinition( std::string const & def ) { return tempDefMap.hasDefinition( def ); }

  // --- accessors
  //
  /// get size of particle data map
         int             size()       const { return tempPDT.size(); }
  /// get size of alias map
         int             aliasSize()  const { return tempAliases.size(); }
  /// get the list of definitions (for EvtGen)
         DefTable      & definitions()      { return tempDefMap; }
  /// return a parameter definition (for EvtGen)
	 double          definition( std::string const & def ) { return tempDefMap.definition( def ); }
  /// find an entry in the alias map
  inline TempAliasData & aliasData( std::string const & alias );

private:
  ParticleDataTable &  pdt;
  TempMap                       tempPDT;
  TempIDMap                     tempIDT;
  TempAliasMap                  tempAliases;	// hold EvtGen alias information
  DefTable                      tempDefMap;	// hold EvtGen "Define" info
  std::ostream &                os;   		// for diagnostics

  inline void fillPDT();		//!< unused
  /// unpack existing PDT so its contents can be modified and added to a new PDT
  /// not implemented
  inline void reverseEngineer();

  // forbidden copy:
  TableBuilder &  operator = ( TableBuilder const & );
  TableBuilder( TableBuilder const & );

};  // TableBuilder<>


// --- free functions
//

/// read PDG input and add particles to the table
bool  addPDGParticles( std::istream & pdfile, TableBuilder & tb );

/// read Pythia input and add particles to the table
bool  addPythiaParticles( std::istream & pdfile, TableBuilder & tb );

bool  addHerwigParticles( std::istream & pdfile, TableBuilder & tb );

/// read Isajet particle input and add particles to the table
bool  addIsajetParticles( std::istream & pdfile, TableBuilder & tb );
/// read Isajet decay input and add decay information to the table
bool  addIsajetDecay( std::istream & pdfile, TableBuilder & tb );

/// read QQ input and add particles to the table
bool  addQQParticles( std::istream & pdfile, TableBuilder & tb );

/// read EvtGen input and add particles to the table
bool  addEvtGenParticles( std::istream & pdfile, TableBuilder & tb );

/// read particle.tbl (or something similar) and add particles to the table
///
/// validate=true => verify that the ParticleID is valid
bool  addParticleTable( std::istream & pdfile, TableBuilder & tb,
                        bool validate = false );


//! HepPDT::detail is for internal use

///
/// \namespace HepPDT::detail
/// This namespace encapsulates free functions used when parsing various input streams.
///
namespace detail {

void getPDGpid( std::vector<int> & idlist,  std::string & pdline ); //!< for internal use
void getPDGnames( std::vector<std::string> & namelst,  std::string & pdline ); //!< for internal use
void parsePDGline( TempParticleData & tpd,  std::string & pdline ); //!< for internal use
bool CheckPDGEntry( TempParticleData & tpd, const std::string &, double, double ); //!< for internal use

bool getPythiaid( int & id, const std::string & pdline ); //!< for internal use
void parsePythiaLine( TempParticleData & tpd, int & anti, std::string & aname, 
                      const std::string & pdline ); //!< for internal use
void parsePythiaDecayLine( TempParticleData & tpd, const std::string & pdline ); //!< for internal use
TempDecayData getPythiaDecay( const std::string & pdline ); //!< for internal use

bool getIsajetID( int & id, const std::string & pdline ); //!< for internal use
void parseIsajetLine( TempParticleData & tpd, const std::string & pdline ); //!< for internal use
void parseIsajetDecayLine( TempParticleData & tpd, const std::string & pdline,
                           TableBuilder & tb ); //!< for internal use

bool getParticleID( int & id, const std::string & pdline ); //!< for internal use
void parseParticleLine( TempParticleData & tpd, const std::string & pdline ); //!< for internal use

}  // namespace detail


}  // namespace HepPDT

#include "HepPDT/TableBuilder.icc"

#endif // TableBuilder_HH
