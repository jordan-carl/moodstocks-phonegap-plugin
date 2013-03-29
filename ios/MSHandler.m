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

#import "MSHandler.h"

#import "MSDebug.h"

@implementation MSHandler

@synthesize plugin = _plugin;
@synthesize callback = _callback;

- (id)initWithPlugin:(MoodstocksPlugin *)plugin callback:(NSString *)callback {
    self = [super init];

    if (self) {
        self.plugin = plugin;
        self.callback = callback;
    }

    return self;
}

- (void)dealloc {
    [super dealloc];

    self.plugin = nil;
    self.callback = nil;
}

- (void)sync {
#if MS_SDK_REQUIREMENTS
    MSScanner *scanner = [MSScanner sharedInstance];
    if ([scanner isSyncing]) return;
    // Retain until the sync is finished (see below)
    [self retain];
    [scanner syncWithDelegate:self];
#endif
}

#pragma mark - Sync Handler

- (void)scannerWillSync:(MSScanner *)scanner {
    [self.plugin returnSyncStatus:@""
                           status:1
                         progress:0
                         callback:self.callback
               shouldKeepCallback:YES];
}

- (void)didSyncWithProgress:(NSNumber *)current total:(NSNumber *)total {
    int percent = 100 * [current floatValue] / [total floatValue];
    [self.plugin returnSyncStatus:@""
                           status:2
                         progress:percent
                         callback:self.callback
               shouldKeepCallback:YES];
}

- (void)scannerDidSync:(MSScanner *)scanner {
    MSDLog(@" [MOODSTOCKS SDK] SYNC SUCCEEDED (%d IMAGE(S))", [scanner count:nil]);
    [self.plugin returnSyncStatus:@""
                           status:3
                         progress:100
                         callback:self.callback
               shouldKeepCallback:NO];

    [self release];
}

- (void)scanner:(MSScanner *)scanner failedToSyncWithError:(NSError *)error {
    ms_errcode ecode = [error code];
    if (ecode != MS_BUSY) {
        MSDLog(@" [MOODSTOCKS SDK] SYNC ERROR: %@", MSErrMsg(ecode));
        [self.plugin returnSyncStatus:MSErrMsg(ecode)
                               status:0
                             progress:0
                             callback:self.callback
                   shouldKeepCallback:YES];
    }

    [self release];
}

#pragma mark - Scanner Session Handler

- (void)scanResultFound:(NSString *)value format:(int)format {
    [self.plugin updateScanResult:value format:format callback:self.callback];
}

- (void)scanDismissed {
    [self.plugin dismissScanner:self.callback];
}

@end
