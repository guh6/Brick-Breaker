#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
#include "HomeScene.h"
USING_NS_CC;
int hours2;

using namespace cocos2d;
int reverse = 0; // 0 = postive y, 1  = negative y( going down) 
int x_reverse = 0;
int extra_opt = 1;
CCSprite *g_ball; // global ball
CCSprite *g_panel; //global panel
CCSprite *g_left; // below shows the border of the game
CCSprite *g_right;
CCSprite *g_bottom;
CCSprite *g_top;
int g_score = 0;
CCLabelTTF *score;
CCMenu* optionsMenu;
CCMenu* pMenu;
CCMenu* music;
CCMenu* music2;

CCMenu* back;

CCMenu* resume;
int if_resume = 0;
int music_opt;
CCSprite *banner;
CCSprite *banner2;
CCSprite *banner3;
CCMenuItemImage *g_options;
float current_delta_x = 10;
float current_delta_y = 50;
float scaleXfactor;
float scaleYfactor;
int last_hit = -1; // 0 - top, 1 - left- 2 - right, 3 - paddle
float current_x, current_y;

void HelloWorld::setMusic(int x){
	music_opt = hours2;
	CCLog("Music is now: %d", music_opt);
}

void HelloWorld::addTarget()
{

	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	//(i*target->getContentSize().width*scaleXfactor) = brick offset for the horizontal
	for (int i = 1; i < 6; i++){
		CCSprite *target = CCSprite::create("brick.png");
		target->setScaleX(scaleXfactor);
		target->setScaleY(scaleYfactor);
		target->setPosition(ccp(winSize.width / 5 + (i*target->getContentSize().width*scaleXfactor), winSize.height / 2));
		this->addChild(target, 1);
		target->setTag(1);
		_targets->addObject(target);
	}


	for (int i = 1; i < 6; i++){
		CCSprite *target = CCSprite::create("brick.png");
		target->setScaleX(scaleXfactor);
		target->setScaleY(scaleYfactor);
		target->setPosition(ccp((target->getContentSize().width*scaleXfactor*i) + 50, winSize.height / 2 + target->getContentSize().height*scaleYfactor + 10));
		this->addChild(target, 1);
		target->setTag(1);
		_targets->addObject(target);
	}

}

