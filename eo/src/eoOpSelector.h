// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

//-----------------------------------------------------------------------------
// eoOpSelector.h
// (c) GeNeura Team 1998
//-----------------------------------------------------------------------------

#ifndef EOOPSELECTOR_H
#define EOOPSELECTOR_H

//-----------------------------------------------------------------------------

#include <stdexcept>  // runtime_error 

#include <eoObject.h>
#include <eoPrintable.h>
#include <eoOp.h>

//-----------------------------------------------------------------------------
/** An operator selector is an object that contains a set of EO operators, and 
and selects one based on whatever criteria. It will be used in the breeder objects.\\
This class is basically a generic interface for operator selection
*/
template<class EOT>
class eoOpSelector: public eoObject, public eoPrintable
{
public:
  typedef unsigned ID;
  
  /** add an operator to the operator set
      @param _op a genetic operator, that will be applied in some way
      @param _arg the operator rate, usually, or any other argument to the operator
      @return an ID that will be used to identify the operator
  */
  virtual ID addOp( eoOp<EOT>& _op, float _arg ) = 0;
  
  /** Gets a non-const reference to an operator, so that it can be changed, 
      modified or whatever 
      @param _id  a previously assigned ID
      @throw runtime_exception if the ID does not exist*/
  virtual const eoOp<EOT>& getOp( ID _id ) = 0;
  
  /** Remove an operator from the operator set
      @param _id a previously assigned ID
      @throw runtime_exception if the ID does not exist
  */
  virtual deleteOp( ID _id ) = 0;
  
  /// Returns a genetic operator according to the established criteria
  virtual const eoOp<EOT>& Op() = 0;
  
  /// Methods inherited from eoObject
  //@{
  
  /** Return the class id. 
      @return the class name as a string
  */
  virtual string className() const { return "eoOpSelector"; };
  
  /**
   * Read object and print objects are left for subclasses to define.
   */
  //@}
};

//-----------------------------------------------------------------------------

#endif EO_H
