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
#include "filtering.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


/**
 * Test 1 with mfsyed.png and luis.png, from far away we can see mfsyed, but from up close it's luis.
*/
void Test1(){

  Image image1("./Input/mfsyed.png");
  Image image2("./Input/luis.png");

  // ... use the UI to specify segments
  
  cout << "hello" << endl;

  vector<Segment> segsBefore;
  segsBefore.push_back(Segment(Vec2f(237, 217), Vec2f(233, 497)));
  segsBefore.push_back(Segment(Vec2f(163, 324), Vec2f(208, 331)));
  segsBefore.push_back(Segment(Vec2f(270, 335), Vec2f(313, 328)));
  segsBefore.push_back(Segment(Vec2f(146, 313), Vec2f(168, 303)));
  segsBefore.push_back(Segment(Vec2f(331, 311), Vec2f(311, 300)));
  segsBefore.push_back(Segment(Vec2f(223, 311), Vec2f(173, 304)));
  segsBefore.push_back(Segment(Vec2f(256, 312), Vec2f(306, 304)));
  segsBefore.push_back(Segment(Vec2f(205, 378), Vec2f(270, 381)));
  segsBefore.push_back(Segment(Vec2f(242, 323), Vec2f(240, 371)));
  segsBefore.push_back(Segment(Vec2f(221, 348), Vec2f(261, 351)));
  segsBefore.push_back(Segment(Vec2f(132, 373), Vec2f(346, 368)));
  segsBefore.push_back(Segment(Vec2f(240, 407), Vec2f(240, 444)));
  segsBefore.push_back(Segment(Vec2f(194, 411), Vec2f(286, 412)));
  segsBefore.push_back(Segment(Vec2f(157, 450), Vec2f(310, 449)));
  segsBefore.push_back(Segment(Vec2f(164, 261), Vec2f(319, 258)));
  segsBefore.push_back(Segment(Vec2f(268, 215), Vec2f(273, 474)));
  segsBefore.push_back(Segment(Vec2f(208, 217), Vec2f(195, 479)));
  segsBefore.push_back(Segment(Vec2f(137, 419), Vec2f(336, 421)));
  segsBefore.push_back(Segment(Vec2f(297, 230), Vec2f(296, 467)));
  segsBefore.push_back(Segment(Vec2f(183, 232), Vec2f(175, 470)));
  segsBefore.push_back(Segment(Vec2f(188, 321), Vec2f(188, 333)));
  segsBefore.push_back(Segment(Vec2f(290, 322), Vec2f(292, 337)));
  segsBefore.push_back(Segment(Vec2f(136, 321), Vec2f(166, 360)));
  segsBefore.push_back(Segment(Vec2f(345, 337), Vec2f(312, 356)));
  segsBefore.push_back(Segment(Vec2f(132, 399), Vec2f(339, 398)));
  segsBefore.push_back(Segment(Vec2f(242, 309), Vec2f(263, 387)));
  segsBefore.push_back(Segment(Vec2f(232, 308), Vec2f(205, 368)));
  segsBefore.push_back(Segment(Vec2f(304, 472), Vec2f(330, 509)));
  segsBefore.push_back(Segment(Vec2f(168, 472), Vec2f(165, 495)));
  segsBefore.push_back(Segment(Vec2f(234, 501), Vec2f(235, 531)));
  segsBefore.push_back(Segment(Vec2f(209, 481), Vec2f(192, 515)));
  segsBefore.push_back(Segment(Vec2f(264, 481), Vec2f(279, 514)));
  segsBefore.push_back(Segment(Vec2f(244, 491), Vec2f(248, 445)));


  vector<Segment> segsAfter;
  segsAfter.push_back(Segment(Vec2f(256, 240), Vec2f(274, 519)));
  segsAfter.push_back(Segment(Vec2f(195, 327), Vec2f(235, 325)));
  segsAfter.push_back(Segment(Vec2f(289, 324), Vec2f(328, 328)));
  segsAfter.push_back(Segment(Vec2f(179, 309), Vec2f(197, 295)));
  segsAfter.push_back(Segment(Vec2f(342, 308), Vec2f(325, 291)));
  segsAfter.push_back(Segment(Vec2f(239, 303), Vec2f(202, 296)));
  segsAfter.push_back(Segment(Vec2f(280, 303), Vec2f(318, 295)));
  segsAfter.push_back(Segment(Vec2f(234, 369), Vec2f(286, 370)));
  segsAfter.push_back(Segment(Vec2f(257, 312), Vec2f(258, 355)));
  segsAfter.push_back(Segment(Vec2f(236, 339), Vec2f(279, 339)));
  segsAfter.push_back(Segment(Vec2f(170, 361), Vec2f(353, 361)));
  segsAfter.push_back(Segment(Vec2f(260, 405), Vec2f(261, 430)));
  segsAfter.push_back(Segment(Vec2f(224, 414), Vec2f(294, 415)));
  segsAfter.push_back(Segment(Vec2f(186, 459), Vec2f(328, 453)));
  segsAfter.push_back(Segment(Vec2f(187, 265), Vec2f(333, 263)));
  segsAfter.push_back(Segment(Vec2f(292, 234), Vec2f(305, 512)));
  segsAfter.push_back(Segment(Vec2f(230, 238), Vec2f(232, 509)));
  segsAfter.push_back(Segment(Vec2f(171, 417), Vec2f(346, 423)));
  segsAfter.push_back(Segment(Vec2f(312, 241), Vec2f(327, 491)));
  segsAfter.push_back(Segment(Vec2f(209, 240), Vec2f(214, 495)));
  segsAfter.push_back(Segment(Vec2f(215, 317), Vec2f(216, 333)));
  segsAfter.push_back(Segment(Vec2f(311, 318), Vec2f(310, 334)));
  segsAfter.push_back(Segment(Vec2f(164, 327), Vec2f(195, 350)));
  segsAfter.push_back(Segment(Vec2f(353, 320), Vec2f(330, 348)));
  segsAfter.push_back(Segment(Vec2f(170, 391), Vec2f(350, 393)));
  segsAfter.push_back(Segment(Vec2f(265, 298), Vec2f(280, 373)));
  segsAfter.push_back(Segment(Vec2f(252, 296), Vec2f(234, 352)));
  segsAfter.push_back(Segment(Vec2f(338, 476), Vec2f(386, 508)));
  segsAfter.push_back(Segment(Vec2f(193, 476), Vec2f(176, 496)));
  segsAfter.push_back(Segment(Vec2f(271, 527), Vec2f(270, 566)));
  segsAfter.push_back(Segment(Vec2f(254, 521), Vec2f(239, 540)));
  segsAfter.push_back(Segment(Vec2f(293, 519), Vec2f(322, 535)));
  segsAfter.push_back(Segment(Vec2f(282, 514), Vec2f(272, 428)));


  Image im2warped = warp(image2, segsBefore, segsAfter);
  Image im1warped = warp(image1, segsBefore, segsAfter);

  // im2warped.write("./Output/t1im2warped.png");
  // im1warped.write("./Output/t1im1warped.png");

  Image im1Low = gaussianBlur_2D(im1warped, 3.0);

  Image im2Gaussian = gaussianBlur_2D(im2warped, 3.0*1.5);

  Image im2High = im2warped -im2Gaussian;

  // im2High.write("./Output/t1im2High.png");
  // im1Low.write("./Output/t1im1Low.png");

  // This should monsterify Fredo a little.
  Image outImage = hybrid(image1, image2, 3.0, segsBefore, segsAfter);

  
  outImage.write("./Output/hyrid-1.png");
  //outImage.write("./Output/hyrid-1-color.png");

  cout << "ending test 1" << endl;

}