void HelloWorld::init_Menu(){


	this->removeChild(g_ball, true);
	this->removeChild(g_panel, true);
	this->removeChild(g_top, true);
	this->removeChild(g_bottom, true);
	this->removeChild(g_right, true);
	this->removeChild(g_left, true);

	CCObject* jt = NULL;
	if (_targets->count() > 0){
		CCARRAY_FOREACH(_targets, jt)
		{
			CCSprite *abrick = dynamic_cast<CCSprite*>(jt);
			this->removeChild(abrick);
		}
		_targets->removeAllObjects();
	}

	resume->setVisible(false);
	pMenu->setVisible(true);
	optionsMenu->setVisible(true);
	music->setVisible(false);
	music2->setVisible(false);
	back->setVisible(false);
	pause->setVisible(false);
	banner->setVisible(false);
	banner2->setVisible(false);
	if (if_resume == 1) {
		resume->setVisible(true);
		close->setVisible(true);
	};


}
void HelloWorld::create_Menu(){

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	////OutputDebugString(L"I'm in new menu");

	CCMenuItemImage *play = CCMenuItemImage::create(
		"play.png",
		"play.png",
		this,
		menu_selector(HelloWorld::PG_callback));
	play->setOpacity(255);
	play->setScaleX(scaleXfactor);
	play->setScaleY(scaleYfactor);
	//play->setPosition(ccp(visibleSize.width / 2 + play->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + play->getContentSize().height*scaleYfactor / 2));
	//play->setPosition(ccp(visibleSize.width / 2 + (play->getContentSize().width*scaleXfactor*scaleXfactor) / 2, visibleSize.height / 2 + (play->getContentSize().height*scaleYfactor*scaleYfactor) / 2));
	play->setPosition(ccp(visibleSize.width / 2 + (play->getContentSize().width*scaleXfactor) / 2, visibleSize.height / 2 + (play->getContentSize().height*scaleYfactor) / 2));

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(play, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);






	CCMenuItemImage *options = CCMenuItemImage::create(
		"options.png",
		"options.png",
		this,
		menu_selector(HelloWorld::options_callback));
	options->setScaleX(scaleXfactor);
	options->setScaleY(scaleYfactor);
	options->setPosition(ccp(visibleSize.width / 2 + options->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + options->getContentSize().height*scaleYfactor / 2 - play->getContentSize().height*scaleYfactor));

	// create menu, it's an autorelease object
	optionsMenu = CCMenu::create(options, NULL);
	optionsMenu->setPosition(CCPointZero);
	this->addChild(optionsMenu, 2);
	g_options = options;




	CCMenuItemImage *back_item = CCMenuItemImage::create(
		"back.png",
		"back.png",
		this,
		menu_selector(HelloWorld::back_callback));
	back_item->setScaleX(scaleXfactor);
	back_item->setScaleY(scaleYfactor);
	back_item->setPosition(ccp(visibleSize.width / 2 + play->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + play->getContentSize().height*scaleYfactor / 2));

	// create menu, it's an autorelease object
	back = CCMenu::create(back_item, NULL);
	back->setPosition(CCPointZero);
	this->addChild(back, 2);


	CCMenuItemImage *music_item = CCMenuItemImage::create(
		"music_on.png",
		"music_on.png",
		this,
		menu_selector(HelloWorld::music_callback));
	music_opt = 0;
	music_item->setScaleX(scaleXfactor);
	music_item->setScaleY(scaleYfactor);
	music_item->setPosition(ccp(visibleSize.width / 2 + options->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + options->getContentSize().height*scaleYfactor / 2 - back_item->getContentSize().height*scaleYfactor));

	// create menu, it's an autorelease object
	music = CCMenu::create(music_item, NULL);
	music->setPosition(CCPointZero);
	this->addChild(music, 2);


	CCMenuItemImage *music_item2 = CCMenuItemImage::create(
		"music_off.png",
		"music_off.png",
		this,
		menu_selector(HelloWorld::music_callback2));
	music_item2->setScaleX(scaleXfactor);
	music_item2->setScaleY(scaleYfactor);
	music_item2->setPosition(ccp(visibleSize.width / 2 + g_options->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + g_options->getContentSize().height*scaleYfactor / 2 - g_options->getContentSize().height*scaleYfactor));

	// create menu, it's an autorelease object
	music2 = CCMenu::create(music_item2, NULL);
	music2->setPosition(CCPointZero);
	this->addChild(music2, 2);

	CCMenuItemImage *extra_item = CCMenuItemImage::create(
		"extra_on.png",
		"extra_on.png",
		this,
		menu_selector(HelloWorld::extra_callback));
	extra = 0;
	extra_item->setScaleX(scaleXfactor);
	extra_item->setScaleY(scaleYfactor);
	extra_item->setPosition(ccp(visibleSize.width / 2 + options->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + options->getContentSize().height*scaleYfactor / 2 - back_item->getContentSize().height*scaleYfactor*2));

	// create menu, it's an autorelease object
	extra = CCMenu::create(extra_item, NULL);
	extra->setPosition(CCPointZero);
	this->addChild(extra, 2);


	CCMenuItemImage *extra_item2 = CCMenuItemImage::create(
		"extra_off.png",
		"extra_off.png",
		this,
		menu_selector(HelloWorld::extra_callback2));
	extra_item2->setScaleX(scaleXfactor);
	extra_item2->setScaleY(scaleYfactor);
	extra_item2->setPosition(ccp(visibleSize.width / 2 + g_options->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + g_options->getContentSize().height*scaleYfactor / 2 - g_options->getContentSize().height*scaleYfactor*2));

	// create menu, it's an autorelease object
	extra2 = CCMenu::create(extra_item2, NULL);
	extra2->setPosition(CCPointZero);
	this->addChild(extra2, 2);

	extra->setVisible(false);
	extra2->setVisible(false);


	CCMenuItemImage *pauseItem = CCMenuItemImage::create(
		"pause.png",
		"pause.png",
		this,
		menu_selector(HelloWorld::pause_callback));
	pauseItem->setOpacity(255);
	pauseItem->setScaleX(scaleXfactor);
	pauseItem->setScaleY(scaleYfactor);
	pauseItem->setPosition(ccp(origin.x + visibleSize.width - pauseItem->getContentSize().width*scaleXfactor / 2,
		origin.y + visibleSize.height - pauseItem->getContentSize().height*scaleYfactor / 2));

	// create menu, it's an autorelease object
	pause = CCMenu::create(pauseItem, NULL);
	pause->setPosition(CCPointZero);

	this->addChild(pause, 2);


	CCMenuItemImage *resumeItem = CCMenuItemImage::create(
		"resume.png",
		"resume.png",
		this,
		menu_selector(HelloWorld::resume_callback));
	resumeItem->setScaleX(scaleXfactor);
	resumeItem->setScaleY(scaleYfactor);
	resumeItem->setPosition(ccp(visibleSize.width / 2 + options->getContentSize().width*scaleXfactor / 2, visibleSize.height / 2 + options->getContentSize().height*scaleYfactor / 2 - play->getContentSize().height*scaleYfactor * 2));


	// create menu, it's an autorelease object
	resume = CCMenu::create(resumeItem, NULL);
	resume->setPosition(CCPointZero);
	this->addChild(resume, 2);
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setScaleX(scaleXfactor);
	pCloseItem->setScaleY(scaleYfactor);
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width*scaleXfactor / 2,
		origin.y + pCloseItem->getContentSize().height*scaleYfactor / 2));

	// create menu, it's an autorelease object
	close = CCMenu::create(pCloseItem, NULL);
	close->setPosition(CCPointZero);
	this->addChild(close, 2);

	banner = CCSprite::create("Blank.png");
	banner->setScaleX(scaleXfactor);
	banner->setScaleY(scaleYfactor);
	banner->setPosition(ccp(origin.x + visibleSize.width / 2, visibleSize.height / 2 + resumeItem->getContentSize().height*scaleYfactor * 2));
	this->addChild(banner, 3);

	banner2 = CCSprite::create("Blank2.png");
	banner2->setScaleX(scaleXfactor);
	banner2->setScaleY(scaleYfactor);
	banner2->setPosition(ccp(origin.x + visibleSize.width / 2, visibleSize.height / 2 + resumeItem->getContentSize().height*scaleYfactor * 2));
	this->addChild(banner2, 3);

	banner3 = CCSprite::create("Blank3.png");
	banner3->setScaleX(scaleXfactor);
	banner3->setScaleY(scaleYfactor);
	banner3->setPosition(ccp(origin.x + visibleSize.width / 2, visibleSize.height / 2 + resumeItem->getContentSize().height*scaleYfactor * 2));
	this->addChild(banner3, 3);




	CCMenuItemImage *left_item = CCMenuItemImage::create(
		"left.png",
		"left.png",
		this,
		menu_selector(HelloWorld::left_callback));
	left_item->setScaleX(scaleXfactor);
	left_item->setScaleY(scaleYfactor);
	left_item->setPosition(ccp(origin.x + left_item->getContentSize().width*scaleXfactor / 2, origin.y + 1 + (left_item->getContentSize().height*scaleYfactor / 2)));

	// create menu, it's an autorelease object
	leftMenu = CCMenu::create(left_item, NULL);
	leftMenu->setPosition(CCPointZero);
	this->addChild(leftMenu, 2);

	CCMenuItemImage *right_item = CCMenuItemImage::create(
		"right.png",
		"right.png",
		this,
		menu_selector(HelloWorld::right_callback));
	right_item->setScaleX(scaleXfactor);
	right_item->setScaleY(scaleYfactor);
	right_item->setPosition(ccp(origin.x + visibleSize.width - right_item->getContentSize().width*scaleXfactor / 2, origin.y + 1 + (right_item->getContentSize().height*scaleYfactor / 2)));

	// create menu, it's an autorelease object
	rightMenu = CCMenu::create(right_item, NULL);
	rightMenu->setPosition(CCPointZero);
	this->addChild(rightMenu, 2);









	leftMenu->setVisible(false);
	rightMenu->setVisible(false);

	back_item->setOpacity(255);
	resumeItem->setOpacity(255);
	close->setOpacity(255);
	options->setOpacity(255);

}


