/* -----------------------------------------------------------------
 * File:    a5_main.cpp
 * Author:  Michael Gharbi <gharbi@mit.edu>
 * Created: 2015-09-30
 * -----------------------------------------------------------------
 *
 *
 *
 * ---------------------------------------------------------------*/

#include "Image.h"
#include "basicImageManipulation.h"
#include "morphing.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void testNearestNeighbor() {
  // Test nearest neighbor
  const Image im("./Input/BostonRainbow-crop-400.png");
  float fact = 3.5;
  Image scaledNN = scaleNN(im, fact);
  scaledNN.write("./Output/testNN.png");
}

void testBilinearInterpolation() {
  // Test bilinear interpolation
  cout << endl << "linear interpolation" << endl;
  cout << "--------------------" << endl;
  Image test(2, 2, 1);
  test(0, 0, 0) = 0.0f;
  test(0, 1, 0) = 0.25f;
  test(1, 0, 0) = 0.5f;
  test(1, 1, 0) = 1.0f;

  float x = 0.25f, y = 0.0;
  cout << "interpolate at (" << x << ", " << y
       << "): " << interpolateLin(test, x, y, 0, false) << ", should be 0.125"
       << endl;

  x = 0.0;
  y = 0.25f;
  cout << "interpolate at (" << x << ", " << y
       << "): " << interpolateLin(test, x, y, 0, false) << ", should be 0.0625"
       << endl;

  x = 0.5;
  y = 0.5f;
  cout << "interpolate at (" << x << ", " << y
       << "): " << interpolateLin(test, x, y, 0, false) << ", should be 0.4375"
       << endl;
}

void testBilinearRescaling() {
  // Test bilinear
  const Image im("./Input/BostonRainbow-crop-400.png");
  float fact = 3.5;
  Image scaled = scaleLin(im, fact);
  scaled.write("./Output/testLin.png");
}

void testRotation() {
  const Image im("./Input/BostonRainbow-crop-400.png");

  float theta = M_PI / 4;

  Image rot = rotate(im, theta);
  rot.write("./Output/testRotate.png");
}

void testVectorOperations() {
  // Test vector lib
  Vec2f a(10.0f, 3.0f);
  Vec2f b(-4.1f, 2.7f);
  float f = 2.0f;
  cout << endl << "vector operations" << endl;
  cout << "-----------------" << endl;

  cout << "a(" << a.x << ", " << a.y << ")" << endl;
  cout << "b(" << b.x << ", " << b.y << ")" << endl;
  cout << "f=" << f << endl;

  // a+b
  Vec2f c = a + b;
  cout << "a+b: (" << c.x << ", " << c.y << ")" << endl;

  // a-b
  c = a - b;
  cout << "a-b: (" << c.x << ", " << c.y << ")" << endl;

  // a*f
  c = a * f;
  cout << "a*f: (" << c.x << ", " << c.y << ")" << endl;

  // a/f
  c = a / f;
  cout << "a/f: (" << c.x << ", " << c.y << ")" << endl;

  // <a,b>
  float s = dot(a, b);
  cout << "<a,b>=" << s << endl;

  // ||a||
  float l = length(a);
  cout << "||a||=" << l << endl;

  Vec2f p_a = perpendicular(a);
  cout << "<a, perpendicular(a)>=" << dot(a, p_a) << endl;
}

void testSegment() {
  // Test segment
  // are P,Q,e1 e1 correctly implemented?
  // are the u,v coordinates meaningful?
  // What should be u and v for P,Q ?
  // Come up with a few test cases !
}

void testWarpBy1() {
  // Test warpBy1 ----------------------------------
  Image fredo("./Input/fredo2.png");
  Image bear("./Input/bear.png");
  // define before and after segments
  Segment segBefore(Vec2f(81, 105), Vec2f(122, 112));
  Segment segAfter(Vec2f(131, 168), Vec2f(134, 127));
  Segment before = Segment(Vec2f(0,0), Vec2f(10,0));
  Segment after = Segment(Vec2f(10, 10), Vec2f(30, 15));

  // warp
  Image warp1 = warpBy1(fredo, segBefore, segAfter);
  Image warp2 = warpBy1(bear, before, after);
  warp1.write("./Output/fredo_upside_down.png");
  warp2.write("./Output/bear_upside_down.png");
  // ------------------------------------------------
}

