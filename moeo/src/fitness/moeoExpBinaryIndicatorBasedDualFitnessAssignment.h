
#include <fitness/moeoExpBinaryIndicatorBasedFitnessAssignment.h>

template<class MOEOT>
class moeoExpBinaryIndicatorBasedDualFitnessAssignment : public moeoExpBinaryIndicatorBasedFitnessAssignment<MOEOT>
{
protected:
    eoPop<MOEOT> _feasible_pop;
    eoPop<MOEOT> _unfeasible_pop;

public:
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;
    typedef typename ObjectiveVector::Type Type;

    using moeoExpBinaryIndicatorBasedFitnessAssignment<MOEOT>::values;

    moeoExpBinaryIndicatorBasedDualFitnessAssignment(
            moeoNormalizedSolutionVsSolutionBinaryMetric<ObjectiveVector,double> & metric,
            const double kappa = 0.05
        ) : moeoExpBinaryIndicatorBasedFitnessAssignment<MOEOT>( metric, kappa ) {}

    //! Split up the population in two: in one pop the feasible individual, in the other the feasible ones
    virtual void split( eoPop<MOEOT> & pop )
    {
          _feasible_pop.reserve(pop.size());
        _unfeasible_pop.reserve(pop.size());

        for( typename eoPop<MOEOT>::iterator it=pop.begin(), end=pop.end(); it != end; ++it ) {
            // The ObjectiveVector should implement "is_feasible"
            if( it->objectiveVector().is_feasible() ) {
                  _feasible_pop.push_back( *it );
            } else {
                _unfeasible_pop.push_back( *it );
            }
        }
    }

    /*! If the population is homogeneous (only composed of feasible individuals or unfeasible ones),
     * then apply the operators on the whole population.
     * But, if there is at least one feasible individual, then apply them only on the feasible individuals.
     */
    virtual void operator()(eoPop < MOEOT > & pop)
    {
        // separate the pop in the members
        split( pop );

        eoPop<MOEOT>* ppop;
        // if there is at least one feasible individual, it will supersede all the unfeasible ones
        if( _feasible_pop.size() == 0 ) {
            ppop = & _unfeasible_pop;
        } else {
            ppop = & _feasible_pop;
        }

        this->setup(*ppop);
        this->computeValues(*ppop);
        this->setFitnesses(*ppop);
    }

    /**
     * Compute every indicator value in values (values[i] = I(_v[i], _o))
     * @param _pop the population
     */
    void computeValues(const eoPop < MOEOT > & _pop)
    {
      values.clear();
      values.resize(_pop.size());
      for (unsigned int i=0; i<_pop.size(); i++)
        {
          values[i].resize(_pop.size());
          // the metric may not be symetric, thus neither is the matrix
          for (unsigned int j=0; j<_pop.size(); j++)
            {
              if (i != j)
                {
                  values[i][j] = Type( metric(_pop[i].objectiveVector(), _pop[j].objectiveVector()), _pop[i].objectiveVector().is_feasible() );
                }
            }
        }
    }

    virtual void setFitnesses(eoPop < MOEOT > & pop)
    {
        for (unsigned int i=0; i<pop.size(); i++) {
            // We should maintain the feasibility of the fitness across computations
            pop[i].fitness( this->computeFitness(i), pop[i].fitness().is_feasible() );
        }
    }


};

