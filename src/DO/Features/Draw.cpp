// ========================================================================== //
// This file is part of DO++, a basic set of libraries in C++ for computer 
// vision.
//
// Copyright (C) 2013 David Ok <david.ok8@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public 
// License v. 2.0. If a copy of the MPL was not distributed with this file, 
// you can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================== //


#include <DO/Features.hpp>
#include <DO/Graphics.hpp>

using namespace std;

namespace DO {

  void InterestPoint::draw(const Color3ub& c, float z, const Point2f& off) const
  {
    Vector2f p1(z*(center()+off));
    float cross_offset=3.0f;
    Vector2f c1(p1-Vector2f(cross_offset,0.f));
    Vector2f c2(p1+Vector2f(cross_offset,0.f));
    Vector2f c3(p1-Vector2f(0.f,cross_offset));
    Vector2f c4(p1+Vector2f(0.f,cross_offset));
    drawLine(c1, c2, Black8, 5);
    drawLine(c3, c4, Black8, 5);
    drawLine(c1, c2, c, 3);
    drawLine(c3, c4, c, 3);
  }

  void OERegion::draw(const Color3ub& c, float z, const Point2f& off) const
  {
    // Solve characteristic equation to find eigenvalues
    JacobiSVD<Matrix2f> svd(shapeMat(), ComputeFullU);
    const Vector2f& D = svd.singularValues();
    const Matrix2f& U = svd.matrixU();

    // Eigenvalues are l1 and l2.
    const Vector2f radii(D.cwiseSqrt().cwiseInverse());

    const float a = radii(0);
    const float b = radii(1);
    // The normalized eigenvectors/ellipsoid axes.
    Vector2f e1(U.col(0));
    Vector2f e2(U.col(1));

    // Orientation.
    float ellOrient = atan2(U(1,0), U(0,0));
    // Start and end points of orientation line.
    Matrix2f L = affinity().block(0,0,2,2);    
    Vector2f p1(z*(center()+off));
    Vector2f p2(p1 + z*L*Vector2f(1.f,0.f));

    // Draw.
    if (z*a > 1.f && z*b > 1.f && (p1-p2).squaredNorm() > 1.f)
    {
      // Contour of orientation line.
      drawLine(p1, p2, Black8, 5);
      // Contour of ellipse.
      drawEllipse(p1, z*a, z*b, 180.f*ellOrient/float(M_PI), Black8, 5);
      // Fill-in of orientation line.
      drawLine(p1, p2, c, 3);
      // Fill-in of ellipse.
      drawEllipse(p1, z*a, z*b, 180.f*ellOrient/float(M_PI), c, 3);
    }
    else
      InterestPoint::draw(c, z, off);
  }

  void drawOERegions(const vector<OERegion>& features, const Color3ub& c,
                     float scale, const Point2f& off)
  {
    for (size_t i = 0; i < features.size(); ++i)
      features[i].draw(c, scale, off);
  }

} /* namespace DO */