/**
 * Test 2 with marker.png and pen.png, from far away we can see marker, but from up close it's pen.
*/
void Test2(){

  // Test morph
  Image image1("./Input/marker.png");
  Image image2("./Input/pen.png");

  // ... use the UI to specify segments
  
  cout << "starting test 2" << endl;

  vector<Segment> segsBefore;
  segsBefore.push_back(Segment(Vec2f(262, 84), Vec2f(275, 525)));
  segsBefore.push_back(Segment(Vec2f(297, 196), Vec2f(312, 509)));
  segsBefore.push_back(Segment(Vec2f(237, 195), Vec2f(241, 514)));
  segsBefore.push_back(Segment(Vec2f(230, 109), Vec2f(299, 104)));
  segsBefore.push_back(Segment(Vec2f(236, 120), Vec2f(303, 503)));
  segsBefore.push_back(Segment(Vec2f(297, 112), Vec2f(247, 506)));
  segsBefore.push_back(Segment(Vec2f(241, 185), Vec2f(294, 184)));
  segsBefore.push_back(Segment(Vec2f(241, 235), Vec2f(295, 234)));
  segsBefore.push_back(Segment(Vec2f(245, 454), Vec2f(303, 451)));
  segsBefore.push_back(Segment(Vec2f(242, 364), Vec2f(300, 359)));
  segsBefore.push_back(Segment(Vec2f(242, 262), Vec2f(292, 262)));
  segsBefore.push_back(Segment(Vec2f(243, 332), Vec2f(299, 310)));
  segsBefore.push_back(Segment(Vec2f(279, 93), Vec2f(297, 523)));
  segsBefore.push_back(Segment(Vec2f(248, 95), Vec2f(258, 523)));
  segsBefore.push_back(Segment(Vec2f(239, 214), Vec2f(295, 216)));


  vector<Segment> segsAfter;
  segsAfter.push_back(Segment(Vec2f(260, 97), Vec2f(264, 586)));
  segsAfter.push_back(Segment(Vec2f(242, 142), Vec2f(242, 540)));
  segsAfter.push_back(Segment(Vec2f(280, 140), Vec2f(284, 545)));
  segsAfter.push_back(Segment(Vec2f(253, 98), Vec2f(267, 98)));
  segsAfter.push_back(Segment(Vec2f(246, 148), Vec2f(278, 538)));
  segsAfter.push_back(Segment(Vec2f(273, 119), Vec2f(251, 534)));
  segsAfter.push_back(Segment(Vec2f(245, 135), Vec2f(276, 133)));
  segsAfter.push_back(Segment(Vec2f(246, 219), Vec2f(277, 215)));
  segsAfter.push_back(Segment(Vec2f(229, 453), Vec2f(282, 448)));
  segsAfter.push_back(Segment(Vec2f(235, 389), Vec2f(277, 387)));
  segsAfter.push_back(Segment(Vec2f(246, 283), Vec2f(279, 284)));
  segsAfter.push_back(Segment(Vec2f(246, 340), Vec2f(280, 341)));
  segsAfter.push_back(Segment(Vec2f(267, 106), Vec2f(275, 577)));
  segsAfter.push_back(Segment(Vec2f(250, 109), Vec2f(250, 578)));
  segsAfter.push_back(Segment(Vec2f(244, 182), Vec2f(278, 179)));


  Image im2warped = warp(image2, segsBefore, segsAfter);
  Image im1warped = warp(image1, segsBefore, segsAfter);

  // im2warped.write("./Output/t2im2warped.png");
  // im1warped.write("./Output/t2im1warped.png");

  Image im1Low = gaussianBlur_2D(im1warped, 3.0);

  Image im2Gaussian = gaussianBlur_2D(im2warped, 3.0*2);

  Image im2High = im2warped -im2Gaussian;

  im2High.write("./Output/t2im2High.png");
  im1Low.write("./Output/t2im1Low.png");

  // This should monsterify Fredo a little.
  Image outImage = hybrid(image1, image2, 3.0, segsBefore, segsAfter);

  // outImage.write("./Output/hybrid-2.png");

  //outImage.write("./Output/hybrid-2-color.png");

  cout << "ending test 2" << endl;

}




