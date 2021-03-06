/*
 * $Revision: 1.0 $
 *
 * last checkin:
 *   $Author: bartel $
 *   $Date: 2008-01-26 15:44:58 +0100 (Sa, 26 Jan 2008) $
 ***************************************************************/

/** \file
 * \brief ScalingLayout scales and calls a secondary layout
 *
 * \author Gereon Bartel
 *
 * \par License:
 * This file is part of the Open Graph Drawing Framework (OGDF).
 * Copyright (C) 2005-2007
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

//#define USE_OGL_DRAWER

#include <ogdf/energybased/multilevelmixer/ScalingLayout.h>
#ifdef USE_OGL_DRAWER
	#include <../ModularMultilevelMixer/ModularMultilevelMixer/mmm/DrawOGLGraph.h>
#endif

namespace ogdf {

ScalingLayout::ScalingLayout()
    : m_secondaryLayoutModule(0),
	m_minScaling(1.0),
	m_maxScaling(2.0),
	m_desEdgeLength(1.0),
	m_extraScalingSteps(0),
	m_layoutRepeats(1),
	m_scalingType(st_relativeToDrawing)
{
}


void ScalingLayout::call(GraphAttributes &GA)
{
	MultilevelGraph MLG(GA);
	call(MLG);
	MLG.exportAttributes(GA);
}


void ScalingLayout::call(MultilevelGraph &MLG)
{
	Graph &G = MLG.getGraph();
	float avgDesiredEdgeLength = 0.0;
	edge e;
	
	if (m_scalingType == st_relativeToAvgLength) {
		forall_edges(e, G) {
			avgDesiredEdgeLength += MLG.weight(e);
		}
		avgDesiredEdgeLength /= G.numberOfNodes();
	}

	float avgStartEdgeLength = 0.0;
	for (unsigned int i = 0; i <= m_extraScalingSteps; i++) {
		float step;
		if (m_extraScalingSteps > 0) {
			step = (float)i / (float)m_extraScalingSteps;
		} else {
			step = 0;
		}
		float scalingFactor = m_minScaling * step + m_maxScaling * (1.0f-step);

		float avgEdgeLength = 0.0;
		forall_edges(e, G) {
			float x = MLG.x(e->source()) - MLG.x(e->target());
			float y = MLG.y(e->source()) - MLG.y(e->target());
			avgEdgeLength += sqrt( x*x + y*y );
		}
		avgEdgeLength /= G.numberOfNodes();

		if(avgEdgeLength <= 0.0) {
			MLG.moveToZero();
		} else {
			float scaling = 1.0f;
			if (m_scalingType == st_relativeToDrawing) {
				if (i == 0) {
					avgStartEdgeLength = avgEdgeLength;
				}
				scaling = scalingFactor * avgStartEdgeLength / avgEdgeLength;
			} else { 
					if (m_scalingType == st_relativeToDesiredLength)
					{
						scaling = scalingFactor * m_desEdgeLength / avgEdgeLength;
					} else //st_relativeToAvgLength
						scaling = scalingFactor * avgDesiredEdgeLength / avgEdgeLength;
#ifdef OGDF_DEBUG
				cout << "Scaling: F/s "<<scalingFactor<<" "<<scaling<<"\n";
#endif
			}
			
			MLG.moveToZero();

			// scale to scaling
			node v;
			forall_nodes(v, G) {
				MLG.x(v, MLG.x(v) * scaling);
				MLG.y(v, MLG.y(v) * scaling);
			}
		}

		if (m_secondaryLayoutModule != 0) {
			for (unsigned int j = 1; j <= m_layoutRepeats; j++) {
				m_secondaryLayoutModule->call(MLG);
			}
		}

#ifdef USE_OGL_DRAWER
		DrawOGLGraph::setGraph(&MLG);
		DrawOGLGraph::drawUntilEsc();
#endif

	}
}


void ScalingLayout::setScaling(float min, float max)
{
	m_minScaling = min;
	m_maxScaling = max;
}


void ScalingLayout::setExtraScalingSteps(unsigned int steps)
{
	m_extraScalingSteps = steps;
}


void ScalingLayout::setSecondaryLayout(LayoutModule * layout)
{
	m_secondaryLayoutModule = layout;
}


void ScalingLayout::setScalingType(ScalingType type)
{
	m_scalingType = type;
}


void ScalingLayout::setLayoutRepeats(unsigned int repeats)
{
	m_layoutRepeats = repeats;
}

void ScalingLayout::setDesiredEdgeLength(double eLength)
{
	m_desEdgeLength = eLength;
}

} // namespace ogdf
