#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#define userDefault CCUserDefault::sharedUserDefault()

#include "cocos2d.h"
#include "ZYWebView.h"
#include <string>

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void menuStartGame(CCObject* pSender);
    void menuLeadBorad(CCObject* pSender);
    void timeTicker(float dt);

    char const* getUUID();

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    cocos2d::CCSprite *spTitle;
    cocos2d::CCSprite *spBox;
private:
    ZYWebView* m_webView;
};

#endif // __HELLOWORLD_SCENE_H__
