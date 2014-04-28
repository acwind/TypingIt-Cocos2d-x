#include "HelloWorldScene.h"
#include "GammingScene.h"

USING_NS_CC;



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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    // CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // // position the label on the center of the screen
    // pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //                         origin.y + visibleSize.height - pLabel->getContentSize().height));

    // // add the label as a child to this layer
    // this->addChild(pLabel, 1);

    // // add "HelloWorld" splash screen"
    // CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // // position the sprite on the center of the screen
    // pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // // add the sprite as a child to this layer
    // this->addChild(pSprite, 0);    

    CCSprite *sp;
    sp = CCSprite::create("back.png");
    sp->setAnchorPoint(ccp(0.5, 0.5));
    sp->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sp, 0); 
    
    
    spTitle = CCSprite::create("title.png");
    spTitle->setPosition(ccp(visibleSize.width/2, visibleSize.height/2 + 300));
    this->addChild(spTitle, 0); 

    CCSprite *spBox;
    spBox = CCSprite::create("box.png");
    spBox->setPosition(ccp(visibleSize.width/2, 200));
    this->addChild(spBox, 0);

    CCMenuItemFont *menuNewGame;
    CCMenuItemFont *menuOption;
    CCMenuItemFont *menuHelp;

    menuNewGame = CCMenuItemFont::create("开始游戏", this, menu_selector(HelloWorld::menuStartGame));
    menuOption = CCMenuItemFont::create("游戏帮助", this, menu_selector(HelloWorld::menuStartGame));
    menuHelp = CCMenuItemFont::create("达人排行", this, menu_selector(HelloWorld::menuStartGame));
    CCMenu *menu = CCMenu::create(menuNewGame, menuOption, menuHelp, NULL);
    menu->alignItemsVerticallyWithPadding(15);

    this->addChild(menu, 0);


    this->schedule(schedule_selector(HelloWorld::timeTicker), 1);
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::menuStartGame(CCObject* pSender) {
    CCScene *sc = Gamming::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.2f, sc, kCCTransitionOrientationLeftOver));
    // [sc addChild:[Gamming node]];
    // [[CCDirector sharedDirector] replaceScene:[CCTransitionFlipX transitionWithDuration:1.2f scene:sc]];
}

void HelloWorld::timeTicker(float dt) {
    CCScaleBy *s1 = CCScaleBy::create(0.5f, 1.1f);
    CCScaleBy *s2 = CCScaleBy::create(0.5f, 1/1.1f);
    CCRotateBy *r = CCRotateBy::create(1, 60);
    spTitle->runAction(CCSequence::createWithTwoActions(s1, s2));
    // spBox->runAction(CCSequence::create(r, NULL));
}