/*
Sets up the game screen.
1. Ball
2. Panel
3. Bricks
4. calls moveBall();
5. Uses layer 1
*/
void HelloWorld::firstScreen(){
	close->setVisible(false);
	resume->setVisible(false);
	pause->setVisible(true);
	pMenu->setVisible(false);
	optionsMenu->setVisible(false);
	this->setTouchEnabled(true);
	//Load the images
	g_ball = CCSprite::create("Ball.png");
	g_panel = CCSprite::create("panel.png");
	g_top = CCSprite::create("top_bottom.png");
	g_bottom = CCSprite::create("top_bottom.png");
	g_right = CCSprite::create("left_right.png");
	g_left = CCSprite::create("left_right.png");
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int ball_width = g_ball->getContentSize().width*scaleXfactor;
	int panel_height = g_panel->getContentSize().height*scaleYfactor;
	float true_panel_height = origin.y + g_panel->getContentSize().height*scaleYfactor / 2;
	//Sets the position of the sprites
	g_ball->setScaleX(scaleXfactor);
	g_ball->setScaleY(scaleYfactor);
	g_ball->setPosition(ccp(visibleSize.width / 2 + origin.x, true_panel_height + (ball_width + 10)));
	g_panel->setPosition(ccp(origin.x + visibleSize.width / 2 - (g_panel->getContentSize().width*scaleXfactor) / 2, origin.y + g_panel->getContentSize().height*scaleYfactor / 2));
	g_panel->setScaleX(scaleXfactor);
	g_panel->setScaleY(scaleYfactor);

	//Adds the sprite to the layout
	this->addChild(g_ball, 1);
	this->addChild(g_panel, 1);


	// use ccp = to create a new CC Point with (x,y);
	addTarget();
	printf("Trying printf");
	CCLog("brick size %d", _targets->count());
	CCLog("winsize: %f,%f ||| visiblesize:%f,%f", winSize.width, winSize.height, visibleSize.width, visibleSize.height);
	CCLog("***Game initialized.");
	//moveBall(visibleSize.width / 2 + g_ball->getContentSize().width*scaleXfactor / 2 + 50, visibleSize.height);
	current_x = visibleSize.width / 2 + origin.x;
	current_y = (ball_width / 2) + (panel_height + 5);

}
// cpp with cocos2d-x
void HelloWorld::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	//this->removeChild(g_panel, true); // Debug uses
	//OutputDebugString(L"In movedFinished");
	//Sleep(100);
	//moveBall(210, 320);
}

