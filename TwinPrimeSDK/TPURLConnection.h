//
//  TPURLConnection.h
//
//  API to download an object addressed by a URL using TwinPrime acceleration
//
//  Copyright (c) 2013 Twin Prime Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class TPURLConnection;

@interface TPURLConnection : NSURLConnection
// Only methods listed below are supported on TPURLConnection
// or its instances.

// Create a new TPURLConnection object and initiate object download
//
- (id)initWithRequest:(NSURLRequest *)request delegate:(id <NSURLConnectionDataDelegate>)delegate;

/**
 * Create a new TPURLConnection and initiate object download, but do run accelerate.
 */
- (id)initWithRequest:(NSURLRequest *)request delegate:(id <NSURLConnectionDataDelegate>)delegate withAcceleration:(BOOL)acc;


/**
 * Warning: this API is deprecated and will be removed in the future
 * versions of the SDK.
 *
 * Create a new TPURLConnection and initiate object download, 
 * but also accelerate subsequent links that are downloaded due to 
 * this object (primarily in the context of a UIWebView).
 * 
 * @param[in] request - The URLRequest to be fetched
 * @param[in] delegate - The user defined delegate receiving the response to the request.
 * @param[in] acc - To Accelerate or not.
 * @param[in] accelerateChildren - Inspect HTML/Javascript to have subsquent objects go through TwinPrimeSDK with acceleration.
 * @return id - urlconnection handle.
 */
- (id)initWithRequest:(NSURLRequest *)request
             delegate:(id <NSURLConnectionDataDelegate>)delegate
     withAcceleration:(BOOL)acc
   accelerateChildren:(BOOL)accelerateChildren __deprecated_msg("deprecated API!");

@end