/**
 * Test 3 with alex.png and luis.png, from far away we can see luis, but from up close it's alex.
*/
void Test3(){

  // Test morph
  Image image1("./Input/luis.png");
  Image image2("./Input/alex.png");

  // ... use the UI to specify segments
  
  cout << "starting test 3" << endl;

  vector<Segment> segsBefore;
  segsBefore.push_back(Segment(Vec2f(262, 237), Vec2f(265, 488)));
  segsBefore.push_back(Segment(Vec2f(169, 351), Vec2f(353, 357)));
  segsBefore.push_back(Segment(Vec2f(213, 316), Vec2f(213, 331)));
  segsBefore.push_back(Segment(Vec2f(310, 317), Vec2f(310, 329)));
  segsBefore.push_back(Segment(Vec2f(196, 327), Vec2f(236, 324)));
  segsBefore.push_back(Segment(Vec2f(289, 325), Vec2f(327, 325)));
  segsBefore.push_back(Segment(Vec2f(175, 310), Vec2f(196, 297)));
  segsBefore.push_back(Segment(Vec2f(201, 297), Vec2f(236, 305)));
  segsBefore.push_back(Segment(Vec2f(278, 306), Vec2f(315, 298)));
  segsBefore.push_back(Segment(Vec2f(320, 300), Vec2f(340, 307)));
  segsBefore.push_back(Segment(Vec2f(258, 311), Vec2f(257, 357)));
  segsBefore.push_back(Segment(Vec2f(243, 337), Vec2f(278, 337)));
  segsBefore.push_back(Segment(Vec2f(230, 368), Vec2f(290, 369)));
  segsBefore.push_back(Segment(Vec2f(269, 378), Vec2f(268, 401)));
  segsBefore.push_back(Segment(Vec2f(259, 405), Vec2f(261, 425)));
  segsBefore.push_back(Segment(Vec2f(229, 416), Vec2f(293, 418)));
  segsBefore.push_back(Segment(Vec2f(270, 431), Vec2f(275, 484)));
  segsBefore.push_back(Segment(Vec2f(251, 432), Vec2f(250, 486)));
  segsBefore.push_back(Segment(Vec2f(312, 241), Vec2f(312, 468)));
  segsBefore.push_back(Segment(Vec2f(214, 242), Vec2f(211, 472)));
  segsBefore.push_back(Segment(Vec2f(182, 275), Vec2f(180, 427)));
  segsBefore.push_back(Segment(Vec2f(345, 292), Vec2f(346, 431)));
  segsBefore.push_back(Segment(Vec2f(170, 387), Vec2f(353, 396)));
  segsBefore.push_back(Segment(Vec2f(218, 482), Vec2f(303, 477)));
  segsBefore.push_back(Segment(Vec2f(198, 471), Vec2f(177, 492)));
  segsBefore.push_back(Segment(Vec2f(335, 476), Vec2f(388, 506)));
  segsBefore.push_back(Segment(Vec2f(272, 495), Vec2f(273, 584)));
  segsBefore.push_back(Segment(Vec2f(189, 266), Vec2f(333, 268)));
  segsBefore.push_back(Segment(Vec2f(275, 236), Vec2f(273, 299)));
  segsBefore.push_back(Segment(Vec2f(237, 236), Vec2f(233, 295)));
  segsBefore.push_back(Segment(Vec2f(294, 240), Vec2f(292, 287)));
  segsBefore.push_back(Segment(Vec2f(243, 346), Vec2f(168, 373)));
  segsBefore.push_back(Segment(Vec2f(280, 343), Vec2f(357, 371)));
  segsBefore.push_back(Segment(Vec2f(223, 415), Vec2f(175, 378)));
  segsBefore.push_back(Segment(Vec2f(305, 413), Vec2f(346, 375)));


  vector<Segment> segsAfter;
  segsAfter.push_back(Segment(Vec2f(235, 207), Vec2f(243, 426)));
  segsAfter.push_back(Segment(Vec2f(104, 309), Vec2f(382, 304)));
  segsAfter.push_back(Segment(Vec2f(175, 278), Vec2f(175, 288)));
  segsAfter.push_back(Segment(Vec2f(300, 272), Vec2f(302, 284)));
  segsAfter.push_back(Segment(Vec2f(151, 286), Vec2f(203, 285)));
  segsAfter.push_back(Segment(Vec2f(272, 283), Vec2f(331, 282)));
  segsAfter.push_back(Segment(Vec2f(132, 265), Vec2f(156, 250)));
  segsAfter.push_back(Segment(Vec2f(164, 251), Vec2f(211, 258)));
  segsAfter.push_back(Segment(Vec2f(259, 257), Vec2f(319, 251)));
  segsAfter.push_back(Segment(Vec2f(327, 252), Vec2f(348, 265)));
  segsAfter.push_back(Segment(Vec2f(233, 270), Vec2f(233, 319)));
  segsAfter.push_back(Segment(Vec2f(220, 296), Vec2f(250, 293)));
  segsAfter.push_back(Segment(Vec2f(201, 323), Vec2f(278, 328)));
  segsAfter.push_back(Segment(Vec2f(245, 336), Vec2f(246, 351)));
  segsAfter.push_back(Segment(Vec2f(234, 355), Vec2f(235, 362)));
  segsAfter.push_back(Segment(Vec2f(184, 365), Vec2f(301, 360)));
  segsAfter.push_back(Segment(Vec2f(248, 364), Vec2f(257, 425)));
  segsAfter.push_back(Segment(Vec2f(226, 369), Vec2f(224, 421)));
  segsAfter.push_back(Segment(Vec2f(301, 205), Vec2f(302, 411)));
  segsAfter.push_back(Segment(Vec2f(155, 224), Vec2f(159, 409)));
  segsAfter.push_back(Segment(Vec2f(121, 260), Vec2f(127, 377)));
  segsAfter.push_back(Segment(Vec2f(367, 271), Vec2f(361, 367)));
  segsAfter.push_back(Segment(Vec2f(115, 355), Vec2f(369, 349)));
  segsAfter.push_back(Segment(Vec2f(172, 413), Vec2f(292, 417)));
  segsAfter.push_back(Segment(Vec2f(148, 399), Vec2f(140, 421)));
  segsAfter.push_back(Segment(Vec2f(347, 389), Vec2f(349, 446)));
  segsAfter.push_back(Segment(Vec2f(243, 436), Vec2f(247, 496)));
  segsAfter.push_back(Segment(Vec2f(132, 236), Vec2f(331, 236)));
  segsAfter.push_back(Segment(Vec2f(244, 203), Vec2f(245, 250)));
  segsAfter.push_back(Segment(Vec2f(199, 211), Vec2f(199, 246)));
  segsAfter.push_back(Segment(Vec2f(267, 209), Vec2f(266, 247)));
  segsAfter.push_back(Segment(Vec2f(227, 301), Vec2f(111, 330)));
  segsAfter.push_back(Segment(Vec2f(255, 299), Vec2f(377, 316)));
  segsAfter.push_back(Segment(Vec2f(175, 366), Vec2f(121, 337)));
  segsAfter.push_back(Segment(Vec2f(306, 362), Vec2f(360, 325)));


  Image im2warped = warp(image2, segsBefore, segsAfter);
  Image im1warped = warp(image1, segsBefore, segsAfter);

  im2warped.write("./Output/t3im2warped.png");
  im1warped.write("./Output/t3im1warped.png");

  Image im1Low = gaussianBlur_2D(im1warped, 3.0);

  Image im2Gaussian = gaussianBlur_2D(im2warped, 3.0*2);

  Image im2High = im2warped -im2Gaussian;

  im2High.write("./Output/t3im2High.png");
  im1Low.write("./Output/t3im1Low.png");

  // This should monsterify Fredo a little.
  Image outImage = hybrid(image1, image2, 3.0, segsBefore, segsAfter);

  outImage.write("./Output/hybrid-3.png");

  cout << "ending test 3" << endl;

}



