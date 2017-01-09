// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define BOOST_TEST_INCLUDED
#pragma warning (disable: 4702)
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <vector>
#include <memory>
#include "../Shapes/Point.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CCircle.h"
#include "../Shapes/CShapesController.h"
#include "VerifyShapeFunctions.h"