/*
This method is for the touch. Whenever it is touched left or right, the panel is moved in the x. Y is constant.
*/
void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gets the visible size of the frame
	this->setTouchEnabled(true);
	// Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocation(); // location of the touch
	CCPoint panel_location = g_panel->getPosition(); // location of the current panel
	location = CCDirector::sharedDirector()->convertToGL(location);
	CCLog("Touched after  x:%f, y:%f", location.x, location.y);
	// Set up initial location of projectile
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	float moveX = location.x;
	if (location.x < 0){

		moveX = 0 + g_panel->getContentSize().width*scaleXfactor / 2;

	}
	else if (location.x > visibleSize.width){

		moveX = visibleSize.width;
	}

	else{
		float moveX = location.x;

	}
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	float moveY = origin.y + g_panel->getContentSize().height*scaleYfactor / 2;

	float real_distance = abs(panel_location.x - location.x); //Trying to get real distance of the click and the current panel
	float duration = real_distance / 500; // trying to get the ratio of the time
	//Below moves the panel
	CCFiniteTimeAction* actionMove =
		CCMoveTo::create(duration,
		ccp(moveX, moveY));
	CCFiniteTimeAction* actionMoveDone =
		CCCallFuncN::create(this,
		NULL);
	g_panel->runAction(CCSequence::create(actionMove,
		actionMoveDone, NULL));
}

