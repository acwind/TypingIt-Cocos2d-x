/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package typing.acwind.net;

import java.util.UUID;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.view.View.OnClickListener;

public class typing extends Cocos2dxActivity{
	
    private static Handler handler;
    public LinearLayout bannerLayout;
    public int YOUMI_AD_BANNER = 1;
    public int YOUMI_AD_BANNER_HIDE = 2;
    
    static typing test  = null;
    WebView m_webView;
    FrameLayout m_webLayout;
    LinearLayout m_topLayout;
    Button m_backButton;
    
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		 test = this;
        //初始化一个空布局
        m_webLayout = new FrameLayout(this);
        FrameLayout.LayoutParams lytp = new FrameLayout.LayoutParams(800,640);
        lytp .gravity = Gravity.CENTER;
        addContentView(m_webLayout, lytp);
		
	}

   
    
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// typing should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }
    
    public static String getUUID() {
        SharedPreferences userInfo = typing.getInstance().getSharedPreferences("userinfo", 0);
        String uid = userInfo.getString("uid", "none");
        if (uid == "none") {
            uid = UUID.randomUUID().toString();
            userInfo.edit().putString("uid", uid).commit();
        }
        return uid;
    }
    
  //返回实例
    public static typing getInstance() {
        return test;
    }
    public void openWebview() {
        this.runOnUiThread(new Runnable() {//在主线程里添加别的控件
            public void run() {
                //初始化webView
                m_webView = new WebView(test);
                //设置webView能够执行javascript脚本
                m_webView.getSettings().setJavaScriptEnabled(true);            
                //设置可以支持缩放
//                m_webView.getSettings().setSupportZoom(true);//设置出现缩放工具
//                m_webView.getSettings().setBuiltInZoomControls(true);
                //载入URL
                m_webView.loadUrl("http://game.acwind.net/index.php/typing/top?uid=" + typing.getUUID());
                //使页面获得焦点
                m_webView.requestFocus();
                
                //如果页面中链接，如果希望点击链接继续在当前browser中响应
                m_webView.setWebViewClient(new WebViewClient(){       
                    public boolean shouldOverrideUrlLoading(WebView view, String url) {   
                        if(url.indexOf("tel:")<0){
                            view.loadUrl(url); 
                        }
                        return true;       
                    }    
                });
                
                //初始化线性布局 里面加按钮和webView
                m_topLayout = new LinearLayout(test);      
                m_topLayout.setOrientation(LinearLayout.VERTICAL);
                LinearLayout.LayoutParams linearParams=
                        new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
                linearParams.width = 750;
                linearParams.height = 600;
                linearParams.gravity = Gravity.RIGHT;
                m_topLayout.setLayoutParams(linearParams);
                
                //初始化返回按钮
                m_backButton = new Button(test);
                m_backButton.setBackgroundResource(R.drawable.btn);
                LinearLayout.LayoutParams lypt=new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
                lypt.gravity=Gravity.RIGHT;
                m_backButton.setLayoutParams(lypt);            
                m_backButton.setOnClickListener(new OnClickListener() {
                    public void onClick(View v) {
                        removeWebView();
                    }
                });
                //把webView加入到线性布局
                m_topLayout.addView(m_backButton);
                m_topLayout.addView(m_webView);                
                //再把线性布局加入到主布局
                m_webLayout.addView(m_topLayout);
            }
        });
    }
    //移除webView
    public void removeWebView() {              
        m_webLayout.removeView(m_topLayout);
        m_topLayout.destroyDrawingCache();
                
        m_topLayout.removeView(m_webView);
        m_webView.destroy();
                
        m_topLayout.removeView(m_backButton);
        m_backButton.destroyDrawingCache();
    }
    
    //重写return键
    public boolean onKeyDown(int keyCoder,KeyEvent event)
    {
        //如果网页能回退则后退，如果不能后退移除WebView
        if(m_webView.canGoBack() && keyCoder == KeyEvent.KEYCODE_BACK){
            m_webView.goBack();
        }else{
            removeWebView();
        }
        return false;      
    }

}
