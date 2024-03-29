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

#include "HomeScene.h"
#include "HelloWorldScene.h"
#include "OptionScene.h"

using namespace cocos2d;

bool HomeScene::init()
{
	if (CCScene::init())
	{
		this->_layer = HomeLayer::create();
		this->_layer->retain();
		this->addChild(_layer);

		return true;
	}
	else
	{
		return false;
	}
}

HomeScene::~HomeScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}


bool HomeLayer::init()
{
	if (CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		








		this->runAction(CCSequence::create(
			CCDelayTime::create(3),
			CCCallFunc::create(this,
			callfunc_selector(HomeLayer::gameOverDone)),
			NULL));

		return true;
	}
	else
	{
		return false;
	}
}




void HomeLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

HomeLayer::~HomeLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}