double Distance(float dX0, float dY0, float dX1, float dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}
void HelloWorld::moveBall(float x, float y){

	CCPoint g_ball_pos = g_ball->getPosition();

	// Create the actions
	float duration = Distance(g_ball_pos.x, g_ball_pos.y, x, y) / 100; // time it takes to move

	//CCLog("Current BALL POS  x:%f, y:%f====", g_ball_pos.x, g_ball_pos.y);


	CCFiniteTimeAction* actionMove = CCMoveTo::create(duration, ccp(x, y));
	g_ball->runAction(actionMove);
	//CCLog("Moving ball to  x:%f, y:%f", x, y);


}

void HelloWorld::moveBy(){

	float duration = 200;

	if ((int)current_delta_x == 0 && (int)current_delta_y == 0){
		current_delta_x = current_delta_x + 5;
		current_delta_y = current_delta_y + -5;
	}
	else{

	}

	//CCLog("Moving ball at delta  x:%f, y:%f", current_delta_x, current_delta_y);
	CCFiniteTimeAction* actionMove = CCMoveBy::create(100, ccp(current_delta_x, current_delta_y));
	g_ball->runAction(actionMove);

}


//this is like constructor that creates automatically the first scene.
//scene is the parent that holds all
//returns CCScene* as a pointer so that the class itself can add to it!
CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	// Initialize arrays
	_targets = new CCArray;
	_projectiles = new CCArray;


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCLOG("framesize : %f, %f", frameSize.width, frameSize.height);
	

	
	scaleXfactor = frameSize.width / 2054;
	scaleYfactor = frameSize.height / 1536;

	scaleXfactor = .7;
	scaleYfactor = .5;

	create_Menu();

	init_Menu();
	CCLog("****hours2 %d", hours2);

	setMusic(hours2);
	CCObject *temp = NULL;
	PG_callback(temp);






	return true;
}

void HelloWorld::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void HelloWorld::updateScore(){

	if (score == NULL){

	}
	else{
		this->removeChild(score, true);

	}

	char str[10];
	sprintf(str, "%d", g_score);
	char str2[20];
	strcpy(str2, "Score: ");
	strcat(str2, str);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	score = CCLabelTTF::create(str2, "Arial", TITLE_FONT_SIZE);

	// position the label on the center of the screen
	score->setPosition(ccp(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - score->getContentSize().height*scaleYfactor));

	// add the label as a child to this layer
	this->addChild(score, 1);
}

