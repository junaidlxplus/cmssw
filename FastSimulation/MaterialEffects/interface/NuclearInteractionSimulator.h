#ifndef FastSimulation_MaterialEffects_NuclearInteractionSimulator_H
#define FastSimulation_MaterialEffects_NuclearInteractionSimulator_H

/** 
 * This class computes the probability for hadrons to interact with a 
 * nucleon of the tracker material (inelastically) and then reads a 
 * nuclear interaction randomly from multiple fully simulated files 
 * The fraction of interaction lengths traversed by the particle in this 
 * tracker layer is determined in MaterialEffectsSimulator as a fraction 
 * the radiation lengths. 
 *
 * \author Patrick Janot
 * $Date: 25-Jan-2007
 */ 

#include "FastSimulation/MaterialEffects/interface/MaterialEffectsSimulator.h"

#include <vector>
#include <map>
#include <string>
#include <fstream>

class TFile;
class TTree;
class TBranch;
class NUEvent;

class ParticlePropagator;
class RandomEngine;
//class DaqMonitorBEInterface;
//class MonitorElement;

class NuclearInteractionSimulator : public MaterialEffectsSimulator
{
 public:

  /// Constructor
  NuclearInteractionSimulator(std::vector<double>& pionEnergies,
			      std::vector<int>& pionTypes,
			      std::vector<std::string>& pionNames,
			      std::vector<double>& pionMasses,
			      std::vector<double>& pionPMin,
			      double pionEnergy,
			      std::vector<double>& lengthRatio,
			      double fudgeFactor,
			      std::vector< std::vector<double> >& ratios,
			      std::map<int,int >& idMap,
			      std::string inputFile,
			      const RandomEngine* engine);

  /// Default Destructor
  ~NuclearInteractionSimulator();

  /// Save current nuclear interaction (for later use)
  void save();

  /// Read former nuclear interaction (from previous run)
  bool read(std::string inputFile);

 private:

  /// Generate a nuclear interaction according to the probability that it happens
  void compute(ParticlePropagator& Particle);

  /// Return a hashed index for a given pid
  unsigned index(int thePid);

  std::vector<double> thePionEN;
  std::vector<int> thePionID;
  std::vector<std::string> thePionNA;
  std::vector<double> thePionMA;
  std::vector<double> thePionPMin;
  double thePionEnergy;
  std::vector<double> theLengthRatio;
  std::vector< std::vector<double> > theRatios;

  std::vector< std::vector<TFile*> > theFiles;
  std::vector< std::vector<TTree*> > theTrees;
  std::vector< std::vector<TBranch*> > theBranches;
  std::vector< std::vector<NUEvent*> > theNUEvents;
  std::vector< std::vector<unsigned> > theCurrentEntry;
  std::vector< std::vector<unsigned> > theCurrentInteraction;
  std::vector< std::vector<unsigned> > theNumberOfEntries;
  std::vector< std::vector<unsigned> > theNumberOfInteractions;
  std::vector< std::vector<std::string> > theFileNames;
  std::vector< std::vector<double> > thePionCM;
  
  std::map< int, int > theIDMap;
  unsigned ien4;

  std::ofstream myOutputFile;
  unsigned myOutputBuffer;
  



  //  DaqMonitorBEInterface * dbe;
  //  MonitorElement* htot;
  //  MonitorElement* helas;
  //  MonitorElement* hinel;
  //  MonitorElement* hscatter;
  //  MonitorElement* hscatter2;

};
#endif