/**
 * Test 4 with pad.png and dollar.png, from far away we can see pad, but from up close it's dollar.
*/
void Test4(){

  // Test morph
  Image image1("./Input/pad.png");
  Image image2("./Input/dollar.png");

  // ... use the UI to specify segments
  
  cout << "starting test 4" << endl;

  
  vector<Segment> segsBefore;
  segsBefore.push_back(Segment(Vec2f(82, 121), Vec2f(351, 123)));
  segsBefore.push_back(Segment(Vec2f(84, 123), Vec2f(92, 494)));
  segsBefore.push_back(Segment(Vec2f(350, 124), Vec2f(362, 473)));
  segsBefore.push_back(Segment(Vec2f(100, 491), Vec2f(356, 471)));
  segsBefore.push_back(Segment(Vec2f(91, 278), Vec2f(113, 277)));
  segsBefore.push_back(Segment(Vec2f(111, 278), Vec2f(121, 375)));
  segsBefore.push_back(Segment(Vec2f(114, 376), Vec2f(92, 375)));
  segsBefore.push_back(Segment(Vec2f(173, 254), Vec2f(264, 250)));
  segsBefore.push_back(Segment(Vec2f(265, 253), Vec2f(264, 319)));
  segsBefore.push_back(Segment(Vec2f(257, 319), Vec2f(176, 326)));
  segsBefore.push_back(Segment(Vec2f(170, 312), Vec2f(171, 262)));
  segsBefore.push_back(Segment(Vec2f(314, 168), Vec2f(329, 434)));
  segsBefore.push_back(Segment(Vec2f(88, 126), Vec2f(348, 457)));
  segsBefore.push_back(Segment(Vec2f(345, 129), Vec2f(105, 475)));
  segsBefore.push_back(Segment(Vec2f(220, 123), Vec2f(239, 482)));
  segsBefore.push_back(Segment(Vec2f(300, 125), Vec2f(315, 474)));
  segsBefore.push_back(Segment(Vec2f(131, 122), Vec2f(156, 489)));
  segsBefore.push_back(Segment(Vec2f(89, 239), Vec2f(348, 231)));
  segsBefore.push_back(Segment(Vec2f(89, 302), Vec2f(351, 299)));
  segsBefore.push_back(Segment(Vec2f(92, 386), Vec2f(355, 385)));
  segsBefore.push_back(Segment(Vec2f(93, 468), Vec2f(356, 440)));


  vector<Segment> segsAfter;
  segsAfter.push_back(Segment(Vec2f(114, 44), Vec2f(340, 63)));
  segsAfter.push_back(Segment(Vec2f(112, 45), Vec2f(117, 541)));
  segsAfter.push_back(Segment(Vec2f(340, 66), Vec2f(340, 533)));
  segsAfter.push_back(Segment(Vec2f(124, 536), Vec2f(333, 530)));
  segsAfter.push_back(Segment(Vec2f(117, 207), Vec2f(150, 204)));
  segsAfter.push_back(Segment(Vec2f(150, 209), Vec2f(146, 395)));
  segsAfter.push_back(Segment(Vec2f(139, 395), Vec2f(117, 395)));
  segsAfter.push_back(Segment(Vec2f(159, 257), Vec2f(271, 255)));
  segsAfter.push_back(Segment(Vec2f(284, 267), Vec2f(283, 334)));
  segsAfter.push_back(Segment(Vec2f(273, 338), Vec2f(162, 342)));
  segsAfter.push_back(Segment(Vec2f(160, 325), Vec2f(158, 267)));
  segsAfter.push_back(Segment(Vec2f(304, 139), Vec2f(306, 457)));
  segsAfter.push_back(Segment(Vec2f(120, 51), Vec2f(326, 516)));
  segsAfter.push_back(Segment(Vec2f(330, 72), Vec2f(126, 519)));
  segsAfter.push_back(Segment(Vec2f(226, 54), Vec2f(234, 547)));
  segsAfter.push_back(Segment(Vec2f(291, 59), Vec2f(287, 535)));
  segsAfter.push_back(Segment(Vec2f(159, 50), Vec2f(163, 542)));
  segsAfter.push_back(Segment(Vec2f(118, 154), Vec2f(336, 156)));
  segsAfter.push_back(Segment(Vec2f(117, 271), Vec2f(331, 279)));
  segsAfter.push_back(Segment(Vec2f(118, 404), Vec2f(346, 409)));
  segsAfter.push_back(Segment(Vec2f(118, 502), Vec2f(342, 485)));






  Image im2warped = warp(image2, segsBefore, segsAfter);
  Image im1warped = warp(image1, segsBefore, segsAfter);

  im2warped.write("./Output/t4im2warped.png");
  im1warped.write("./Output/t4im1warped.png");

  Image im1Low = gaussianBlur_2D(im1warped, 3.0);

  Image im2Gaussian = gaussianBlur_2D(im2warped, 3.0);

  Image im2High = im2warped -im2Gaussian;

  im2High.write("./Output/t4im2High.png");
  im1Low.write("./Output/t4im1Low.png");

  // This should monsterify Fredo a little.
  Image outImage = hybrid(image1, image2, 3.0, segsBefore, segsAfter);

  outImage.write("./Output/hybrid-4.png");

  cout << "ending test 4" << endl;

}



