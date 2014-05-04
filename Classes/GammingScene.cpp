#include "GammingScene.h"
#include "HelloWorldScene.h"
#include "cocos-ext.h"

USING_NS_CC;



CCScene* Gamming::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Gamming *layer = Gamming::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Gamming::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    this->initYanyus();
    this->initInterface();
    this->makeAWords();

    struct cocos2d::cc_timeval now;
    startTime = CCTime::gettimeofdayCocos2d(&now, NULL);
    
    this->schedule(schedule_selector(Gamming::timeTicker), 1);
    return true;
}

void Gamming::initInterface() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    float scale = 1.0f;

    CCSprite *sp = CCSprite::create("gameback.png");
    sp->setAnchorPoint(ccp(0.5, 0.5));
    sp->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sp, -1, 0); 

    spGameOverBack = CCSprite::create("gameback.png");
    spGameOverBack->setAnchorPoint(ccp(0.5, 0.5));
    spGameOverBack->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(spGameOverBack, 20, 0);
    spGameOverBack->setVisible(false);

    spPause = TouchableSprite::touchSpriteWithFile("pause.png");
    spPause->setAnchorPoint(ccp(1, 1));
    spPause->setPosition(ccp(visibleSize.width-5, visibleSize.height-5-65));
    this->addChild(spPause, 2, GAME_PAUSE);
    spPause->setVisible(false);

    spLife = CCSprite::create("life.png");
    spLife->setAnchorPoint(ccp(0.5, 0.5));
    spLife->setPosition(ccp(LIFE_BAR_POSITION, visibleSize.height - (10*scale) - 10 - 65));
    this->addChild(spLife, 10, 0);

    spFishWait = CCSprite::create("fishwait.png");
    spFishWait->setAnchorPoint(ccp(0.5, 0.5));
    spFishWait->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    // spFishWait->setVisible(false);
    this->addChild(spFishWait, 10, 0);

    spFishRight = CCSprite::create("fishright.png");
    spFishRight->setAnchorPoint(ccp(0.5, 0.5));
    spFishRight->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    spFishRight->setVisible(false);
    this->addChild(spFishRight, 10, 0);


    spFishFalse = CCSprite::create("fishfalse.png");
    spFishFalse->setAnchorPoint(ccp(0.5, 0.5));
    spFishFalse->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    spFishFalse->setVisible(false);
    this->addChild(spFishFalse, 10, 0);

    spHurryup = CCSprite::create("hurry.png");
    spHurryup->setAnchorPoint(ccp(0.5, 0.5));
    spHurryup->setPosition(ccp(50 + 80*(scale-1), visibleSize.height/2));
    spHurryup->setVisible(false);
    this->addChild(spHurryup, 10, 0);

    keyboards = CCArray::create();
    keyboards->retain();
    lbls = CCArray::create();
    lbls->retain();

    int i = 65;
    int j = 0;
    for (i = 65; i <= 74; i++) {
        this->addButton(i, j*48.0f, 150.0f, 0);
        j++;
    }

    j = 0;
    for (i = 75; i <= 84; i++) {
        this->addButton(i, j*48.0f, 100.0f, 0);
        j++;
    }

    this->addButton(85, 48.0f*0, 50.0f, 0);
    this->addButton(86, 48.0f*1, 50.0f, 0);
    this->addButton(87, 48.0f*2, 50.0f, 0);
    
    this->addButton(88, 48.0f*7, 50.0f, 0);
    this->addButton(89, 48.0f*8, 50.0f, 0);
    this->addButton(90, 48.0f*9, 50.0f, 0);


    TouchableSprite *button = TouchableSprite::touchSpriteWithFile("buttonspace.png");
    button->delegate_ = this;
    this->addChild(button, 10, 32);
    button->tagId = 32;   
    button->setPosition(ccp(48.0f*5,  50.0f + HEIGHT_FIX));
    
    CCLabelTTF *lbl = CCLabelTTF::create("空格", "Thonburi-Bold", 22);
    this->addChild(lbl, 10, 0);
    lbl->setPosition(ccp(48.0f*5,  50.0f + HEIGHT_FIX));
    lbls->addObject(lbl);

    rightCount  = 0;
    falseCount  = 0;
    lifes       = MAX_LIFE;
    typeSpeed   = 0;

    spRight = CCSprite::create("right.png");
    spFalse = CCSprite::create("false.png");
    spSpeed = CCSprite::create("speed.png");

    this->addChild(spRight, 10, 0);
    this->addChild(spFalse, 10, 0);
    this->addChild(spSpeed, 10, 0);

    spRight->setPosition(ccp(20, 253));
    lblRight = CCLabelTTF::create("0", "Arial", 22);
    this->addChild(lblRight, 10, 0);
    lblRight->setPosition(ccp(63, 253));

    spFalse->setPosition(ccp(100, 253));
    lblFalse = CCLabelTTF::create("0", "Arial", 22);
    this->addChild(lblFalse, 10, 0);
    lblFalse->setPosition(ccp(140, 253));

    spSpeed->setPosition(ccp(240, 253));
    lblSpeed = CCLabelTTF::create("0", "Arial", 22);
    this->addChild(lblSpeed, 10, 0);
    lblSpeed->setPosition(ccp(320, 253));

    lblScore = CCLabelTTF::create("本次游戏得分：", "Arial", 30);
    this->addChild(lblScore, 30, 0);
    lblScore->setAnchorPoint(ccp(0.5, 0.5));
    lblScore->setPosition(ccp(visibleSize.width/2, visibleSize.height/2 + 80));
    lblScore->setVisible(false);
    lblScore->setFontFillColor(ccRED);

    this->createGameMenu();
    
    isGamePause = false;

    
}

void Gamming::addButton(int tagId, float x, float y, int index) {
    float scale = 1.0f;
    char word[0];
    sprintf(word, "%c", tagId);
    x = x*scale + 25.0f; 
    y = y*scale + HEIGHT_FIX + 15*(scale-1);
    TouchableSprite *button;
    button = TouchableSprite::touchSpriteWithFile("button1.png");
    button->delegate_ = this;
    button->tagId = tagId;
    this->addChild(button, 9, tagId);
    button->setPosition(ccp(x, y));
    keyboards->addObject(button);

    CCLabelTTF *lbl = CCLabelTTF::create(word, "Thonburi-Bold", 22);
    this->addChild(lbl, 10, tagId);
    lbl->setPosition(ccp(x, y));
    lbls->addObject(lbl);
}

