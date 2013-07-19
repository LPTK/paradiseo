/*
  <moBestFitnessStat.h>
  Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

  Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

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

#ifndef moFitnessMomentsStat_h
#define moFitnessMomentsStat_h

#include <utility>
#include <continuator/moStat.h>

/**
 * Statistic that saves the standard deviation of the fitness of the solutions during the search
 */
template <class EOT>
//class moFitnessMomentsStat : public moStat<EOT, std::pair<typename EOT::Fitness,typename EOT::Fitness> >
class moFitnessMomentsStat : public moStat<EOT, std::pair<double, double> >
{
public :
    typedef typename EOT::Fitness Fitness;
    //typedef std::pair<typename EOT::Fitness,typename EOT::Fitness> Pair;
    typedef std::pair<double, double> Pair;
    using moStat<EOT, Pair >::value;

    /**
     * Default Constructor
     * @param _reInitSol when true the best so far is reinitialized
     */
    moFitnessMomentsStat(bool _reInitSol = true)
    : moStat<EOT, Pair>(Pair(Fitness(), 0.0), "moments (average and stdev)"),
      reInitSol(_reInitSol), firstTime(true),
      nbSolutionsEncountered(0), currentAvg(0), currentVar(0)
    { }
    
    /**
     * Initialization of the best solution on the first one
     * @param _sol the first solution
     */
    virtual void init(EOT & _sol) {
    	if (reInitSol || firstTime)
    	{
    		value() = Pair(0.0,0.0);
    		nbSolutionsEncountered = currentAvg = currentVar = 0;
			firstTime = false;
    	}
    	/*else if (firstTime)
		{
			value() = 0.0;
			firstTime = false;
		}*/
    	operator()(_sol);
    }
    
	/**
	 * Update the best solution
	 * @param _sol the current solution
	 */
	virtual void operator()(EOT & _sol) {
		++nbSolutionsEncountered;
		double x = _sol.fitness();
		double oldAvg = currentAvg;
		currentAvg = oldAvg + (x - oldAvg)/nbSolutionsEncountered;
		if (nbSolutionsEncountered > 1) // <- not really necessary
		{
			//value() = (value()/nbSolutionsEncountered + _sol.fitness())/(nbSolutionsEncountered+1);
			double oldVar = currentVar;
			currentVar = oldVar + (x - oldAvg) * (x - currentAvg);
			value() = Pair(currentAvg, currentVar/nbSolutionsEncountered);
		}
	}

    /**
     * @return name of the class
     */
    virtual std::string className(void) const {
        return "moFitnessVarianceStat";
    }

protected:
    bool reInitSol;
    bool firstTime;
    double
      nbSolutionsEncountered
    , currentAvg
    , currentVar // actually the var * n
    ;

};

#endif // moFitnessMomentsStat_h
