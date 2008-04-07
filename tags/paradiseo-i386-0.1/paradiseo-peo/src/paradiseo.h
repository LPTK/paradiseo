// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

// "paradiseo.h"

// (c) OPAC Team, LIFL, August 2005

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
   
   Contact: cahon@lifl.fr
*/

#ifndef __paradiseo_h_
#define __paradiseo_h_

#include <eo>
#include <mo>

#include "peo_init.h"
#include "peo_run.h"
#include "peo_fin.h"

#include "eoVector_comm.h"

#include "peoEA.h"

/* Parallel steps of the E.A. */
#include "peoSeqTransform.h"
#include "peoParaSGATransform.h"
#include "peoSeqPopEval.h"
#include "peoParaPopEval.h"

/* Cooperative island model */
#include "ring_topo.h"
#include "peoAsyncIslandMig.h"
#include "peoSyncIslandMig.h"

/* */
#include "peoSyncMultiStart.h"

#endif