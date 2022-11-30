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








// vector<Image> morph(const Image &im_before, const Image &im_after,
//                     const vector<Segment> &segs_before,
//                     const vector<Segment> &segs_after, int N, float a, float b,
//                     float p) {
//   // --------- HANDOUT  PS05 ------------------------------
//   // return a vector of N+2 images: the two inputs plus N images that morphs
//   // between im_before and im_after for the corresponding segments. 
//   //im_before
//   // should be the first image, im_after the last.
//   vector<Image> morphedImages;
//   //adding starting image
//   morphedImages.push_back(im_before);

//   for (int n = 1; n <= N; n++) {
//     // creating img to be added
//     Image imgN(im_before.width(), im_before.height(), im_before.channels());

//     float t = n / float(N + 1); //time constant adjustment

//     // build target
//     vector<Segment> targetSegments;
//     for (int i = 0; i < segs_before.size(); i++) {

//       //creating segment by calculating p and q vectors using before and after segments
//       Vec2f P = ((segs_after[i].getP() - segs_before[i].getP()) * t) + segs_before[i].getP();
//       Vec2f Q = ((segs_after[i].getQ() - segs_before[i].getQ()) * t) + segs_before[i].getQ();

//       targetSegments.push_back(Segment(P, Q));
//     }

//     Image after = warp(im_after, segs_after, targetSegments, a, b, p);
//     Image before = warp(im_before, segs_before, targetSegments, a, b, p);
    

//     for (int i = 0; i < before.number_of_elements(); i++) {
//       //averaging location points from slides
//       imgN(i) = after(i) * t + before(i) * (1 - t);
//     }

//     morphedImages.push_back(imgN);
//   }
//   //adding last photo
//   morphedImages.push_back(im_after);
//   return morphedImages;
// }
