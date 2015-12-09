//
//  TwinPrimeSDK.h
//
//
//  Copyright (c) 2013 Twin Prime Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TPURLConnection.h"

extern NSString* kTPSDKBuildRev;
extern NSString* kTPSDKBuildDate;

/**
 * The TwinPrimeSDK, when initialized with initWithKey:options takes an
 * NSDictionary as the second parameter.
 *
 * The keys for this dictionary are typed TwinPrimeSDKOtionKey and are listed
 * below.  Each key will have it's own value expectations, which is documented
 * along with the individual key.
 */
typedef NSString* TwinPrimeSDKOptionKey;
typedef NSObject* TwinPrimeSDKOptionValue;

/**
 * Enable HTTP intercept
 *
 * Install HTTP protocol handler.  Directing all HTTP traffic
 * through Twin Prime accelerator.
 * "enable" - Will enable all HTTP NSURLRequests to be accelerated through Twin Prime's Accelerators.
 */
extern TwinPrimeSDKOptionKey kTPOptionHTTPIntercept;

/**
 * Enable limited HTTP intercept for prespecified URLs
 *
 * Install HTTP protocolo handler to direct only specific HTTP URLs
 * through the Twin Prime accelerator.
 * "enable" - Will enable specific URLs to be accelerated. Such URLs may
        be specified by using the [TwinPrimeSDK addURLToIntercept:] API
 */
extern TwinPrimeSDKOptionKey kTPOptionLimitedHTTPIntercept;

/**
 * Specify existing NSProtocol handlers.
 *
 * A string name of the existing handler class or an array of names.  Given the
 * class names of existing handlers, we query each of those NSProtocol handlers
 * in the given order. We allow the first one that can handle the request, to
 * take over.
 */
extern TwinPrimeSDKOptionKey kTPOptionProtocolHandlers;

/**
 * Honor System Proxy settings.
 *
 * Twin Prime's service is itself an accelerating proxy, and as such overrides
 * proxy settings for accelerated requests.  As a matter of debugging, you can
 * set this option to "enable" to have accelerated requests also flow through
 * the system provided proxy.  This option is disabled by default as it likely
 * negitively impact performance.
 */
extern TwinPrimeSDKOptionKey kTPOptionHonorSystemProxySettings;

/**
 * Specify a whitelist to accelerate only those URLs which match the given
 * patterns.
 */
extern TwinPrimeSDKOptionKey kTPOptionURLWhiteList;

/**
 * Specify a blacklist to acclerate all but those URLs which match the given
 * patterns. If used with the whitelist option, only URLs that match a 
 * whitelist pattern but do not match a blacklist pattern will be accelerated.
 */
extern TwinPrimeSDKOptionKey kTPOptionURLBlackList;

/**
 * Specify a string identifying an experiment held by an Analytics SDK.
 * In a typical A/B test, the acceleration is applied over a certain set
 * of users for a certain set of time. The "Experiment ID" is the glue that
 * aligns the TwinPrime SDK's behavior with the Analytics' experiment.
 * By default, the TwinPrime SDK accelerates any non-null Experiment ID,
 * and bypasses any null one.
 */
extern TwinPrimeSDKOptionKey kTPOptionExperimentID;

typedef NSInteger TPLogLevel;

/*
 * Logging levels. Normal levels are 0..3, where 0 means no logging whatsoever,
 * while 3 means very verbose logging. Most of the users are expected to run with
 * level 0 or 1. Levels 2 or 3 will only be useful when working with Twin Prime, Inc.
 * on debugging potential issues. Generally anything >= 1 will have some implementation
 * details which may change at any time without prior warning.
 */
extern TPLogLevel kTPLogLevel0; // no logging
extern TPLogLevel kTPLogLevel1; // default logging level
extern TPLogLevel kTPLogLevel2; // verbose logging
extern TPLogLevel kTPLogLevel3; // very verbose logging

@interface TPLogMessage : NSObject

/**
 * level
 *
 * the severity of the message.
 */
