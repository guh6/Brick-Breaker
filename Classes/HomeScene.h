/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2010      Ray Wenderlich
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef _GAME_OVER_SCENE_H2_
#define _GAME_OVER_SCENE_H2_

#include "cocos2d.h"

class HomeLayer : public cocos2d::CCLayerColor
{
public:
    HomeLayer():_label(NULL) {};
    virtual ~HomeLayer();
    bool init();
    CREATE_FUNC(HomeLayer);

	void gameOverDone();
   

    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
};

class HomeScene : public cocos2d::CCScene
{
public:
    HomeScene():_layer(NULL) {};
    ~HomeScene();
    bool init();
    CREATE_FUNC(HomeScene);
  
    CC_SYNTHESIZE_READONLY(HomeLayer*, _layer, Layer);
};

#endif // _GAME_OVER_SCENE_H_