void HelloWorld::updateGame(float dt)
{
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	if (last_hit == -5){

	}
	else{
		CCArray *projectilesToDelete = new CCArray;
		CCObject* panel = NULL;
		CCObject* ball = NULL;
		//this->removeChild(g_panel,true); // debug
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gets the visible size of the frame
		CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

		CCSprite *projectile = dynamic_cast<CCSprite*>(g_ball); // ball
		CCRect projectileRect = CCRectMake(
			projectile->getPosition().x - (projectile->boundingBox().size.width/ 2),
			projectile->getPosition().y - (projectile->boundingBox().size.height / 2),
			projectile->boundingBox().size.width,
			projectile->boundingBox().size.height);


		CCSprite *target = dynamic_cast<CCSprite*>(g_panel); // panel
		CCRect targetRect = CCRectMake(
			target->getPosition().x - (target->boundingBox().size.width / 2),
			target->getPosition().y - (target->boundingBox().size.height / 2),
			target->boundingBox().size.width,
			target->boundingBox().size.height);



		CCPoint g_ball_pos = g_ball->getPosition();

		//last_hit = 0; 0 - top, 1 - left- 2 - right, 3 - paddle


		if (_targets->count() == 0){

			CCLog("User has won!");
			banner->setVisible(true);
			pMenu->setVisible(true);
			pause->setVisible(false);
			last_hit = -5;
			this->setTouchEnabled(false);

		}





		if (projectileRect.intersectsRect(targetRect))
		{

			CCLog("\nPaddle hit!");		//Sleep(500);
			if (last_hit == 3){
				CCLog("\nARGH!!!");		//Sleep(1000);

			}
			else{
				g_ball->cleanup();
				Sleep(1000);
				if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("paddle.wav");
				float x1, x2, x3, y1, y2, y3;

				x1 = current_x;
				y1 = current_y;

				x2 = g_ball_pos.x;
				y2 = g_ball_pos.y;

				float delta_x, delta_y;

				delta_x = x2 - x1;
				delta_y = y2 - y1;

				x3 = x2 + delta_x;
				y3 = y2 + (-delta_y);

				CCLog("x1:%f y1:%f || x2:%f y2:%f || x3:%f y3:%f", x1, y1, x2, y2, x3, y3);

				current_x = x2;
				current_y = y2;


				current_delta_x = delta_x;
				current_delta_y = (-delta_y);
				last_hit = 3;
			}
		}

		if (g_ball_pos.y > visibleSize.height - (g_ball->boundingBox().size.width/ 2)){ // top and ball
			CCLog("\nTop hit!");		//Sleep(1000);
			if (last_hit == 0){
				CCLog("\nARGH!!!");		//Sleep(1000);

			}
			else{
				if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("paddle.wav");
				g_ball->cleanup();
				float x1, x2, x3, y1, y2, y3;
				x1 = current_x;
				y1 = current_y;
				x2 = g_ball_pos.x;
				y2 = g_ball_pos.y;
				float delta_x, delta_y;
				delta_x = x2 - x1;
				delta_y = y2 - y1;

				x3 = x2 + delta_x * 5;
				y3 = y2 + (-delta_y) * 5;

				CCLog("x1:%f y1:%f || x2:%f y2:%f || x3:%f y3:%f", x1, y1, x2, y2, x3, y3);

				current_x = x2;
				current_y = y2;
				last_hit = 0;



				current_delta_x = delta_x;
				current_delta_y = (-delta_y);

			}






		}

		if (g_ball_pos.y < (origin.y)   ){ // balll and bottom
			if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("lost.wav");
			Sleep(1000);
			CCLog("Bottom hitS!");
			last_hit = -5;
			banner2->setVisible(true);
			pause->setVisible(false);
			pMenu->setVisible(true);
			this->setTouchEnabled(false);

		}

		if (g_ball_pos.x - (g_ball->boundingBox().size.width)/2 < origin.x){ // left and ball
			CCLog("\nleft hit!");		//Sleep(1000);
			if (last_hit == 1){
				CCLog("\nARGH!!!");
			}
			else{
				if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("paddle.wav");

				g_ball->cleanup();
				//if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("scifi002.wav");
				float x1, x2, x3, y1, y2, y3;

				x1 = current_x;
				y1 = current_y;

				x2 = g_ball_pos.x;

				y2 = g_ball_pos.y;

				float delta_x, delta_y;

				delta_x = x2 - x1;
				delta_y = y2 - y1;

				x3 = x2 + delta_x;
				y3 = y2 + (-delta_y);

				CCLog("x1:%f y1:%f || x2:%f y2:%f || x3:%f y3:%f", x1, y1, x2, y2, x3, y3);

				current_x = x2;
				current_y = y2;



				current_delta_x = -delta_x;
				current_delta_y = (delta_y);







				last_hit = 1;
			}
		}
	
		if (g_ball_pos.x > visibleSize.width - g_ball->boundingBox().size.width){ // right and ball
			CCLog("\nright hit!");		//Sleep(1000);
			if (last_hit == 2){
				CCLog("\nARGH!!!");
			}
			else{
				if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("paddle.wav");

				g_ball->cleanup();
				//if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("scifi002.wav");
				float x1, x2, x3, y1, y2, y3;

				x1 = current_x;
				y1 = current_y;

				x2 = g_ball_pos.x;
				y2 = g_ball_pos.y;

				float delta_x, delta_y;

				delta_x = x2 - x1;
				delta_y = y2 - y1;

				x3 = x2 + delta_x;
				y3 = y2 + (-delta_y);

				CCLog("x1:%f y1:%f || x2:%f y2:%f || x3:%f y3:%f", x1, y1, x2, y2, x3, y3);

				current_x = x2;
				current_y = y2;


				current_delta_x = -delta_x;
				current_delta_y = (delta_y);






				last_hit = 2;
			}

		}


		//this->removeChild(g_panel, true);
		//Detect collision between ball and brick
		CCObject* jt = NULL;
		CCARRAY_FOREACH(_targets, jt)
		{
				//*FIX THIS THURSDAY
			CCSprite *abrick = dynamic_cast<CCSprite*>(jt);
			CCLog("BEFORE: %f", abrick->getContentSize().width);
			abrick->setScale(scaleXfactor);
			abrick->setScale(scaleYfactor);
			CCLog("after: %f", abrick->boundingBox().size.width);
						
			CCRect abrickRect = CCRectMake(
				abrick->getPosition().x - (abrick->boundingBox().size.width / 2),
				abrick->getPosition().y - (abrick->boundingBox().size.height / 2),
				abrick->boundingBox().size.width,
				abrick->boundingBox().size.height);
			

			if (projectileRect.intersectsRect(abrickRect))
			{

				if (music_opt == 0)CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("scifi002.wav");
				g_ball->cleanup();
				CCLog("Brick hit!");
				//Sleep(1234);
				_projectiles->addObject(abrick);

				this->removeChild(abrick, true);

				abrick->release();
				g_score++;
				updateScore();
				_targets->removeObject(abrick);
				CCLog("brick size %d", _targets->count());
				float x1, x2, x3, y1, y2, y3;




				x1 = current_x;
				y1 = current_y;

				x2 = g_ball_pos.x;
				y2 = g_ball_pos.y;

				float delta_x, delta_y;

				delta_x = x2 - x1;
				delta_y = y2 - y1;

				x3 = x2 + delta_x;
				y3 = y2 + (-delta_y);

				CCLog("x1:%f y1:%f || x2:%f y2:%f || x3:%f y3:%f", x1, y1, x2, y2, x3, y3);

				current_x = x2;
				current_y = y2;
				current_delta_x = delta_x;
				current_delta_y = (-delta_y);
				last_hit = 4;
			}

			if (last_hit != -5){
				if (if_resume == 1){
					//CCLog("Pausing");
				}
				else{
					moveBy();
				}
			}
			else{

			}

		}
	}
}


