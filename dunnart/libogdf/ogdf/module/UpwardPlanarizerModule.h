
/** \file
 * \brief Declaration of UpwardPlanarizer Module, an interface for upward planarization algorithms.
 * 
 * \author Hoi-Ming Wong
 * 
 * \par License:
 * This file is part of the Open Graph Drawing Framework (OGDF).
 * Copyright (C) 2005-2008
 * 
 * \par
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * Version 2 or 3 as published by the Free Software Foundation
 * and appearing in the files LICENSE_GPL_v2.txt and
 * LICENSE_GPL_v3.txt included in the packaging of this file.
 *
 * \par
 * In addition, as a special exception, you have permission to link
 * this software with the libraries of the COIN-OR Osi project
 * (http://www.coin-or.org/projects/Osi.xml), all libraries required
 * by Osi, and all LP-solver libraries directly supported by the
 * COIN-OR Osi project, and distribute executables, as long as
 * you follow the requirements of the GNU General Public License
 * in regard to all of the software in the executable aside from these
 * third-party libraries.
 * 
 * \par
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * \par
 * You should have received a copy of the GNU General Public 
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 * 
 * \see  http://www.gnu.org/copyleft/gpl.html
 ***************************************************************/

#ifndef OGDF_UPWARD_PLANARIZER_MODULE_H
#define OGDF_UPWARD_PLANARIZER_MODULE_H


#include <ogdf/basic/Module.h>
#include <ogdf/upward/UpwardPlanRep.h>


namespace ogdf {

/**
 * \brief Interface for upward planarization algorithms.
 *
 */
class OGDF_EXPORT UpwardPlanarizerModule : public Module
{

public:

	//! Initializes an upward planarizer module.
	UpwardPlanarizerModule() { }

	// destruction
	virtual ~UpwardPlanarizerModule() { }

	/**
	 * \brief Computes a upward planarized representation (UPR) of the input graph \a G.
	 *
	 * @param UPR represents the input graph as well as the computed upward planarized
	 *        representation after the call. The original graph of \a UPR muss be the input graph \a G. 
	 *		  Crossings are replaced by dummy vertices. The UPR is finaly augmented to a st-graph. Since this augmentation,
	 *		  crossings dummies may not got an in- and outdegree of 2!
	 *		  
	 * @param forbid points to an edge array indicating which edges are not allowed
	 *        to be crossed, i.e., (*forbid)[e] = true. If forbid = 0, no edges are
	 *        forbidden.
	 *
	 * @param cost points to an edge array that gives the cost of each edge. If cost
	 *        = 0, all edges have cost 1.
	 *
	 * \return the status of the result.
	 *
	 */
	ReturnType call(UpwardPlanRep &UPR,				
					const EdgeArray<int>  * cost = 0,
					const EdgeArray<bool> * forbid = 0)
	{
		m_useCost = (cost != 0);
		m_useForbid = (forbid != 0);
	
		if(!useCost())      cost      = OGDF_NEW EdgeArray<int> (UPR.original(), 1);
		if(!useForbid())    forbid    = OGDF_NEW EdgeArray<bool> (UPR.original(), 0);


		ReturnType R = doCall(UPR, *cost, *forbid);

		if(!useCost())      delete cost;
		if(!useForbid())    delete forbid;	
		return R;
	};


	//! Computes a upward planarized representation of the input graph (shorthand for call)
	ReturnType operator()(UpwardPlanRep &UPR,				
			const EdgeArray<int>  * cost = 0,
			const EdgeArray<bool> * forbid = 0) {
		return call(UPR, cost, forbid);
	};


	//! Returns true iff edge costs are given.
	bool useCost() const { return m_useCost; }

	//! Returns true iff forbidden edges are given.
	bool useForbid() const { return m_useForbid; }

protected:
	/**
	 * \brief Computes a upward planarized representation of the input graph.
	 *
	 * @param UPR represents the input graph as well as the computed upward planarized
	 *        representation after the call. The original graph of \a UPR muss be the input graph \a G. 
	 *		  Crossings are replaced by dummy vertices. The UPR is finaly augmented to a st-graph. Since this augmentation,
	 *		  crossings dummies may not got an in- and outdegree of 2!
	 *
	 * @param crossingNumber is assigned the number of crossings.
	 *
	 * @param forbid points to an edge array indicating which edges are not allowed
	 *        to be crossed, i.e., (*forbid)[e] = true. If forbid = 0, no edges are
	 *        forbidden.
	 *
	 * @param cost points to an edge array that gives the cost of each edge. If cost
	 *        = 0, all edges have cost 1.
	 *
	 * \return the status of the result.
	 */
	virtual ReturnType doCall(UpwardPlanRep &UPR,		
							  const EdgeArray<int>  &cost,
							  const EdgeArray<bool> &forbid) = 0;

		
	OGDF_MALLOC_NEW_DELETE
	
private:

	bool m_useCost; //!< True iff edge costs are given.
	bool m_useForbid; //!< True iff forbidden edges are given.

};

} // end namespace ogdf

#endif