void Gamming::createGameMenu() {
    CCMenuItem *menuResume = CCMenuItemFont::create("继续游戏", this, menu_selector(Gamming::gameResume));
    CCMenuItem *menuRestart = CCMenuItemFont::create("重新开始", this, menu_selector(Gamming::gameRestart));
    CCMenuItem *menuExit = CCMenuItemFont::create("退出", this, menu_selector(Gamming::gameExit));

    menuGamePause = CCMenu::create(menuResume, menuRestart, menuExit, NULL);
    menuGamePause->alignItemsVerticallyWithPadding(15);
    this->addChild(menuGamePause, 30, 2);
    menuGamePause->setVisible(false);

    CCMenuItem *menuRestart2 = CCMenuItemFont::create("重新开始", this, menu_selector(Gamming::gameRestart));
    CCMenuItem *menuExit2 = CCMenuItemFont::create("退出", this, menu_selector(Gamming::gameExit));
    menuGameOver = CCMenu::create(menuRestart, menuExit, NULL);
    menuGameOver->alignItemsVerticallyWithPadding(15);
    this->addChild(menuGameOver, 30, 2);
    menuGameOver->setVisible(false);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    spGameOver = CCSprite::create("gameover.png");
    spGameOver->setPosition(ccp(visibleSize.width/2, 550));
    this->addChild(spGameOver, 30, 0);
    spGameOver->setVisible(false);

}

void Gamming::makeAWords() {
    int count = 18;
    float scale = 1.0f;
    lblWords = CCArray::create();

    for (int i = (lblWords->count() - 1); i >= 0; i--) {
        CCLabelTTF *obj = (CCLabelTTF *)lblWords->objectAtIndex(i);
        this->removeChild(obj, 1);
    }
    int all = Yanyus->count() - 1;
    p = arc4random()%all;
    currentWords = (CCString *)Yanyus->objectAtIndex(p);
    currentWords->retain();
    wordPosition = 0;
    
    for (int i = 0; i < currentWords->length(); i++) {
        const char *words = currentWords->getCString();
        char word[1];
        word[0] = words[i];
        CCLabelTTF *lbl = CCLabelTTF::create(word, "Arial", 35);
        this->addChild(lbl, 10, 0);
        float x = 15 + (i%count)*26.0f;
        float y = 550 - (i/count)*38.0f;
        lbl->setPosition(ccp(x, y));
        lblWords->addObject(lbl);
    }
    lblWords->retain();
}

void Gamming::reduceLife() {
    if (lifes <= 0) {
        return;
    }
    lifes--;
    CCLOG("life left: %d", lifes);
    if (lifes <= 10) {
        spHurryup->setVisible(true);
    } else {
        spHurryup->setVisible(false);
    }
    CCMoveTo *s1 = CCMoveTo::create(1, ccp(LIFE_BAR_POSITION-(40*(MAX_LIFE-lifes)), spLife->getPositionY()));
    spLife->runAction(CCSequence::create(s1, NULL));
    
    


}

void Gamming::timeTicker(float dt) {
    if (isGamePause)
        return;

    if (lifes <= 0) {
        this->submitScore(rightCount);
        this->gameOver();
        return;
    }
    
    if (lifes > 0) {
        this->reduceLife();
    }



    if (rightCount <= 0) {
        lblSpeed->setString("0/分钟");
    } else {
        struct cocos2d::cc_timeval now;
        int nowTime = CCTime::gettimeofdayCocos2d(&now, NULL);
        int interval = nowTime - startTime;
        if (interval == 0) {
            interval = 1;
        }
        
        interval = abs(interval);
        typeSpeed = rightCount*60/interval;

        lblSpeed->setString(CCString::createWithFormat("%d/分", typeSpeed)->getCString());
    }

        
    // [spFishWait runAction:[CCSequence actions:
    //                        [CCScaleBy actionWithDuration:0.4 scale:1.1],
    //                        [CCScaleBy actionWithDuration:0.4 scale:1/1.1],
    //                        nil]];
    
    // [spFishFalse runAction:[CCRotateBy actionWithDuration:1 angle:180]];
    
    // [spFishRight runAction:[CCSequence actions:
    //                        [CCScaleBy actionWithDuration:0.4 scale:1.1],
    //                        [CCScaleBy actionWithDuration:0.4 scale:1/1.1],
    //                        nil]];
    
    // [spHurryup runAction:[CCSequence actions:
    //                        [CCScaleBy actionWithDuration:0.4 scale:1.2],
    //                        [CCScaleBy actionWithDuration:0.4 scale:1/1.2],
    //                        nil]];

}


// void Gamming::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
// {
//     CCLog("ccTouchesBegan");
// }

// void Gamming::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
// {
// }
// void Gamming::ccTouchEnded(CCTouch *touch, CCEvent *event) {
//     CCLOG("Touched CCLayer!!!!");
// }
void Gamming::spriteClicked(int tagId) {
    if (wordPosition  == currentWords->length()) {
        return;
    }
    char word1[1];
    sprintf(word1, "%c", tagId);
    CCString *clickWord = CCString::create(word1);

    char word2[2];
    const char *words = currentWords->getCString();
    memcpy(word2, &words[wordPosition], 1);
    word2[1] = '\0';
    CCString *currentWord = CCString::create(word2);

    CCLOG("1:%s", clickWord->getCString());
    CCLOG("2:%s", currentWord->getCString());

    if ( clickWord->isEqual(currentWord)) {
        // [self createExplosionX:sprite.position.x y:sprite.position.y];
        // [sprite runAction:[CCSequence actions:
        //                    [CCScaleBy actionWithDuration:0.1 scale:1.5],
        //                    [CCScaleBy actionWithDuration:0.1 scale:1/1.5],
        //                    nil]];
    //     [((CCLabelTTF*)[lblWords objectAtIndex:wordPosition]) runAction:[CCSequence actions:
    //                                                                      [CCScaleBy actionWithDuration:0.3 scale:2],
    //                                                                      [CCScaleBy actionWithDuration:0.3 scale:1/2],
    //                                                                      nil]];
        CCLabelTTF *lblWord = (CCLabelTTF *)lblWords->objectAtIndex(wordPosition);
        lblWord->runAction(CCSequence::createWithTwoActions(CCScaleBy::create(0.3, 4), CCScaleBy::create(0.3, 1/4)));
        lblWord->setFontFillColor(ccRED);
        wordPosition++;
        this->changeKeyboardSet(26);
        this->actionTypeRight();
    } else {
        CCLog("NOOOOOOOOOOOOOOOOOOOO");
        this->actionTypeWrong();
    }
    
    
        
    
    //     
    //     [self actionTypeRight];
        
    //     if (wordPosition == ([lblWords count])) {
    //         [self makeAWords];
    //     }
    // } else {
        
    //     [sprite runAction:[CCSequence actions:
    //                        [CCFadeOut actionWithDuration:0.1],
    //                        [CCFadeIn  actionWithDuration:0.1],
    //                        [CCFadeOut actionWithDuration:0.1],
    //                        [CCFadeIn  actionWithDuration:0.1],
    //                        nil]];
    //     [self actionTypeWrong];
    // }
    // CCLOG("SUCCESS!!!!!!!!!!!!!!!!!!!!!!%d", tagId);
}