@property (readonly) TPLogLevel level;

/**
 * message
 *
 * Logged infomation.
 */
@property (readonly) NSString* message;
@end


@protocol TPLogHandler <NSObject>

/**
 * Log messages from TwinPrime SDK library are logged through this interface.
 *
 */
-(void) logMessage:(TPLogMessage*)log;

@end

@interface TwinPrimeSDK : NSObject

/**
 * Initialize the library as soon as app launches (e.g.
 * in the appropriate app delegate callback.
 *
 * @param[in] key An API key that authorizes the app to use Twin Prime service.
 */
+ (void)initWithKey:(NSString *)key;

/**
 * Initialize the library with the given key and options dictionary.
 * 
 * @param[in] key An API key that authorizes the app to use Twin Prime service.
 * @param[in] options dictionary with TwinPrimeSDKOptionKey keys defining
 * run-time library customization.
 */
+ (void)initWithKey:(NSString *)key options:(NSDictionary*)options;

/**
 * Used to disable/enable acceleration inside the app after the library has initialized.
 * Calling this method before library initialization has no effect.
 *
 * @param[in] Globally enable/disable Acceleration.
 */
+ (void)setAccelerate:(BOOL)on;

/**
 * Current global library state, whether or not requests will be accelerated.
 *
 * @return Global Acceleration state of the library.
 */
+ (BOOL)Accelerate;

/**
 * Can requests be accelerated taking into account [TwinPrimeSDK Accerate], the connection to the acelerater, and the
 * policies received by the accelerater.
 *
 * @return YES if it's possible for requests to be accelerated.
 */
+ (BOOL) canAccelerate;

/**
 * Customers can create applcation-level events all network requests are tagged with this event name
 * and shown together in the client dashboard.
 *
 * @param[in] eventName - name of the application event.
 */
+ (void)startLoggingEvent:(NSString *)eventName;

/**
 * Marks the end of the current application-level event.
 */
+ (void)endLoggingEvent;

/**
 * setLogHandler
 *
 * Sets the log message handler to user defined handler.  Default handler will
 * log at INFO level via NSLog.  See setLogLevel to allow selected log messages.
 *
 * To prevent logs from appearing on the console completely, either invoke
 * setLogHandler with a nil parameter or
 * invoke setLogHandler with a custom handler object that consumes the logs.
 */
+ (void) setLogHandler:(NSObject<TPLogHandler>*)handler;

/**
 * setLogLevel
 *
 * Sets the log message level.  Default level is kTPLogLevel_info.
 */
+ (void) setLogLevel:(TPLogLevel)level;

/**
 * SummaryStatistics
 *
 * Gets summary statistics about the library.
 */
+ (NSDictionary*) SummaryStatistics;

/**
 *
 * setLongitude:Latitude:
 *
 * Set the current location. This information helps further improve and
 * specialize optimizations. It is also used to provide better visualization of
 * network data on the customer dashboard.
 */
+ (void)setLongitude:(float)lng Latitude:(float)lat;

/**
 *
 * sessionConfigurationWithConfiguration:
 *
 * Get an accelerated URL Session Configuration based on the given URL Session
 * Configuration.  Note that acceleration doesn't work with background url
 * session configurations.  The sdk also needs to be initialized with HTTP
 * and/or HTTPS intercept options "enable".
 */
+ (NSURLSessionConfiguration*) sessionConfigurationWithConfiguration:
    (NSURLSessionConfiguration *)sessionConfig NS_AVAILABLE_IOS(7_0);

/**
 *
 * sessionConfiguration:
 *
 * Get an accelerated URL Session Configuration based on
 * +[NSURLSessionConfiguration defaultSessionConfiguration].  Note that
 * acceleration doesn't work with background url session configurations.  The
 * sdk also needs to be initialized with HTTP and/or HTTPS intercept options
 * "enable".
 */
+ (NSURLSessionConfiguration*) defaultSessionConfiguration
    NS_AVAILABLE_IOS(7_0);

@end
