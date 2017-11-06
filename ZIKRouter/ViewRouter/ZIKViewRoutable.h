//
//  ZIKViewRoutable.h
//  ZIKRouter
//
//  Created by zuik on 2017/8/21.
//  Copyright © 2017 zuik. All rights reserved.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <Foundation/Foundation.h>

/**
 Protocols inheriting from ZIKViewRoutable can be used to fetch view router with ZIKViewRouter.forView().
 @discussion
 ZIKViewRoutable is for:
 1. Let module declare routable protocol in header as the module's provided interface
 1. Checking declared protocol is correctly supported in it's view router
 
 It's safe to use objc protocols inheriting from ZIKViewRoutable with ZIKViewRouter.forView() and won't get nil. ZIKViewRouter will validate all ZIKViewRoutable protocols and registered protocols when app launchs and ZIKVIEWROUTER_CHECK is enbled. When ZIKVIEWROUTER_CHECK is disabled, the protocol doesn't need to inheriting from ZIKViewRoutable.
 */
@protocol ZIKViewRoutable

@end