void Gamming::changeKeyboardSet(int times) {
    int count = lbls->count() - 1;
    for (int i = 0; i < times; i++) {
        int leftIndex  = 0;
        int rightIndex = 0;
        while (leftIndex == rightIndex) {
            leftIndex  = arc4random()%count;
            rightIndex = arc4random()%count;
        }
        TouchableSprite *sprite1 = (TouchableSprite *)keyboards->objectAtIndex(leftIndex);
        TouchableSprite *sprite2 = (TouchableSprite *)keyboards->objectAtIndex(rightIndex);
        int tag1 = sprite1->tagId;
        sprite1->tagId = sprite2->tagId;
        sprite2->tagId = tag1;
        
        CCLabelTTF *lbl1 = (CCLabelTTF *)lbls->objectAtIndex(leftIndex);
        CCLabelTTF *lbl2 = (CCLabelTTF *)lbls->objectAtIndex(rightIndex);
        tag1 = lbl1->getTag();
        char letter[1];
        sprintf(letter, "%c", lbl1->getTag());
        char letter2 [1];
        sprintf(letter2, "%c", lbl2->getTag());

        lbl1->setTag(lbl2->getTag());
        lbl1->setString(letter2);
        lbl1->setFontFillColor(ccWHITE);
        lbl2->setTag(tag1);
        lbl1->setVisible(true);
        lbl2->setString(letter);
        lbl2->setFontFillColor(ccWHITE); 
    }
}


void Gamming::actionTypeRight(){
    rightCount++;
    char word[6];
    sprintf(word, "%d", rightCount);
    lblRight->setString(word);
    this->addLife(2);
    this->hideFish();
    spFishRight->setVisible(true);
    
}


void Gamming::actionTypeWrong(){
    falseCount++;
    char word[6];
    sprintf(word, "%d", falseCount);
    lblFalse->setString(word); 
    this->reduceLife(); 
    
    this->hideFish();
    spFishFalse->setVisible(true);
}

void Gamming::addLife(int life) {
    lifes += life;
    if (lifes > MAX_LIFE) {
        lifes = MAX_LIFE;
    }
    
    CCMoveTo *s1 = CCMoveTo::create(1, ccp(LIFE_BAR_POSITION-(40*(MAX_LIFE-lifes)), spLife->getPositionY()));
    spLife->runAction(CCSequence::create(s1, NULL));
}



void Gamming::hideFish() {
    spFishWait->setVisible(false);
    spFishRight->setVisible(false);
    spFishFalse->setVisible(false);
}

void Gamming::registerWithTouchDispatcher(void) {
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    // CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
void Gamming::gameResume(CCObject* pSender) {

}

void Gamming::gameRestart(CCObject* pSender) {
    spLife->setVisible(false);
    CCScene *sc = Gamming::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.2f, sc, kCCTransitionOrientationLeftOver));
}

void Gamming::gameExit(CCObject* pSender) {
    CCScene *sc = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.2f, sc, kCCTransitionOrientationLeftOver));
}

void Gamming::gameOver() {
    isGamePause = true;
    spPause->setVisible(false);
    spLife->setVisible(false);

    spGameOverBack->setVisible(true);
    spGameOver->setVisible(true);
    lblScore->setVisible(true);
    menuGameOver->setVisible(true);

    lblScore->setString(CCString::createWithFormat("本次游戏得分：%d", rightCount)->getCString());

}

void Gamming::submitScore(int score) {
    int highScore = userDefault->getIntegerForKey("high_score", 0);
    if (rightCount <= highScore)
        return;
    userDefault->setIntegerForKey("high_score", rightCount);

    cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
    request->setUrl("http://game.acwind.net/index.php/typing/submitscore");
    request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(Gamming::onHttpRequestCompleted));

    // write the post data
    char authString[200];
    sprintf(authString, "%d%sfuckthief", rightCount, (userDefault->getStringForKey("uid")).c_str());
    std::string strTmp(authString);
    std::string auth = md5(strTmp);
    char postData[200];// = "ver=1.0&auth=&uid=&score=";
    sprintf(postData, "ver=1.0&auth=%s&uid=%s&score=%d", auth.c_str(), (userDefault->getStringForKey("uid")).c_str(), rightCount);
    request->setRequestData(postData, strlen(postData));
    CCLOG("%s", postData);
    request->setTag("POST test1");
    cocos2d::extension::CCHttpClient::getInstance()->send(request);
    request->release();
}

void Gamming::onHttpRequestCompleted() {

}


