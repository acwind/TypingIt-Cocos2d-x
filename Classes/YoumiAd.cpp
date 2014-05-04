#include "YoumiAd.h"

YoumiAd::YoumiAd(){}
YoumiAd::~YoumiAd(){}

void YoumiAd::showSpotAd()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showSpotAd;//定义Jni函数信息结构体
    //getStaticMethodInfo 函数返回一个bool值表示是否找到此静态函数
	//"com/youmi/sample/YoumiCocos2dxSample“与你的Activity(即YoumiCocos2dxSample)的包名对应：com.youmi.sample.YoumiCocos2dxSample
	//"showSpotAdStatic"这是JAVA中定义的静态函数名
	//（）V表示JAVA中定义的showSpotAdStatic函数参数为空，返回值为空（ JAVA中的定义是void showSpotAdStatic() ）
	//开发者需要更换成自己工程的主Activity的包名，如开发者的类MyProjectActivity在包com.a.b中，那么这里应该是"com/a/b/MyProjectActivity"
    bool isHave = JniHelper::getStaticMethodInfo(showSpotAd,"typing/acwind/net/typing","showSpotAdStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showSpotAdStatic此函数不存在");
    }else{
        CCLog("jni:showSpotAdStatic此函数存在");
        //调用此函数
        showSpotAd.env->CallStaticVoidMethod(showSpotAd.classID, showSpotAd.methodID);
    }
	#endif
}

void YoumiAd::showBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showBanner;
    bool isHave = JniHelper::getStaticMethodInfo(showBanner,"typing/acwind/net/typing","showBannerStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showBannerStatic此函数不存在");
    }else{
        CCLog("jni:showBannerStatic此函数存在");
        //调用此函数
        showBanner.env->CallStaticVoidMethod(showBanner.classID, showBanner.methodID);
    }
	#endif

}

void YoumiAd::hideBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo hideBanner;
    bool isHave = JniHelper::getStaticMethodInfo(hideBanner,"typing/acwind/net/typing","hideBannerStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:hideBannerStatic此函数不存在");
    }else{
        CCLog("jni:hideBannerStatic此函数存在");
        //调用此函数
        hideBanner.env->CallStaticVoidMethod(hideBanner.classID, hideBanner.methodID);
    }
	#endif

}


void YoumiAd::showOfferBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showOfferBanner;
    bool isHave = JniHelper::getStaticMethodInfo(showOfferBanner,"typing/acwind/net/typing","showOfferBannerStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showOfferBannerStatic此函数不存在");
    }else{
        CCLog("jni:showOfferBannerStatic此函数存在");
        //调用此函数
        showOfferBanner.env->CallStaticVoidMethod(showOfferBanner.classID, showOfferBanner.methodID);
    }
	#endif

}

void YoumiAd::hideOfferBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo hideOfferBanner;
    bool isHave = JniHelper::getStaticMethodInfo(hideOfferBanner,"typing/acwind/net/typing","hideOfferBannerStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:hideOfferBannerStatic此函数不存在");
    }else{
        CCLog("jni:hideOfferBannerStatic此函数存在");
        //调用此函数
        hideOfferBanner.env->CallStaticVoidMethod(hideOfferBanner.classID, hideOfferBanner.methodID);
    }
	#endif

}


void YoumiAd::showOfferDialog()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showOfferDialog;
    bool isHave = JniHelper::getStaticMethodInfo(showOfferDialog,"typing/acwind/net/typing","showOfferDialogStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showOfferDialogStatic此函数不存在");
    }else{
        CCLog("jni:showOfferDialogStatic此函数存在");
        //调用此函数
        showOfferDialog.env->CallStaticVoidMethod(showOfferDialog.classID, showOfferDialog.methodID);
    }
	#endif
}


void YoumiAd::showOfferWall()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showOfferWall;
    bool isHave = JniHelper::getStaticMethodInfo(showOfferWall,"typing/acwind/net/typing","showOfferWallStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showOfferWallStatic此函数不存在");
    }else{
        CCLog("jni:showOfferWallStatic此函数存在");
        //调用此函数
        showOfferWall.env->CallStaticVoidMethod(showOfferWall.classID, showOfferWall.methodID);
    }
	#endif

}

/*
void YoumiAd::showRecommandWall()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showRecommandWall;
    bool isHave = JniHelper::getStaticMethodInfo(showRecommandWall,"com/youmi/sample/YoumiCocos2dxSample","showRecommandWallStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showRecommandWallStatic此函数不存在");
    }else{
        CCLog("jni:showRecommandWallStatic此函数存在");
        //调用此函数
        showRecommandWall.env->CallStaticVoidMethod(showRecommandWall.classID, showRecommandWall.methodID);
    }
	#endif

}


void YoumiAd::showDiyAd()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showDiyAd;
    bool isHave = JniHelper::getStaticMethodInfo(showDiyAd,"com/youmi/sample/YoumiCocos2dxSample","showDiyAdStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showDiyAdStatic此函数不存在");
    }else{
        CCLog("jni:showDiyAdStatic此函数存在");
        //调用此函数
        showDiyAd.env->CallStaticVoidMethod(showDiyAd.classID, showDiyAd.methodID);
    }
	#endif

}
*/

void YoumiAd::showSmartBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showSmartBanner;
    bool isHave = JniHelper::getStaticMethodInfo(showSmartBanner,"typing/acwind/net/typing","showSmartBannerStatic", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showSmartBannerStatic此函数不存在");
    }else{
        CCLog("jni:showSmartBannerStatic此函数存在");
        //调用此函数
        showSmartBanner.env->CallStaticVoidMethod(showSmartBanner.classID, showSmartBanner.methodID);
    }
	#endif

}

void YoumiAd::awardPoints( int point )
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo awardPoints;
    bool isHave = JniHelper::getStaticMethodInfo(awardPoints,"typing/acwind/net/typing","awardPoints", "(I)V"); 
 
    if (!isHave) {
        CCLog("jni:awardPoints此函数不存在");
    }else{
        CCLog("jni:awardPoints此函数存在");
        //调用此函数
        awardPoints.env->CallStaticVoidMethod(awardPoints.classID, awardPoints.methodID,point);
    }
	#endif
}

void YoumiAd::spendPoints( int point )
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo spendPoints;
    bool isHave = JniHelper::getStaticMethodInfo(spendPoints,"typing/acwind/net/typing","spendPoints", "(I)V"); 
 
    if (!isHave) {
        CCLog("jni:spendPoints此函数不存在");
    }else{
        CCLog("jni:spendPoints此函数存在");
        //调用此函数
        spendPoints.env->CallStaticVoidMethod(spendPoints.classID, spendPoints.methodID,point);
    }
	#endif
}

int YoumiAd::queryPoints()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo queryPoints;
    bool isHave = JniHelper::getStaticMethodInfo(queryPoints,"typing/acwind/net/typing","queryPointsStatic", "()I"); 
 
    if (!isHave) {
        CCLog("jni:queryPointsStatic此函数不存在");
    }else{
        CCLog("jni:queryPointsStatic此函数存在");
        //调用此函数
		return queryPoints.env->CallStaticIntMethod(queryPoints.classID, queryPoints.methodID);
    }
	#endif
}


