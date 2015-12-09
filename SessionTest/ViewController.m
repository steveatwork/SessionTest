//
//  ViewController.m
//  SessionTest
//
//  Created by Steve Wilburn on 12/7/15.
//  Copyright © 2015 Steve Wilburn. All rights reserved.
//

#import "ViewController.h"
#import "TwinPrimeSDK/TwinPrimeSDK.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UISegmentedControl *SessionSelect;
@property (weak, nonatomic) IBOutlet UITextField *ToGet;
@property NSURLSession *SessionOne;
@property NSURLSession *SessionTwo;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    NSURLSessionConfiguration *cfg = [NSURLSessionConfiguration
                                      defaultSessionConfiguration];
    cfg = [TwinPrimeSDK defaultSessionConfiguration];
    self.SessionOne = [NSURLSession sessionWithConfiguration:cfg];
    
    self.SessionTwo = [NSURLSession sessionWithConfiguration:cfg];
}

- (IBAction)Fetch:(UIButton *)sender {
    NSURL *url = [NSURL URLWithString: self.ToGet.text];
    if (!url){
        return;
    } else {
        if ([self.SessionSelect selectedSegmentIndex] == 0){
            [[self.SessionOne dataTaskWithURL: url
                completionHandler:^(NSData *data,
                                    NSURLResponse *response,
                                    NSError *error) {
                    NSLog([NSString stringWithFormat: @"Length of content received: %lu", response.expectedContentLength]);
                }] resume];
            NSLog( @"first session");
        } else if ([self.SessionSelect selectedSegmentIndex] == 1) {
            [[self.SessionTwo dataTaskWithURL: url
                completionHandler:^(NSData *data,
                                    NSURLResponse *response,
                                    NSError *error) {
                    NSLog([NSString stringWithFormat: @"Length of content received: %lu", response.expectedContentLength]);
                }] resume];
            NSLog( @"second session");
        } else {
            NSURLResponse *response = nil;
            NSError *error = nil;
            NSData *data = [NSURLConnection sendSynchronousRequest: [NSURLRequest requestWithURL: url]
                                                 returningResponse: &response
                                                             error: &error];
            NSLog([NSString stringWithFormat: @"Length of content received: %lu", response.expectedContentLength]);
        }
    }
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
