/* -----------------------------------------------------------------
 * File:    morphing.cpp
 * Created: 2015-09-25
 * -----------------------------------------------------------------
 *
 *
 *
 * ---------------------------------------------------------------*/

#include "morphing.h"
#include <cassert>
#include "filtering.h"

using namespace std;

Vec2f operator+(const Vec2f &a, const Vec2f &b) {
  // --------- HANDOUT  PS05 ------------------------------
  // Return the vector sum of a an b
  return Vec2f(a.x + b.x, a.y + b.y); // change me
}

Vec2f operator-(const Vec2f &a, const Vec2f &b) {
  // --------- HANDOUT  PS05 ------------------------------
  // Return a-b
  return Vec2f(a.x - b.x, a.y - b.y); // change me
}

Vec2f operator*(const Vec2f &a, float f) {
  // --------- HANDOUT  PS05 ------------------------------
  // Return a*f
  return Vec2f(a.x * f, a.y * f); // change me
}

Vec2f operator/(const Vec2f &a, float f) {
  // --------- HANDOUT  PS05 ------------------------------
  // Return a/f
  return Vec2f(a.x/f, a.y/f); // change me
}

float dot(const Vec2f &a, const Vec2f &b) {
  // --------- HANDOUT  PS05 ------------------------------
  // Return the dot product of a and b.
  return a.x * b.x + a.y * b.y; // change me
}

float length(const Vec2f &a) {
  // --------- HANDOUT  PS05 ------------------------------
  // Return the length of a.
  return sqrt(pow(a.x,2) + pow(a.y,2)); // change me
}

Vec2f perpendicular(const Vec2f &a) {
  // --------- HANDOUT  PS05 ------------------------------
  // Return a vector that is perpendicular to a.
  // Either direction is fine.
  return Vec2f(-a.y, a.x);
}

// The Segment constructor takes in 2 points P(x1,y1) and Q(x2,y2) corresponding
// to the ends of a segment and initialize the local reference frame e1,e2.
Segment::Segment(Vec2f P_, Vec2f Q_) : P(P_), Q(Q_) {
  // // --------- HANDOUT  PS05 ------------------------------
  // // The initializer list above ": P(P_), Q(Q_)" already copies P_
  // // and Q_, so you don't have to do it in the body of the constructor.
  // You should:
  // * Initialize the local frame e1,e2 (see header file)

  Vec2f difference = Q-P;
  lPQ = length(difference);

  e1 = difference * (1/length(difference));

  e2 = perpendicular(difference) * (1/length(difference));


}

Vec2f Segment::XtoUV(Vec2f X) const {
  // --------- HANDOUT  PS05 ------------------------------
  // Compute the u,v coordinates of a point X with
  // respect to the local frame of the segment.
  // e2 ^
  //    |
  // v  +  * X
  //    | /
  //    |/
  //    *--+------>-----*
  //    P  u     e1     Q
  //                    u=1
  //
  // * Be careful with the different normalization for u and v

  return Vec2f(dot(X-P, Q-P)/pow(lPQ,2), dot(X-P, perpendicular(Q-P))/lPQ);
}

Vec2f Segment::UVtoX(Vec2f uv) const {
  // --------- HANDOUT  PS05 ------------------------------
  // compute the (x, y) position of a point given by the (u,v)
  // location relative to this segment.
  // * Be careful with the different normalization for u and v

  return e1 * (lPQ * uv.x) + (e2 * uv.y) + P;;
}

float Segment::distance(Vec2f X) const {
  // --------- HANDOUT  PS05 ------------------------------
  // Implement distance from a point X(x,y) to the segment. Remember the 3
  // cases from class.

  float lengthSquared = pow(lPQ,2);

  if (lengthSquared == 0){
      return length(Q-X);
  }
  //projection of p as per instruction in pset
  float projectP = dot(X-P, Q-P)/lengthSquared;

  if (projectP > 1) {
      return length(X-Q);
  }  
  else if (projectP < 0) {
      return length(X-P);
  } 

  Vec2f project =  P + (Q-P * projectP);

  return length(project - X); 
}

