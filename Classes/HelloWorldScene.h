#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
class HelloWorld : public cocos2d::CCLayer
{
public:
	
	cocos2d::CCSprite *g_ball; // global ball
	cocos2d::CCSprite *g_panel; //global panel
	cocos2d::CCSprite *g_left; // below shows the border of the game
	cocos2d::CCSprite *g_right;
	cocos2d::CCSprite *g_bottom;
	cocos2d::CCSprite *g_top;

	cocos2d::CCLabelTTF *score;
	cocos2d::CCMenu* optionsMenu;
	cocos2d::CCMenu* pMenu;
	cocos2d::CCMenu* music;
	cocos2d::CCMenu* music2;
	cocos2d::CCMenu* extra;
	cocos2d::CCMenu* extra2;
	cocos2d::CCMenu* pause;
	cocos2d::CCMenu* back;
	cocos2d::CCMenu* close;
	cocos2d::CCMenu* resume;
	cocos2d::CCMenu* rightMenu;
	cocos2d::CCMenu* leftMenu;

	cocos2d::CCSprite *banner;
	cocos2d::CCSprite *banner2;
	cocos2d::CCSprite *banner3;
	cocos2d::CCMenuItemImage *g_options;

	//My own methods
	void setMusic(int setting);
	void firstScreen();
	void moveBall(float x, float y);
	void spriteMoveFinished(CCNode* sender);
	void updateGame(float dt);
	void debug(int type);
	void updateScore();
	void create_Menu();
	void init_Menu();


	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void registerWithTouchDispatcher();
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event); // for the panel movement
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	//My own callback
	void PG_callback(CCObject* pSender);
	void options_callback(CCObject* Sender);
	void back_callback(CCObject* Sender);
	void music_callback(CCObject* Sender);
	void music_callback2(CCObject* Sender);
	void extra_callback(CCObject* Sender);
	void extra_callback2(CCObject* Sender);
	void pause_callback(CCObject* Sender);
	void resume_callback(CCObject* Sender);
	void left_callback(CCObject* Sender);
	void right_callback(CCObject* Sender);
	void moveBy();
	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);

protected:
	cocos2d::CCArray *_targets;
	cocos2d::CCArray *_projectiles;
	int _projectilesDestroyed;
	void addTarget();



};

#endif // __HELLOWORLD_SCENE_H__
