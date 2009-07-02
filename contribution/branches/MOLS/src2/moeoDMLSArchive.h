/*
* <moeoDMLSArchive.h>
* Copyright (C) DOLPHIN Project-Team, INRIA Futurs, 2006-2007
* (C) OPAC Team, LIFL, 2002-2007
*
* Arnaud Liefooghe
*
* This software is governed by the CeCILL license under French law and
* abiding by the rules of distribution of free software.  You can  use,
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info".
*
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited liability.
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or
* data to be ensured and,  more generally, to use and operate it in the
* same conditions as regards security.
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*
* ParadisEO WebSite : http://paradiseo.gforge.inria.fr
* Contact: paradiseo-help@lists.gforge.inria.fr
*
*/
//-----------------------------------------------------------------------------

#ifndef MOEODMLSARCHIVE_H_
#define MOEODMLSARCHIVE_H_

#include <comparator/moeoObjectiveVectorComparator.h>
#include <comparator/moeoParetoObjectiveVectorComparator.h>
#include <archive/moeoArchive.h>

template < class MOEOT >
class moeoDMLSArchive : public moeoArchive < MOEOT >
{
public:

    using moeoArchive < MOEOT > :: size;
    using moeoArchive < MOEOT > :: operator[];
    using moeoArchive < MOEOT > :: back;
    using moeoArchive < MOEOT > :: pop_back;


    /**
     * The type of an objective vector for a solution
     */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;


    /**
     * Default ctor.
     * The moeoObjectiveVectorComparator used to compare solutions is based on Pareto dominance
     */
    moeoDMLSArchive() : moeoArchive < MOEOT >(), comparator(paretoComparator), isModified(false)
    {}


    /**
     * Ctor
     * @param _comparator the moeoObjectiveVectorComparator used to compare solutions
     */
    moeoDMLSArchive(moeoObjectiveVectorComparator < ObjectiveVector > & _comparator) : moeoArchive < MOEOT >(), comparator(_comparator), isModified(false)
    {}


    /**
     * Returns true if the current archive dominates _objectiveVector according to the moeoObjectiveVectorComparator given in the constructor
     * @param _objectiveVector the objective vector to compare with the current archive
     */
    bool dominates (const ObjectiveVector & _objectiveVector) const
    {
        for (unsigned int i = 0; i<size(); i++)
        {
            // if _objectiveVector is dominated by the ith individual of the archive...
            if ( comparator(_objectiveVector, operator[](i).objectiveVector()) )
            {
                return true;
            }
        }
        return false;
    }


    /**
     * Returns true if the current archive already contains a solution with the same objective values than _objectiveVector
     * @param _objectiveVector the objective vector to compare with the current archive
     */
    bool contains (const ObjectiveVector & _objectiveVector) const
    {
        for (unsigned int i = 0; i<size(); i++)
        {
            if (operator[](i).objectiveVector() == _objectiveVector)
            {
                return true;
            }
        }
        return false;
    }


    /**
     * Updates the archive with a given individual _moeo
     * @param _moeo the given individual
     * @return true if _moeo is added to the archive
     */
    bool operator()(const MOEOT & _moeo)
    {
        return update(_moeo);
    }


    /**
     * Updates the archive with a given population _pop
     * @param _pop the given population
     * @return true if a _pop[i] is added to the archive
     */
    bool operator()(const eoPop < MOEOT > & _pop)
    {
        bool res = false;
        for (unsigned int i=0; i<_pop.size(); i++)
        {
            res = (*this).update(_pop[i]) || res;
        }
        return res;
    }


    /**
     * Returns true if the current archive contains the same objective vectors than the given archive _arch
     * @param _arch the given archive
     */
    bool equals (const moeoArchive < MOEOT > & _arch)
    {
        for (unsigned int i=0; i<size(); i++)
        {
            if (! _arch.contains(operator[](i).objectiveVector()))
            {
                return false;
            }
        }
        for (unsigned int i=0; i<_arch.size() ; i++)
        {
            if (! contains(_arch[i].objectiveVector()))
            {
                return false;
            }
        }
        return true;
    }

    bool modified(){
    	bool tmp = isModified;
    	isModified = false;
    	return tmp;
    }

protected:
    /** bool*/
    bool isModified;
    
private:

    /** The moeoObjectiveVectorComparator used to compare solutions */
    moeoObjectiveVectorComparator < ObjectiveVector > & comparator;
    /** A moeoObjectiveVectorComparator based on Pareto dominance (used as default) */
    moeoParetoObjectiveVectorComparator < ObjectiveVector > paretoComparator;


    /**
     * Updates the archive with a given individual _moeo *** NEW ***
     * @param _moeo the given individual
     */
    virtual bool update(const MOEOT & _moeo) = 0;
    
};

#endif /*MOEODMLSARCHIVE_H_ */