Image warpBy1(const Image &im, const Segment &segBefore,
              const Segment &segAfter) {
  // --------- HANDOUT  PS05 ------------------------------
  // Warp an entire image according to a pair of segments.

  Image result(im.width(), im.height(), im.channels());

  for (int x =0; x < im.width(); x++){
    for(int y = 0; y < im.height(); y++){
      for(int c = 0; c < im.channels(); c++){

        //breaking down into vector
        Vec2f xseg = segBefore.UVtoX(segAfter.XtoUV(Vec2f(x, y)));

        //interpolating
        result(x, y, c) = interpolateLin(im, xseg.x, xseg.y, c, true);
      }

    }
  }

  return result;
}

float Segment::weight(Vec2f X, float a, float b, float p) const {
  // --------- HANDOUT  PS05 ------------------------------
  // compute the weight of a segment to a point X(x,y) given the weight
  // parameters a,b, and p (see paper for details).

  //changed to accomodate do length of PQ
  return pow(pow(length(X), p)/(a + lPQ), b);
  
}

Image warp(const Image &im, const vector<Segment> &src_segs,
           const vector<Segment> &dst_segs, float a, float b, float p) {
  // --------- HANDOUT  PS05 ------------------------------
  // Warp an image according to a vector of before and after segments using
  // segment weighting
  
  Image warped(im.width(), im.height(), im.channels());
    // For each pixel X in the destination
  for (int x =0; x < im.width(); x++){
    for(int y = 0; y < im.height(); y++){
      for(int c = 0; c < im.channels(); c++){

          Vec2f weightedSum(0, 0);
          float weightTotal = 0;
          Vec2f X(x, y);

          //loop through segments

          for (int i = 0; i < src_segs.size(); ++i) {
            Segment before = src_segs[i];
            Segment after = dst_segs[i];
            
            //calculate uv using after and X
            //decompose X into uv using after seg
            Vec2f uv = after.XtoUV(X);

            float weight = after.weight(X, a, b, p);
            //get distances from segments to pixels.

            //Vec2f Xsrc = pq.UVtoX(uv); 
            // displacement = X' - X
            Vec2f displacement = before.UVtoX(uv) - X;

            
            // get shortest distance from x to pq
            weightedSum = weightedSum + (displacement * weight);
            weightTotal += weight;
          }

          //add weighted average
          Vec2f weightedAve = weightedSum / weightTotal;
          Vec2f xPrime = X + weightedAve;

          //
          warped(x, y, c) = interpolateLin(im, xPrime.x, xPrime.y, c, true);
        }
      }
    }
    return warped;

}


Image hybrid(const Image &im1, const Image &im2, float sigma, const vector<Segment> &src_segs,
           const vector<Segment> &dst_segs){

  //low pass filter using gaussian
  //float sigma = 3.0;

  Image im2warped = warp(im2, src_segs, dst_segs);

  //im2warped.write("./Output/im2warped.png");

  Image im1warped = warp(im1, src_segs, dst_segs);

  //im1warped.write("./Output/im1warped.png");

  Image im1Low = gaussianBlur_2D(im1warped, sigma);

  //im1Low.write("./Output/lowpass.png");

  
  Image im2Gaussian = gaussianBlur_2D(im2warped, sigma*2);

  //high pass filter: original
  Image im2High = im2warped -im2Gaussian;

  //im2High.write("./Output/highpass.png");

  //average images

  Image hybridImage(im1.width(), im1.height(), im1.channels());

  for (int x = 0; x < im1.width(); x++){
    for(int y = 0; y < im1.height(); y++){
      for(int c = 0; c < im1.channels(); c++){
        hybridImage(x, y, c) = (im1Low(x, y, c) + im2warped(x, y, c));
        //experiment with color:
        //hybridImage(x, y, c) = (im1Low(x, y, c) + im2warped(x, y, c)*(1/2)  + im2High(x, y, c));
      }
    }
  }

  cout << "done with hybrid" << endl;

  return hybridImage;



}
