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

#include "HelloWorldScene.h"
#include "OptionScene.h"
#include "NewScene.h"
using namespace cocos2d;
extern int hours;
int music_opt_2;

CCScene* OptionScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	OptionScene *layer = OptionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool OptionScene::init()
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
	CCLog("HOURS: %d", hours);
	CCLOG("framesize : %f, %f", frameSize.width, frameSize.height);
	float scaleXfactor = frameSize.width / 2054;
	float scaleYfactor = frameSize.height / 1536;

	CCMenuItemImage *back_item = CCMenuItemImage::create(
		"back.png",
		"back.png",
		this,
		menu_selector(OptionScene::back_callback));
	back_item->setScaleX(scaleXfactor);
	back_item->setScaleY(scaleYfactor);
	back_item->setPosition(ccp(visibleSize.width / 2 + back_item->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + back_item->getContentSize().height*scaleYfactor / 2));

	// create menu, it's an autorelease object
	back = CCMenu::create(back_item, NULL);
	back->setPosition(CCPointZero);
	this->addChild(back, 2);


	CCMenuItemImage *music_item = CCMenuItemImage::create(
		"music_on.png",
		"music_on.png",
		this,
		menu_selector(OptionScene::music_callback));
	music_item->setScaleX(scaleXfactor);
	music_item->setScaleY(scaleYfactor);
	music_item->setPosition(ccp(visibleSize.width / 2 + back_item->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + back_item->getContentSize().height*scaleYfactor / 2 - back_item->getContentSize().height*scaleYfactor));

	// create menu, it's an autorelease object
	music = CCMenu::create(music_item, NULL);
	music->setPosition(CCPointZero);
	this->addChild(music, 2);


	CCMenuItemImage *music_item2 = CCMenuItemImage::create(
		"music_off.png",
		"music_off.png",
		this,
		menu_selector(OptionScene::music_callback2));
	music_item2->setScaleX(scaleXfactor);
	music_item2->setScaleY(scaleYfactor);
	music_item2->setPosition(ccp(visibleSize.width / 2 + back_item->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + back_item->getContentSize().height*scaleYfactor / 2 - back_item->getContentSize().height*scaleYfactor));

	// create menu, it's an autorelease object
	music2 = CCMenu::create(music_item2, NULL);
	music2->setPosition(CCPointZero);
	this->addChild(music2, 2);

	int music_opt = 0;

	if (hours == 0)
	{
		music2->setVisible(false);
	}
	else music2->setVisible(true);

	return true;
}
void OptionScene::music_callback(CCObject *pSender){
	
	//OutputDebugString(L"music 1  called");
	music2->setVisible(true);
	music->setVisible(false);
	music_opt_2 = 1;
	CCLog("music:%d", music_opt_2);
	hours = 1;

}

void OptionScene::music_callback2(CCObject *pSender){
	//OutputDebugString(L"music 2 called");
	music2->setVisible(false);
	music->setVisible(true);
	music_opt_2 = 0;
	CCLog("music:%d", music_opt_2);
	hours = 0;

}

void OptionScene::back_callback(CCObject *pSender){

	NewScene *setMusic = NewScene::create();
	
	CCDirector::sharedDirector()->replaceScene(setMusic->scene());
	setMusic->setMusicNS(999);
}