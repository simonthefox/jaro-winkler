//
//  ViewController.m
//  jaro-winkler
//
//  Created by Simon on 10/9/16.
//  Copyright © 2016 simonthefox. All rights reserved.
//

#import "ViewController.h"
#import "StringMetric.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UITextField *first;
@property (weak, nonatomic) IBOutlet UITextField *second;
@property (weak, nonatomic) IBOutlet UILabel *result;
- (IBAction)didEditField:(UITextField *)sender;

@end

@implementation ViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  // Do any additional setup after loading the view, typically from a nib.
  
  [self.first becomeFirstResponder];
}


- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}


- (IBAction)didEditField:(UITextField *)sender {
  float jaroWinklerMetric = jaro_winkler([self.first.text UTF8String], [self.second.text UTF8String]);
  
  dispatch_async(dispatch_get_main_queue(), ^{
    self.result.text = [NSString stringWithFormat:@"Jaro-Winkler similarity %f", jaroWinklerMetric];
  });
}
@end
