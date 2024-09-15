#include "utils.h"

#import <Foundation/Foundation.h>
#include <filesystem>

std::filesystem::path DamathZero::Utils::resourcePath()
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    std::filesystem::path rpath;
    NSBundle*             bundle = [NSBundle mainBundle];

    if (bundle == nil)
    {
#ifdef DEBUG
        NSLog(@"bundle is nil... thus no resources path can be found.");
#endif
    }
    else
    {
        NSString* path = [bundle resourcePath];
        rpath          = [path UTF8String] + std::string("/");
    }

    [pool drain];

    return rpath;
}
