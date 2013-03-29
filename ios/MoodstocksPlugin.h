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

#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>

#import "MSScannerController.h"

@class MSScannerController;

@interface MoodstocksPlugin : CDVPlugin

@property (nonatomic, retain)MSScannerController *scanner;

- (void)open:(CDVInvokedUrlCommand *)command;
- (void)sync:(CDVInvokedUrlCommand *)command;
- (void)scan:(CDVInvokedUrlCommand *)command;
- (void)pause:(CDVInvokedUrlCommand *)command;
- (void)resume:(CDVInvokedUrlCommand *)command;
- (void)dismiss:(CDVInvokedUrlCommand *)command;

- (void)updateScanResult:(NSString *)value
                  format:(int)format
                callback:(NSString *)callback;

- (void)dismissScanner:(NSString *)callback;

- (void)returnSyncStatus:(NSString *)message
                  status:(int)status
                progress:(int)progress
                callback:(NSString *)callback
      shouldKeepCallback:(BOOL)shouldKeepCallback;

@end