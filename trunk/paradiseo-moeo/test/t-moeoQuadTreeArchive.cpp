	/*
* <t-moeoquadTreeArchive.cpp>
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
// t-moeoEpsilonHyperboxArchive.cpp
//-----------------------------------------------------------------------------

#include <eo>
#include <moeo>
#include <cmath>

//-----------------------------------------------------------------------------

class ObjectiveVectorTraits : public moeoObjectiveVectorTraits
{
public:
    static bool minimizing (int i)
    {
        return true;
    }
    static bool maximizing (int i)
    {
        return false;
    }
    static unsigned int nObjectives ()
    {
        return 3;
    }
};

typedef moeoRealObjectiveVector < ObjectiveVectorTraits > ObjectiveVector;

typedef MOEO < ObjectiveVector, double, double > Solution;





//-----------------------------------------------------------------------------

int main()
{
    std::cout << "[moeoQuadTreeArchive]\t=>\t";
    moeoQuadTree<ObjectiveVector> tree;

    bool empty= tree.isEmpty();
    std::cout <<"empty? " << empty << std::endl;
    ObjectiveVector obj1;
    obj1[0]=2.0;
    obj1[1]=2.0;
    obj1[2]=2.0;
    ObjectiveVector obj2;
    obj2[0]=2.0;
    obj2[1]=1.0;
    obj2[2]=1.0;
    ObjectiveVector obj3;
    obj3[0]=1.0;
    obj3[1]=1.0;
    obj3[2]=1.0;
    QuadTreeNode<ObjectiveVector> hop(obj1);
    QuadTreeNode<ObjectiveVector> hop2(obj2);
    QuadTreeNode<ObjectiveVector> hop3(obj3);
//    empty = hop.getSubTree().empty();
//    std::cout <<"empty? " << empty << std::endl;
//    std::vector< QuadTreeNode<ObjectiveVector> > nodes;
//    nodes.push_back(hop);
//    nodes.push_back(hop2);
//    nodes.push_back(hop3);
//    std::cout << nodes[1].getVec() << std::endl;

//    std::cout << "size: " << nodes.size() << std::endl;
    tree.insert(obj1);
    tree.insert(obj2);
    tree.insert(obj2);
    tree.printTree();




    std::cout << "OK" << std::endl;
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------