void HelloWorld::PG_callback(CCObject *pSender){
	CCLog("%d", music_opt);
	banner3->setVisible(false);
	g_score = 0;
	last_hit = -1;
	updateScore();
	current_delta_x = 10;
	current_delta_y = 50;
	this->removeChild(g_ball, true);
	this->removeChild(g_panel, true);
	CCObject* jt = NULL;
	CCARRAY_FOREACH(_targets, jt)
	{
		CCSprite *abrick = dynamic_cast<CCSprite*>(jt);
		this->removeChild(abrick);
	}
	_targets->removeAllObjects();
	//OutputDebugString(L"PG called");
	this->schedule(schedule_selector(HelloWorld::updateGame));
	firstScreen();
	pMenu->setVisible(false);
	optionsMenu->setVisible(false);
	banner->setVisible(false);
	banner2->setVisible(false);
	if_resume = 0;

}

void HelloWorld::music_callback(CCObject *pSender){
	close->setVisible(false);

	//OutputDebugString(L"music 1  called");
	CCLog("music:%d", music_opt);
	music2->setVisible(true);
	music->setVisible(false);
	music_opt = 1;
}

void HelloWorld::music_callback2(CCObject *pSender){
	close->setVisible(false);
	//OutputDebugString(L"music 2 called");
	CCLog("music:%d", music_opt);
	music2->setVisible(false);
	music->setVisible(true);
	music_opt = 0;

}


