#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include "cocos2d.h"
#endif
using namespace cocos2d;
class YoumiAd
{
public:
	YoumiAd();
	virtual ~YoumiAd();
	static void showSpotAd();//通过JNI调用JAVA静态函数，实现展示插屏广告
	static void showOfferBanner();//通过JNI调用JAVA静态函数，实现展示积分Banner
	static void hideOfferBanner();//通过JNI调用JAVA静态函数，实现关闭积分banner展示
	static void showOfferDialog();//通过JNI调用JAVA静态函数，实现展示积分对话框
	static void showOfferWall();//通过JNI调用JAVA静态函数，实现展示积分墙
	//static void showRecommandWall();//通过JNI调用JAVA静态函数，实现展示推荐墙
	//static void showDiyAd();//通过JNI调用JAVA静态函数，实现展示自定义广告
	static void showSmartBanner();//通过JNI调用JAVA静态函数，实现展示SmartBanner
	static void showBanner();//通过JNI调用JAVA静态函数，实现展示Banner
	static void hideBanner();//通过JNI调用JAVA静态函数，实现关闭banner展示
	static void awardPoints( int point );//通过JNI调用JAVA静态函数，实现增加积分
	static void spendPoints( int point );//通过JNI调用JAVA静态函数，实现减少积分
	static int queryPoints();//通过JNI调用JAVA静态函数，实现查询积分
};
