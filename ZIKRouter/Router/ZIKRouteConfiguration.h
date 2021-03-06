//
//  ZIKRouteConfiguration.h
//  ZIKRouter
//
//  Created by zuik on 2017/10/13.
//  Copyright © 2017 zuik. All rights reserved.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ZIKRouterState) {
    ZIKRouterStateNotRoute,
    ZIKRouterStateRouting,
    ZIKRouterStateRouted,
    ZIKRouterStateRemoving,
    ZIKRouterStateRemoved
};

///Route action.
typedef NSString *ZIKRouteAction NS_EXTENSIBLE_STRING_ENUM;

///Initialize router with configuration. See ZIKViewRouteErrorInvalidConfiguration, ZIKViewRouteErrorUnsupportType, ZIKViewRouteErrorInvalidSource, ZIKViewRouteErrorInvalidContainer.
extern ZIKRouteAction const ZIKRouteActionInit;

///Perform route. See ZIKViewRouteErrorActionFailed, ZIKServiceRouteErrorActionFailed, ZIKViewRouteErrorOverRoute, ZIKViewRouteErrorUnbalancedTransition, ZIKViewRouteErrorSegueNotPerformed, ZIKViewRouteErrorInfiniteRecursion, ZIKServiceRouteErrorInfiniteRecursion, ZIKServiceRouteErrorServiceUnavailable.
extern ZIKRouteAction const ZIKRouteActionPerformRoute;

///Remove route. See ZIKViewRouteErrorActionFailed, ZIKServiceRouteErrorActionFailed.
extern ZIKRouteAction const ZIKRouteActionRemoveRoute;

typedef void(^ZIKRouteErrorHandler)(ZIKRouteAction routeAction, NSError *error);
typedef void(^ZIKRouteStateNotifier)(ZIKRouterState oldState, ZIKRouterState newState);

///Configuration for destination module. You can use a subclass to add complex dependencies for destination. The subclass must conforms to NSCopying, because the configuration will be copied.
@interface ZIKRouteConfiguration : NSObject <NSCopying>

/**
 Error handler for router's provider.
 @note
 Use weakSelf in errorHandler to avoid retain cycle.
 */
@property (nonatomic, copy, nullable) ZIKRouteErrorHandler errorHandler;

/**
 Success handler for router's provider.
 @note
 Use weakSelf in successHandler to avoid retain cycle.
 */
@property (nonatomic, copy, nullable) void(^successHandler)(void);

/**
 Monitor state
 @note
 Use weakSelf in stateNotifier to avoid retain cycle.
 */
@property (nonatomic, copy, nullable) ZIKRouteStateNotifier stateNotifier;

///Initialize properties in currrent configuration class from another configuration, the other configuration must be same class or subclass of self. This is a convenient method to initialize a copy from an existing configuration in -copyWithZone:.
- (BOOL)setPropertiesFromConfiguration:(ZIKRouteConfiguration *)configuration;

@end

@interface ZIKPerformRouteConfiguration : ZIKRouteConfiguration <NSCopying>

/**
 Prepare for performRoute, and config other dependency for destination here. Subclass can offer more specific info.
 
 @note
 Use weakSelf in prepareDestination to avoid retain cycle.
 */
@property (nonatomic, copy, nullable) void(^prepareDestination)(id destination);

/**
 Completion for performRoute. Default implemenation will call routeCompletion synchronously.
 
 @note
 Use weakSelf in routeCompletion to avoid retain cycle.
 */
@property (nonatomic, copy, nullable) void(^routeCompletion)(id destination);
@end

@interface ZIKRemoveRouteConfiguration : ZIKRouteConfiguration <NSCopying>

/**
 Prepare for removeRoute. Subclass can offer more specific info.
 
 @note
 Use weakSelf in prepareDestination to avoid retain cycle.
 */
@property (nonatomic, copy, nullable) void(^prepareDestination)(id destination);

@end

NS_ASSUME_NONNULL_END
