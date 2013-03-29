/**
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

#import <UIKit/UIKit.h>
#import <Cordova/CDVViewController.h>

#import "MoodstocksPlugin.h"
#import "MSHandler.h"

#import "MSScannerSession.h"
#import "MSResult.h"

@class MoodstocksPlugin;
@class MSHandler;

@interface MSScannerController : UIViewController
#if MS_SDK_REQUIREMENTS
<MSScannerSessionDelegate>
#endif
{
    MSScannerSession *_scannerSession;
    UIView *_videoPreview;
    UIToolbar *_toolbar;
    UIBarButtonItem *_barButton;
    NSInteger _scanOptions;

    MoodstocksPlugin *_plugin;
    UIWebView *_resultOverlay;
    UIColor *_originBGColor;
}

- (id)initWithHandler:(MSHandler *)handler scanOptions:(NSInteger)scanOptions plugin:(MoodstocksPlugin *)plugin;
- (void)pause;
- (void)resume;
- (void)dismissAction;

@property (nonatomic, retain) MSHandler *handler;
@property (nonatomic, retain) MSResult *result;

@end
