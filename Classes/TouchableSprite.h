//
//  TouchableSprite.h
//  TouchDemo
//
//  Created by Tom on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef TouchDemo_TouchableSprite_h
#define TouchDemo_TouchableSprite_h

#include "cocos2d.h"
#include "VirtualClassC.h"

USING_NS_CC;

// 可接收触摸事件的精灵
class TouchableSprite: public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{
    
public:
    TouchableSprite();
    virtual ~TouchableSprite();
    
    static TouchableSprite *touchSpriteWithFile(const char *file);
    
    bool initWithFile(const char *file);
    
    virtual void onEnter();
    virtual void onExit();
    
    CCRect rect();
    bool containsTouchLocation(CCTouch *touch);
    
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);

    VirtualClassC *delegate_; 
    int tagId;

};

#endif
