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

#include "OptionScene.h"
#include "HelloWorldScene.h"
#include "HomeScene.h"
#include "NewScene.h"


using namespace cocos2d;

int hours;
extern int hours2;
void NewScene::setMusicNS(int x){
	
	music_NS = x;
	CCLog("music setting to :%d", music_NS);
}

CCScene* NewScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	NewScene *layer = NewScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool NewScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	////OutputDebugString(L"I'm in new menu");
	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCLOG("framesize : %f, %f", frameSize.width, frameSize.height);
	float scaleXfactor = frameSize.width / 2054;
	float scaleYfactor = frameSize.height / 1536;

	CCMenuItemImage *play = CCMenuItemImage::create(
		"play.png",
		"play.png",
		this,
		menu_selector(NewScene::PG_callback));
	play->setOpacity(255);
	play->setScaleX(scaleXfactor);
	play->setScaleY(scaleYfactor);
	//play->setPosition(ccp(visibleSize.width / 2 + play->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + play->getContentSize().height*scaleYfactor / 2));
	//play->setPosition(ccp(visibleSize.width / 2 + (play->getContentSize().width*scaleXfactor*scaleXfactor) / 2, visibleSize.height / 2 + (play->getContentSize().height*scaleYfactor*scaleYfactor) / 2));
	play->setPosition(ccp(visibleSize.width / 2 + (play->getContentSize().width*scaleXfactor) / 2, visibleSize.height / 2 + (play->getContentSize().height*scaleYfactor) / 2));

	// create menu, it's an autorelease object
	CCMenu*pMenu = CCMenu::create(play, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);
	
	CCMenuItemImage *options = CCMenuItemImage::create(
		"options.png",
		"options.png",
		this,
		menu_selector(NewScene::options_callback));
	options->setScaleX(scaleXfactor);				
	options->setScaleY(scaleYfactor);
	options->setPosition(ccp(visibleSize.width / 2 + options->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + options->getContentSize().height*scaleYfactor / 2 - play->getContentSize().height*scaleYfactor));

	// create menu, it's an autorelease object
	CCMenu* optionsMenu = CCMenu::create(options, NULL);
	optionsMenu->setPosition(CCPointZero);
	this->addChild(optionsMenu, 2);

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(NewScene::closeMenu));
	pCloseItem->setScaleX(scaleXfactor);
	pCloseItem->setScaleY(scaleYfactor);
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width*scaleXfactor / 2,
		origin.y + pCloseItem->getContentSize().height*scaleYfactor / 2));

	// create menu, it's an autorelease object
	CCMenu* close = CCMenu::create(pCloseItem, NULL);
	close->setPosition(CCPointZero);
	this->addChild(close, 2);
	
	CCLog("*** Logging music: %d", hours);
	
	banner3 = CCSprite::create("Blank3.png");
	banner3->setScaleX(scaleXfactor);
	banner3->setScaleY(scaleYfactor);
	banner3->setPosition(ccp(origin.x + visibleSize.width / 2, visibleSize.height / 2 + options->getContentSize().height*scaleYfactor * 2));
	this->addChild(banner3, 3);

	


	return true;
}



void NewScene::PG_callback(CCObject* pSender){
	
	CCLog("*** Logging music: %d", music_NS);
	hours2 = hours;
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	

}
void NewScene::options_callback(CCObject* Sender){
	CCLog("*** Logging music 2: %d", music_NS);
	
	CCDirector::sharedDirector()->replaceScene(OptionScene::scene());
	
}

void NewScene::closeMenu(CCObject* pSender)
{
	//OutputDebugString(L"Calling...close item menu");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}