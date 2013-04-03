/*
 * Copyright (c) 2013 Moodstocks SAS
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

package com.moodstocks.phonegap.demo;

import android.content.Intent;
import android.os.Bundle;
import org.apache.cordova.*;
import org.apache.cordova.api.CordovaPlugin;

import com.moodstocks.phonegap.plugin.MoodstocksWebView;

public class Demo extends DroidGap {
	private boolean scanActivityStarted = false;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        super.loadUrl("file:///android_asset/www/index.html");
    }
    
    @Override
    public void init() {
    	MoodstocksWebView webView = new MoodstocksWebView(Demo.this);
        CordovaWebViewClient webViewClient;
        
        if(android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.HONEYCOMB) {
            webViewClient = new CordovaWebViewClient(this, webView);
        }
        else {
            webViewClient = new IceCreamCordovaWebViewClient(this, webView);
        }
        
        this.init(webView, webViewClient, new CordovaChromeClient(this, webView));
    }
    
    @Override
    public void onPause() {
    	super.onPause();
    	
    	// Remove the web view from the root view when we launch the Moodstocks scanner
    	if (scanActivityStarted) {
    		super.root.removeView(super.appView);
    	}
    }
    
	@Override
    public void onResume() {
    	super.onResume();
    	
    	// Reset the web view to root container when we dismiss the Moodstocks scanner 
    	if (scanActivityStarted) {
    		super.root.addView(super.appView);
    		scanActivityStarted = false;
    	}
    }
    
    @Override
    public void startActivityForResult(CordovaPlugin command, Intent intent, int requestCode) {
    	// If the intent indicate the upcoming activity is a Moodtsocks scan activity
    	// We will launch the activity and keep the js/native code running on the background
    	if(intent.getExtras().getString("activity").equals("MoodstocksScanActivity"))  {
    		scanActivityStarted = true;
    		this.startActivityForResult(intent, requestCode);
    	}
    	else {
    		super.startActivityForResult(command, intent, requestCode);
    	}
    }
}