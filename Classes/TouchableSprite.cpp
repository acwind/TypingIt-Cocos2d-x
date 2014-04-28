//
//  TouchableSprite.cpp
//  TouchDemo
//
//  Created by Tom on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "TouchableSprite.h"

TouchableSprite::TouchableSprite()
{
}

TouchableSprite::~TouchableSprite()
{
}

TouchableSprite* TouchableSprite::touchSpriteWithFile(const char *file)
{
    TouchableSprite *sprite = new TouchableSprite();
    
    if (sprite && sprite->initWithFile(file)) 
    {
        sprite->autorelease();
        return sprite;
    }
    
    return NULL;
}

bool TouchableSprite::initWithFile(const char *file)
{
    CCSprite::initWithFile(file);
    
    return true;
}

void TouchableSprite::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void TouchableSprite::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

CCRect TouchableSprite::rect()
{
    CCSize size = getTexture()->getContentSize();

    return CCRectMake(-size.width / 2, -size.height / 2, size.width, size.height);
    
//    CCSize size = getContentSize();
//    CCPoint pos = getPosition();
//    
//    return CCRectMake(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
}

bool TouchableSprite::containsTouchLocation(cocos2d::CCTouch *touch)
{
    return this->rect().containsPoint(convertTouchToNodeSpaceAR(touch));
    
//    CCPoint touchPoint = touch->locationInView(touch->view());
//    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
//    
//    return CCRect::CCRectContainsPoint(rect(), touchPoint);
    
//    return CCRect::CCRectContainsPoint(getTextureRect(), convertTouchToNodeSpaceAR(touch));
//    CCLog("Texture Rect: %f, %f, %f, %f", -getTextureRect().size.width / 2, -getTextureRect().size.height / 2, getTextureRect().size.width, getTextureRect().size.height);
    
//    CCLog("Point On Node: %f, %f", convertTouchToNodeSpaceAR(touch).x, convertTouchToNodeSpaceAR(touch).y);
}

bool TouchableSprite::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    bool bRet = false;
    
    if (containsTouchLocation(touch))
    {
        // CCLog("Touchable Sprite Began");
        
        bRet = true;
    }
    
    return bRet;
}

void TouchableSprite::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void TouchableSprite::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCLog("Touchable Sprite Ended");
    if (delegate_)
    {
       delegate_->spriteClicked(this->tagId);
    }
    
}

