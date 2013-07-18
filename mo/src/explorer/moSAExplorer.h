/*
  <moSAExplorer.h>
  Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

  Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau, Lionel Parreaux

  This software is governed by the CeCILL license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,  and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.
  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.

  ParadisEO WebSite : http://paradiseo.gforge.inria.fr
  Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef _moSAExplorer_h
#define _moSAExplorer_h

#include <cstdlib>

//#include <explorer/moNeighborhoodExplorer.h>
#include <explorer/moMetropolisHastingsExplorer.h>
#include <comparator/moSolNeighborComparator.h>
#include <coolingSchedule/moCoolingSchedule.h>
#include <neighborhood/moNeighborhood.h>
#include <eoOptional.h>
#include <eval/moFullEvalByCopy.h>

#include <utils/eoRNG.h>

/**
 * Explorer for the Simulated Annealing
 * Only the symetric case is considered when Q(x,y) = Q(y,x)
 * Fitness must be > 0
 *
 */
template< class Neighbor >
class moSAExplorer : public moMetropolisHastingsExplorer< Neighbor, moSAExplorer<Neighbor> >
{
public:
    typedef typename Neighbor::EOT EOT ;
    typedef moNeighborhood<Neighbor> Neighborhood ;
    
    using moNeighborhoodExplorer<Neighbor>::neighborhood;
    using moNeighborhoodExplorer<Neighbor>::eval;
    using moNeighborhoodExplorer<Neighbor>::selectedNeighbor;

    /**
     * Constructor for the simple MH explorer
     * @param _neighborhood the neighborhood
     * @param _eval the evaluation function
     * @param _cool the cooling schedule
     * @param _solNeighborComparator a solution vs neighbor comparator
     */
    moSAExplorer (
        Neighborhood& _neighborhood,
        moEval<Neighbor>& _eval,
        moCoolingSchedule<EOT>& _cool,
        eoOptional< moSolNeighborComparator<Neighbor> > _comp = NULL
    )
    : moMetropolisHastingsExplorer< Neighbor, moSAExplorer<Neighbor> >(_neighborhood, _eval, _comp)
    , coolingSchedule(_cool)
    { }
    
    /**
     * Destructor
     */
    ~moSAExplorer() {
    }

    /**
     * initialization of the initial temperature
     * @param _solution the solution
     */
    virtual void initParam(EOT & _solution) {
      temperature = coolingSchedule.init(_solution);
      //isMoveAccepted = false;
    };

    /**
     * decrease the temperature if necessary
     * @param _solution unused solution
     */
    virtual void updateParam(EOT & _solution) {
        coolingSchedule.update(temperature, this->moveApplied(), _solution);
    };

    /**
     * terminate: Nothing to do
     * @param _solution unused solution
     */
    virtual void terminate(EOT & _solution) {};

    /**
     * Explore one random solution in the neighborhood
     * @param _solution the solution
     */
    virtual void operator()(EOT & _solution) {
        //Test if _solution has a Neighbor
        if (neighborhood.hasNeighbor(_solution))
        {
            //init on the first neighbor: supposed to be random solution in the neighborhood
            neighborhood.init(_solution, selectedNeighbor);

            //eval the _solution moved with the neighbor and stock the result in the neighbor
            eval(_solution, selectedNeighbor);
        }
    };

    /**
     * continue if the temperature is not too low
     * @param _solution the solution
     * @return true if the criteria from the cooling schedule is true
     */
    virtual bool isContinue(EOT & _solution) {
        return coolingSchedule(temperature);
    };
    
    /**
     * getTemperature getter function
     * @return the temperature
     */
    double getTemperature() const {
        return temperature;
    }
    
    /**
     * alpha required by moMetropolisHastingsExplorer, using the Boltzman distribution e^(-delta/T)
     * @param _solution the solution
     * @return a real between 0 and 1 representing the probability of accepting a worse solution
     */
    double alpha(EOT & _solution) {
        return exp( - fabs((double) selectedNeighbor.fitness() - (double) _solution.fitness()) / temperature );
    }
    
    
private:
    
    // The cooling schedule
    moCoolingSchedule<EOT>& coolingSchedule;
    
    // current temperatur of the process
    double temperature;
    
};


#endif

