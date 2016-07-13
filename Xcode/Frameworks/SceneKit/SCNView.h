//
//  SCNView.h
//
//  Copyright (c) 2012-2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 3
typedef NSString * SCNViewOption NS_STRING_ENUM;
#else
typedef NSString * SCNViewOption;
#endif

/*!
 @constant SCNViewOptionPreferredRenderingAPI Specifies the preferred rendering API to be used by the renderer.
 @discussion Pass it as the key in the options dictionary given to initWithFrame:options:. The value is a NSNumber wrapping a SCNRenderingAPI. You can also select the preferred rendering API directly from the SCNView inspector in InterfaceBuilder.
 */
FOUNDATION_EXTERN SCNViewOption const SCNViewOptionPreferredRenderingAPI NS_AVAILABLE(10_12, 10_0) __WATCHOS_UNAVAILABLE;

/*!
 @constant SCNViewOptionPreferredDevice Specifies the preferred metal device to be used by the renderer.
 @discussion The value is directly a id <MTLDevice>.
 */
FOUNDATION_EXTERN SCNViewOption const SCNViewOptionPreferredDevice NS_AVAILABLE(10_12, 10_0);

/*!
 @constant SCNViewOptionPreferLowPowerDevice Specifies if the renderer should prefer a low power metal device.
 @discussion The value is a NSNumber wrapping a BOOL. Defaults to NO.
 */
FOUNDATION_EXTERN SCNViewOption const SCNViewOptionPreferLowPowerDevice NS_AVAILABLE(10_12, 10_0);

FOUNDATION_EXTERN NSString * const SCNPreferredRenderingAPIKey NS_AVAILABLE(10_11, 9_0) __WATCHOS_UNAVAILABLE; // Please use SCNViewOption.preferredRenderingAPI instead.
FOUNDATION_EXTERN NSString * const SCNPreferredDeviceKey NS_AVAILABLE(10_11, 9_0);                             // Please use SCNViewOption.preferredDevice instead.
FOUNDATION_EXTERN NSString * const SCNPreferLowPowerDeviceKey NS_AVAILABLE(10_11, 9_0);                        // Please use SCNViewOption.preferLowPowerDevice instead.


/*!
 @class SCNView
 @abstract A SCNView is a subclass of NSView that can display a SCNScene
 */
__WATCHOS_PROHIBITED
@interface SCNView : UIView <SCNSceneRenderer, SCNTechniqueSupport>

/*!
 @method initWithFrame:options:
 @abstract 初始化并返回一个特定大小框架的已经被分配内存的SCNView
 @param 框架：框架矩形是为了创建视图
 @param 可选项是一个可选型字典。 具体看上面的 "View initialization options"。
 */
- (instancetype)initWithFrame:(CGRect)frame options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 @property scene
 @abstract 指定一个场景为接受者
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @property allowsCameraControl
 @abstract 一个可以设置用户是否可以操纵一个视图的当前视图的点的布尔值
 @discussion  当设置为YES时，用户可以操纵当前视图的点通过鼠标或者触控板。通过这个动作不会被修改该场景的图像和已经存在的摄像机。该属性默认值为NO。
 注意：这个属性的初始目的是辅助你debug。你可以定制你的摄像机控制器来适应你的应用
 这个内置摄像头控制器可以让你:
 - 滑动一个手指来围绕着场景旋转摄像机。
 - 滑动两个手指在X，Y平面上滑动摄像机。
 - 垂直滑动三个手指移动摄像机向前/向后。
 - 双击切换到下一个场景里的摄像机。
 - 旋转两根手指来转动摄像机（在Z轴上旋转）。
 - 捏来缩小/放大（改变摄像头的视角）。
 */
@property(nonatomic) BOOL allowsCameraControl;

/*!
 @property snapshot
 @abstract 绘制当前视图的内容并返回一个新的图像对象。
 @discussion 这个方法是线程安全的并且可以随时调用。
 */
- (UIImage *)snapshot NS_AVAILABLE(10_10, 8_0);

/*!
 @functiongroup Actions
 */
/*!
 @method play:
 @abstract 这个动作方法开始在当前位置播放场景。
 @param 发送者（想一个按钮或者菜单项目）发送信息来开始播放场景
 @discussion 当场景已经在播放的时候这个方法不会做任何事
 */
- (IBAction)play:(nullable id)sender;

/*!
 @method pause:
 @abstract 这个动作方法暂停当前场景的回放
 @param 发送者（想一个按钮或者菜单项目）发送信息来暂停场景的回放
 @discussion 当场景已经被暂停的时候这个方法不会做任何事
 */
- (IBAction)pause:(nullable id)sender;

/*!
 @method stop:
 @abstract 这个动作方法停止场景的回放并且重置当前的时间到开始场景的时间
 @param 发送者（想一个按钮或者菜单项目）发送信息来停止播放场景
 */
- (IBAction)stop:(nullable id)sender;
/*!
 @property preferredFramesPerSecond
 @abstract 视图重绘的速率 
 @discussion 当你的应用设置了它的重绘速率，视图会选择一个尽可能接近视图显示功能的重绘速率。选择的真实帧数通常是一个屏幕最大刷新速率的因子以提供一个一致的帧数。例如，如果屏幕的最大刷新速率是60帧每秒，这同时也是视图可以被设置的最高帧数。然而如果你没有请求一个更低的帧数，它可能会选择30，20，15或者其他一个因数作为他的真实的速率。你的应用应该选择一个可以始终保持的帧数。
 默认值是0，这意味着显示链接会随着显示硬件的频率而改变。
 */
@property(nonatomic) NSInteger preferredFramesPerSecond NS_AVAILABLE(10_12, 8_0);

/*!
 @property eaglContext
 @abstract 设置与接收者有关的EAGL（AGL的嵌入式版本）内容
 @discussion 此属性返回值为nil并且在当前API为Metal时没有效果。
 */
@property(nonatomic, retain, nullable) EAGLContext *eaglContext;

/*!
 @property antialiasingMode
 @abstract 默认值在OSX（mac OS）上为SCNAntialiasingModeMultisampling4X（4倍多重采样），在iOS上默认为SCNAntialiasingModeNone（无抗锯齿）。
 */
@property(nonatomic) SCNAntialiasingMode antialiasingMode NS_AVAILABLE(10_10, 8_0);


@end

NS_ASSUME_NONNULL_END
