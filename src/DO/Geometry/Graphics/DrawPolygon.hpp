// ========================================================================== //
// This file is part of DO++, a basic set of libraries in C++ for computer 
// vision.
//
// Copyright (C) 2014 David Ok <david.ok8@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public 
// License v. 2.0. If a copy of the MPL was not distributed with this file, 
// you can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================== //

#pragma once

#include <DO/Graphics.hpp>
#include <DO/Geometry/Objects.hpp>
#include <vector>
#include <string>

namespace DO {

  //! Drawing functions
  void drawLineSegment(const LineSegment& s, const Color3ub& c = Black8,
                       int penWidth = 1);
  void drawBBox(const BBox& bbox, const Color3ub& c, int penWidth = 1);
  void drawPoly(const std::vector<Point2d>& p, const Color3ub& color,
                int penWidth = 1);
  void drawEllipse(const Ellipse& e, const Color3ub col, int penWidth = 1);
  
  template <int N>
  void drawPoly(const SmallPolygon<N>& poly, const Color3ub& color,
                int penWidth = 1)
  {
    for (int i1 = N-1, i2 = 0; i2 != N; i1=i2++)
      drawLine(poly[i1], poly[i2], color, penWidth);
  }

  inline void drawTriangle(const Triangle& t, const Rgb8& col = Red8,
                           int penWidth = 1)
  { drawPoly(t, col, penWidth); }
  
  inline void drawQuad(const Quad& q, const Rgb8& col = Red8,
                       int penWidth = 1)
  { drawPoly(q, col, penWidth); }

  void drawAffineCone(const AffineCone2& K, double arrowLength = 50.,
                          const Color3ub& color = Black8);

} /* namespace DO */