void Gamming::initYanyus() {
    Yanyus = CCArray::create();
    Yanyus->addObject(CCString::create("xxx"));
    Yanyus->addObject(CCString::create("A BAD BEGINNING MAKES A BAD ENDING"));
    Yanyus->addObject(CCString::create("A BAD THING NEVER DIES"));
    Yanyus->addObject(CCString::create("A BAD WORKMAN ALWAYS BLAMES HIS TOOLS"));
    Yanyus->addObject(CCString::create("A BOASTER AND A LIAR ARE COUSINS-GERMAN"));
    Yanyus->addObject(CCString::create("A BULLY IS ALWAYS A COWARD"));
    Yanyus->addObject(CCString::create("A CANDLE LIGHTS OTHERS AND CONSUMES ITSELF"));
    Yanyus->addObject(CCString::create("A CAT HAS 9 LIVES"));
    Yanyus->addObject(CCString::create("A CAT MAY LOOK AT A KING"));
    Yanyus->addObject(CCString::create("A CLOSE MOUTH CATCHES NO FLIES"));
    Yanyus->addObject(CCString::create("A CONSTANT GUEST IS NEVER WELCOME"));
    Yanyus->addObject(CCString::create("ACTIONS SPEAK LOUDER THAN WORDS"));
    Yanyus->addObject(CCString::create("ADVERSITY LEADS TO PROSPERITY"));
    Yanyus->addObject(CCString::create("A FAIR DEATH HONORS THE WHOLE LIFE"));
    Yanyus->addObject(CCString::create("A FAITHFUL FRIEND IS HARD TO FIND"));
    Yanyus->addObject(CCString::create("A FRIEND IN NEED IS A FRIEND INDEED"));
    Yanyus->addObject(CCString::create("A FRIEND IS EASIER LOST THAN FOUND"));
    Yanyus->addObject(CCString::create("A FRIEND IS NEVER KNOWN TILL A MAN HAS NEED"));
    Yanyus->addObject(CCString::create("A FRIEND WITHOUT FAULTS WILL NEVER BE FOUND"));
    Yanyus->addObject(CCString::create("A GOOD BEGINNING IS HALF DONE"));
    Yanyus->addObject(CCString::create("A GOOD BEGINNING MAKES A GOOD ENDING"));
    Yanyus->addObject(CCString::create("A GOOD BOOK IS A GOOD FRIEND"));
    Yanyus->addObject(CCString::create("A GOOD CONSCIENCE IS A SOFT PILLOW"));
    Yanyus->addObject(CCString::create("A GOOD FAME IS BETTER THAN A GOOD FACE"));
    Yanyus->addObject(CCString::create("A GOOD HUSBAND MAKES A GOOD WIFE"));
    Yanyus->addObject(CCString::create("A GOOD MEDICINE TASTES BITTER"));
    Yanyus->addObject(CCString::create("A GREAT TALKER IS A GREAT LIAR"));
    Yanyus->addObject(CCString::create("A HEDGE BETWEEN KEEPS FRIENDSHIP GREEN"));
    Yanyus->addObject(CCString::create("A JOKE NEVER GAINS AN ENEMY BUT LOSES A FRIEND"));
    Yanyus->addObject(CCString::create("A LEOPARD CANNOT CHANGE ITS SPOTS"));
    Yanyus->addObject(CCString::create("A LIGHT HEART LIVES LONG"));
    Yanyus->addObject(CCString::create("A LITTLE BODY OFTEN HARBORS A GREAT SOUL"));
    Yanyus->addObject(CCString::create("A LITTLE KNOWLEDGE IS A DANGEROUS THING"));
    Yanyus->addObject(CCString::create("A LITTLE POT IS SOON HOT"));
    Yanyus->addObject(CCString::create("ALL ARE BRAVE WHEN THE ENEMY FLIES"));
    Yanyus->addObject(CCString::create("ALL GOOD THINGS COME TO AN END"));
    Yanyus->addObject(CCString::create("ALL RIVERS RUN INTO SEA"));
    Yanyus->addObject(CCString::create("ALL ROADS LEAD TO ROME"));
    Yanyus->addObject(CCString::create("ALL THAT ENDS WELL IS WELL"));
    Yanyus->addObject(CCString::create("ALL THAT GLITTERS IS NOT GOLD"));
    Yanyus->addObject(CCString::create("ALL THINGS ARE DIFFICULT BEFORE THEY ARE EASY"));
    Yanyus->addObject(CCString::create("ALL WORK AND NO PLAY MAKES JACK A DULL BOY"));
    Yanyus->addObject(CCString::create("A MAN BECOMES LEARNED BY ASKING QUESTIONS"));
    Yanyus->addObject(CCString::create("A MAN CAN DO NO MORE THAN HE CAN"));
    Yanyus->addObject(CCString::create("A MAN CANNOT SPIN AND REEL AT THE SAME TIME"));
    Yanyus->addObject(CCString::create("A MAN IS KNOWN BY HIS FRIENDS"));
    Yanyus->addObject(CCString::create("A MAN WITHOUT MONEY IS NO MAN AT ALL"));
    Yanyus->addObject(CCString::create("A MERRY HEART GOES ALL THE WAY"));
    Yanyus->addObject(CCString::create("A MISS IS AS GOOD AS A MILE"));
    Yanyus->addObject(CCString::create("AN APPLE A DAY KEEPS THE DOCTOR AWAY"));
    Yanyus->addObject(CCString::create("A NEW BROOM SWEEPS CLEAN"));
    Yanyus->addObject(CCString::create("AN EYE FOR AN EYE AND A TOOTH FOR A TOOTH"));
    Yanyus->addObject(CCString::create("AN OLD DOG CANNOT LEARN NEW TRICKS"));
    Yanyus->addObject(CCString::create("A ROLLING STONE GATHERS NO MOSS"));
    Yanyus->addObject(CCString::create("A SINGLE FLOWER DOES NOT MAKE A SPRING"));
    Yanyus->addObject(CCString::create("A SNOW YEAR A RICH YEAR"));
    Yanyus->addObject(CCString::create("A SOUND MIND IN A SOUND BODY"));
    Yanyus->addObject(CCString::create("A STILL TONGUE MAKES A WISE HEAD"));
    Yanyus->addObject(CCString::create("A STITCH IN TIME SAVES NINE"));
    Yanyus->addObject(CCString::create("A WISE HEAD MAKES A CLOSE MOUTH"));
    Yanyus->addObject(CCString::create("A WORD SPOKEN IS PAST RECALLING"));
    Yanyus->addObject(CCString::create("BAD NEWS HAS WINGS"));
    Yanyus->addObject(CCString::create("BARKING DOGS SELDOM BITE"));
    Yanyus->addObject(CCString::create("BETTER LATE THAN NEVER"));
    Yanyus->addObject(CCString::create("BETTER TO ASK THE WAY THAN GO ASTRAY"));
    Yanyus->addObject(CCString::create("BETWEEN FRIENDS ALL IS COMMON"));
    Yanyus->addObject(CCString::create("BIRDS OF A FEATHER FLOCK TOGETHER"));
    Yanyus->addObject(CCString::create("BLOOD IS THICKER THAN WATER"));
    Yanyus->addObject(CCString::create("BLOOD WILL HAVE BLOOD"));
    Yanyus->addObject(CCString::create("BOOKS AND FRIENDS SHOULD BE FEW BUT GOOD"));
    Yanyus->addObject(CCString::create("BUSINESS IS BUSINESS"));
    Yanyus->addObject(CCString::create("BUSINESS IS THE SALT OF LIFE"));
    Yanyus->addObject(CCString::create("CANNOT SEE THE WOOD FOR THE TREES"));
    Yanyus->addObject(CCString::create("CARE AND DILIGENCE BRING LUCK"));
    Yanyus->addObject(CCString::create("CAUTION IS THE PARENT OF SAFETY"));
    Yanyus->addObject(CCString::create("CHEATS NEVER PROSPER"));
    Yanyus->addObject(CCString::create("CHILDREN ARE WHAT THE MOTHERS ARE"));
    Yanyus->addObject(CCString::create("CHOOSE AN AUTHOR AS YOU CHOOSE A FRIEND"));
    Yanyus->addObject(CCString::create("COMPLACENCY IS THE ENEMY OF STUDY"));
    Yanyus->addObject(CCString::create("CONSTANT DRIPPING WEARS AWAY A STONE"));
    Yanyus->addObject(CCString::create("CONTENT IS BETTER THAN RICHES"));
    Yanyus->addObject(CCString::create("COURTESY ON ONE SIDE ONLY LASTS NOT LONG"));
    Yanyus->addObject(CCString::create("CREEP BEFORE YOU WALK"));
    Yanyus->addObject(CCString::create("CRY FOR THE MOON"));
    Yanyus->addObject(CCString::create("CUSTOM IS A SECOND NATURE"));
    Yanyus->addObject(CCString::create("CUSTOM MAKES ALL THINGS EASY"));
    Yanyus->addObject(CCString::create("DIAMOND CUTS DIAMOND"));
    Yanyus->addObject(CCString::create("DO AS THE ROMANS DO"));
    Yanyus->addObject(CCString::create("DO AS YOU WOULD BE DONE BY"));
    Yanyus->addObject(CCString::create("DOING IS BETTER THAN SAYING"));
    Yanyus->addObject(CCString::create("DO IT NOW"));
    Yanyus->addObject(CCString::create("DO NOTHING BY HALVES"));
    Yanyus->addObject(CCString::create("DO WELL AND HAVE WELL"));
    Yanyus->addObject(CCString::create("EACH BIRD LOVE TO HEAR HIMSELF SING"));
    Yanyus->addObject(CCString::create("EASIER SAID THAN DONE"));
    Yanyus->addObject(CCString::create("EASY COME EASY GO"));
    Yanyus->addObject(CCString::create("EMPTY VESSELS MAKE THE GREATEST SOUND"));
    Yanyus->addObject(CCString::create("ENVY HAS NO HOLIDAYS"));
    Yanyus->addObject(CCString::create("EVEN HOMER SOMETIMES NODS"));
    Yanyus->addObject(CCString::create("EVEN RECKONING MAKES LONG FRIENDS"));
    Yanyus->addObject(CCString::create("EVERY ADVANTAGE HAS ITS DISADVANTAGE"));
    Yanyus->addObject(CCString::create("EVERY DAY IS NOT SUNDAY"));
    Yanyus->addObject(CCString::create("EVERY DOG HAS HIS DAY"));
    Yanyus->addObject(CCString::create("EVERY HEART HAS ITS OWN SORROW"));
    Yanyus->addObject(CCString::create("EVERY LITTLE HELPS A MICKLE"));
    Yanyus->addObject(CCString::create("EVERY MAN HAS HIS FAULTS"));
    Yanyus->addObject(CCString::create("EVERY MAN HAS HIS HOBBYHORSE"));
    Yanyus->addObject(CCString::create("EVERY MAN HAS HIS WEAK SIDE"));
    Yanyus->addObject(CCString::create("EVERY MAN IS THE ARCHITECT OF HIS OWN FORTUNE"));
    Yanyus->addObject(CCString::create("EVERY MINUTE COUNTS"));
    Yanyus->addObject(CCString::create("EVERY POTTER PRAISES HIT POT"));
    Yanyus->addObject(CCString::create("EXAMPLE IS BETTER THEN PERCEPT"));
    Yanyus->addObject(CCString::create("EXPERIENCE MUST BE BOUGHT"));
    Yanyus->addObject(CCString::create("FACT SPEAK LOUDER THAN WORDS"));
    Yanyus->addObject(CCString::create("FAILURE IS THE MOTHER OF SUCCESS"));
    Yanyus->addObject(CCString::create("FALSE FRIENDS ARE WORSE THAN BITTER ENEMIES"));
    Yanyus->addObject(CCString::create("FAR WATER DOES NOT PUT OUT NEAR FIRE"));
    Yanyus->addObject(CCString::create("FAULTS ARE THICK WHERE LOVE IS THIN"));
    Yanyus->addObject(CCString::create("FEAR ALWAYS SPRINGS FROM IGNORANCE"));
    Yanyus->addObject(CCString::create("FIRE AND WATER HAVE NO MERCY"));
    Yanyus->addObject(CCString::create("FIRE IS A GOOD SERVANT BUT A BAD MASTER"));
    Yanyus->addObject(CCString::create("FIRST IMPRESSIONS ARE HALF THE BATTLE"));
    Yanyus->addObject(CCString::create("FIRST THINK AND THEN SPEAK"));
    Yanyus->addObject(CCString::create("FOOLS GROW WITHOUT WATERING"));
    Yanyus->addObject(CCString::create("FOOLS HAS FORTUNE"));
    Yanyus->addObject(CCString::create("FORBIDDEN FRUIT IS SWEET"));
    Yanyus->addObject(CCString::create("FORTUNE FAVORS THOSE WHO USE THEIR JUDGEMENT"));
    Yanyus->addObject(CCString::create("FOUR EYES SEE MORE THAN TWO"));
    Yanyus->addObject(CCString::create("FRIENDS AGREE BEST AT DISTANCE"));
    Yanyus->addObject(CCString::create("FRIENDS ARE THIEVES OF TIME"));
    Yanyus->addObject(CCString::create("FRIENDS MUST PART"));
    Yanyus->addObject(CCString::create("GENIUS IS NOTHING BUT LABOR AND DILIGENCE"));
    Yanyus->addObject(CCString::create("GIVE A DOG A BAD NAME AND HANG HIM"));
    Yanyus->addObject(CCString::create("GOD HELPS THOSE WHO HELP THEMSELVES"));
    Yanyus->addObject(CCString::create("GOLD WILL NOT BUY ANYTHING"));
    Yanyus->addObject(CCString::create("GOOD HEALTH IS OVER WEALTH"));
    Yanyus->addObject(CCString::create("GOOD WATCH PREVENTS MISFORTUNE"));
    Yanyus->addObject(CCString::create("GREAT BARKERS ARE NO BITERS"));
    Yanyus->addObject(CCString::create("GREAT HOPES MAKE GREAT MAN"));
    Yanyus->addObject(CCString::create("GREAT MINDS THINK ALIKE"));
    Yanyus->addObject(CCString::create("GREAT MEN HAVE GREAT FAULTS"));
    Yanyus->addObject(CCString::create("GREAT TREES ARE GOOD FOR NOTHING BUT SHADE"));
    Yanyus->addObject(CCString::create("GREAT WITS HAVE SHORT MEMORIES"));
    Yanyus->addObject(CCString::create("GREEDY FOLKS HAVE LONG ARMS"));
    Yanyus->addObject(CCString::create("GUILTY CONSCIENCES MAKE MEN COWARDS"));
    Yanyus->addObject(CCString::create("HABIT CURES HABIT"));
    Yanyus->addObject(CCString::create("HANDSOME IS HE WHO DOES HANDSOMELY"));
    Yanyus->addObject(CCString::create("HAPPINESS TAKES NO ACCOUNT OF TIME"));
    Yanyus->addObject(CCString::create("HAPPY IS HE WHO OWES NOTHING"));
    Yanyus->addObject(CCString::create("HARM SET HARM GET"));
    Yanyus->addObject(CCString::create("HEALTH IS BETTER THAN WEALTH"));
    Yanyus->addObject(CCString::create("HEALTH IS HAPPINESS"));
    Yanyus->addObject(CCString::create("HEAR ALL PARTIES"));
    Yanyus->addObject(CCString::create("HEAVEN NEVER HELPS THE MAN WHO WILL NOT ACT"));
    Yanyus->addObject(CCString::create("HE IS A FOOL THAT FORGETS HIMSELF"));
    Yanyus->addObject(CCString::create("HE IS A WISE MAN WHO SPEAKS LITTLE"));
    Yanyus->addObject(CCString::create("HE IS LIFELESS THAT IS FAULTLESS"));
    Yanyus->addObject(CCString::create("HE IS WISE THAT IS HONEST"));
    Yanyus->addObject(CCString::create("HE KNOWS MOST WHO SPEAKS LEAST"));
    Yanyus->addObject(CCString::create("HE LAUGHS BEST WHO LAUGHS LAST"));
    Yanyus->addObject(CCString::create("HE SETS THE FOX TO KEEP THE GEESE"));
    Yanyus->addObject(CCString::create("HE THAT CLIMBS HIGH FALLS HEAVILY"));
    Yanyus->addObject(CCString::create("HE THAT WILL NOT WORK SHALL NOT EAT"));
    Yanyus->addObject(CCString::create("HE WHO DOES NOT ADVANCE LOSES GROUND"));
    Yanyus->addObject(CCString::create("HE WHO MAKES NO MISTAKES MAKES NOTHING"));
    Yanyus->addObject(CCString::create("HE WHO RISKS NOTHING GAINS NOTHING"));
    Yanyus->addObject(CCString::create("HISTORY REPEATS ITSELF"));
    Yanyus->addObject(CCString::create("HONESTY IS THE BEST POLICY"));
    Yanyus->addObject(CCString::create("I CANNOT BE YOUR FRIEND AND YOUR FLATTERER TOO"));
    Yanyus->addObject(CCString::create("INDUSTRY IS THE PARENT OF SUCCESS"));
    Yanyus->addObject(CCString::create("IT IS BETTER TO DIE WHEN LIFE IS A DISGRACE"));
    Yanyus->addObject(CCString::create("IT IS EASIER TO GET MONEY THAN TO KEEP IT"));
    Yanyus->addObject(CCString::create("IT IS EASY TO BE WISE AFTER THE EVENT"));
    Yanyus->addObject(CCString::create("IT IS HARD TO PLEASE ALL"));
    Yanyus->addObject(CCString::create("IT IS NEVER TOO OLD TO LEARN"));
    Yanyus->addObject(CCString::create("IT IS NO USE CRYING OVER SPILT MILK"));
    Yanyus->addObject(CCString::create("IT IS THE FIRST STEP THAT COSTS TROUBLESOME"));
    Yanyus->addObject(CCString::create("IT IS THE UNFORESEEN THAT ALWAYS HAPPENS"));
    Yanyus->addObject(CCString::create("IT IS TOO LATE TO GRIEVE WHEN THE CHANCE IS PAST"));
    Yanyus->addObject(CCString::create("IT NEVER RAINS BUT IT POURS"));
    Yanyus->addObject(CCString::create("JACK OF ALL TRADES AND MASTER OF NONE"));
    Yanyus->addObject(CCString::create("JUDGE NOT FROM APPEARANCES"));
    Yanyus->addObject(CCString::create("JUSTICE HAS LONG ARMS"));
    Yanyus->addObject(CCString::create("KILL TWO BIRDS WITH ONE STONE"));
    Yanyus->addObject(CCString::create("KINGS HAVE LONG ARMS"));
    Yanyus->addObject(CCString::create("KNOWLEDGE IS POWER"));
    Yanyus->addObject(CCString::create("LEARN AND LIVE"));
    Yanyus->addObject(CCString::create("LEARN NOT AND KNOW NOT"));
    Yanyus->addObject(CCString::create("LEARN TO WALK BEFORE YOU RUN"));
    Yanyus->addObject(CCString::create("LET BYGONES BE BYGONES"));
    Yanyus->addObject(CCString::create("LET SLEEPING DOGS LIE"));
    Yanyus->addObject(CCString::create("LET THE CAT OUT OF THE BAG"));
    Yanyus->addObject(CCString::create("LIES CAN NEVER CHANGES FACT"));
    Yanyus->addObject(CCString::create("LIES HAVE SHORT LEGS"));
    Yanyus->addObject(CCString::create("LIFE IS BUT A SPAN"));
    Yanyus->addObject(CCString::create("LIFE IS HALF SPENT BEFORE WE KNOW WHAT IT IS"));
    Yanyus->addObject(CCString::create("LIFE IS NOT ALL ROSES"));
    Yanyus->addObject(CCString::create("LIFE WITHOUT A FRIEND IS DEATH"));
    Yanyus->addObject(CCString::create("LIKE A RAT IN A HOLE"));
    Yanyus->addObject(CCString::create("LIKE FOR LIKE"));
    Yanyus->addObject(CCString::create("LIKE KNOWS LIKE"));
    Yanyus->addObject(CCString::create("LITTLE THINGS AMUSE LITTLE MINDS"));
    Yanyus->addObject(CCString::create("LOOK BEFORE YOU LEAP"));
    Yanyus->addObject(CCString::create("LOOKERS-ON SEE MORE THAN PLAYERS"));
    Yanyus->addObject(CCString::create("LOSERS ARE ALWAYS IN THE WRONG"));
    Yanyus->addObject(CCString::create("LOST TIME IS NEVER FOUND AGAIN"));
    Yanyus->addObject(CCString::create("LOVE AT FIRST SIGHT"));
    Yanyus->addObject(CCString::create("LOVE CANNOT BE COMPELLED"));
    Yanyus->addObject(CCString::create("LOVE IS BLIND"));
    Yanyus->addObject(CCString::create("LOVE IS FULL OF TROUBLE"));
    Yanyus->addObject(CCString::create("LOVE IS NEVER WITHOUT JEALOUSY"));
    Yanyus->addObject(CCString::create("MAKE HAY WHILE THE SUN SHINES"));
    Yanyus->addObject(CCString::create("MAKE YOUR ENEMY YOUR FRIEND"));
    Yanyus->addObject(CCString::create("MAN IS THE SOUL OF THE UNIVERSE"));
    Yanyus->addObject(CCString::create("MANY HANDS MAKE LIGHT WORK"));
    Yanyus->addObject(CCString::create("MANY HEADS ARE BETTER THAN ONE"));
    Yanyus->addObject(CCString::create("MEASURE FOR MEASURE"));
    Yanyus->addObject(CCString::create("MISFORTUNES NEVER COME ALONE"));
    Yanyus->addObject(CCString::create("MURDER WILL OUT"));
    Yanyus->addObject(CCString::create("NATURE IS THE TRUE LAW"));
    Yanyus->addObject(CCString::create("NECESSITY IS THE MOTHER OF INVENTION"));
    Yanyus->addObject(CCString::create("NEVER FISH IN TROUBLE WATER"));
    Yanyus->addObject(CCString::create("NEVER JUDGE FROM APPEARANCES"));
    Yanyus->addObject(CCString::create("NEVER SAY DIE"));
    Yanyus->addObject(CCString::create("NEW WINE IN OLD BOTTLES"));
    Yanyus->addObject(CCString::create("NO GARDEN WITHOUT ITS WEEDS"));
    Yanyus->addObject(CCString::create("NO LIVING MAN ALL THINGS CAN"));
    Yanyus->addObject(CCString::create("NO MAN CAN DO TWO THINGS AT ONCE"));
    Yanyus->addObject(CCString::create("NO MAN IS BORN WISE OR LEARNED"));
    Yanyus->addObject(CCString::create("NO MAN IS CONTENT"));
    Yanyus->addObject(CCString::create("NO MAN IS WISE AT ALL TIMES"));
    Yanyus->addObject(CCString::create("NO NEWS IS GOOD NEWS"));
    Yanyus->addObject(CCString::create("NO ONE CAN CALL BACK YESTERDAY"));
    Yanyus->addObject(CCString::create("NO PLEASURE WITHOUT PAIN"));
    Yanyus->addObject(CCString::create("NO ROSE WITHOUT A THORN"));
    Yanyus->addObject(CCString::create("NO SWEET WITHOUT SWEAT"));
    Yanyus->addObject(CCString::create("NO SMOKE WITHOUT FIRE"));
    Yanyus->addObject(CCString::create("NOTHING DRIES SOONER THAN A TEAR"));
    Yanyus->addObject(CCString::create("NOTHING IS DIFFICULT TO THE MAN WHO WILL TRY"));
    Yanyus->addObject(CCString::create("NOT TO ADVANCE IS TO GO BACK"));
    Yanyus->addObject(CCString::create("NO WAY IS IMPOSSIBLE TO COURAGE"));
    Yanyus->addObject(CCString::create("OBEDIENCE IS THE FIRST DUTY OF A SOLDIER"));
    Yanyus->addObject(CCString::create("OBSERVATION IS THE BEST TEACHER"));
    Yanyus->addObject(CCString::create("OFFENSE IS THE BEST DEFENSE"));
    Yanyus->addObject(CCString::create("OLD FRIENDS AND OLD WINES ARE BEST"));
    Yanyus->addObject(CCString::create("OLD SIN MAKES NEW SHAME"));
    Yanyus->addObject(CCString::create("ONCE A MAN AND TWICE A CHILD"));
    Yanyus->addObject(CCString::create("ONE CANNOT PUT BACK THE CLOCK"));
    Yanyus->addObject(CCString::create("ONE FALSE MOVE MAY LOSE THE GAME"));
    Yanyus->addObject(CCString::create("ONE GOOD TURN DESERVES ANOTHER"));
    Yanyus->addObject(CCString::create("ONE HOUR TODAY IS WORTH TWO TOMORROW"));
    Yanyus->addObject(CCString::create("ONE NEVER LOSES ANYTHING BY POLITENESS"));
    Yanyus->addObject(CCString::create("ONE SWALLOW DOES NOT MAKE A SUMMER"));
    Yanyus->addObject(CCString::create("PLEASE THE EYE AND PLAGUE THE HEART"));
    Yanyus->addObject(CCString::create("PLEASURE COMES THROUGH TOIL"));
    Yanyus->addObject(CCString::create("POUR WATER INTO A SIEVE"));
    Yanyus->addObject(CCString::create("PRACTICE MAKES PERFECT"));
    Yanyus->addObject(CCString::create("PRAISE IS NOT PUDDING"));
    Yanyus->addObject(CCString::create("PREFER LOSS TO UNJUST GAIN"));
    Yanyus->addObject(CCString::create("PREVENTION IS BETTER THAN CURE"));
    Yanyus->addObject(CCString::create("PROMISE IS DEBT"));
    Yanyus->addObject(CCString::create("PULL THE CHESTNUT OUT OF FIRE"));
    Yanyus->addObject(CCString::create("PUT THE CART BEFORE THE HORSE"));
    Yanyus->addObject(CCString::create("PUT YOUR SHOULDER TO THE WHEEL"));
    Yanyus->addObject(CCString::create("READING ENRICHES THE MIND"));
    Yanyus->addObject(CCString::create("ROME IS NOT BUILT IN A DAY"));
    Yanyus->addObject(CCString::create("SAYING IS ONE THING AND DOING ANOTHER"));
    Yanyus->addObject(CCString::create("SEEING IS BELIEVING"));
    Yanyus->addObject(CCString::create("SEEK THE TRUTH FROM FACTS"));
    Yanyus->addObject(CCString::create("SET A THIEF TO CATCH A THIEF"));
    Yanyus->addObject(CCString::create("SHORT ACCOUNTS MAKE LONG FRIENDS"));
    Yanyus->addObject(CCString::create("SOMETHING IS BETTER THAN NOTHING"));
    Yanyus->addObject(CCString::create("STILL WATER RUN DEEP"));
    Yanyus->addObject(CCString::create("STRIKE THE IRON WHILE IT IS HOT"));
    Yanyus->addObject(CCString::create("SUCCESS BELONGS TO THE PERSEVERING"));
    Yanyus->addObject(CCString::create("TAKE THINGS AS THEY COME"));
    Yanyus->addObject(CCString::create("TALKING MENDS NO HOLES"));
    Yanyus->addObject(CCString::create("TALK OF THE DEVIL AND HE WILL APPEAR"));
    Yanyus->addObject(CCString::create("TALL TREES CATCH MUCH WIND"));
    Yanyus->addObject(CCString::create("TEACH OTHERS BY YOUR EXAMPLE"));
    Yanyus->addObject(CCString::create("THE BEST HEARTS ARE ALWAYS THE BRAVEST"));
    Yanyus->addObject(CCString::create("THE BEST MAN STUMBLES"));
    Yanyus->addObject(CCString::create("THE CAT SHUTS ITS EYES WHEN STEALING"));
    Yanyus->addObject(CCString::create("THE DANGER PAST AND GOD FORGOTTEN"));
    Yanyus->addObject(CCString::create("THE DARKEST HOUR IS NEAREST THE DAWN"));
    Yanyus->addObject(CCString::create("THE DARKEST PLACE IS UNDER THE CANDLESTICK"));
    Yanyus->addObject(CCString::create("THE DEVIL KNOWS MANY THINGS BECAUSE HE IS OLD"));
    Yanyus->addObject(CCString::create("THE DEVIL SOMETIMES SPEAKS THE TRUTH"));
    Yanyus->addObject(CCString::create("THE DIE IS CAST"));
    Yanyus->addObject(CCString::create("THE EARLY BIRD CATCHES THE WORM"));
    Yanyus->addObject(CCString::create("THE END JUSTIFIES THE MEANS"));
    Yanyus->addObject(CCString::create("THE END MAKES ALL EQUAL"));
    Yanyus->addObject(CCString::create("THE EYE IS BIGGER THAN THE BELLY"));
    Yanyus->addObject(CCString::create("THE FINEST DIAMOND MUST BE CUT"));
    Yanyus->addObject(CCString::create("THE FIRST STEP IS THE ONLY DIFFICULTY"));
    Yanyus->addObject(CCString::create("THE FOX PREYS FARTHEST FROM HOME"));
    Yanyus->addObject(CCString::create("THE GRASS IS GREENER ON THE OTHER SIDE"));
    Yanyus->addObject(CCString::create("THE GREATEST TALKERS ARE ALWAYS LEAST DOERS"));
    Yanyus->addObject(CCString::create("THE LEOPARD CANNOT CHANGE ITS SPOTS"));
    Yanyus->addObject(CCString::create("THE OUTSIDER SEES THE MOST OF THE GAME"));
    Yanyus->addObject(CCString::create("THE PEN IS MIGHTIER THAN THE SWORD"));
    Yanyus->addObject(CCString::create("THE POT CALLS THE KETTLE BLACK"));
    Yanyus->addObject(CCString::create("THERE ARE SPOTS IN THE SUN"));
    Yanyus->addObject(CCString::create("THERE ARE TWO SIDES TO EVERY QUESTION"));
    Yanyus->addObject(CCString::create("THERE IS A SKELETON IN THE CUPBOARD"));
    Yanyus->addObject(CCString::create("THERE IS KINDNESS TO BE FOUND EVERYWHERE"));
    Yanyus->addObject(CCString::create("THERE IS NO GENERAL RULE WITHOUT SOME EXCEPTION"));
    Yanyus->addObject(CCString::create("THERE IS NO MEDICINE AGAINST DEATH"));
    Yanyus->addObject(CCString::create("THERE IS NO PLACE LIKE HOME"));
    Yanyus->addObject(CCString::create("THERE IS NO ROYAL ROAD TO LEARNING"));
    Yanyus->addObject(CCString::create("THE STYLE IS THE MAN"));
    Yanyus->addObject(CCString::create("THINK TWICE BEFORE YOU DO"));
    Yanyus->addObject(CCString::create("THINGS AT THE WORST WILL MEND"));
    Yanyus->addObject(CCString::create("TIME AND TIDE WAIT FOR NO MAN"));
    Yanyus->addObject(CCString::create("TIME CURES ALL THINGS"));
    Yanyus->addObject(CCString::create("TIME FLIES"));
    Yanyus->addObject(CCString::create("TIME IS MONEY"));
    Yanyus->addObject(CCString::create("TIME LOST CANNOT BE WON AGAIN"));
    Yanyus->addObject(CCString::create("TIME PAST CANNOT BE CALLED BACK AGAIN"));
    Yanyus->addObject(CCString::create("TIME TRIES ALL"));
    Yanyus->addObject(CCString::create("TIT FOR TAT IS FAIR PLAY"));
    Yanyus->addObject(CCString::create("TO ERR IS HUMAN"));
    Yanyus->addObject(CCString::create("TO KNOW EVERYTHING IS TO KNOW NOTHING"));
    Yanyus->addObject(CCString::create("TO KNOW ONESELF IS TRUE PROGRESS"));
    Yanyus->addObject(CCString::create("TOMORROW NEVER COMES"));
    Yanyus->addObject(CCString::create("TOO MUCH FAMILIARITY BREEDS CONTEMPT"));
    Yanyus->addObject(CCString::create("TOO MUCH KNOWLEDGE MAKES THE HEAD BALD"));
    Yanyus->addObject(CCString::create("TOO MUCH LIBERTY SPILLS ALL"));
    Yanyus->addObject(CCString::create("TOO MUCH PRAISE IS A BURDEN"));
    Yanyus->addObject(CCString::create("TO SAVE TIME IS TO LENGTHEN LIFE"));
    Yanyus->addObject(CCString::create("TROUBLES NEVER COME SINGLY"));
    Yanyus->addObject(CCString::create("TRUTH NEVER GROWS OLD"));
    Yanyus->addObject(CCString::create("TURN OVER A NEW LEAF"));
    Yanyus->addObject(CCString::create("TWO HEADS ARE BETTER THAN ONE"));
    Yanyus->addObject(CCString::create("TWO OF A TRADE SELDOM AGREE"));
    Yanyus->addObject(CCString::create("TWO WRONGS DO NOT MAKE A RIGHT"));
    Yanyus->addObject(CCString::create("UNITY IS STRENGTH"));
    Yanyus->addObject(CCString::create("UNPLEASANT ADVICE IS A GOOD MEDICINE"));
    Yanyus->addObject(CCString::create("VENTURE A SMALL FISH TO CATCH A GREAT ONE"));
    Yanyus->addObject(CCString::create("VIRTUE IS FAIRER FAR THAN BEAUTY"));
    Yanyus->addObject(CCString::create("WALLS HAVE EARS"));
    Yanyus->addObject(CCString::create("WASH YOUR DIRTY LINEN AT HOME"));
    Yanyus->addObject(CCString::create("WATER DROPPING DAY BY DAY WEARS THE HARDEST ROCK AWAY"));
    Yanyus->addObject(CCString::create("WEALTH IS NOTHING WITHOUT HEALTH"));
    Yanyus->addObject(CCString::create("WE KNOW NOT WHAT IS GOOD UNTIL WE HAVE LOST IT"));
    Yanyus->addObject(CCString::create("WELL BEGUN IS HALF DONE"));
    Yanyus->addObject(CCString::create("WE NEVER KNOW THE WORTH OF WATER TILL THE WELL IS DRY"));
    Yanyus->addObject(CCString::create("WET BEHIND THE EARS"));
    Yanyus->addObject(CCString::create("WHAT IS LEARNED IN THE CRADLE IS CARRIED TO THE GRAVE"));
    Yanyus->addObject(CCString::create("WHAT WE DO WILLINGLY IS EASY"));
    Yanyus->addObject(CCString::create("WHOM THE GODS LOVE DIE YOUNG"));
    Yanyus->addObject(CCString::create("WORK MAKES THE WORKMAN"));
    Yanyus->addObject(CCString::create("YOU CANNOT BURN THE CANDLE AT BOTH ENDS"));
    Yanyus->addObject(CCString::create("YOU CANNOT EAT YOUR CAKE AND HAVE IT"));
    Yanyus->addObject(CCString::create("YOU MAY KNOW BY A HANDFUL THE WHOLE SACK"));
    Yanyus->addObject(CCString::create("YOU NEVER KNOW WHAT YOU CAN TILL YOU TRY"));
}