void HelloWorld::extra_callback(CCObject *pSender){
	close->setVisible(false);

	//OutputDebugString(L"extra 1  called");
	CCLog("extra:%d", extra_opt);
	extra2->setVisible(true);
	extra->setVisible(false);
	extra_opt = 1;
}

void HelloWorld::extra_callback2(CCObject *pSender){
	close->setVisible(false);
	//OutputDebugString(L"extra 2 called");
	CCLog("extra:%d", extra_opt);
	extra2->setVisible(false);
	extra->setVisible(true);
	extra_opt = 0;

}
void HelloWorld::back_callback(CCObject *pSender){
	//OutputDebugString(L"back called");
	pMenu->setVisible(true);
	optionsMenu->setVisible(true);
	music->setVisible(false);
	music2->setVisible(false);
	back->setVisible(false);
	extra->setVisible(false);
	extra2->setVisible(false);
	if (if_resume == 1) 	{
		resume->setVisible(true);
		close->setVisible(true);
	};


}
void HelloWorld::pause_callback(CCObject *pSender){
	//OutputDebugString(L"pause called");
	//this->pauseSchedulerAndActions(HelloWorld::updateGame);
	
	
	
	pause->setVisible(false);
	leftMenu->setVisible(false);
	rightMenu->setVisible(false);
	
	pMenu->setVisible(true);
	optionsMenu->setVisible(true);
	resume->setVisible(true);
	close->setVisible(true);
	if_resume = 1;
	//CCNode::pauseSchedulerAndActions();
	//CCNode::resumeSchedulerAndActions();
	g_ball->pauseSchedulerAndActions();

	this->setTouchEnabled(false);

}
void HelloWorld::resume_callback(CCObject *pSender){
	//OutputDebugString(L"resume called");
	
	if (extra_opt == 0){
		leftMenu->setVisible(true);
		rightMenu->setVisible(true);
	}
	else{
		leftMenu->setVisible(false);
		rightMenu->setVisible(false);
	}

	
	extra->setVisible(false);
	extra2->setVisible(false);
	pMenu->setVisible(false);
	optionsMenu->setVisible(false);
	music->setVisible(false);
	music2->setVisible(false);
	back->setVisible(false);
	resume->setVisible(false);
	close->setVisible(false);
	pause->setVisible(true);
	if_resume = 0;
	CCNode::resumeSchedulerAndActions();
	g_ball->resumeSchedulerAndActions();
	this->setTouchEnabled(true);
}
void HelloWorld::options_callback(CCObject *pSender){
	//OutputDebugString(L"options called");
	close->setVisible(false);
	resume->setVisible(false);
	pMenu->setVisible(false);
	if (if_resume == 0) {

	


	}
	else{
	
		//resume->setVisible(true);
	}
	optionsMenu->setVisible(false);
	if (music_opt == 0){
		music2->setVisible(false);
		music->setVisible(true);
	}
	else{
		music->setVisible(false);
		music2->setVisible(true);
	}
	if (extra_opt == 0){
		extra->setVisible(true);
		extra2->setVisible(false);

	}
	else{
		extra->setVisible(false);
		extra2->setVisible(true);

	}


	back->setVisible(true);
}













void HelloWorld::left_callback(CCObject *pSender){

	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	float moveY = origin.y + g_panel->getContentSize().height*scaleYfactor / 2;
	CCPoint panel_location = g_panel->getPosition(); // location of the current panel
	float x = panel_location.x - 50;
	CCFiniteTimeAction* actionMove = CCMoveTo::create(.1, ccp(x, moveY));
	g_panel->runAction(actionMove);

}

void HelloWorld::right_callback(CCObject *pSender){
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	float moveY = origin.y + g_panel->getContentSize().height*scaleYfactor / 2;
	CCPoint panel_location = g_panel->getPosition(); // location of the current panel
	
	float x = panel_location.x + 50;
	CCFiniteTimeAction* actionMove = CCMoveTo::create(.1, ccp(x, moveY));
	g_panel->runAction(actionMove);

}





void HelloWorld::menuCloseCallback(CCObject* pSender)
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