void testWarp() {
  // Make your own test !
}



void classMorph(){

  // Test morph
  Image mfsyed("./Input/mfsyed.png");
  Image mgomez12("./Input/mgomez12.png");

  // ... use the UI to specify segments
  
  vector<Segment> segsBefore;
  segsBefore.push_back(Segment(Vec2f(154, 306), Vec2f(323, 299)));
  segsBefore.push_back(Segment(Vec2f(132, 384), Vec2f(234, 492)));
  segsBefore.push_back(Segment(Vec2f(258, 487), Vec2f(349, 384)));
  segsBefore.push_back(Segment(Vec2f(159, 329), Vec2f(317, 326)));
  segsBefore.push_back(Segment(Vec2f(122, 307), Vec2f(228, 206)));
  segsBefore.push_back(Segment(Vec2f(242, 213), Vec2f(344, 276)));
  segsBefore.push_back(Segment(Vec2f(135, 359), Vec2f(344, 356)));
  segsBefore.push_back(Segment(Vec2f(234, 313), Vec2f(233, 382)));

  vector<Segment> segsAfter;
  segsAfter.push_back(Segment(Vec2f(154, 212), Vec2f(313, 211)));
  segsAfter.push_back(Segment(Vec2f(133, 321), Vec2f(235, 462)));
  segsAfter.push_back(Segment(Vec2f(255, 458), Vec2f(329, 327)));
  segsAfter.push_back(Segment(Vec2f(155, 258), Vec2f(306, 258)));
  segsAfter.push_back(Segment(Vec2f(127, 197), Vec2f(218, 119)));
  segsAfter.push_back(Segment(Vec2f(226, 132), Vec2f(340, 209)));
  segsAfter.push_back(Segment(Vec2f(132, 295), Vec2f(323, 295)));
  segsAfter.push_back(Segment(Vec2f(231, 234), Vec2f(232, 309)));



  // This should monsterify Fredo a little.
  vector<Image> out = morph(mfsyed, mgomez12, segsBefore, segsAfter, 30);

  // This is how you can write an image sequence
  for (int i = 0; i < (int)out.size(); ++i) {
    ostringstream fname;
    fname << "./class_morph/classmateMorph";
    fname << setfill('0') << setw(2);
    fname << i;
    fname << ".png";
    out[i].write(fname.str());
  }


}

void testMorph() {
  // Test morph
  Image fredo("./Input/fredo2.png");
  Image werewolf("./Input/werewolf.png");

  // ... use the UI to specify segments
  vector<Segment> segsBefore;
  segsBefore.push_back(Segment(Vec2f(85, 102), Vec2f(119, 108)));
  segsBefore.push_back(Segment(Vec2f(143, 117), Vec2f(169, 114)));
  vector<Segment> segsAfter;
  segsAfter.push_back(Segment(Vec2f(86, 93), Vec2f(114, 104)));
  segsAfter.push_back(Segment(Vec2f(137, 94), Vec2f(152, 79)));

  // This should monsterify Fredo a little.
  vector<Image> out = morph(fredo, werewolf, segsBefore, segsAfter, 5);

  // This is how you can write an image sequence
  for (int i = 0; i < (int)out.size(); ++i) {
    ostringstream fname;
    fname << "./Output/test_morph_";
    fname << setfill('0') << setw(2);
    fname << i;
    fname << ".png";
    out[i].write(fname.str());
  }
}

// This is a way for you to test your functions.
// We will only grade the contents of morphing.cpp and
// basicImageManipulation.cpp
int main() {
  classMorph();
  cout << "nothing done in a5_main.cpp, debug me !" << endl;
  // testNearestNeighbor();
  // testBilinearInterpolation();
  // testBilinearRescaling();
  // testRotation();
  // testVectorOperations();
  // testSegment();
  // testWarpBy1();
  // // testWarp();
  // testMorph();
}