/**
 * Test 5 with pad.png and dollar.png, from far away we can see pad, but from up close it's dollar.
*/
void Test5(){

  // Test morph
  Image image1("./Input/smile.png");
  Image image2("./Input/frown.png");

  // ... use the UI to specify segments
  
  cout << "starting test 5" << endl;

  
  vector<Segment> segsBefore;
  segsBefore.push_back(Segment(Vec2f(195, 390), Vec2f(245, 386)));
  segsBefore.push_back(Segment(Vec2f(250, 384), Vec2f(259, 390)));
  segsBefore.push_back(Segment(Vec2f(264, 387), Vec2f(281, 385)));
  segsBefore.push_back(Segment(Vec2f(285, 385), Vec2f(325, 396)));
  segsBefore.push_back(Segment(Vec2f(187, 399), Vec2f(211, 436)));
  segsBefore.push_back(Segment(Vec2f(220, 439), Vec2f(287, 445)));
  segsBefore.push_back(Segment(Vec2f(297, 438), Vec2f(328, 403)));
  segsBefore.push_back(Segment(Vec2f(198, 396), Vec2f(252, 415)));
  segsBefore.push_back(Segment(Vec2f(260, 414), Vec2f(322, 399)));
  segsBefore.push_back(Segment(Vec2f(155, 278), Vec2f(206, 278)));
  segsBefore.push_back(Segment(Vec2f(210, 280), Vec2f(223, 292)));
  segsBefore.push_back(Segment(Vec2f(303, 286), Vec2f(349, 274)));
  segsBefore.push_back(Segment(Vec2f(353, 275), Vec2f(361, 285)));
  segsBefore.push_back(Segment(Vec2f(260, 258), Vec2f(258, 350)));
  segsBefore.push_back(Segment(Vec2f(245, 286), Vec2f(277, 281)));
  segsBefore.push_back(Segment(Vec2f(248, 308), Vec2f(275, 309)));
  segsBefore.push_back(Segment(Vec2f(217, 342), Vec2f(303, 344)));
  segsBefore.push_back(Segment(Vec2f(161, 283), Vec2f(219, 294)));
  segsBefore.push_back(Segment(Vec2f(297, 297), Vec2f(361, 287)));
  segsBefore.push_back(Segment(Vec2f(143, 256), Vec2f(170, 245)));
  segsBefore.push_back(Segment(Vec2f(172, 246), Vec2f(238, 261)));
  segsBefore.push_back(Segment(Vec2f(286, 259), Vec2f(349, 246)));
  segsBefore.push_back(Segment(Vec2f(353, 247), Vec2f(377, 262)));
  segsBefore.push_back(Segment(Vec2f(261, 374), Vec2f(265, 389)));
  segsBefore.push_back(Segment(Vec2f(219, 363), Vec2f(217, 381)));
  segsBefore.push_back(Segment(Vec2f(304, 367), Vec2f(305, 391)));
  segsBefore.push_back(Segment(Vec2f(258, 449), Vec2f(255, 499)));
  segsBefore.push_back(Segment(Vec2f(260, 145), Vec2f(258, 244)));
  segsBefore.push_back(Segment(Vec2f(210, 141), Vec2f(197, 242)));
  segsBefore.push_back(Segment(Vec2f(304, 142), Vec2f(322, 241)));
  segsBefore.push_back(Segment(Vec2f(172, 169), Vec2f(342, 166)));
  segsBefore.push_back(Segment(Vec2f(154, 206), Vec2f(365, 198)));
  segsBefore.push_back(Segment(Vec2f(124, 233), Vec2f(386, 230)));
  segsBefore.push_back(Segment(Vec2f(117, 252), Vec2f(118, 392)));
  segsBefore.push_back(Segment(Vec2f(118, 392), Vec2f(387, 245)));
  segsBefore.push_back(Segment(Vec2f(390, 389), Vec2f(389, 245)));
  segsBefore.push_back(Segment(Vec2f(123, 399), Vec2f(238, 501)));
  segsBefore.push_back(Segment(Vec2f(264, 495), Vec2f(386, 396)));
  segsBefore.push_back(Segment(Vec2f(113, 327), Vec2f(398, 326)));
  segsBefore.push_back(Segment(Vec2f(114, 281), Vec2f(393, 280)));
  segsBefore.push_back(Segment(Vec2f(171, 458), Vec2f(344, 455)));
  segsBefore.push_back(Segment(Vec2f(259, 126), Vec2f(254, 504)));
  segsBefore.push_back(Segment(Vec2f(280, 133), Vec2f(282, 492)));
  segsBefore.push_back(Segment(Vec2f(226, 132), Vec2f(221, 494)));
  segsBefore.push_back(Segment(Vec2f(114, 371), Vec2f(395, 358)));
  segsBefore.push_back(Segment(Vec2f(350, 178), Vec2f(351, 447)));
  segsBefore.push_back(Segment(Vec2f(188, 147), Vec2f(165, 455)));


  vector<Segment> segsAfter;
  segsAfter.push_back(Segment(Vec2f(189, 406), Vec2f(239, 382)));
  segsAfter.push_back(Segment(Vec2f(241, 384), Vec2f(251, 389)));
  segsAfter.push_back(Segment(Vec2f(255, 389), Vec2f(267, 384)));
  segsAfter.push_back(Segment(Vec2f(269, 385), Vec2f(310, 425)));
  segsAfter.push_back(Segment(Vec2f(183, 419), Vec2f(228, 424)));
  segsAfter.push_back(Segment(Vec2f(234, 423), Vec2f(281, 428)));
  segsAfter.push_back(Segment(Vec2f(284, 427), Vec2f(309, 431)));
  segsAfter.push_back(Segment(Vec2f(194, 408), Vec2f(246, 405)));
  segsAfter.push_back(Segment(Vec2f(253, 405), Vec2f(302, 418)));
  segsAfter.push_back(Segment(Vec2f(159, 269), Vec2f(194, 265)));
  segsAfter.push_back(Segment(Vec2f(199, 266), Vec2f(220, 280)));
  segsAfter.push_back(Segment(Vec2f(293, 275), Vec2f(336, 264)));
  segsAfter.push_back(Segment(Vec2f(338, 264), Vec2f(353, 276)));
  segsAfter.push_back(Segment(Vec2f(257, 245), Vec2f(253, 333)));
  segsAfter.push_back(Segment(Vec2f(241, 268), Vec2f(269, 262)));
  segsAfter.push_back(Segment(Vec2f(237, 296), Vec2f(271, 292)));
  segsAfter.push_back(Segment(Vec2f(215, 330), Vec2f(289, 330)));
  segsAfter.push_back(Segment(Vec2f(159, 274), Vec2f(212, 281)));
  segsAfter.push_back(Segment(Vec2f(290, 284), Vec2f(348, 279)));
  segsAfter.push_back(Segment(Vec2f(142, 244), Vec2f(162, 232)));
  segsAfter.push_back(Segment(Vec2f(167, 232), Vec2f(229, 248)));
  segsAfter.push_back(Segment(Vec2f(277, 243), Vec2f(340, 233)));
  segsAfter.push_back(Segment(Vec2f(344, 236), Vec2f(368, 255)));
  segsAfter.push_back(Segment(Vec2f(255, 356), Vec2f(251, 391)));
  segsAfter.push_back(Segment(Vec2f(220, 357), Vec2f(218, 389)));
  segsAfter.push_back(Segment(Vec2f(285, 362), Vec2f(289, 398)));
  segsAfter.push_back(Segment(Vec2f(244, 428), Vec2f(240, 487)));
  segsAfter.push_back(Segment(Vec2f(255, 144), Vec2f(257, 228)));
  segsAfter.push_back(Segment(Vec2f(213, 138), Vec2f(190, 229)));
  segsAfter.push_back(Segment(Vec2f(315, 151), Vec2f(322, 224)));
  segsAfter.push_back(Segment(Vec2f(166, 158), Vec2f(339, 167)));
  segsAfter.push_back(Segment(Vec2f(141, 190), Vec2f(355, 193)));
  segsAfter.push_back(Segment(Vec2f(126, 216), Vec2f(375, 223)));
  segsAfter.push_back(Segment(Vec2f(109, 250), Vec2f(116, 392)));
  segsAfter.push_back(Segment(Vec2f(120, 386), Vec2f(375, 245)));
  segsAfter.push_back(Segment(Vec2f(373, 385), Vec2f(376, 250)));
  segsAfter.push_back(Segment(Vec2f(119, 400), Vec2f(237, 490)));
  segsAfter.push_back(Segment(Vec2f(254, 483), Vec2f(369, 393)));
  segsAfter.push_back(Segment(Vec2f(110, 325), Vec2f(380, 317)));
  segsAfter.push_back(Segment(Vec2f(108, 279), Vec2f(381, 271)));
  segsAfter.push_back(Segment(Vec2f(156, 455), Vec2f(323, 458)));
  segsAfter.push_back(Segment(Vec2f(254, 125), Vec2f(244, 493)));
  segsAfter.push_back(Segment(Vec2f(280, 132), Vec2f(270, 489)));
  segsAfter.push_back(Segment(Vec2f(221, 133), Vec2f(208, 489)));
  segsAfter.push_back(Segment(Vec2f(110, 367), Vec2f(378, 361)));
  segsAfter.push_back(Segment(Vec2f(337, 171), Vec2f(334, 453)));
  segsAfter.push_back(Segment(Vec2f(159, 163), Vec2f(158, 461)));






  Image im2warped = warp(image2, segsBefore, segsAfter);
  Image im1warped = warp(image1, segsBefore, segsAfter);

  im2warped.write("./Output/t5im2warped.png");
  im1warped.write("./Output/t5im1warped.png");

  Image im1Low = gaussianBlur_2D(im1warped, 3.0);

  Image im2Gaussian = gaussianBlur_2D(im2warped, 3.0);

  Image im2High = im2warped -im2Gaussian;

  im2High.write("./Output/t5im2High.png");
  im1Low.write("./Output/t5im1Low.png");

  // This should monsterify Fredo a little.
  Image outImage = hybrid(image1, image2, 3.0, segsBefore, segsAfter);

  outImage.write("./Output/hybrid-5.png");

  cout << "ending test 5" << endl;

}

// This is a way for you to test your functions.
// We will only grade the contents of morphing.cpp and
// basicImageManipulation.cpp
int main() {
  Test2();
  cout << "nothing done in a5_main.cpp, debug me !" << endl;
}
