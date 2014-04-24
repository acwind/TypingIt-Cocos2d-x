#ifndef __GAMMING_SCENE_H__
#define __GAMMING_SCENE_H__
#define HEIGHT_FIX  50
#define MAX_LIFE    25
#define LIFE_BAR_POSITION 125
#define GAME_PAUSE 200

#include <list>
#include <string>
#include "cocos2d.h"
#include "TouchableSprite.h"

using namespace std;

class Gamming : public cocos2d::CCLayer
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
    

    void initInterface();
    void initYanyus();

    void addButton(int tagId, float x, float y, int index);
    void createGameMenu();
    void gameResume(CCObject* pSender);
    void gameRestart(CCObject* pSender);
    void gameExit(CCObject* pSender);

    void timeTicker(float dt);
    void makeAWords();
};

#endif // __GAMMING_SCENE_H__
