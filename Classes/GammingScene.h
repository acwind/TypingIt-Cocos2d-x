#ifndef __GAMMING_SCENE_H__
#define __GAMMING_SCENE_H__
#define HEIGHT_FIX  50
#define MAX_LIFE    10
#define LIFE_BAR_POSITION 200
#define GAME_PAUSE 200
#define userDefault CCUserDefault::sharedUserDefault()
#define GAME_VER 1.0

#include <list>
#include <string>
#include "cocos2d.h"
#include "TouchableSprite.h"
#include "VirtualClassC.h"
#include "md5.h"

using namespace std;

class Gamming : public VirtualClassC, public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(Gamming);
    cocos2d::CCSprite *spGameOverBack;
    cocos2d::CCSprite *spGameOver;
    
    cocos2d::CCSprite *spRight;
    cocos2d::CCLabelTTF *lblRight;
    cocos2d::CCSprite *spFalse;
    cocos2d::CCLabelTTF *lblFalse;
    cocos2d::CCSprite *spSpeed;
    cocos2d::CCLabelTTF *lblSpeed;
    cocos2d::CCLabelTTF *lblScore;
    
    TouchableSprite *spPause;
    cocos2d::CCSprite *spLife;
    
    cocos2d::CCSprite *spHurryup;
    cocos2d::CCSprite *spFishRight;
    cocos2d::CCSprite *spFishFalse;
    cocos2d::CCSprite *spFishWait;
    
    cocos2d::CCMenu *menuGamePause;
    cocos2d::CCMenu *menuGameOver;

    cocos2d::CCArray *keyboards;
    cocos2d::CCArray *lbls;
    cocos2d::CCArray *Yanyus;
    cocos2d::CCArray *lblWords;
    cocos2d::CCString *currentWords;

    int rightCount;
    int falseCount;
    int lifes;
    int typeSpeed;
    bool isGamePause;
    int wordPosition;
    int startTime;
    int p;
    

    void initInterface();
    void initYanyus();

    void addButton(int tagId, float x, float y, int index);
    void createGameMenu();
    void gameResume(CCObject* pSender);
    void gameRestart(CCObject* pSender);
    void gameExit(CCObject* pSender);
    void gameOver();

    // virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    // virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    // virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    virtual void registerWithTouchDispatcher(void);

    void timeTicker(float dt);
    void makeAWords();
    void changeKeyboardSet(int times);
    void actionTypeRight();
    void actionTypeWrong();
    void addLife(int life);
    void reduceLife();
    void hideFish();

    void submitScore(int score);
    void onHttpRequestCompleted();

    virtual void spriteClicked(int tagId);
};

#endif // __GAMMING_SCENE_H__
